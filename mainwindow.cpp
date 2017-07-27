#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QDebug"
#include <QFileDialog>

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

    qDebug() << "Open file: " << filepath;

    // 读取图片并显示
    QImage image;
    if (!image.load(filepath))
    {
        qDebug() << "Can't open file: " << filepath;
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
    ui->label_value_color->setText((QString::number(image.format(), 10)));
}
