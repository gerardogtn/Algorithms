#ifndef PRISMARECTANGULAR_H
#define PRISMARECTANGULAR_H

#include <QDialog>
#include <QtGui>
#include <QtCore>

namespace Ui {
class PrismaRectangular;
}

class PrismaRectangular : public QDialog
{
    Q_OBJECT

public:
    explicit PrismaRectangular(QWidget *parent = 0);
    ~PrismaRectangular();

protected:
    void paintEvent(QPaintEvent *e);
    void drawPrismRect(QPainter & painter);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();

private:
    Ui::PrismaRectangular *ui;
    bool dibujaPrismaRectangular = false;
    double centerX;
    double centerY;
    QVector<QTransform> transforms;
};

#endif // PRISMARECTANGULAR_H
