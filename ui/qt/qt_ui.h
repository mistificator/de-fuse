#ifndef QT_UI_H
#define QT_UI_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QImage>
#include <functional>

extern "C"
{
    #include <libspectrum.h>
    #include <display.h>
}

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
    void selectRom( const char *title, size_t start, size_t count, int is_peripheral );
    void selectScaler( std::function<int(int)> selector );
    static QPushButton * addOkCancelButtons(QDialog *);
    struct Screen_t 
    {
        enum { AddX = 0 /*3*/, AddY = 0 /*4*/, Pitch = DISPLAY_SCREEN_WIDTH + AddX, Size = (2 * DISPLAY_SCREEN_HEIGHT + AddY) * Pitch };
        QImage * image = nullptr;
    };
    Screen_t getScreen(int w, int h);
    Screen_t getScreen();
    void drawScreen();
    void needToRepaint();
    void setSpeed(float);
    void setMenuActive(const char * path, int state);
    int setStatusBar( int item, int state );
    void reset();
protected:
    DeFuseWindow(QWidget * _parent = nullptr);
    void closeEvent(QCloseEvent *) override;    
    void keyPressEvent(QKeyEvent *) override;
    void keyReleaseEvent(QKeyEvent *) override;
private:
    Ui::DeFuseWindow * ui = nullptr;    
    QLabel * keyboard = nullptr;
    QImage screen_image[2];
    Screen_t screen;
    QLabel * speed_status = nullptr;
    QLabel * disk_status = nullptr, * mdr_status = nullptr, * mouse_status = nullptr, * pause_status = nullptr, * tape_status = nullptr;
    QLabel * machine_status = nullptr;
    bool need_to_repaint = false;
    long long frame = 0;
    void menu_data_init(); // body is generated from menu_data.pl
    void selectSomething(QString title, int current, int count, std::function<QPair<int, QString>(int)> label_fn, std::function<int(int, bool)> apply_fn);
    void checkForWindowResize(QPixmap & new_px);
    QPixmap pixmapWithTransparency(QPixmap px);
};

#endif