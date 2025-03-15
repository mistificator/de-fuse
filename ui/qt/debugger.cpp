#include "debugger.hpp"
#include "ui_debugger.hpp"

#include <QMenu>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QDebug>

extern "C"
{
    #include "fuse.h"
    #include "debugger/breakpoint.h"
    #include "z80/z80.h"
    #include "z80/z80_macros.h"
    #include "event.h"
    #include "spectrum.h"
    #include "machine.h"
    #include "peripherals/ula.h"
    #include "peripherals/scld.h"
    #include "peripherals/ide/zxcf.h"
    #include "settings.h"
}

/* The columns used in the breakpoints pane */

enum {
    BREAKPOINTS_COLUMN_ID,
    BREAKPOINTS_COLUMN_TYPE,
    BREAKPOINTS_COLUMN_VALUE,
    BREAKPOINTS_COLUMN_IGNORE,
    BREAKPOINTS_COLUMN_LIFE,
    BREAKPOINTS_COLUMN_CONDITION,

    BREAKPOINTS_COLUMN_COUNT
};

/* The columns used in the disassembly pane */

enum {
    DISASSEMBLY_COLUMN_PC,
    DISASSEMBLY_COLUMN_BREAKPOINT,
    DISASSEMBLY_COLUMN_ADDRESS,
    DISASSEMBLY_COLUMN_INSTRUCTION,

    DISASSEMBLY_COLUMN_COUNT
};

/* The columns used in the stack pane */

enum {
    STACK_COLUMN_ADDRESS,
    STACK_COLUMN_VALUE_TEXT,
    STACK_COLUMN_VALUE_INT,

    STACK_COLUMN_COUNT
};

/* The columns used in the events pane */

enum {
    EVENTS_COLUMN_TIME,
    EVENTS_COLUMN_TYPE,

    EVENTS_COLUMN_COUNT
};

static QString strhex(int address, int width)
{
    return QString::number(address, 16).rightJustified(width, '0').toUpper();
}


DeFuseDebugger::DeFuseDebugger(QWidget *parent) :
    QDialog(parent, Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::WindowMinMaxButtonsHint),
    ui(new Ui::DeFuseDebugger)
{
    ui->setupUi(this);

    installEventFilter(this);
    ui->tbDisassembly->viewport()->installEventFilter(this);

    ui->tbBreakpoints->resizeColumnsToContents();   ui->tbBreakpoints->setRowCount(0);
    ui->tbDisassembly->resizeColumnsToContents();   ui->tbDisassembly->setRowCount(0);
    ui->tbEvents->resizeColumnsToContents();        ui->tbEvents->setRowCount(0);
    ui->tbFlags->resizeColumnsToContents();         //ui->tbFlags->setRowCount(0);
    ui->tbMemory->resizeColumnsToContents();        ui->tbMemory->setRowCount(0);
    ui->tbRegisters->resizeColumnsToContents();     //ui->tbRegisters->setRowCount(0);
    ui->tbStack->resizeColumnsToContents();         ui->tbStack->setRowCount(0);
    ui->tbStates->resizeColumnsToContents();        //ui->tbStates->setRowCount(0);
    ui->tbStates2->resizeColumnsToContents();       //ui->tbStates2->setRowCount(0);

    connect(ui->actionBreakpoints,  &QAction::toggled, this, [&](bool state) { ui->gbBreakpoints->setVisible(state); });
    connect(ui->actionDisassembly,  &QAction::toggled, this, [&](bool state) { ui->gbDisassembly->setVisible(state); });
    connect(ui->actionEvents,       &QAction::toggled, this, [&](bool state) { ui->gbEvents->setVisible(state); });
    connect(ui->actionMemory_Map,   &QAction::toggled, this, [&](bool state) { ui->gbMemoryMap->setVisible(state); });
    connect(ui->actionRegisters,    &QAction::toggled, this, [&](bool state) { ui->gbRegisters->setVisible(state); });
    connect(ui->actionStack,        &QAction::toggled, this, [&](bool state) { ui->gbStack->setVisible(state); });
}

DeFuseDebugger::~DeFuseDebugger()
{
    delete ui;
}

void DeFuseDebugger::on_bEvaluate_clicked()
{
    debugger_command_evaluate(ui->leEvaluate->text().toLocal8Bit());
    ui->leEvaluate->setText("");
    updateBreakpoints();
}

