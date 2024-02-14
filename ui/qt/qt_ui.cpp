#include "qt_ui.h"
#include "ui_qt_ui.h"
#include <QApplication>
#include <QMessageBox>

#include "menu_data.cpp"
#include "options.cpp"
extern "C"
{
    #include "qt_ui_c_wrap.c"
}

DeFuseWindow::DeFuseWindow(QWidget * _parent): QMainWindow(_parent), ui(new Ui::DeFuseWindow)
{
    ui->setupUi(this);
    menu_data_init();
}

DeFuseWindow * DeFuseWindow::instance()
{
    static DeFuseWindow * w = new DeFuseWindow();
    return w;
}

void DeFuseWindow::closeEvent(QCloseEvent *)
{
    menu_file_exit(0);
}

int DeFuseWindow::ask(char * text)
{
    return QMessageBox::question(this, "Question", text) == QMessageBox::Yes;
}

