/**
 *  @file mainwindow.h
 *  @brief MainWindow class declaration
 *  @author Svätopluk Hanzel (xhanze10), FIT VUT, 2BIT, a.y. 2016/2017
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    int games_opened = 0;
    Ui::MainWindow *ui;

private slots:
    void on_actionExit_triggered();

    void on_actionNew_game_triggered();
    void on_actionLoad_triggered();
};

#endif // MAINWINDOW_H