void DeFuseDebugger::on_leEvaluate_returnPressed()
{
    ui->bEvaluate->click();
}

void DeFuseDebugger::on_bStep_clicked()
{
    debugger_step();
}

void DeFuseDebugger::on_bContinue_clicked()
{
    debugger_run();
}

void DeFuseDebugger::on_bBreak_clicked()
{
    debugger_step();
}

void DeFuseDebugger::on_actionClose_triggered()
{
    close();
}

void DeFuseDebugger::on_bClose_clicked()
{
    ui->actionClose->trigger();
}

void DeFuseDebugger::showEvent(QShowEvent *)
{
    updateAll();
    QMetaObject::invokeMethod(this, &DeFuseDebugger::enterDebugging, Qt::QueuedConnection);
}

void DeFuseDebugger::closeEvent(QCloseEvent *)
{
    exitDebugging();
} 

void DeFuseDebugger::resizeEvent(QResizeEvent *)
{
    updateDisassembly();
}

void DeFuseDebugger::scrollDisassemblyByOffset(int offset)
{
    if (ui->tbDisassembly->currentRow() + offset >= 0 &&
        ui->tbDisassembly->currentRow() + offset < ui->tbDisassembly->rowCount())
    {
        return;
    }

    size_t length = 0;
    int address = ui->scDisassembly->value();
    if (offset > 0)
    {
        while (offset--)
        {
            disassembleAt(address, &length);
            address += length;
        }
    }
    else
    if (offset < 0)
    {
        auto fwd_instr = disassembleAt(address, &length);
        while (offset++)
        {
            auto instr = fwd_instr;
            auto prev_address = address;
            while (address-- >= 0 && instr == fwd_instr)
            {
                instr = disassembleAt(address, &length);
                if (address + length == prev_address)
                {
                    break;
                }
            }
            fwd_instr = instr;
        }
    }
    setPC(address, false);
}

bool DeFuseDebugger::eventFilter(QObject * o, QEvent * e)
{
    if (o == ui->tbDisassembly->viewport())
    {
        switch(e->type())
        {
        case QEvent::Wheel:
            qApp->postEvent(ui->scDisassembly, new QWheelEvent(* dynamic_cast<QWheelEvent *>(e)));
        break;
        default:
            break;
        }
    }
    if (o == this)
    {
        switch(e->type())
        {
        case QEvent::KeyRelease:
            if (ui->tbDisassembly->viewport()->hasFocus())
            {
                auto ke = dynamic_cast<QKeyEvent *>(e);
                int offset = 0;
                switch (ke->key())
                {
                case Qt::Key_Up: --offset; break;
                case Qt::Key_PageUp: offset -= 10; break;
                case Qt::Key_Down: ++offset; break;
                case Qt::Key_PageDown: offset += 10; break;
                }

                scrollDisassemblyByOffset(offset);
            }
            break;
        default:
            break;
        }

    }
    return QDialog::eventFilter(o, e);
}

// command, foreground, background
const std::array<std::tuple<QByteArray, QColor, QColor>, 15> disassembly_color_table = 
{{
  {"JP",   QColor(0x80, 0x40, 0),   Qt::transparent},
  {"JR",   QColor(0xCC, 0x66, 0),   Qt::transparent},
  {"CALL", Qt::blue,                Qt::transparent},
  {"DJNZ", Qt::darkCyan,            Qt::transparent},
  {"NOP",  Qt::lightGray,           Qt::transparent},
  {"RET",  Qt::green,               Qt::transparent},
  {"CP ",  Qt::darkMagenta,         Qt::transparent},
  {"RST",  QColor(0xFF, 0x80, 0),   Qt::black},
  {"OUT",  Qt::green,               Qt::black},
  {"IN ",  Qt::yellow,              Qt::black},
  {"HALT", QColor(0xFF, 0, 0x80),   Qt::black},
  {"DI",   Qt::white,               QColor(0xFF, 0, 0x80)},
  {"EI",   Qt::white,               QColor(0xFF, 0, 0x80)},
  {"EX",   Qt::white,               Qt::darkBlue},
  {"IM",   Qt::white,               Qt::darkGreen}
}};

