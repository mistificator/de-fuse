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
    DeFuseWindow(QWidget * _parent = nullptr);
protected:
    void closeEvent(QCloseEvent *);    
private:
    Ui::DeFuseWindow * ui;    
};

#endif