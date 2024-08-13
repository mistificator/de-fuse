#ifndef DEFUSE_DEBUGGER_H
#define DEFUSE_DEBUGGER_H

#include <QDialog>
#include <QEventLoop>
#include <libspectrum.h>

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
    void setPC(libspectrum_word address);
    void updateDisassembly();
    void updateStack();
    void updateEvents();
    void updateBreakpoints();
    void updateMemoryMap();
    void updateRegisters();
    void updateAll();
    void enterDebugging();
    void exitDebugging();
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
private:
    Ui::DeFuseDebugger *ui;
    QEventLoop loop;
    void colorizeDisassembly(int row, const QByteArray &);
};

#endif // DEFUSE_DEBUGGER_H
