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
    int_fast8_t games_opened = 0;

private slots:
    void on_actionExit_triggered();

    void on_actionNew_game_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
