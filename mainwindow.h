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
        for (int i = 0; i < img.width(); i++)
            for (int j = 0; j < img.height(); j++)
            {
                int gray = qGray(img.pixel(i,j));
                gray /= 64;
                gray *= 64;
                img.setPixelColor(i, j, QColor(gray, gray, gray));
            }
        return img;
    }
    QImage convert2Bit1(const QString& imgPath, const QRgb rgb) {
        QImage img;
        if (!img.load(imgPath)) {
            return img;
        }
        for (int i = 0; i < img.width(); i++)
            for (int j = 0; j < img.height(); j++)
            {
                int gray = qGray(img.pixel(i,j));
                if (gray < 128)
                    img.setPixelColor(i, j, QColor(0, 0, 0));
                else
                    img.setPixelColor(i, j, rgb);
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
