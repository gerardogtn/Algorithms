#include "prismarectangular.h"
#include "ui_prismarectangular.h"
#include <QMessageBox>
#include <math.h>

PrismaRectangular::PrismaRectangular(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PrismaRectangular)
{
  centerX = width()/2;
  centerY = height()/2;
  QTransform center;
  center.translate(centerX,centerY);
  transforms.push_back(center);
  ui->setupUi(this);
}

PrismaRectangular::~PrismaRectangular()
{
  delete ui;
}

void PrismaRectangular::paintEvent(QPaintEvent *e) {
  QPainter painter(this);
  QPen pointPen(Qt::black);
  pointPen.setWidth(2);
  painter.setPen(pointPen);

  if(dibujaPrismaRectangular) {
    for(int i= 0;i<transforms.size();++i) {
      painter.setTransform(transforms[i],true);
      drawPrismRect(painter);
    }
  }
}

void PrismaRectangular::drawPrismRect(QPainter &painter)
{
 int x0 = 0;
 int y0 = 50;
 int x1 = 50;
 int y1 = 50;
 int x2 = 0;
 int y2 = -100;
 int x3 = 50;
 int y3 = -100;
 int x4 = x0+30;
 int y4 = y0-50;
 int x5 = x1+30;
 int y5 = y1-50;
 int x6 = x2+30;
 int y6 = y2-50;
 int x7 = x3+30;
 int y7 = y3-50;

 painter.drawLine(x0,y0,x1,y1);
 painter.drawLine(x2,y2,x3,y3);
 painter.drawLine(x2,y2,x0,y0);
 painter.drawLine(x3,y3,x1,y1);
 painter.drawLine(x4,y4,x5,y5);
 painter.drawLine(x6,y6,x7,y7);
 painter.drawLine(x6,y6,x4,y4);
 painter.drawLine(x7,y7,x5,y5);

 painter.drawLine(x0,y0,x4,y4);
 painter.drawLine(x1,y1,x5,y5);
 painter.drawLine(x2,y2,x6,y6);
 painter.drawLine(x3,y3,x7,y7);
}

// REQUIRES: None
// MODIFIES: this.
// EFFECTS:  Resets graphics.
void PrismaRectangular::on_pushButton_clicked(){
  dibujaPrismaRectangular = !dibujaPrismaRectangular;
  transforms.clear();
  QTransform center;
  center.translate(centerX,centerY);
  transforms.push_back(center);
  update();
}

// REQUIRES: None.
// MODIFIES: this.
// EFFECTS:  Performs a 60˚ clockwise rotation
void PrismaRectangular::on_pushButton_5_clicked(){
  QTransform rotate;
  rotate.rotate(60);
  transforms.push_back(rotate);
  update();
}

// REQUIRES: None.
// MODIFIES: this.
// EFFECTS: Performs a 2x zoom-in
void PrismaRectangular::on_pushButton_4_clicked(){
  QTransform zoomIn;
  zoomIn.scale(2,2);
  transforms.push_back(zoomIn);
  update();
}

// REQUIRES: None.
// MODIFIES: this.
// EFFECTS: Performs a 2x zoom-out
void PrismaRectangular::on_pushButton_3_clicked(){
  QTransform zoomOut;
  zoomOut.scale(0.5,0.5);
  transforms.push_back(zoomOut);
  update();
}

// REQUIRES: None.
// MODIFIES: this.
// EFFECTS:  Performs translation on values in textboxes.
void PrismaRectangular::on_pushButton_2_clicked(){
  QString xStr = ui->transX->toPlainText();
  QString yStr = ui->transY->toPlainText();

  if(!xStr.isEmpty() && !yStr.isEmpty()) {
    int _xStr = xStr.toInt();
    int _yStr = yStr.toInt();

    QTransform translate;
    translate.translate(_xStr, _yStr);
    transforms.push_back(translate);;
  } else {
    QMessageBox msgBox;
    msgBox.setText("Set translation values");
    msgBox.exec();
  }
  update();
}

// REQUIRES: None.
// MODIFIES: this.
// EFFECTS:  Performs a horizontal reflection.
void PrismaRectangular::on_pushButton_6_clicked(){
  QTransform reflect;
  reflect.scale(-1,1);
  transforms.push_back(reflect);
  update();
}

// REQUIRES: None.
// MODIFIES: this.
// EFFECTS:  Performs a vertical reflection.
void PrismaRectangular::on_pushButton_7_clicked(){
  QTransform reflect;
  reflect.scale(1,-1);
  transforms.push_back(reflect);
  update();
}
