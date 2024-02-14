#ifndef QT_UI_H
#define QT_UI_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <functional>

QT_BEGIN_NAMESPACE
    namespace Ui { class DeFuseWindow; }
QT_END_NAMESPACE

class DeFuseWindow: public QMainWindow 
{
    Q_OBJECT
public:
    static DeFuseWindow * instance();
    int ask(char *);
    void showKeyboard();
    void about();
    void selectMachine();
    void selectScaler( std::function<int(int)> selector );
    static QPushButton * addOkCancelButtons(QDialog *); 
protected:
    DeFuseWindow(QWidget * _parent = nullptr);
    void closeEvent(QCloseEvent *) override;    
private:
    Ui::DeFuseWindow * ui = nullptr;    
    QLabel * keyboard = nullptr;
    void menu_data_init(); // body is generated from menu_data.pl
    void selectSomething(QString title, int current, int count, std::function<QPair<int, QString>(int)> label_fn, std::function<int(int, bool)> apply_fn);
};

#endif