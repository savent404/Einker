#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QDebug"
#include "QFileDialog"
#include "dta.h"
#include "QMessageBox"
#include "QGraphicsScene"

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

/**
 * @brief MainWindow::on_actionType1_triggered Open type 1
 */
void MainWindow::on_actionType1_triggered()
{
    convert_type = convert_type1;
    file_1 = QFileDialog::getOpenFileName(
                this,
                tr("Open File Type1"),
                "~/Pictures",
                tr("Image files(*.bmp *.jpeg *.jpg)"));
    if (file_1.isEmpty()) {
        return;
    }
    QImage img = convert2Bit2(file_1);
    if (img.isNull()) {
        return;
    }
    QGraphicsScene *scene = new QGraphicsScene;
    scene->addPixmap(QPixmap::fromImage(img));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
}

/**
 * @brief MainWindow::on_actionType2_triggered Open type 2
 */
void MainWindow::on_actionType2_triggered()
{
    convert_type = convert_type2;
    file_1 = QFileDialog::getOpenFileName(
                this,
                tr("Open File Type2 with Black"),
                "~/Pictures",
                tr("Image files(*.bmp *.jpeg *.jpg)"));
    if (file_1.isEmpty()) {
        return;
    }
    file_2 = QFileDialog::getOpenFileName(
                this,
                tr("Open File Type2 with Read"),
                "~/Pictures",
                tr("Image files(*.bmp *.jpeg *.jpg"));
    if (file_2.isEmpty()) {
        return;
    }
    QImage img1 = convert2Bit1(file_1, qRgb(0, 0, 0));
    QImage img2 = convert2Bit1(file_2, qRgb(200, 0, 0));
    if (img1.width() != img2.width() || img1.height() != img2.height()) {
        QMessageBox::warning(this, "Wrong Picture", "");
        return;
    }
    QImage img(img1.width(), img1.height(), QImage::Format_ARGB32);
    for (int i = 0; i < img.width(); i++)
        for (int j = 0; j < img.height(); j++) {
            if (img2.pixel(i, j) != qRgb(255,255,255))
                img.setPixel(i, j, img2.pixel(i,j));
            else if (img1.pixel(i, j) != qRgb(255,255,255))
                img.setPixel(i, j, img1.pixel(i,j));
            else
                img.setPixel(i, j, qRgb(255,255,255));
        }
    QGraphicsScene *scene = new QGraphicsScene;
    scene->addPixmap(QPixmap::fromImage(img));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
}

/**
 * @brief MainWindow::on_actionConvert_2_triggered Convert file
 */
void MainWindow::on_actionConvert_2_triggered()
{
    QString save_path;
    switch (convert_type) {
    case convert_type1:{
        save_path = QFileDialog::getSaveFileName(this,
                                                 "Save File Path",
                                                 "./demo.dta",
                                                 "Image files(*.dta)");
        if (save_path.isEmpty())
            return;
        QImage img = convert2Bit2(file_1);
        if ((img.width() == 600 && img.height() == 800) ||
                (img.width() == 800 && img.height() == 600)) {

        } else {
            QMessageBox::warning(this, "Wrong size of Image", "Wrong size of Image");
            return;
        }
        auto func = [](int index) {
            index /= 64;
            return index & 3;
        };
        QFile file(save_path);
        file.open(QFile::WriteOnly);
        file.seek(32);
        int cnt = 0;
        uint8_t buf = 0;
//        for (int i = 0; i < img.width(); i++) {
//            for (int j = 0; j < img.height(); j++) {
        for (int j = 0; j < img.height(); j++) {
            for (int i = 0; i < img.width(); i++) {
                buf <<= 2;
                buf |= func(img.pixelIndex(i, j));
                if (++cnt >= 4) {
                    cnt = 0;
                    file.write((const char*)&buf, 1);
                    buf = 0;
                }
            }
        }
        file.close();
        break;
    }
    case convert_type2:{
        save_path = QFileDialog::getSaveFileName(this,
                                                 "Save File Path",
                                                 "./demo.atd",
                                                 "Image files(*.atd");
        if (save_path.isEmpty())
            return;

        auto func = [](QImage img, int i, int j) {
            if (img.pixel(i, j) != qRgb(255,255,255)) {
                return 1;
            } else {
                return 0;
            }
        };

        QImage img1 = convert2Bit1(file_1, qRgb(0, 0, 0));
        QImage img2 = convert2Bit1(file_2, qRgb(255,0,0));
        if (img1.width() != img2.width() ||
            img1.height() != img2.height() ||
            !((img1.width() == 300 && img1.height() == 400) ||
            (img1.height() == 300 && img1.width() == 400))) {
            QMessageBox::warning(this, "Wrong size of Image", "Wrong size of Image");
            return;
        }
        QFile file(save_path);
        file.open(QFile::WriteOnly);
        int cnt = 0;
        uint8_t buf = 0;

        if (img1.height() > img1.height())
        {
            for (int i = 0; i < img1.height(); i++) {
                for (int j = 0; j < img1.width(); j++) {
                    buf <<= 1;
                    buf |= func(img1, j, i);
                    if (++cnt >= 8) {
                        cnt = 0;
                        file.write((const char*)&buf, 1);
                        buf = 0;
                    }
                }
            }
            for (int i = 0; i < img1.height(); i++) {
                for (int j = 0; j < img1.width(); j++) {
                    buf <<= 1;
                    buf |= func(img2, j, i);
                    if (++cnt >= 8) {
                        cnt = 0;
                        file.write((const char*)&buf, 1);
                        buf = 0;
                    }
                }
            }
        }
        else
        {
            for (int i = 0; i < img1.width(); i++) {
                for (int j = 0; j < img1.height(); j++) {
                    buf <<= 1;
                    buf |= func(img1, i, j);
                    if (++cnt >= 8) {
                        cnt = 0;
                        file.write((const char*)&buf, 1);
                        buf = 0;
                    }
                }
            }
            for (int i = 0; i < img1.width(); i++) {
                for (int j = 0; j < img1.height(); j++) {
                    buf <<= 1;
                    buf |= func(img2, i, j);
                    if (++cnt >= 8) {
                        cnt = 0;
                        file.write((const char*)&buf, 1);
                        buf = 0;
                    }
                }
            }
        }

        file.close();
        break;
    }
    }
}
