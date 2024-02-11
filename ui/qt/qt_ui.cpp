#include "qt_ui.h"
#include "ui_qt_ui.h"
#include <QApplication>

DeFuseWindow::DeFuseWindow(QWidget * _parent): QMainWindow(_parent), ui(new Ui::DeFuseWindow)
{
    ui->setupUi(this);
}

void DeFuseWindow::closeEvent(QCloseEvent *)
{
    qApp->quit();
}

// -----------------------------------------------------------------------

extern "C"
{

    #include "qt_ui_c_wrap.c"

}