#include "debugger.h"
#include "ui_debugger.h"

extern "C"
{
    #include "fuse.h"
}

DeFuseDebugger::DeFuseDebugger(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeFuseDebugger)
{
    ui->setupUi(this);

    ui->tbBreakpoints->resizeColumnsToContents();   ui->tbBreakpoints->setRowCount(0);
    ui->tbDisassembly->resizeColumnsToContents();   ui->tbDisassembly->setRowCount(0);
    ui->tbEvents->resizeColumnsToContents();        ui->tbEvents->setRowCount(0);
    ui->tbFlags->resizeColumnsToContents();         ui->tbFlags->setRowCount(0);
    ui->tbMemory->resizeColumnsToContents();        ui->tbMemory->setRowCount(0);
    ui->tbRegisters->resizeColumnsToContents();     ui->tbRegisters->setRowCount(0);
    ui->tbStack->resizeColumnsToContents();         ui->tbStack->setRowCount(0);
    ui->tbStates->resizeColumnsToContents();        ui->tbStates->setRowCount(0);
    ui->tbStates2->resizeColumnsToContents();       ui->tbStates2->setRowCount(0);
}

DeFuseDebugger::~DeFuseDebugger()
{
    delete ui;
}

void DeFuseDebugger::on_bEvaluate_clicked()
{

}

void DeFuseDebugger::on_bStep_clicked()
{

}

void DeFuseDebugger::on_bContinue_clicked()
{

}

void DeFuseDebugger::on_bBreak_clicked()
{

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
}

void DeFuseDebugger::closeEvent(QCloseEvent *)
{
    fuse_emulation_unpause();
} 