void DeFuseDebugger::colorizeDisassembly(int row, const QByteArray & instr)
{
    if (!ui->actionColorize_disassembly->isChecked()) 
    {
        return;
    }
    for (auto c: disassembly_color_table)
    {
        if (!instr.startsWith(std::get<QByteArray>(c)))
        {
            continue;
        }
        for (int col = 0; col < ui->tbDisassembly->columnCount(); ++col)
        {
            if (auto item = ui->tbDisassembly->item(row, col))
            {
                QColor fg = std::get<1>(c);
                if (fg != Qt::transparent)
                {
                    item->setForeground(fg);
                }
                QColor bg = std::get<2>(c);
                if (bg != Qt::transparent)
                {
                    item->setBackground(bg);
                }     
            }
        }
        break;               
    }
}

void DeFuseDebugger::on_tbDisassembly_customContextMenuRequested(const QPoint & pt)
{
    auto click_item = ui->tbDisassembly->itemAt(pt);
    if (!click_item)
    {
        return;
    }
    QMenu menu;
    connect(menu.addAction("Toggle breakpoint"), &QAction::triggered, this, [this, click_item]()
    {
        auto brk_num = ui->tbDisassembly->item(click_item->row(), DISASSEMBLY_COLUMN_BREAKPOINT)->text();
        if (brk_num.isEmpty())
        {
            auto addr = ui->tbDisassembly->item(click_item->row(), DISASSEMBLY_COLUMN_ADDRESS)->text();
            debugger_breakpoint_add_address(
                DEBUGGER_BREAKPOINT_TYPE_EXECUTE,
                memory_source_any,
                0,
                addr.toUInt(nullptr, 16),
                0,
                DEBUGGER_BREAKPOINT_LIFE_PERMANENT,
                nullptr
                );
        }
        else
        {
            debugger_command_evaluate( QString("del %1").arg(brk_num).toUtf8() );
        }
        updateBreakpoints();
        updateDisassembly();
    });
    connect(menu.addAction("Go to offset in instruction"), &QAction::triggered, this, [&]()
    {
        QRegularExpression rx("[\\,\\(\\s)][0-9a-fA-F]{4}");
        auto i = rx.globalMatch(ui->tbDisassembly->item(click_item->row(), DISASSEMBLY_COLUMN_INSTRUCTION)->text());
        while (i.hasNext())
        {
            bool ok;
            auto addr = i.next().captured().mid(1).toUInt(& ok, 16);
            if (ok && addr <= 0xFFFF)
            {
                setPC(addr);
                break;
            }
        }
    });
    connect(menu.addAction("Go to current program counter (PC)"), &QAction::triggered, this, [this]()
    {
        setPC(PC);
    });
    menu.exec(ui->tbDisassembly->viewport()->mapToGlobal(pt));
}

void DeFuseDebugger::setPC(libspectrum_word address, bool move_selection)
{
    ui->scDisassembly->setValue(address);
    if (move_selection)
    {
        ui->tbDisassembly->selectRow(0);
    }
}

QByteArray DeFuseDebugger::disassembleAt(libspectrum_word address, size_t * length)
{
    QByteArray instr(128, 0);
    size_t length_ = 0;
    debugger_disassemble(instr.data(), instr.size(), &length_, address);
    if (length)
    {
        * length = length_;
    }
    return instr;
}

void DeFuseDebugger::updateDisassembly()
{
    ui->tbDisassembly->setRowCount(ui->tbDisassembly->height() / ui->tbDisassembly->verticalHeader()->defaultSectionSize());
    for( int i = 0; i < ui->tbDisassembly->rowCount() ; i++ ) 
    {
        for (int j = 0; j < ui->tbDisassembly->columnCount(); j++)
        {
            ui->tbDisassembly->setItem(i, j, new QTableWidgetItem());
        }
    }
    libspectrum_word address = ui->scDisassembly->value();
    for( int i = 0; i < ui->tbDisassembly->rowCount(); i++ )
    {
        if (address == PC)
        {
            ui->tbDisassembly->item(i, DISASSEMBLY_COLUMN_PC)->setText("->");
        }
        for(GSList * ptr = debugger_breakpoints; ptr; ptr = ptr->next ) 
        {
            debugger_breakpoint *bp = reinterpret_cast<debugger_breakpoint *>(ptr->data);

            switch( bp->type ) 
            {

            case DEBUGGER_BREAKPOINT_TYPE_EXECUTE:
            case DEBUGGER_BREAKPOINT_TYPE_READ:
            case DEBUGGER_BREAKPOINT_TYPE_WRITE:
                if ( bp->value.address.offset == address ) 
                {
                    ui->tbDisassembly->item(i, DISASSEMBLY_COLUMN_BREAKPOINT)->setText(QString::number(bp->id));
                }
                break;
            default:
                break;
            }
        }
        ui->tbDisassembly->item(i, DISASSEMBLY_COLUMN_ADDRESS)->setText(strhex(address, 4));

        size_t length = 0;
        auto instr = disassembleAt(address, &length);
        ui->tbDisassembly->item(i, DISASSEMBLY_COLUMN_INSTRUCTION)->setText(instr);
        colorizeDisassembly(i, instr);

        address += length;
    }
}

