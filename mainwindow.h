#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QGraphicsScene"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    enum {
        convert_type1,
        convert_type2,
    } convert_type;
    QString file_1;
    QString file_2;

    QImage convert2Bit2(const QString& imgPath) {
        QImage img;
        if (!img.load(imgPath)) {
            return img;
        }
        img = img.convertToFormat(QImage::Format_Indexed8);
        img.setColorCount(256);
        for (int i = 0; i < 256; i++) {
            int c = (i/64)*64;
            img.setColor(i, qRgb(c, c, c));
        }
        return img;
    }
    QImage convert2Bit1(const QString& imgPath, const QRgb rgb) {
        QImage img;
        if (!img.load(imgPath)) {
            return img;
        }
        img = img.convertToFormat(QImage::Format_Indexed8);
        img.setColorCount(256);
        for (int i = 0; i < 256; i++) {
            if (i < 128) {
                img.setColor(i, qRgb(255,255,255));
            } else {
                img.setColor(i, rgb);
            }
        }
        return img;
    }

private slots:
    void on_actionType1_triggered();

    void on_actionType2_triggered();

    void on_actionConvert_2_triggered();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
