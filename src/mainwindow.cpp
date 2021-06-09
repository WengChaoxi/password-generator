#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QClipboard>
#include <QLabel>
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    clipboard = QApplication::clipboard();

    ui->status_bar->setSizeGripEnabled(false);

    ui->tedit_info->installEventFilter(this);
    ui->ledit_passwd->setContextMenuPolicy(Qt::NoContextMenu);

    // about
    QLabel *about = new QLabel(this);
    about->setText("<h4 style=\"margin-right:18px\"><a href=\"https://github.com/WengChaoxi/password-generator\">by wcx</a></h4>");
    about->setOpenExternalLinks(true);
    ui->status_bar->addPermanentWidget(about);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->tedit_info)
    {
        if((static_cast<QMouseEvent *>(event))->type()==QEvent::MouseButtonPress)
        {
            createContextMenu(watched);
            return true;
        }
    }
    return QWidget::eventFilter(watched, event);
}

void MainWindow::on_tedit_info_textChanged()
{
    _info = ui->tedit_info->toPlainText();
    updatePasswd();
}

void MainWindow::on_ledit_pw_textChanged(const QString &arg)
{
    _pw = arg;
    updatePasswd();
}

void MainWindow::on_chk_unique_clicked(bool checked)
{
    QString msg = checked?"[已开启] 生成的密码将只有当前主机能复现":"[已关闭] 生成的密码可在任意主机上复现";
    ui->status_bar->showMessage(msg, 5000);
    updatePasswd();
}

void MainWindow::updatePasswd()
{
    if(_info.isEmpty())
    {
        ui->ledit_passwd->setText("");
        return ;
    }
    if(_pw.isEmpty())
    {
        _pw = CRYPTO_DEFAULT_KEY;
    }

    QByteArray data;
    bool unique = ui->chk_unique->isChecked();
    if(unique)
    {
        QString tmp = QString("{%1:%2}").arg(_info).arg(_pw);
        data = _crypto.xorWithUniqueKey(tmp.toLocal8Bit());
    }
    else
    {
        QString tmp = QString("{%1}").arg(_info);
        data = _crypto.xorWithKey(tmp.toLocal8Bit(), _crypto.md5(_pw.toLocal8Bit()));
    }
    data = _pw==CRYPTO_DEFAULT_KEY?_crypto.md5(data):_crypto.sha256(data);
    _passwd = _crypto.toBase64Str(data);

    ui->ledit_passwd->setText(_passwd);
    ui->btn_copy->setText("复制");
}

void MainWindow::on_btn_copy_clicked()
{
    if(ui->ledit_passwd->text().isEmpty())
        return ;
    clipboard->setText(ui->ledit_passwd->text());
    ui->btn_copy->setText("已复制");
    ui->status_bar->showMessage("[复制成功] "+_passwd, 5000);
}

void MainWindow::createContextMenu(QObject *watched)
{
    QMenu *menu = new QMenu();

    if(watched == ui->tedit_info)
    {
        QAction *clear = new QAction("清空", this);
        menu->addAction(clear);
        connect(clear, &QAction::triggered, this, [this](){
            this->ui->tedit_info->setText("");
        });
    }

    menu->exec(cursor().pos());

    QList<QAction *> list = menu->actions(); // 释放内存
    foreach(QAction *action, list) {
        delete action;
    }
    delete menu;
}