void DeFuseDebugger::on_scDisassembly_valueChanged(int)
{
    updateDisassembly();
}

void DeFuseDebugger::on_actionColorize_disassembly_toggled(bool)
{
    updateDisassembly();
}

void DeFuseDebugger::updateStack()
{
    ui->tbStack->setRowCount(ui->tbStack->height() / ui->tbStack->verticalHeader()->defaultSectionSize());
    for( int i = 0; i < ui->tbStack->rowCount() ; i++ )
    {
        for (int j = 0; j < ui->tbStack->columnCount(); j++)
        {
            ui->tbStack->setItem(i, j, new QTableWidgetItem());
        }
    }
    for( int i = 0, address = SP + 38; i < ui->tbStack->rowCount(); i++, address -= 2 )
    {
        libspectrum_word contents = readbyte_internal( address ) +
                                    0x100 * readbyte_internal( address + 1 );
        ui->tbStack->item(i, STACK_COLUMN_ADDRESS)->setText(strhex(address, 4));
        ui->tbStack->item(i, STACK_COLUMN_VALUE_TEXT)->setText(strhex(contents, 4));
    }
}

void DeFuseDebugger::updateEvents()
{
    ui->tbEvents->setRowCount(0);
    event_foreach([](gpointer data, gpointer user_data)
    {
        QTableWidget * tbEvents = reinterpret_cast<QTableWidget *>(user_data);
        event_t * event = reinterpret_cast<event_t *>(data);

        int row = tbEvents->rowCount();
        tbEvents->setRowCount(row + 1);
        tbEvents->setItem(row, EVENTS_COLUMN_TIME, new QTableWidgetItem(QString::number(event->tstates)));
        tbEvents->setItem(row, EVENTS_COLUMN_TYPE, new QTableWidgetItem(event_name(event->type)));
    }, ui->tbEvents);
}

void DeFuseDebugger::updateBreakpoints()
{
    int row = 0;
    ui->tbBreakpoints->setRowCount(0);
    for(GSList * ptr = debugger_breakpoints; ptr; ptr = ptr->next ) 
    {

        debugger_breakpoint *bp = reinterpret_cast<debugger_breakpoint *>(ptr->data);
        
        QString buffer;

        switch( bp->type ) 
        {
            case DEBUGGER_BREAKPOINT_TYPE_EXECUTE:
            case DEBUGGER_BREAKPOINT_TYPE_READ:
            case DEBUGGER_BREAKPOINT_TYPE_WRITE:
                if( bp->value.address.source == memory_source_any ) 
                {
                    buffer = strhex(bp->value.address.offset, 4);
                } 
                else 
                {
                    buffer = QString("%1:%2:%3")
                        .arg(memory_source_description( bp->value.address.source ))
                        .arg(bp->value.address.page)
                        .arg(strhex(bp->value.address.offset, 4));
                }
                break;

            case DEBUGGER_BREAKPOINT_TYPE_PORT_READ:
            case DEBUGGER_BREAKPOINT_TYPE_PORT_WRITE:
                buffer = QString("%1:%2").arg(bp->value.port.mask).arg(bp->value.port.port);
                break;

            case DEBUGGER_BREAKPOINT_TYPE_TIME:
                buffer = QString::number(bp->value.time.tstates).rightJustified(5, '0');
                break;

            case DEBUGGER_BREAKPOINT_TYPE_EVENT:
                buffer = QString("%1:%2").arg(bp->value.event.type).arg(bp->value.event.detail);
                break;
            default:
                break;
        }

        ui->tbBreakpoints->setRowCount(row + 1);
        for (int j = 0; j < ui->tbBreakpoints->columnCount(); j++)
        {
            ui->tbBreakpoints->setItem(row, j, new QTableWidgetItem());
        }
        ui->tbBreakpoints->item(row, BREAKPOINTS_COLUMN_ID)->setText(QString::number(bp->id));
        ui->tbBreakpoints->item(row, BREAKPOINTS_COLUMN_TYPE)->setText(debugger_breakpoint_type_text[ bp->type ]);
        ui->tbBreakpoints->item(row, BREAKPOINTS_COLUMN_VALUE)->setText(buffer);
        ui->tbBreakpoints->item(row, BREAKPOINTS_COLUMN_IGNORE)->setText(QString::number(bp->ignore));
        ui->tbBreakpoints->item(row, BREAKPOINTS_COLUMN_LIFE)->setText(debugger_breakpoint_life_text[ bp->life ]);

        if( bp->condition ) {
            char buffer2[80];
            debugger_expression_deparse( buffer2, sizeof( buffer2 ), bp->condition );
            ui->tbBreakpoints->item(row, BREAKPOINTS_COLUMN_CONDITION)->setText(buffer2);
        }

        row++;

    }

    ui->tbBreakpoints->resizeColumnsToContents();
}

