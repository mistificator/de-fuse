#ifndef DEFUSE_DEBUGGER_H
#define DEFUSE_DEBUGGER_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class DeFuseDebugger; }
QT_END_NAMESPACE

class DeFuseDebugger : public QDialog
{
    Q_OBJECT

public:
    explicit DeFuseDebugger(QWidget *parent = nullptr);
    ~DeFuseDebugger();
private slots:    
    void updateDisassembly();
    void updateStack();
    void updateEvents();
    void updateBreakpoints();
    void updateMemoryMap();
    void updateRegisters();
    void updateAll();
    void on_bEvaluate_clicked();
    void on_leEvaluate_returnPressed();
    void on_bStep_clicked();
    void on_bContinue_clicked();
    void on_bBreak_clicked();
    void on_actionClose_triggered();
    void on_bClose_clicked();
    void on_scDisassembly_valueChanged(int value);
    void on_actionColorize_disassembly_toggled(bool);
protected:
    void showEvent(QShowEvent *) override;
    void closeEvent(QCloseEvent *) override;   
    void resizeEvent(QResizeEvent *) override; 
private:
    Ui::DeFuseDebugger *ui;
    void colorizeDisassembly(int row, const QByteArray &);
};

#endif // DEFUSE_DEBUGGER_H
