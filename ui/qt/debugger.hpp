#ifndef DEFUSE_DEBUGGER_H
#define DEFUSE_DEBUGGER_H

#include <QDialog>
#include <QEventLoop>

extern "C"
{
    #include <config.h>
#ifdef HAVE_LIB_GLIB
    #include <glib.h>
#endif				/* #ifdef HAVE_LIB_GLIB */
    #include <libspectrum.h>
    #include "debugger/debugger.h"
}

QT_BEGIN_NAMESPACE
namespace Ui { class DeFuseDebugger; }
QT_END_NAMESPACE

class DeFuseDebugger : public QDialog
{
    Q_OBJECT

public:
    explicit DeFuseDebugger(QWidget *parent = nullptr);
    ~DeFuseDebugger();
public slots:
    void setPC(libspectrum_word address, bool move_selection = true);
    void updateDisassembly();
    void updateStack();
    void updateEvents();
    void updateBreakpoints();
    void updateMemoryMap();
    void updateRegisters();
    void updateAll();
    void enterDebugging();
    void exitDebugging(debugger_mode_t mode = DEBUGGER_MODE_ACTIVE);
private slots:
    void on_bEvaluate_clicked();
    void on_leEvaluate_returnPressed();
    void on_bStep_clicked();
    void on_bContinue_clicked();
    void on_bBreak_clicked();
    void on_actionClose_triggered();
    void on_bClose_clicked();
    void on_scDisassembly_valueChanged(int value);
    void on_actionColorize_disassembly_toggled(bool);
    void on_tbDisassembly_customContextMenuRequested(const QPoint &pt);
protected:
    void showEvent(QShowEvent *) override;
    void closeEvent(QCloseEvent *) override;   
    void resizeEvent(QResizeEvent *) override;
    bool eventFilter(QObject * o, QEvent * e) override;
private:
    Ui::DeFuseDebugger *ui;
    QEventLoop loop;
    void colorizeDisassembly(int row, const QByteArray &);
    QByteArray disassembleAt(libspectrum_word address, size_t * length = nullptr);
    void scrollDisassemblyByOffset(int offset);
};

#endif // DEFUSE_DEBUGGER_H
