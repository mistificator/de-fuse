#ifndef QT_UI_H
#define QT_UI_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
    namespace Ui { class DeFuseWindow; }
QT_END_NAMESPACE

class DeFuseWindow: public QMainWindow 
{
    Q_OBJECT
public:
    static DeFuseWindow * instance();
    int ask(char *);
protected:
    DeFuseWindow(QWidget * _parent = nullptr);
    void closeEvent(QCloseEvent *) override;    
private:
    Ui::DeFuseWindow * ui;    
    void menu_data_init(); // body is generated from menu_data.pl
};

#endif