/**
 *  @file main.cpp
 *  @brief Entry-point file
 *  @author Svätopluk Hanzel (xhanze10), FIT VUT, 2BIT, a.y. 2016/2017
 */
#ifdef KLONDIKE_CLI

#include <QCoreApplication>
#include "mainconsole.h"

#else

#include <QApplication>
#include "mainwindow.h"

#endif

int main(int argc, char *argv[]) {
#ifdef KLONDIKE_CLI
    QCoreApplication a(argc, argv);

    MainConsole c;
    c.repl();

    return 0;

    //return a.exec();
#else
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
#endif
}
