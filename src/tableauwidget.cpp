/**
 *  @file tableauwidget.cpp
 *  @brief TableauWidget class implementation
 *  @author Svätopluk Hanzel (xhanze10), FIT VUT, 2BIT, a.y. 2016/2017
 */
#include <sstream>
#include <QDebug>
#include <QFileDialog>
#include <QJsonArray>
#include <QToolBar>
#include <QMessageBox>
#include "tableauwidget.h"
#include "ui_tableauwidget.h"

using namespace std;

template <typename T>
std::string tmpl_to_string(T value) {
    std::ostringstream os ;
    os << value ;
    return os.str() ;
}

TableauWidget::TableauWidget(QWidget *parent) : QWidget(parent), ui(new Ui::TableauWidget) {
    ui->setupUi(this);

    //set background
    QPalette pal = palette();
    this->setAutoFillBackground(true);

     this->score_counter = this->findChild<QLCDNumber*>("score_counter");
}

TableauWidget::~TableauWidget() {
    delete ui;
}

void TableauWidget::initialize() {
    this->generate_decks();
    this->generate_cards();
}

void TableauWidget::generate_decks() {
    QHBoxLayout* top = this->findChild<QHBoxLayout*>("top");
    QHBoxLayout* main = this->findChild<QHBoxLayout*>("main");

    HeapWidget* heap  = new HeapWidget();
    heap->set_game(this);
    this->heap = heap;
    top->addWidget(heap);

    WasteWidget* waste = new WasteWidget();
    waste->set_game(this);
    this->waste  = waste;
    top->addWidget(waste);

    // add empty widget - TODO: make stretcher work
    top->addWidget(new QWidget());

    for(int i = 0; i < FOUNDATIONS_COUNT; i++) {
        FoundationWidget* widget = new FoundationWidget(i);
        widget->set_game(this);
        this->get_foundations()->at(i) = widget;
        top->addWidget(widget);
    }

    for(int i = 0; i < STACKS_COUNT; i++) {
        StackWidget* widget = new StackWidget(i);
        widget->set_game(this);
        this->get_stacks()->at(i) = widget;
        main->addWidget(widget);
    }
}

void TableauWidget::load(QJsonObject &json) {
    QHBoxLayout* top = this->findChild<QHBoxLayout*>("top");
    QHBoxLayout* main = this->findChild<QHBoxLayout*>("main");

    QJsonObject heap_json = json["heap"].toObject();
    HeapWidget* heap  = HeapWidget::load(heap_json);
    heap->set_game(this);
    this->heap = heap;
    top->addWidget(heap);

    QJsonObject waste_json = json["waste"].toObject();
    WasteWidget* waste  = WasteWidget::load(waste_json);
    waste->set_game(this);
    this->waste  = waste;
    top->addWidget(waste);

    // add empty widget - TODO: make stretcher work
    top->addWidget(new QWidget());

    QJsonArray foundations = json["foundations"].toArray();
    if(foundations.size() != FOUNDATIONS_COUNT) {
        throw "Invalid file";
    }
    for(int i = 0; i < FOUNDATIONS_COUNT; i++) {
        QJsonObject foundation = foundations[i].toObject();
        FoundationWidget* widget = FoundationWidget::load(foundation);
        widget->set_game(this);
        this->get_foundations()->at(foundation["n"].toInt()) = widget;
        top->addWidget(widget);
    }

    QJsonArray stacks = json["stacks"].toArray();
    if(stacks.size() != STACKS_COUNT) {
        throw "Invalid file";
    }
    for(int i = 0; i < STACKS_COUNT; i++) {
        QJsonObject stack = stacks[i].toObject();
        StackWidget* widget = StackWidget::load(stack);
        widget->set_game(this);
        this->get_stacks()->at(stack["n"].toInt()) = widget;
        main->addWidget(widget);
    }

}


