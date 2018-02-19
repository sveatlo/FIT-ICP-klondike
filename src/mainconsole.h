/**
 *  @file mainconsole.h
 *  @brief MainConsole class declaration
 *  @author Svätopluk Hanzel (xhanze10), FIT VUT, 2BIT, a.y. 2016/2017
 */
#ifndef MAINCONSOLE_H
#define MAINCONSOLE_H

#include <QObject>
#include <QString>
#include <vector>
#include "decktype.h"
#include "game.h"

class MainConsole : public QObject {
    Q_OBJECT
public:
    MainConsole(QObject *parent = 0);
    ~MainConsole();

    void repl();

private:
    QList<Game*> games;
    int active_game_id;
    Game* active_game = nullptr;

    void print_welcome_message();
    void print_help();
    void process_move_command(QStringList&);
    void process_heap_reveal();
    void process_hint_command();
    void process_undo_command();
    void process_save_command(QString filename);
    int create_game();
    void switch_game(int ID);


signals:
    void finished();
};

#endif // MAINCONSOLE_H
