#ifndef DEFUSE_DEBUGGER_H
#define DEFUSE_DEBUGGER_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class DeFuseDebugger; }
QT_END_NAMESPACE

class DeFuseDebugger : public QWidget
{
    Q_OBJECT

public:
    explicit DeFuseDebugger(QWidget *parent = nullptr);
    ~DeFuseDebugger();

private:
    Ui::DeFuseDebugger *ui;
};

#endif // DEFUSE_DEBUGGER_H
