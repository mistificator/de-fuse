#include "tapebrowser.h"
#include "ui/ui.h"
#include "ui_tapebrowser.h"

DeFuseTapeBrowser::DeFuseTapeBrowser(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DeFuseTapeBrowser)
{
    ui->setupUi(this);
}

DeFuseTapeBrowser::~DeFuseTapeBrowser()
{
    delete ui;
}

void DeFuseTapeBrowser::add_block_details( libspectrum_tape_block *block, void *user_data )
{
    reinterpret_cast<DeFuseTapeBrowser *>(user_data)->add_block_details(block);
}

void DeFuseTapeBrowser::add_block_details( libspectrum_tape_block *block )
{
    const int row = ui->tbTape->rowCount();
    ui->tbTape->setRowCount(row + 1);
    QByteArray ba(128, '\0');
    ui->tbTape->setItem(row, 0, new QTableWidgetItem());
    libspectrum_tape_block_description( ba.data(), ba.count(), block );
    ui->tbTape->setItem(row, 1, new QTableWidgetItem(QString::fromLatin1(ba)));
    tape_block_details( ba.data(), ba.count(), block );
    ui->tbTape->setItem(row, 2, new QTableWidgetItem(QString::fromLatin1(ba)));
}

void DeFuseTapeBrowser::update(ui_tape_browser_update_type change,
            libspectrum_tape_block *block)
{
    fuse_emulation_pause();

    ui->tbTape->setRowCount(0);
    if( tape_foreach( add_block_details, this ) )
    {
        fuse_emulation_unpause();
        return;
    }

    auto current_block = tape_get_current_block();
    if( current_block >= 0 && current_block < ui->tbTape->rowCount())
    {
        ui->tbTape->item(current_block, 0)->setText(">");
    }

    if( tape_modified )
    {
        ui->lState->setText("Tape modified");
    }
    else
    {
        ui->lState->setText("Tape not modified");
    }

    ui->tbTape->resizeColumnsToContents();

    fuse_emulation_unpause();
}

void DeFuseTapeBrowser::showEvent(QShowEvent *)
{
    fuse_emulation_pause();
}

void DeFuseTapeBrowser::closeEvent(QCloseEvent *)
{
    fuse_emulation_unpause();
}
void DeFuseTapeBrowser::on_bClose_clicked()
{
    close();
}

void DeFuseTapeBrowser::on_tbTape_itemDoubleClicked(QTableWidgetItem *item)
{
    if( item->row() == tape_get_current_block() )
    {
        tape_do_play(1);
        return;
    }

    tape_select_block_no_update( item->row() );
    update(UI_TAPE_BROWSER_SELECT_BLOCK, nullptr);
}

