#include <QMessageBox>
#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamewidget.h"

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

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionNew_game_triggered()
{
    if(this->games_opened >= 4) {
        QMessageBox msgBox;
        msgBox.setText("Maximum of 4 games is allowed");
        msgBox.exec();
        return;
    }

    //delete all the labels from init screen
    while(QWidget* w = this->centralWidget()->findChild<QLabel*>()) {
        delete w;
    }

    GameWidget* game = new GameWidget();
    QGridLayout* lay = (QGridLayout*)this->centralWidget()->layout();
    lay->addWidget(game, this->games_opened / 2, this->games_opened % 2, 1, 1);


    this->games_opened++;
}
