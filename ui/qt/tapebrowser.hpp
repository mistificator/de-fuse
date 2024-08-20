#ifndef DEFUSE_TAPEBROWSER_H
#define DEFUSE_TAPEBROWSER_H

#include <QDialog>
#include <QTableWidget>

extern "C"
{
#ifndef LIBSPECTRUM_HAS_GLIB_REPLACEMENT
    #include <glib.h>
#endif
    #include <libspectrum.h>
    #include <fuse.h>
    #include <tape.h>
    #include <ui/ui.h>
}

namespace Ui {
class DeFuseTapeBrowser;
}

class DeFuseTapeBrowser : public QDialog
{
    Q_OBJECT

public:
    explicit DeFuseTapeBrowser(QWidget *parent = nullptr);
    ~DeFuseTapeBrowser();

    void update(ui_tape_browser_update_type change,
           libspectrum_tape_block *block);
protected:
    void showEvent(QShowEvent *) override;
    void closeEvent(QCloseEvent *) override;
private slots:
    void on_bClose_clicked();
    void on_tbTape_itemDoubleClicked(QTableWidgetItem *item);

private:
    Ui::DeFuseTapeBrowser *ui;
    static void add_block_details( libspectrum_tape_block *block, void *user_data );
    void add_block_details( libspectrum_tape_block *block );
};

#endif // DEFUSE_TAPEBROWSER_H
