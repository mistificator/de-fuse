#include "qt_ui.h"
#include "ui_qt_ui.h"
#include <QApplication>
#include <QMessageBox>
#include <QButtonGroup>

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

    QPushButton * _ok = DeFuseWindow::addOkCancelButtons( _dialog );
    QObject::connect( _ok, &QPushButton::clicked, [=]() {
        apply_fn( _bg->checkedId(), true ); // apply selected
    });

  /* Process events until the window is done with */
    _dialog->exec();
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
