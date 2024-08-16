#ifndef DEFUSE_HEXVIEW_H
#define DEFUSE_HEXVIEW_H

#include <QDialog>
#include <QTableWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class DeFuseHexView; }
QT_END_NAMESPACE

class DeFuseHexView : public QDialog
{
    Q_OBJECT

public:
    explicit DeFuseHexView(QWidget *parent = nullptr);
    ~DeFuseHexView();
public slots:
    void updateHexView();
private slots:
    void on_bClose_clicked();
    void on_cbBytesPerRow_currentIndexChanged(int index);
    void on_tbHexView_itemSelectionChanged();
    void on_tbCharView_itemSelectionChanged();
protected:
    void showEvent(QShowEvent *) override;
    void closeEvent(QCloseEvent *) override;
private:
    Ui::DeFuseHexView *ui;
    void updateSelection(QTableWidget * table1, QTableWidget * table2);
};

#endif // DEFUSE_HEXVIEW_H