void TableauWidget::generate_cards() {
    // Add all 52 cards to heap
    this->get_heap()->add_card(new CardWidget(CardSuite::Hearts, CardRank::Ace), true);
    this->get_heap()->add_card(new CardWidget(CardSuite::Hearts, CardRank::Two), true);
    this->get_heap()->add_card(new CardWidget(CardSuite::Hearts, CardRank::Three), true);
    this->get_heap()->add_card(new CardWidget(CardSuite::Hearts, CardRank::Four), true);
    this->get_heap()->add_card(new CardWidget(CardSuite::Hearts, CardRank::Five), true);
    this->get_heap()->add_card(new CardWidget(CardSuite::Hearts, CardRank::Six), true);
    this->get_heap()->add_card(new CardWidget(CardSuite::Hearts, CardRank::Seven), true);
    this->get_heap()->add_card(new CardWidget(CardSuite::Hearts, CardRank::Eight), true);
    this->get_heap()->add_card(new CardWidget(CardSuite::Hearts, CardRank::Nine), true);
    this->get_heap()->add_card(new CardWidget(CardSuite::Hearts, CardRank::Ten), true);
    this->get_heap()->add_card(new CardWidget(CardSuite::Hearts, CardRank::Jack), true);
    this->get_heap()->add_card(new CardWidget(CardSuite::Hearts, CardRank::Queen), true);
    this->get_heap()->add_card(new CardWidget(CardSuite::Hearts, CardRank::King), true);

    this->get_heap()->add_card(new CardWidget(CardSuite::Diamonds, CardRank::Ace), true);
    this->get_heap()->add_card(new CardWidget(CardSuite::Diamonds, CardRank::Two), true);
    this->get_heap()->add_card(new CardWidget(CardSuite::Diamonds, CardRank::Three), true);
    this->get_heap()->add_card(new CardWidget(CardSuite::Diamonds, CardRank::Four), true);
    this->get_heap()->add_card(new CardWidget(CardSuite::Diamonds, CardRank::Five), true);
    this->get_heap()->add_card(new CardWidget(CardSuite::Diamonds, CardRank::Six), true);
    this->get_heap()->add_card(new CardWidget(CardSuite::Diamonds, CardRank::Seven), true);
    this->get_heap()->add_card(new CardWidget(CardSuite::Diamonds, CardRank::Eight), true);
    this->get_heap()->add_card(new CardWidget(CardSuite::Diamonds, CardRank::Nine), true);
    this->get_heap()->add_card(new CardWidget(CardSuite::Diamonds, CardRank::Ten), true);
    this->get_heap()->add_card(new CardWidget(CardSuite::Diamonds, CardRank::Jack), true);
    this->get_heap()->add_card(new CardWidget(CardSuite::Diamonds, CardRank::Queen), true);
    this->get_heap()->add_card(new CardWidget(CardSuite::Diamonds, CardRank::King), true);

    this->get_heap()->add_card(new CardWidget(CardSuite::Clubs, CardRank::Ace), true);
    this->get_heap()->add_card(new CardWidget(CardSuite::Clubs, CardRank::Two), true);
    this->get_heap()->add_card(new CardWidget(CardSuite::Clubs, CardRank::Three), true);
    this->get_heap()->add_card(new CardWidget(CardSuite::Clubs, CardRank::Four), true);
    this->get_heap()->add_card(new CardWidget(CardSuite::Clubs, CardRank::Five), true);
    this->get_heap()->add_card(new CardWidget(CardSuite::Clubs, CardRank::Six), true);
    this->get_heap()->add_card(new CardWidget(CardSuite::Clubs, CardRank::Seven), true);
    this->get_heap()->add_card(new CardWidget(CardSuite::Clubs, CardRank::Eight), true);
    this->get_heap()->add_card(new CardWidget(CardSuite::Clubs, CardRank::Nine), true);
    this->get_heap()->add_card(new CardWidget(CardSuite::Clubs, CardRank::Ten), true);
    this->get_heap()->add_card(new CardWidget(CardSuite::Clubs, CardRank::Jack), true);
    this->get_heap()->add_card(new CardWidget(CardSuite::Clubs, CardRank::Queen), true);
    this->get_heap()->add_card(new CardWidget(CardSuite::Clubs, CardRank::King), true);

    this->get_heap()->add_card(new CardWidget(CardSuite::Spades, CardRank::Ace), true);
    this->get_heap()->add_card(new CardWidget(CardSuite::Spades, CardRank::Two), true);
    this->get_heap()->add_card(new CardWidget(CardSuite::Spades, CardRank::Three), true);
    this->get_heap()->add_card(new CardWidget(CardSuite::Spades, CardRank::Four), true);
    this->get_heap()->add_card(new CardWidget(CardSuite::Spades, CardRank::Five), true);
    this->get_heap()->add_card(new CardWidget(CardSuite::Spades, CardRank::Six), true);
    this->get_heap()->add_card(new CardWidget(CardSuite::Spades, CardRank::Seven), true);
    this->get_heap()->add_card(new CardWidget(CardSuite::Spades, CardRank::Eight), true);
    this->get_heap()->add_card(new CardWidget(CardSuite::Spades, CardRank::Nine), true);
    this->get_heap()->add_card(new CardWidget(CardSuite::Spades, CardRank::Ten), true);
    this->get_heap()->add_card(new CardWidget(CardSuite::Spades, CardRank::Jack), true);
    this->get_heap()->add_card(new CardWidget(CardSuite::Spades, CardRank::Queen), true);
    this->get_heap()->add_card(new CardWidget(CardSuite::Spades, CardRank::King), true);

    this->deal_cards();
}

