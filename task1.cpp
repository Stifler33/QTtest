#include <QApplication>
#include <QPushButton>
#include <Qslider>
#include <QspinBox>
#include <QTimer>
#include <iostream>
#include <QPixmap>
#include <QPaintEvent>
#include <QPainter>
#include <QStyle>
#include <QVBoxLayout>
class MainWidget: public QWidget
{
public:
    MainWidget(QWidget *parent);
    void paintEvent(QPaintEvent *event) override;
    void setImage(int num);
private:
    QPixmap image1;
    QPixmap image2;
    QPixmap image3;
    QPixmap current;
};
MainWidget::MainWidget(QWidget *parent) {
    setParent(parent);
    image1 = QPixmap("C:\\Users\\bagi3\\Pictures\\1.png");
    image2 = QPixmap("C:\\Users\\bagi3\\Pictures\\2.png");
    image3 = QPixmap("C:\\Users\\bagi3\\Pictures\\3.png");
    current = image1;
    setGeometry(current.rect());
    setFixedSize(86,84);
}

void MainWidget::setImage(int num) {
    if (num >= 0 && num <= 30){
        current = image1;
        update();
    }
    if (num > 30 && num <= 60){
        current = image2;
        update();
    }
    if (num > 60 && num <= 99){
        current = image3;
        update();
    }
}

void MainWidget::paintEvent(QPaintEvent *event) {
    QPainter parent(this);
    parent.drawPixmap(event->rect(), current);
}
int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    QApplication::setStyle("fusion");
    QWidget *windows = new QWidget;
    MainWidget main(windows);
    auto *slider = new QSlider(windows);
    auto *spinbox = new QSpinBox(windows);
    slider->setOrientation(Qt::Horizontal);
    auto *layout = new QVBoxLayout(windows);
    windows->resize(100,160);
    windows->setMinimumSize(100,160);
    layout->addWidget(&main);
    layout->addWidget(spinbox);
    layout->addWidget(slider);
    QObject::connect(slider, &QSlider::valueChanged, spinbox, &QSpinBox::setValue);
    QObject::connect(slider, &QSlider::valueChanged, [&main](int newValue){main.setImage(newValue);});
    windows->show();
    app.exec();
}