void DeFuseDebugger::updateMemoryMap()
{
    memory_page prev_page = { nullptr, -1, -1, -1, -1, -1, 0 };
    int offset = 0;
    int row = 0;

    ui->tbMemory->setRowCount(0);
    for(int block = 0; block < MEMORY_PAGES_IN_64K; block++) 
    {
        const memory_page & page = memory_map_read[block];

        if( page.source     != prev_page.source ||
            page.page_num   != prev_page.page_num ||
//            page.offset     != prev_page.offset ||
            page.writable   != prev_page.writable ||
            page.contended  != prev_page.contended ) 
        {

            ui->tbMemory->setRowCount(row + 1);
            for (int j = 0; j < ui->tbMemory->columnCount(); j++)
            {
                ui->tbMemory->setItem(row, j, new QTableWidgetItem());
            }
            ui->tbMemory->item(row, 0)->setText(QString("%1%2").arg(memory_source_description( page.source )).arg(page.page_num));
            ui->tbMemory->item(row, 1)->setText(strhex(block * MEMORY_PAGE_SIZE, 4));
            ui->tbMemory->item(row, 2)->setText(page.writable ? "Y" : "N");
            ui->tbMemory->item(row, 3)->setText(page.contended ? "Y" : "N");

            row++;

            prev_page = page;
        }

        /* We expect the next page to have an increased offset */
        offset += MEMORY_PAGE_SIZE;
    }
}

