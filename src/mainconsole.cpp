/**
 *  @file mainconsole.cpp
 *  @brief MainConsole class implementation
 *  @author Svätopluk Hanzel (xhanze10), FIT VUT, 2BIT, a.y. 2016/2017
 */
#include <QDebug>
#include <iostream>
#include "mainconsole.h"
#ifdef _WIN32
#include <conio.h>
#else
#define clrscr(); cout << "\x1b[2J\x1b[1;1H" << flush;
#endif

using namespace std;

MainConsole::MainConsole(QObject *parent) : QObject(parent) { }
MainConsole::~MainConsole() { }

void MainConsole::repl() {
    clrscr();
    this->print_welcome_message();

    QTextStream qtin(stdin);
    QString command;
    while((command = qtin.readLine()) != "gthoh" && !qtin.atEnd()) {
        clrscr();
        QStringList results = command.split(" ");
        // remove all empty  elements from the list
        results.removeAll(" ");
        results.removeAll("");
        // check arguments count
        int res_count = results.count();
        if(res_count <= 0) {
            if(this->active_game != nullptr) {
                this->active_game->print_game();
            }
            goto get_input;
        }

        if(results[0] == "help") {
            // help
            this->print_help();
            goto get_input;
        } else if(results[0] == "games") {
            if(res_count <= 1 || (results[1] == "switch" && res_count <= 2)) {
                cout << "Invalid syntax" << endl;
                goto get_input;
            }

            if(results[1] == "new") {
                // games new
                this->switch_game(this->create_game());
                this->active_game->initialize();
                this->active_game->print_game();
            } else if(results[1] == "load") {
                if(res_count < 3) {
                    cout << "Invalid syntax" << endl;
                    goto get_input;
                }

                this->switch_game(this->create_game());
                try {
                    this->active_game->load_from_file(results[2]);
                    this->active_game->print_game();
                } catch(const char * err) {
                    qDebug() << "Error: " << err;
                }
            } else if(results[1] == "list") {
                // games list
                int i = 1;
                for(auto &game : this->games) {
                    cout << " * Game #" << i << (game == this->active_game ? " [active]" : "") << endl;
                    i++;
                }
            } else if(results[1] == "switch") {
                // games switch
                bool ok = false;
                int id = results[2].toInt(&ok, 10);
                if(!ok) {
                    cout << "Invalid game number" << endl;
                    goto get_input;
                }
                this->switch_game(id - 1);
            } else if(results[1] == "print") {
                // games print
                if(this->active_game == nullptr) {
                    cout << "No active game found" << endl;
                    goto get_input;
                }

                this->active_game->print_game();
            } else if(results[1] == "move") {
                // games move
                if(this->active_game == nullptr) {
                    cout << "No active game found" << endl;
                    goto get_input;
                }

                QStringList move_command;
                for(QStringList::iterator it = results.begin() + 2; it != results.end(); it++) {
                    move_command << *it;
                }

                try {
                    this->process_move_command(move_command);
                } catch(...) {
                    cout << "Invalid move" << endl;
                    goto get_input;
                }
            } else if(results[1] == "reveal") {
                if(this->active_game == nullptr) {
                    cout << "No active game found" << endl;
                    goto get_input;
                }

                try {
                    this->process_heap_reveal();
                } catch(const char* err) {
                    cout << "Invalid move: " << err << endl;
                    goto get_input;
                }
            } else if(results[1] == "hint") {
                if(this->active_game == nullptr) {
                    cout << "No active game found" << endl;
                    goto get_input;
                }

                this->process_hint_command();
            } else if(results[1] == "hint") {
                if(this->active_game == nullptr) {
                    cout << "No active game found" << endl;
                    goto get_input;
                }

                this->process_undo_command();
            } else if(results[1] == "save") {
                if(this->active_game == nullptr) {
                    cout << "No active game found" << endl;
                    goto get_input;
                }

                if(res_count < 3 ) {
                    cout << "Invalid syntax";
                    goto get_input;
                }

                this->process_save_command(results[2]);
            } else {
                cout << "Unknown command" << endl;
            }
        } else if(this->active_game != nullptr && results[0] == "print") {
            // (games) print
            this->active_game->print_game();
        } else if(this->active_game != nullptr && results[0] == "move") {
            QStringList move_command;
            for(QStringList::iterator it = results.begin() + 1; it != results.end(); it++) {
                move_command << *it;
            }

            try {
                this->process_move_command(move_command);
            } catch(...) {
                cout << "Invalid move" << endl;
                goto get_input;
            }
        } else if(this->active_game != nullptr && results[0] == "reveal") {
            try {
                this->process_heap_reveal();
            } catch(...) {
                cout << "Invalid move" << endl;
                goto get_input;
            }
        } else if(this->active_game != nullptr && results[0] == "hint") {
            this->process_hint_command();
        } else if(this->active_game != nullptr && results[0] == "undo") {
            this->process_undo_command();
        } else if(this->active_game != nullptr && results[0] == "save") {
            if(res_count < 2 ) {
                cout << "Invalid syntax";
                goto get_input;
            }
            this->process_save_command(results[1]);
        } else {
            cout << "Unknown command" << endl;
        }

get_input:
        cout << "\033[1;36m[ICP KLONDIKE]";
        if(this->active_game == nullptr) {
        } else {
            cout << "[GAME #" << this->active_game_id + 1 << "]";
        }
        cout << " > \033[0m";
    }

    for(auto &game : this->games) {
        delete game;
    }
    emit finished();
}

