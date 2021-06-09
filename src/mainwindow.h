#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "crypto.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    void on_tedit_info_textChanged();
    void on_ledit_pw_textChanged(const QString &arg);
    void on_chk_unique_clicked(bool checked);
    void on_btn_copy_clicked();

    void createContextMenu(QObject *watched);

private:
    Ui::MainWindow *ui;
    Crypto _crypto;
    QString _info, _pw;
    QString _passwd;
    QClipboard *clipboard;
    void updatePasswd();
};

#endif // MAINWINDOW_H
