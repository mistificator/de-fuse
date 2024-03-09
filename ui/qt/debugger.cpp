#include "debugger.h"
#include "ui_debugger.h"

extern "C"
{    
    #include <glib.h> // for GSList

    #include "fuse.h"
    #include "debugger/debugger.h"
    #include "debugger/breakpoint.h"
    #include "z80/z80.h"
    #include "z80/z80_macros.h"
}

DeFuseDebugger::DeFuseDebugger(QWidget *parent) :
    QDialog(parent, Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::WindowMinMaxButtonsHint),
    ui(new Ui::DeFuseDebugger)
{
    ui->setupUi(this);

    ui->tbBreakpoints->resizeColumnsToContents();   ui->tbBreakpoints->setRowCount(0);
    ui->tbDisassembly->resizeColumnsToContents();   ui->tbDisassembly->setRowCount(0);
    ui->tbEvents->resizeColumnsToContents();        ui->tbEvents->setRowCount(0);
    ui->tbFlags->resizeColumnsToContents();         //ui->tbFlags->setRowCount(0);
    ui->tbMemory->resizeColumnsToContents();        ui->tbMemory->setRowCount(0);
    ui->tbRegisters->resizeColumnsToContents();     //ui->tbRegisters->setRowCount(0);
    ui->tbStack->resizeColumnsToContents();         ui->tbStack->setRowCount(0);
    ui->tbStates->resizeColumnsToContents();        //ui->tbStates->setRowCount(0);
    ui->tbStates2->resizeColumnsToContents();       //ui->tbStates2->setRowCount(0);
}

DeFuseDebugger::~DeFuseDebugger()
{
    delete ui;
}

void DeFuseDebugger::on_bEvaluate_clicked()
{
    debugger_command_evaluate(ui->leEvaluate->text().toLocal8Bit());
}

void DeFuseDebugger::on_bStep_clicked()
{

}

void DeFuseDebugger::on_bContinue_clicked()
{

}

void DeFuseDebugger::on_bBreak_clicked()
{
    updateAll();
}

void DeFuseDebugger::on_bClose_clicked()
{
    close();
}

void DeFuseDebugger::showEvent(QShowEvent *)
{
    fuse_emulation_pause();

    ui->bContinue->setEnabled(false);
    ui->bBreak->setEnabled(true);

    ui->scDisassembly->setValue(PC);
    updateAll();
}

void DeFuseDebugger::closeEvent(QCloseEvent *)
{
    fuse_emulation_unpause();
} 

void DeFuseDebugger::resizeEvent(QResizeEvent *)
{
    updateDisassembly();
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
    for( int i = 0, address = ui->scDisassembly->value(); i < ui->tbDisassembly->rowCount() && address <= 0xFFFF; i++ ) 
    {
        if (address == PC)
        {
            ui->tbDisassembly->item(i, 0)->setText("->");
        }
        for(GSList * ptr = debugger_breakpoints; ptr; ptr = ptr->next ) 
        {
            debugger_breakpoint *bp = ptr->data;

            switch( bp->type ) 
            {

            case DEBUGGER_BREAKPOINT_TYPE_EXECUTE:
            case DEBUGGER_BREAKPOINT_TYPE_READ:
            case DEBUGGER_BREAKPOINT_TYPE_WRITE:
                if ( bp->value.address.offset == address ) 
                {
                    ui->tbDisassembly->item(i, 1)->setText(QString::number(bp->id));
                }
                break;
            default:
                break;
            }
        }
        ui->tbDisassembly->item(i, 2)->setText(QString::number(address, 16).rightJustified(4, '0').toUpper());

        QByteArray instr(128, 0);
        size_t length = 0;
        debugger_disassemble(instr.data(), instr.size(), &length, address);
        ui->tbDisassembly->item(i, 3)->setText(instr);
        colorizeDisassembly(i, instr);

        address += length;
    }
}

void DeFuseDebugger::on_scDisassembly_valueChanged(int value)
{
    updateDisassembly();
}

void DeFuseDebugger::on_actionColorize_disassembly_toggled(bool)
{
    updateDisassembly();
}

void DeFuseDebugger::updateStack()
{

}

void DeFuseDebugger::updateEvents()
{

}

void DeFuseDebugger::updateBreakpoints()
{
    int row = 0;
    ui->tbBreakpoints->setRowCount(0);
    for(GSList * ptr = debugger_breakpoints; ptr; ptr = ptr->next ) 
    {

        debugger_breakpoint *bp = ptr->data;
        
        QString buffer;

        switch( bp->type ) 
        {
            case DEBUGGER_BREAKPOINT_TYPE_EXECUTE:
            case DEBUGGER_BREAKPOINT_TYPE_READ:
            case DEBUGGER_BREAKPOINT_TYPE_WRITE:
                if( bp->value.address.source == memory_source_any ) 
                {
                    buffer = QString::number(bp->value.address.offset, 16).rightJustified(4, '0').toUpper();
                } 
                else 
                {
                    buffer = QString("%1:%2:%3")
                        .arg(memory_source_description( bp->value.address.source ))
                        .arg(bp->value.address.page)
                        .arg(QString::number(bp->value.address.offset, 16).rightJustified(4, '0').toUpper());
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
        ui->tbBreakpoints->item(row, 0)->setText(QString::number(bp->id));
        ui->tbBreakpoints->item(row, 1)->setText(debugger_breakpoint_type_text[ bp->type ]);
        ui->tbBreakpoints->item(row, 2)->setText(buffer);
        ui->tbBreakpoints->item(row, 3)->setText(QString::number(bp->ignore));
        ui->tbBreakpoints->item(row, 4)->setText(debugger_breakpoint_life_text[ bp->life ]);

        if( bp->condition ) {
            char buffer2[80];
            debugger_expression_deparse( buffer2, sizeof( buffer2 ), bp->condition );
            ui->tbBreakpoints->item(row, 5)->setText(buffer2);
        }

        row++;

    }
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
            ui->tbMemory->item(row, 1)->setText(QString::number(block * MEMORY_PAGE_SIZE, 16).rightJustified(4, '0').toUpper());
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