void MainConsole::process_move_command(QStringList &move_command) {
    int res_count = move_command.count();
    if(res_count != 3 && res_count != 5) {
        cout << "Invalid syntax" << endl;
        return;
    }


    QStringList::iterator current_command = move_command.begin();
    DeckType deck_from, deck_to;
    int deck_from_n, card_n, deck_to_n;
    bool ok = false;
    // get the deck from which to take a card
    if(*current_command == "waste" || *current_command == "w") {
        deck_from = DeckType::Waste;
        *current_command++;
        deck_from_n = 0;
        card_n = 0;
    } else {
        if(res_count != 5) {
            cout << "Invalid syntax" << endl;
            return;
        }

        if(*current_command == "foundation" || *current_command == "f") {
            deck_from = DeckType::Foundation;
        } else if(*current_command == "stack" || *current_command == "s") {
            deck_from = DeckType::Stack;
        } else {
            cout << "Invalid syntax" << endl;
            return;
        }
        *current_command++;

        deck_from_n = (*current_command).toInt(&ok, 10);
        if(!ok) {
            cout << "Invalid syntax: " << (*current_command).toStdString() << " is not a valid deck's number" << endl;
            return;
        }
        *current_command++;

        ok = false;
        card_n = (*current_command).toInt(&ok, 10);
        if(!ok) {
            cout << "Invalid syntax: " << (*current_command).toStdString() << " is not a valid card's number" << endl;
            return;
        }
        *current_command++;
    }

    if(*current_command == "stack" || *current_command == "s") {
        deck_to = DeckType::Stack;
    } else if(*current_command == "foundation" || *current_command == "f") {
        deck_to = DeckType::Foundation;
    } else {
        cout << "Invalid syntax: " << (*current_command).toStdString() << " is not a valid deck type to move a card to." << endl;
        return;
    }
    *current_command++;

    ok = false;
    deck_to_n = (*current_command).toInt(&ok, 10);
    if(!ok) {
        cout << "Invalid syntax: " << (*current_command).toStdString() << " is not a valid deck's number" << endl;
        return;
    }

    this->active_game->game_move(std::make_pair(std::make_tuple(deck_from, deck_from_n, card_n), std::make_tuple(deck_to, deck_to_n)));
    if(this->active_game->have_won()) {
        this->active_game = nullptr;
        delete this->games[this->active_game_id];
        this->games.removeAt(this->active_game_id);
        this->active_game_id = -1;
    } else {
        this->active_game->print_game();
    }
}

void MainConsole::process_heap_reveal() {
    this->active_game->reveal();
    this->active_game->print_game();
}

