#include "arco.h"
#include "ui_arco.h"
#include <QMessageBox>
#include <math.h>

#define PI 3.14159265

arco::arco(QWidget *parent) :QDialog(parent), ui(new Ui::arco) {
  centerX = width()/2;
  centerY = height()/2;
  QTransform center;
  center.translate(centerX,centerY);
  transforms.push_back(center);
  ui->setupUi(this);
}


arco::~arco(){
  delete ui;
}

void arco::paintEvent(QPaintEvent *e){
  QPainter painter(this);
  QPen pointPen(Qt::black);
  pointPen.setWidth(2);
  painter.setPen(pointPen);

  if (drawArcArco){
    QString radioStr = ui->radioTxt->toPlainText();
    QString anguloStr = ui->angulosTxt->toPlainText();

    if (!radioStr.isEmpty() && !anguloStr.isEmpty()) {
      angulo = anguloStr.toInt();
      radio = radioStr.toInt();
      for(int i=0; i<transforms.size(); ++i){
        painter.setTransform(transforms[i],true);
        drawArc(angulo, radio,painter);
     }
    }
  }
}

void arco::drawArc(int angulo, int radio, QPainter &painter){
  int x = 0;
  int y = radio;
  double p = 5.0/4.0-y;

  int maxx = 0;
  int maxy = 0;

  int oct = (angulo - (angulo % 45)) / 45;
  double limit1 = tan((90.0 - (angulo % 90)) * PI / 180.0) * x;
  double limit2 = tan((45.0 + (angulo % 45)) * PI / 180.0) * x;

  if (oct > 0 || (oct == 0 && y > limit1))
      painter.drawPoint(maxx+x,maxy-y);
  if (oct > 1 || (oct == 1 && y <= limit2))
      painter.drawPoint(maxx+y,maxy-x);
  if (oct > 2 || (oct == 2 && y > limit1))
      painter.drawPoint(maxx+y,maxy+x);
  if (oct > 3 || (oct == 3 && y <= limit2))
      painter.drawPoint(maxx+x,maxy+y);
  if (oct > 4 || (oct == 4 && y > limit1))
      painter.drawPoint(maxx-x,maxy+y);
  if (oct > 5 || (oct == 5 && y <= limit2))
      painter.drawPoint(maxx-y,maxy+x);
  if (oct > 6 || (oct == 6 && y > limit1))
      painter.drawPoint(maxx-y,maxy-x);
  if (oct > 7 || (oct == 7 && y <= limit2))
      painter.drawPoint(maxx-x,maxy-y);

  while(y > x){
    if(p < 0){
      p += 2.0 * x + 3.0;
    } else {
      p += 2.0 * (x - y) + 5.0;
      y--;
    }
    x++;

    int maxx = 0;
    int maxy = 0;

    int oct = (angulo - (angulo % 45)) / 45;
    double limit1 = tan((90.0 - (angulo % 90)) * PI / 180.0) * x;
    double limit2 = tan((45.0 + (angulo % 45)) * PI / 180.0) * x;

    if (oct > 0 || (oct == 0 && y > limit1))
        painter.drawPoint(maxx+x,maxy-y);
    if (oct > 1 || (oct == 1 && y <= limit2))
        painter.drawPoint(maxx+y,maxy-x);
    if (oct > 2 || (oct == 2 && y > limit1))
        painter.drawPoint(maxx+y,maxy+x);
    if (oct > 3 || (oct == 3 && y <= limit2))
        painter.drawPoint(maxx+x,maxy+y);
    if (oct > 4 || (oct == 4 && y > limit1))
        painter.drawPoint(maxx-x,maxy+y);
    if (oct > 5 || (oct == 5 && y <= limit2))
        painter.drawPoint(maxx-y,maxy+x);
    if (oct > 6 || (oct == 6 && y > limit1))
        painter.drawPoint(maxx-y,maxy-x);
    if (oct > 7 || (oct == 7 && y <= limit2))
        painter.drawPoint(maxx-x,maxy-y);
  }
}


// REQUIRES: None
// MODIFIES: this.
// EFFECTS:  Resets graphics.
void arco::on_pushButton_clicked() {
  QString r = ui->radioTxt->toPlainText();
  QString a = ui->angulosTxt->toPlainText();
  if(r.isEmpty() && a.isEmpty()) {
    QMessageBox msgBox;
    msgBox.setText("Set radius and angle");
    msgBox.exec();
  }
  else if (r.isEmpty()) {
    QMessageBox msgBox;
    msgBox.setText("Set radius");
    msgBox.exec();
  }
  else if (a.isEmpty()) {
    QMessageBox msgBox;
    msgBox.setText("Set angle");
    msgBox.exec();
  }
  drawArc = !drawArc;
  transforms.clear();
  QTransform center;
  center.translate(centerX,centerY);
  transforms.push_back(center);
  update();
}

// REQUIRES: None.
// MODIFIES: this.
// EFFECTS:  Performs a 60˚ clockwise rotation
void arco::on_pushButton_5_clicked() {
  QTransform rotate;
  rotate.rotate(60);
  transforms.push_back(rotate);
  update();
}

// REQUIRES: None.
// MODIFIES: this.
// EFFECTS: Performs a 2x zoom-in
void arco::on_pushButton_4_clicked() {
  QTransform zoomIn;
  zoomIn.scale(2,2);
  transforms.push_back(zoomIn);
  update();
}

// REQUIRES: None.
// MODIFIES: this.
// EFFECTS: Performs a 2x zoom-out
void arco::on_pushButton_3_clicked(){
  QTransform zoomOut;
  zoomOut.scale(0.5,0.5);
  transforms.push_back(zoomOut);
  update();
}


// REQUIRES: None.
// MODIFIES: this.
// EFFECTS:  Performs translation on values in textboxes.
void arco::on_pushButton_2_clicked() {
  QString xStr = ui->transX->toPlainText();
  QString yStr = ui->transY->toPlainText();


  if(!xStr.isEmpty() && !yStr.isEmpty()) {
    int _xStr = xStr.toInt();
    int _yStr = yStr.toInt();

    QTransform translate;
    translate.translate(_xStr, _yStr);
    transforms.push_back(translate);
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
void arco::on_pushButton_6_clicked() {
  QTransform reflect;
  reflect.scale(-1,1);
  transforms.push_back(reflect);
  update();
}

// REQUIRES: None.
// MODIFIES: this.
// EFFECTS:  Performs a vertical reflection.
void arco::on_pushButton_7_clicked() {
  QTransform reflect;
  reflect.scale(1,-1);
  transforms.push_back(reflect);
  update();
}
