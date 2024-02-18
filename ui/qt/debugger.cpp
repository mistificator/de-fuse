#include "debugger.h"
#include "ui_debugger.h"

DeFuseDebugger::DeFuseDebugger(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeFuseDebugger)
{
    ui->setupUi(this);
}

DeFuseDebugger::~DeFuseDebugger()
{
    delete ui;
}