void MainConsole::process_hint_command() {
    try {
        this->active_game->print_game();
        cout << endl << "Possible moves: " << endl;
        std::vector<GameMove> moves = this->active_game->hint();
        if(moves.size() <= 0) {
            cout << "No hints available" << endl;
            return;
        }

        for(auto &hinted_move : moves) {
            cout << this->active_game->move_to_string(hinted_move);
        }

    } catch(const char* err) {
        cout << "Error: " << err << endl;
    } catch(int err) {
        cout << "Error: " << err << endl;
    } catch(...) {
        cout << "No hints available" << endl;
    }
}

void MainConsole::process_undo_command() {
    try {
        this->active_game->undo_last_move();
        this->active_game->print_game();
    } catch(const char* err) {
        cout << err << endl;
    }
}

void MainConsole::process_save_command(QString filename) {
    try {
        this->active_game->save_game(filename);
        cout << "Game saved to " << filename.toStdString() << endl;
    } catch(...) {
        cout << "Couldn't save file" << endl;
    }
}

void MainConsole::print_welcome_message() {
    cout << "██╗ ██████╗██████╗     ██╗  ██╗██╗      ██████╗ ███╗   ██╗██████╗ ██╗██╗  ██╗███████╗" << endl;
    cout << "██║██╔════╝██╔══██╗    ██║ ██╔╝██║     ██╔═══██╗████╗  ██║██╔══██╗██║██║ ██╔╝██╔════╝" << endl;
    cout << "██║██║     ██████╔╝    █████╔╝ ██║     ██║   ██║██╔██╗ ██║██║  ██║██║█████╔╝ █████╗  " << endl;
    cout << "██║██║     ██╔═══╝     ██╔═██╗ ██║     ██║   ██║██║╚██╗██║██║  ██║██║██╔═██╗ ██╔══╝  " << endl;
    cout << "██║╚██████╗██║         ██║  ██╗███████╗╚██████╔╝██║ ╚████║██████╔╝██║██║  ██╗███████╗" << endl;
    cout << "╚═╝ ╚═════╝╚═╝         ╚═╝  ╚═╝╚══════╝ ╚═════╝ ╚═╝  ╚═══╝╚═════╝ ╚═╝╚═╝  ╚═╝╚══════╝" << endl;
    cout << endl << endl;
    cout << "\033[1;36m[ICP KLONDIKE] >\033[0m ";
}

void MainConsole::print_help() {
    cout << "This is the console version of ICP Klondike game." << endl;
    cout << "It mainly serves as a demonstration of our super awesome OOP design, thus it's possibilities are a little bit limited." << endl;
    cout << "Available commands:" << endl;
    cout << "\tgames new" << endl
            << "\t\tCreates new game" << endl;
    cout << "\tgames load <filename>" << endl
            << "\t\tLoads new game from file" << endl;
    cout << "\tgames list" << endl
            << "\t\tList active games" << endl;
    cout << "\tgames switch <ID>" << endl
            << "\t\tSwitch to game with ID <ID>" << endl;
    cout << "\t(games) print <ID>" << endl
            << "\t\tPrints the current game's status" << endl;
    cout << "\t(games) reveal" << endl
            << "\t\tReveals heap's top card by moving it to waste. If heap is empty,`reveal` will reset it from the waste" << endl;
    cout << "\t(games) move <stack|foundation|waste> [X] [N] <stack|foundation> <Y>" << endl
            << "\t\tMoves the Nth card from stack/foundation n.X or waste to stack/foundation n.Y" << endl;
    cout << "\t(games) hint" << endl
            << "\t\tMove hint" << endl;
    cout << "\t(games) save <filename>" << endl
            << "\t\tSaves active game to file" << endl;
    cout << "\treveal" << endl
            << "\t\tReveals top card from heap to waste deck." << endl;
}

int MainConsole::create_game() {
    this->games.push_back(new Game());
    return this->games.size() - 1;
}

void MainConsole::switch_game(int ID) {
    try {
        this->active_game = this->games.at(ID);
    } catch(...) {
        cout << "No such game" << endl;
        return;
    }
    this->active_game_id = ID;
}
