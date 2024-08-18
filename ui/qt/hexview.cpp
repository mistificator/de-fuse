#include "hexview.hpp"
#include "ui_hexview.hpp"

#include <QScrollBar>

extern "C" {
    #include <memory_pages.h>
    #include <fuse.h>
}

DeFuseHexView::DeFuseHexView(QWidget *parent)
    : QDialog(parent, Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::WindowMinMaxButtonsHint)
    , ui(new Ui::DeFuseHexView)
{
    ui->setupUi(this);

    connect(ui->tbHexView->verticalScrollBar(), &QScrollBar::valueChanged, this,
    [this](int value) {
        ui->tbCharView->verticalScrollBar()->setValue(value);
    });
    connect(ui->tbCharView->verticalScrollBar(), &QScrollBar::valueChanged, this,
    [this](int value) {
        ui->tbHexView->verticalScrollBar()->setValue(value);
    });

    connect(ui->tbHexView->horizontalScrollBar(), &QScrollBar::valueChanged, this,
    [this](int value) {
        ui->tbCharView->horizontalScrollBar()->setValue(value);
    });
    connect(ui->tbCharView->horizontalScrollBar(), &QScrollBar::valueChanged, this,
    [this](int value) {
        ui->tbHexView->horizontalScrollBar()->setValue(value);
    });

}

DeFuseHexView::~DeFuseHexView()
{
    delete ui;
}

void DeFuseHexView::updateHexView()
{
    int width = ui->cbBytesPerRow->currentText().toInt();
    int height = 65536 / width;

    ui->tbHexView->setColumnCount(width);
    ui->tbHexView->setRowCount(height);
    ui->tbCharView->setColumnCount(width);
    ui->tbCharView->setRowCount(height);
    for (int col = 0; col < width; ++col)
    {
        ui->tbHexView->setHorizontalHeaderItem(
            col,
            new QTableWidgetItem(QString::number(col, 16).rightJustified(2, '0')));
        ui->tbCharView->setHorizontalHeaderItem(
            col,
            new QTableWidgetItem(QString()));
    }
    for (int row = 0; row < height; ++row)
    {
        ui->tbHexView->setVerticalHeaderItem(
            row,
            new QTableWidgetItem(QString::number(row * width, 16).rightJustified(4, '0')));
    }
    for (size_t addr = 0; addr < 65536; ++addr)
    {
        auto val = readbyte_internal(addr);
        ui->tbHexView->setItem(
            addr / width, addr % width,
            new QTableWidgetItem(QString::number(val, 16).rightJustified(2, '0')));
        ui->tbCharView->setItem(
            addr / width, addr % width,
            new QTableWidgetItem(val >= 32 ? QString::fromLatin1(& val, 1) : QString('.')));
    }

    ui->tbHexView->resizeColumnsToContents();
//    ui->tbCharView->resizeColumnsToContents();
}

void DeFuseHexView::showEvent(QShowEvent *)
{
    fuse_emulation_pause();
    updateHexView();
}

void DeFuseHexView::closeEvent(QCloseEvent *)
{
    fuse_emulation_unpause();
}

void DeFuseHexView::on_bClose_clicked()
{
    close();
}


void DeFuseHexView::on_cbBytesPerRow_currentIndexChanged(int index)
{
    updateHexView();
}

void DeFuseHexView::updateSelection(QTableWidget * table1, QTableWidget * table2)
{
    bool block_state = table2->signalsBlocked();
    table2->blockSignals(true);
    auto sel_model1 = table1->selectionModel();
    auto sel_model2 = table2->selectionModel();
    auto model2 = table2->model();
    auto indexes1 = sel_model1->selectedIndexes();
    QItemSelection sel;
    for(const QModelIndex & index1 : indexes1)
    {
        auto index2 = model2->index(index1.row(), index1.column());
        sel.append(QItemSelectionRange(index2, index2));
    }
    sel_model2->clearSelection();
    sel_model2->select(sel, QItemSelectionModel::Select);
    table2->blockSignals(block_state);
}

void DeFuseHexView::on_tbHexView_itemSelectionChanged()
{
    updateSelection(ui->tbHexView, ui->tbCharView);
}


void DeFuseHexView::on_tbCharView_itemSelectionChanged()
{
    updateSelection(ui->tbCharView, ui->tbHexView);
}

