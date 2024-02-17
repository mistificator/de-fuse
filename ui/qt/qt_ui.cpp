#include "qt_ui.h"
#include "ui_qt_ui.h"

#include <QApplication>
#include <QMessageBox>
#include <QButtonGroup>
#include <QKeyEvent>
#include <QFileDialog>
#include <QDebug>

#include "menu_data.cpp"
#include "options.cpp"
extern "C"
{
    #include "qt_ui_c_wrap.c"
}

DeFuseWindow::DeFuseWindow(QWidget * _parent): QMainWindow(_parent), ui(new Ui::DeFuseWindow)
{
    ui->setupUi(this);
    ui->statusbar->addPermanentWidget(speed_status = new QLabel());
    menu_data_init();
//    grabKeyboard();
    setFocusPolicy(Qt::WheelFocus);

    ui->menu_help->addAction("About Qt", []() {
        QMessageBox::aboutQt(DeFuseWindow::instance());
    });
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

void DeFuseWindow::showKeyboard()
{
    if (!keyboard)
    {
        keyboard = new QLabel(this);
        keyboard->setPixmap(QPixmap(":/keyboard.png"));
        keyboard->setWindowTitle("De-Fuse - Keyboard");
        keyboard->setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
    }
    keyboard->show();
}

void DeFuseWindow::about()
{
    QMessageBox::about(this, "De-Fuse",
    (QStringList()  << "De-Fuse" << "Based on Fuse - the Free Unix Spectrum Emulator" 
                    << "" << FUSE_COPYRIGHT << "" << "version " VERSION << PACKAGE_URL).join("\n\n")); 
}

void DeFuseWindow::selectMachine()
{
    selectSomething("De-Fuse - Select Machine", machine_current->machine, machine_count,
        [](int i)->QPair<int, QString> { return qMakePair(machine_types[i]->machine, libspectrum_machine_name( machine_types[i]->machine )); },
        [](int machine, bool not_test)->int { if (not_test) { machine_select( machine ); } return machine; });
}

void DeFuseWindow::selectScaler( std::function<int(int)> selector )
{
    selectSomething("De-Fuse - Screen filter", current_scaler, SCALER_NUM,
        [](int i)->QPair<int, QString> { return qMakePair(i, scaler_name( i )); },
        [=](int scaler, bool not_test)->int { if (!not_test) { return selector(scaler) ? scaler : -1; } return (current_scaler = scaler); });    
}

void  DeFuseWindow::selectSomething(QString title, int current, int count, std::function<QPair<int, QString>(int)> label_fn, std::function<int(int, bool)> apply_fn)
{
    QDialog * _dialog = new QDialog(DeFuseWindow::instance());
    _dialog->setWindowTitle(title);

    QVBoxLayout * _vbox = new QVBoxLayout();
    _dialog->setLayout(_vbox);
    QButtonGroup * _bg = new QButtonGroup(_dialog);
    for( int i = 0; i < count; i++ ) 
    {
        auto pair = label_fn(i);
        if ( apply_fn( pair.first, false ) == -1) // test if available
        {
            continue;
        }
        QCheckBox * _cb = new QCheckBox( pair.second );
        _bg->addButton( _cb, pair.first );
        _vbox->addWidget(_cb);
        if ( current == pair.first )
        {
            _cb->setChecked(true);
        }
    }   

    DeFuseWindow::addOkCancelButtons( _dialog );

  /* Process events until the window is done with */
    if (_dialog->exec() == QDialog::Accepted)
    {
        apply_fn( _bg->checkedId(), true ); // apply selected
    }
    delete _dialog;
}

void DeFuseWindow::selectRom( const char *title, size_t start, size_t count, int is_peripheral )
{
    QDialog * _dialog = new QDialog(DeFuseWindow::instance());
    _dialog->setWindowTitle(QString("De-Fuse - Select ROMs - %1").arg(title));

    QVBoxLayout * _vbox = new QVBoxLayout();
    _dialog->setLayout(_vbox);

    QList<QLineEdit *> lines;
    for( int i = 0; i < count; i++ ) 
    {
        QHBoxLayout * _hbox = new QHBoxLayout();
        QLineEdit * _le = new QLineEdit( *settings_get_rom_setting( &settings_current, start + i, is_peripheral ) );
        _hbox->addWidget(_le);
        lines << _le;
        QPushButton * _btn = new QPushButton( "Select..." );
        _hbox->addWidget(_btn);
        QGroupBox * _gb = new QGroupBox(QString("ROM %1").arg(i));
        _gb->setLayout(_hbox);
        _vbox->addWidget(_gb);

        QObject::connect(_btn, &QPushButton::clicked, [=]() {
            const char * filename = ui_get_open_filename( "De-Fuse - Select ROM" );
            if( !filename ) return;
            _le->setText( filename );
        });
    }   

    DeFuseWindow::addOkCancelButtons( _dialog );

  /* Process events until the window is done with */
    if (_dialog->exec() == QDialog::Accepted)
    {
        for( int i = 0; i < count; i++ ) {
            char **setting = settings_get_rom_setting( &settings_current, start + i, is_peripheral );
            settings_set_string( setting, lines.at(i)->text().toLocal8Bit().constData() );
        }
    }

    delete _dialog;
}

QPushButton * DeFuseWindow::addOkCancelButtons(QDialog * _dialog)
{
  QHBoxLayout * _hbox = new QHBoxLayout();
  _hbox->addSpacerItem( new QSpacerItem( 10, 1 ) );
  QPushButton * _cancel = new QPushButton( "Cancel ");
  QObject::connect( _cancel, &QPushButton::clicked, _dialog, &QDialog::reject );
  _hbox->addWidget( _cancel );
  QPushButton * _ok = new QPushButton( "OK ");
  _ok->setDefault(true);
  QObject::connect( _ok, &QPushButton::clicked, _dialog, &QDialog::accept );
  _hbox->addWidget( _ok );
  dynamic_cast<QBoxLayout *>(_dialog->layout())->addLayout( _hbox );
  return _ok;
} 

DeFuseWindow::Screen_t DeFuseWindow::getScreen(int w, int h)
{
    for (int i = 0; i < 2; ++i)
    {
        if (screen_image[i].size() != QSize(w, h))
        {
            screen_image[i] = QImage(w, h, QImage::Format_RGB32);
            screen_image[i].fill(Qt::black);
        }
    }
    return getScreen();
}

DeFuseWindow::Screen_t DeFuseWindow::getScreen()
{
    screen.image = & screen_image[settings_current.pretty_gigascreen ? (frame & 0x01) : 0];
    return screen;
}

void DeFuseWindow::drawScreen()
{
    if (need_to_repaint)
    {
        if (!settings_current.pretty_gigascreen || (frame & 0x01) == 1)
        {
            auto image = &screen_image[0];
            const int w = image->width();
            const int h = image->height();
            if (settings_current.pretty_gigascreen)
            {
                auto frame0 = (unsigned int *)image->constBits();
                auto frame1 = (unsigned int *)screen_image[1].constBits();
                const int sz = w * h;
                for (int i = 0; i < sz; ++i, ++frame0, ++frame1)
                {
                    *frame0 += *frame1 & 0x00FFFFFF;
                }
            }            
            auto scale = scaler_get_scaling_factor(current_scaler);
            // extremely stupid way to update screen
            ui->screenWidget->setPixmap(QPixmap::fromImage(
                image->scaled(
                    w * scale,
                    h * scale,
                    Qt::KeepAspectRatio,
                    Qt::FastTransformation
                    )
                ));
            need_to_repaint = false;
        }
    }
    frame++;
}

void DeFuseWindow::needToRepaint()
{
    need_to_repaint = true;
}

void DeFuseWindow::setSpeed(float speed)
{
    speed_status->setText(QString::number(speed, 'f', 1) + "%");
}

void DeFuseWindow::keyPressEvent(QKeyEvent * ke)
{
    if (ke->modifiers().testFlag(Qt::AltModifier))
    {
        return;
    }
    input_event_t fuse_event;
    fuse_event.type = INPUT_EVENT_KEYPRESS;
    fuse_event.types.key.spectrum_key = fuse_event.types.key.native_key = keysyms_remap( ke->key() );
    input_event( &fuse_event );
}

void DeFuseWindow::keyReleaseEvent(QKeyEvent * ke)
{
    if (ke->modifiers().testFlag(Qt::AltModifier))
    {
        return;
    }
    input_event_t fuse_event;
    fuse_event.type = INPUT_EVENT_KEYRELEASE;
    fuse_event.types.key.spectrum_key = fuse_event.types.key.native_key = keysyms_remap( ke->key() );
    input_event( &fuse_event );
}

void DeFuseWindow::setMenuActive(const char * path, int state)
{
    QString action_name = QString(path).toLower().replace(QRegExp("[\\/]+"), "_").replace(QRegExp("[\\W]+"), "");
    if (auto action = findChild<QAction *>("action" + action_name))
    {
        action->setEnabled(state);
        return;
    }
    if (auto menu = findChild<QMenu *>("menu" + action_name))
    {
        menu->setEnabled(state);
        return;
    }
}