void DeFuseDebugger::updateRegisters()
{
    ui->tbRegisters->item(0, 1)->setText(strhex(PC, 4));
    ui->tbRegisters->item(0, 3)->setText(strhex(SP, 4));
    ui->tbRegisters->item(1, 1)->setText(strhex(AF, 4));
    ui->tbRegisters->item(1, 3)->setText(strhex(AF_, 4));
    ui->tbRegisters->item(2, 1)->setText(strhex(BC, 4));
    ui->tbRegisters->item(2, 3)->setText(strhex(BC_, 4));
    ui->tbRegisters->item(3, 1)->setText(strhex(DE, 4));
    ui->tbRegisters->item(3, 3)->setText(strhex(DE_, 4));
    ui->tbRegisters->item(4, 1)->setText(strhex(HL, 4));
    ui->tbRegisters->item(4, 3)->setText(strhex(HL_, 4));
    ui->tbRegisters->item(5, 1)->setText(strhex(IX, 4));
    ui->tbRegisters->item(5, 3)->setText(strhex(IY, 4));
    ui->tbRegisters->item(6, 1)->setText(strhex(I, 2));
    ui->tbRegisters->item(6, 3)->setText(strhex(( R & 0x7f ) | ( R7 & 0x80 ), 2));

    ui->tbStates->item(0, 0)->setText(QString::number(tstates));
    ui->tbStates->item(0, 1)->setText(QString::number(z80.halted));
    ui->tbStates->item(0, 2)->setText(QString::number(IM));
    ui->tbStates->item(0, 3)->setText(QString::number(IFF1));
    ui->tbStates->item(0, 4)->setText(QString::number(IFF2));

    for (int i = 0; i < 8; ++i)
    {
        ui->tbFlags->item(0, i)->setText((F & ( 0x80 >> i ) ) ? "1" : "0");
    }

    int state2_col = 0;
    auto capabilities = libspectrum_machine_capabilities( machine_current->machine );
    ui->tbStates2->item(0, state2_col)->setText(strhex(ula_last_byte(), 2));
    ++state2_col;
    if( capabilities & LIBSPECTRUM_MACHINE_CAPABILITY_AY )
    {
        ui->tbStates2->setColumnHidden(state2_col, false);
        ui->tbStates2->item(0, state2_col)->setText(strhex(machine_current->ay.current_register, 2));
    }
    else
    {
        ui->tbStates2->setColumnHidden(state2_col, true);
    }
    ++state2_col;

    if( capabilities & LIBSPECTRUM_MACHINE_CAPABILITY_128_MEMORY )
    {
        ui->tbStates2->setColumnHidden(state2_col, false);
        ui->tbStates2->item(0, state2_col)->setText(strhex(machine_current->ram.last_byte, 2));
    }
    else
    {
        ui->tbStates2->setColumnHidden(state2_col, true);
    }
    ++state2_col;

    if( capabilities & LIBSPECTRUM_MACHINE_CAPABILITY_PLUS3_MEMORY )
    {
        ui->tbStates2->setColumnHidden(state2_col, false);
        ui->tbStates2->item(0, state2_col)->setText(strhex(machine_current->ram.last_byte2, 2));
    }
    else
    {
        ui->tbStates2->setColumnHidden(state2_col, true);
    }
    ++state2_col;

    if( capabilities & LIBSPECTRUM_MACHINE_CAPABILITY_TIMEX_VIDEO  ||
        capabilities & LIBSPECTRUM_MACHINE_CAPABILITY_TIMEX_MEMORY ||
        capabilities & LIBSPECTRUM_MACHINE_CAPABILITY_SE_MEMORY       )
    {
        ui->tbStates2->setColumnHidden(state2_col, false);
        ui->tbStates2->item(0, state2_col)->setText(strhex(scld_last_dec.byte, 2));
    }
    else
    {
        ui->tbStates2->setColumnHidden(state2_col, true);
    }
    ++state2_col;

    if( capabilities & LIBSPECTRUM_MACHINE_CAPABILITY_TIMEX_MEMORY ||
        capabilities & LIBSPECTRUM_MACHINE_CAPABILITY_SE_MEMORY       )
    {
        ui->tbStates2->setColumnHidden(state2_col, false);
        ui->tbStates2->item(0, state2_col)->setText(strhex(scld_last_hsr, 2));
    }
    else
    {
        ui->tbStates2->setColumnHidden(state2_col, true);
    }
    ++state2_col;

    if( settings_current.zxcf_active )
    {
        ui->tbStates2->setColumnHidden(state2_col, false);
        ui->tbStates2->item(0, state2_col)->setText(strhex(zxcf_last_memctl(), 2));
    }
    else
    {
        ui->tbStates2->setColumnHidden(state2_col, true);
    }
    ++state2_col;

}

void DeFuseDebugger::updateAll()
{
    updateDisassembly();
    updateBreakpoints();
    updateEvents();
    updateMemoryMap();
    updateRegisters();
    updateStack();
}

void DeFuseDebugger::enterDebugging()
{
    debugger_mode = DEBUGGER_MODE_HALTED;
    fuse_emulation_pause();

    ui->bContinue->setEnabled(true);
    ui->bBreak->setEnabled(false);

    setPC(PC);
    updateAll();

    loop.exec();
}

void DeFuseDebugger::exitDebugging(debugger_mode_t mode)
{
    if (mode != DEBUGGER_MODE_HALTED)
    {
        debugger_mode = debugger_breakpoints ? DEBUGGER_MODE_ACTIVE : DEBUGGER_MODE_INACTIVE;
    }
    else
    {
        debugger_mode = DEBUGGER_MODE_HALTED;
    }
    fuse_emulation_unpause();

    ui->bContinue->setEnabled(false);
    ui->bBreak->setEnabled(true);

    loop.quit();
}


