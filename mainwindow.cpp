#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QDebug"
#include <QFileDialog>
#include "dta.h"
#include "QMessageBox"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    // 获取文件路径
    QString filepath = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                ".",
                tr("Image files(*.bmp)"));

    if (filepath.isEmpty())
    {
        return;
    }

    QImage image;
    if (!image.load(filepath))  {
        return;
    }

    this->sPathBMP = filepath;

    QGraphicsScene *scene = new QGraphicsScene;
    scene->addPixmap(QPixmap::fromImage(image));

    ui->graphicsView->setScene(scene);
    ui->centralWidget->resize(image.width() + 200, image.height() + 50);
    ui->graphicsView->show();

    ui->label_value_w->setText(QString::number(image.width(), 10));
    ui->label_value_h->setText(QString::number(image.height(), 10));
    ui->label_value_color->setText((QString::number(image.depth(), 10)));
}

void MainWindow::on_actionDTA_triggered()
{
    DTA file(sPathBMP);
    if (int8_t res = file.check() != 0)
    {
        QString message;
        if (res == 1) {
            message += tr("颜色个数应为:4(颜色深度:2)");
        }
        else if (res == 2)
        {
            message += tr("图片大小:");
            message += QString::number(file.getHeight());
            message += tr(" x ");
            message += QString::number(file.getWith());
            message += tr("\r\n应为600x800或800x600");
        }

        QMessageBox::warning(this, tr("图片格式错误"),
                             message, QMessageBox::Yes);
        qDebug() << "Format Error";
        return;
    }
    QString save_path = QFileDialog::getSaveFileName(
                this,
                tr("Save DTA file"),
                ".",
                tr("Image files(*.dta"));

    if (file.convert(save_path)){
        qDebug() << "Convert DTA file OK";
    }
    else{
        qDebug() << "Fail to convert DTA file";
    }
}
