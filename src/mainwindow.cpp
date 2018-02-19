/**
 *  @file mainwindow.cpp
 *  @brief MainWindow class implementation
 *  @author Svätopluk Hanzel (xhanze10), FIT VUT, 2BIT, a.y. 2016/2017
 */
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tableauwidget.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

#ifdef __ANDROID__
    this->setWindowState(this->windowState() ^ Qt::WindowFullScreen);
#else
    this->showMaximized();
#endif
    this->setWindowTitle("ICP Klondike - GUI version");
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionExit_triggered() {
    QApplication::quit();
}

void MainWindow::on_actionNew_game_triggered() {
    //delete all the labels from init screen
    while(QWidget* w = this->centralWidget()->findChild<QLabel*>()) {
        delete w;
    }

    if((this->games_opened = this->findChildren<TableauWidget*>().count()) >= 4) {
        QMessageBox msgBox;
        msgBox.setText("Maximum of 4 games is allowed");
        msgBox.exec();
        return;
    }

    QGridLayout* lay = (QGridLayout*)this->centralWidget()->layout();
    TableauWidget* game = new TableauWidget();
    lay->addWidget(game, this->games_opened / 2, this->games_opened % 2, 1, 1);
    game->initialize();
}

void MainWindow::on_actionLoad_triggered() {
    QString filename = QFileDialog::getOpenFileName(this, "Open game savefile", nullptr, tr("JSON files (*.json)"));
    if(filename == "") {
        return;
    }

    //delete all the labels from init screen
    while(QWidget* w = this->centralWidget()->findChild<QLabel*>()) {
        delete w;
    }

    if((this->games_opened = this->findChildren<TableauWidget*>().count()) >= 4) {
        QMessageBox msgBox;
        msgBox.setText("Maximum of 4 games is allowed");
        msgBox.exec();
        return;
    }

    QGridLayout* lay = (QGridLayout*)this->centralWidget()->layout();
    TableauWidget* game = new TableauWidget();
    lay->addWidget(game, this->games_opened / 2, this->games_opened % 2, 1, 1);
    game->load_from_file(filename);
}
