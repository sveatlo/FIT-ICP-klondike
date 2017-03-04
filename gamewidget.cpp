#include <QDebug>
#include "gamewidget.h"
#include "ui_gamewidget.h"

GameWidget::GameWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWidget)
{
    ui->setupUi(this);

    //set background
    QPalette pal = palette();

    // set background
    pal.setColor(QPalette::Background,  QColor::fromRgb(0, 123, 60, 255));
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    qInfo() << "New game initialized";
}

GameWidget::~GameWidget()
{
    delete ui;
}
