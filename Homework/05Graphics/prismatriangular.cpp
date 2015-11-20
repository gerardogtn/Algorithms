#include "prismatriangular.h"
#include "ui_prismatriangular.h"
#include <QMessageBox>
#include <math.h>

bool dibujaPrismaTriangular = false;

prismaTriangular::prismaTriangular(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::prismaTriangular){
  centerX = width()/2;
  centerY = height()/2;
  QTransform center;
  center.translate(centerX,centerY);
  transforms.push_back(center);
  ui->setupUi(this);
}


prismaTriangular::~prismaTriangular(){
  delete ui;
}

void prismaTriangular::paintEvent(QPaintEvent *e){
  QPainter painter(this);
  QPen pointPen(Qt::black);
  pointPen.setWidth(2);
  painter.setPen(pointPen);

  if(dibujaPrismaTriangular) {
    for(int i=0; i<transforms.size(); ++i) {
      painter.setTransform(transforms[i],true);
      drawPrismTriangle(painter);
    }
  }
}
void prismaTriangular::drawPrismTriangle(QPainter &painter){
  int x1 = 0;
  int y1 = -50;
  int x2 = -25;
  int y2 = -70;
  int x3 = 25;
  int y3 = -70;
  int _x1 = 0;
  int _y1 = -50+50;
  int _x2 = -25;
  int _y2 = -70+50;
  int _x3 = 25;
  int _y3 = -70+50;


  painter.drawLine(x1,y1,x2,y2);
  painter.drawLine(x1,y1,x3,y3);
  painter.drawLine(x2,y2,x3,y3);
  painter.drawLine(_x1,_y1,_x2,_y2);
  painter.drawLine(_x1,_y1,_x3,_y3);
  painter.drawLine(_x2,_y2,_x3,_y3);
  painter.drawLine(x1,y1,_x1,_y1);
  painter.drawLine(x2,y2,_x2,_y2);
  painter.drawLine(_x3,_y3,x3,y3);
}

// REQUIRES: None
// MODIFIES: this.
// EFFECTS:  Resets graphics.
void prismaTriangular::on_pushButton_clicked(){
  dibujaPrismaTriangular = !dibujaPrismaTriangular;
  transforms.clear();
  QTransform center;
  center.translate(centerX,centerY);
  transforms.push_back(center);
  update();
}

// REQUIRES: None.
// MODIFIES: this.
// EFFECTS:  Performs a 60˚ clockwise rotation
void prismaTriangular::on_pushButton_5_clicked(){
  QTransform rotate;
  rotate.rotate(60);
  transforms.push_back(rotate);
  update();
}

// REQUIRES: None.
// MODIFIES: this.
// EFFECTS: Performs a 2x zoom-in
void prismaTriangular::on_pushButton_4_clicked(){
  QTransform zoomIn;
  zoomIn.scale(2,2);
  transforms.push_back(zoomIn);
  update();
}

// REQUIRES: None.
// MODIFIES: this.
// EFFECTS: Performs a 2x zoom-out
void prismaTriangular::on_pushButton_3_clicked(){
  QTransform zoomOut;
  zoomOut.scale(0.5,0.5);
  transforms.push_back(zoomOut);
  update();
}

// REQUIRES: None.
// MODIFIES: this.
// EFFECTS:  Performs translation on values in textboxes.
void prismaTriangular::on_pushButton_2_clicked(){
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
void prismaTriangular::on_pushButton_6_clicked(){
  QTransform reflect;
  reflect.scale(-1,1);
  transforms.push_back(reflect);
  update();
}

// REQUIRES: None.
// MODIFIES: this.
// EFFECTS:  Performs a vertical reflection.
void prismaTriangular::on_pushButton_7_clicked(){
  QTransform reflect;
  reflect.scale(1,-1);
  transforms.push_back(reflect);
  update();
}