std::string ordinary_to_string(int n) {
    return (n == 1 ? "1st" : (n == 2 ? "2nd" : (n == 3 ? "3rd" : tmpl_to_string(n) + "th")));
}

std::string TableauWidget::move_to_string(GameMove move) {
    std::string deck_from_str, deck_to_str;

    switch (std::get<0>(move.first)) {
        case DeckType::Waste:
            deck_from_str = "waste";
            break;
        case DeckType::Stack:
            deck_from_str = "stack";
            break;
        case DeckType::Foundation:
            deck_from_str = "foundation";
            break;
        case DeckType::Heap:
            deck_from_str = "heap";
            break;
    }

    switch (std::get<0>(move.second)) {
        case DeckType::Waste:
            deck_to_str = "waste";
            break;
        case DeckType::Stack:
            deck_to_str = "stack";
            break;
        case DeckType::Foundation:
            deck_to_str = "foundation";
            break;
        case DeckType::Heap:
            deck_to_str = "heap";
            break;
    }

    std::stringstream ss;
    int deck_from_n = std::get<1>(move.first) + 1;
    int deck_to_n = std::get<1>(move.second) + 1;
    Deck* deck_from = this->type_to_deck(std::get<0>(move.first), std::get<1>(move.first));
    Card* card = deck_from->get_last(std::get<2>(move.first));
    ss << "move <b>" << card->to_string(false, false) << "</b> from "
       << ((std::get<0>(move.first) == DeckType::Stack || std::get<0>(move.first) == DeckType::Foundation)
           ? ordinary_to_string(deck_from_n)
           : "")
       << " " << deck_from_str << " to "
       << ((std::get<0>(move.second) == DeckType::Stack || std::get<0>(move.second) == DeckType::Foundation)
           ? ordinary_to_string(deck_to_n)
           : "")
       << " " << deck_to_str << "<br>" << std::endl;

    return ss.str();
}


void TableauWidget::celebrate() {
    QMessageBox celebration_window;
    celebration_window.setWindowTitle("Congratulations!");
    celebration_window.setText("You have won");
    celebration_window.exec();
}


void TableauWidget::on_close_button_clicked() {
    delete this;
}

void TableauWidget::on_undo_button_clicked() {
    try {
        this->undo_last_move();
    } catch(const char* err) {
        qDebug() << err;
        QMessageBox hints_window;
        hints_window.setWindowTitle("Cannot undo");
        hints_window.setText("No previous moves");
        hints_window.exec();
    }
}

void TableauWidget::on_hint_button_clicked() {
    std::stringstream ss;

    try {
        std::vector<GameMove> moves = this->hint();
        if(moves.size() <= 0) {
            ss << "No hints available" << std::endl;
        }

        for(auto &hinted_move : moves) {
            ss << this->move_to_string(hinted_move);
        }

    } catch(const char* err) {
        ss << "Error: " << err << std::endl;
    } catch(int err) {
        ss << "Error: " << err << std::endl;
    } catch(...) {
        ss << "No hints available" << std::endl;
    }

    QMessageBox hints_window;
    hints_window.setWindowTitle("Possible moves");
    hints_window.setText(ss.str().c_str());
    hints_window.exec();
}

void TableauWidget::on_save_clicked() {
    QString filename = QFileDialog::getSaveFileName(this, "Save game", "untitled.json", tr("Game save (*.json)"));
    if(filename == "") {
        return;
    }

    try {
        this->save_game(filename);

        QMessageBox info_box;
        info_box.setWindowTitle("Game saved");
        info_box.setText("Game was saved to <b>" + filename + "</b>");
        info_box.exec();
    } catch(...) {
        QMessageBox info_box;
        info_box.setWindowTitle("Error");
        info_box.setText("An exception was thrown while saving the game");
        info_box.exec();
    }
}

void TableauWidget::update_score() {
    if(this->score_counter != nullptr) {
        this->score_counter->display(this->score);
    }
}
