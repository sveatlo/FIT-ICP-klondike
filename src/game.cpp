/**
 *  @file game.cpp
 *  @brief Game class implementation
 *  @author Svätopluk Hanzel (xhanze10), FIT VUT, 2BIT, a.y. 2016/2017
 */
#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <chrono>
#include <iostream>
#include <sstream>
#include "game.h"
#include "card.h"

#include <fstream>

using namespace std;

Game::Game() { }

Game::~Game() {
    delete this->heap;
    delete this->waste;
    for(int i = 0; i < FOUNDATIONS_COUNT; i++) {
        delete this->get_foundations()->at(i);
    }
    for(int i = 0; i < STACKS_COUNT; i++) {
        delete this->get_stacks()->at(i);
    }
}

void Game::initialize() {
    this->generate_decks();
    this->generate_cards();
}

void Game::generate_decks() {
    this->heap = new Deck(DeckType::Heap, 0);
    this->waste = new Deck(DeckType::Waste, 0);
    for(int i = 0; i < FOUNDATIONS_COUNT; i++) {
        this->get_foundations()->at(i) = new Deck(DeckType::Foundation, i);
    }
    for(int i = 0; i < STACKS_COUNT; i++) {
        this->get_stacks()->at(i) = new Deck(DeckType::Stack, i);
    }
}

void Game::generate_cards() {
    // Add all 52 cards to heap
    this->get_heap()->add_card(new Card(CardSuite::Hearts, CardRank::Ace), true);
    this->get_heap()->add_card(new Card(CardSuite::Hearts, CardRank::Two), true);
    this->get_heap()->add_card(new Card(CardSuite::Hearts, CardRank::Three), true);
    this->get_heap()->add_card(new Card(CardSuite::Hearts, CardRank::Four), true);
    this->get_heap()->add_card(new Card(CardSuite::Hearts, CardRank::Five), true);
    this->get_heap()->add_card(new Card(CardSuite::Hearts, CardRank::Six), true);
    this->get_heap()->add_card(new Card(CardSuite::Hearts, CardRank::Seven), true);
    this->get_heap()->add_card(new Card(CardSuite::Hearts, CardRank::Eight), true);
    this->get_heap()->add_card(new Card(CardSuite::Hearts, CardRank::Nine), true);
    this->get_heap()->add_card(new Card(CardSuite::Hearts, CardRank::Ten), true);
    this->get_heap()->add_card(new Card(CardSuite::Hearts, CardRank::Jack), true);
    this->get_heap()->add_card(new Card(CardSuite::Hearts, CardRank::Queen), true);
    this->get_heap()->add_card(new Card(CardSuite::Hearts, CardRank::King), true);

    this->get_heap()->add_card(new Card(CardSuite::Diamonds, CardRank::Ace), true);
    this->get_heap()->add_card(new Card(CardSuite::Diamonds, CardRank::Two), true);
    this->get_heap()->add_card(new Card(CardSuite::Diamonds, CardRank::Three), true);
    this->get_heap()->add_card(new Card(CardSuite::Diamonds, CardRank::Four), true);
    this->get_heap()->add_card(new Card(CardSuite::Diamonds, CardRank::Five), true);
    this->get_heap()->add_card(new Card(CardSuite::Diamonds, CardRank::Six), true);
    this->get_heap()->add_card(new Card(CardSuite::Diamonds, CardRank::Seven), true);
    this->get_heap()->add_card(new Card(CardSuite::Diamonds, CardRank::Eight), true);
    this->get_heap()->add_card(new Card(CardSuite::Diamonds, CardRank::Nine), true);
    this->get_heap()->add_card(new Card(CardSuite::Diamonds, CardRank::Ten), true);
    this->get_heap()->add_card(new Card(CardSuite::Diamonds, CardRank::Jack), true);
    this->get_heap()->add_card(new Card(CardSuite::Diamonds, CardRank::Queen), true);
    this->get_heap()->add_card(new Card(CardSuite::Diamonds, CardRank::King), true);

    this->get_heap()->add_card(new Card(CardSuite::Clubs, CardRank::Ace), true);
    this->get_heap()->add_card(new Card(CardSuite::Clubs, CardRank::Two), true);
    this->get_heap()->add_card(new Card(CardSuite::Clubs, CardRank::Three), true);
    this->get_heap()->add_card(new Card(CardSuite::Clubs, CardRank::Four), true);
    this->get_heap()->add_card(new Card(CardSuite::Clubs, CardRank::Five), true);
    this->get_heap()->add_card(new Card(CardSuite::Clubs, CardRank::Six), true);
    this->get_heap()->add_card(new Card(CardSuite::Clubs, CardRank::Seven), true);
    this->get_heap()->add_card(new Card(CardSuite::Clubs, CardRank::Eight), true);
    this->get_heap()->add_card(new Card(CardSuite::Clubs, CardRank::Nine), true);
    this->get_heap()->add_card(new Card(CardSuite::Clubs, CardRank::Ten), true);
    this->get_heap()->add_card(new Card(CardSuite::Clubs, CardRank::Jack), true);
    this->get_heap()->add_card(new Card(CardSuite::Clubs, CardRank::Queen), true);
    this->get_heap()->add_card(new Card(CardSuite::Clubs, CardRank::King), true);

    this->get_heap()->add_card(new Card(CardSuite::Spades, CardRank::Ace), true);
    this->get_heap()->add_card(new Card(CardSuite::Spades, CardRank::Two), true);
    this->get_heap()->add_card(new Card(CardSuite::Spades, CardRank::Three), true);
    this->get_heap()->add_card(new Card(CardSuite::Spades, CardRank::Four), true);
    this->get_heap()->add_card(new Card(CardSuite::Spades, CardRank::Five), true);
    this->get_heap()->add_card(new Card(CardSuite::Spades, CardRank::Six), true);
    this->get_heap()->add_card(new Card(CardSuite::Spades, CardRank::Seven), true);
    this->get_heap()->add_card(new Card(CardSuite::Spades, CardRank::Eight), true);
    this->get_heap()->add_card(new Card(CardSuite::Spades, CardRank::Nine), true);
    this->get_heap()->add_card(new Card(CardSuite::Spades, CardRank::Ten), true);
    this->get_heap()->add_card(new Card(CardSuite::Spades, CardRank::Jack), true);
    this->get_heap()->add_card(new Card(CardSuite::Spades, CardRank::Queen), true);
    this->get_heap()->add_card(new Card(CardSuite::Spades, CardRank::King), true);

    this->deal_cards();
}

void Game::deal_cards() {
    std::srand(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());

    // Shuffle the cards
    this->get_heap()->shuffle();

    // Divide cards to stacks 1-7
    for(int i = 0; i < 7; i++) {
        for(int j = i; j < 7; j++) {
            Card* card = this->get_heap()->get_last();
            if(i == j) {
                card->set_turned(true);
            }
            this->get_heap()->remove_last();
            Deck* stack = this->get_stacks()->at(j);
            stack->add_card(card, true);
        }
    }
}

void Game::game_move(GameMove move) {
    this->game_move(move, false);
}

void Game::game_move(GameMove move, bool force, bool new_turned, bool turn_new_last, bool save_move, bool is_undo) {
    // get the from deck
    Deck* deck_from = this->type_to_deck(std::get<0>(move.first), std::get<1>(move.first));
    // get the from deck
    Deck* deck_to = this->type_to_deck(std::get<0>(move.second), std::get<1>(move.second));

    // move it
    for(int i = std::get<2>(move.first); i >= 0; i--) {
        // get the card to move
        Card* card = deck_from->get_last(i);
        this->game_move(card, deck_from, deck_to, force, new_turned, turn_new_last, is_undo);
    }

    if(save_move) {
        this->moves.push_back(move);
    }
}

void Game::game_move(Card* card, Deck* deck_from, Deck* deck_to, bool force, bool new_turned, bool turn_new_last, bool is_undo) {
    if(!force && !card->is_turned() && deck_from != this->get_heap()) {
        throw "Cannot move an unturned card";
    }

    try {
        deck_to->add_card(card, force);
    } catch(...) {
        throw 1;
    }

    try {
        deck_from->remove_card(card);
    } catch(...) {
        deck_to->remove_card(card);
        throw 2;
    }


    // calculate score
    int move_score = 0;

    card->set_turned(new_turned);
    try {
        Card* new_last_card = deck_from->get_last();
        if(!new_last_card->is_turned()) {
            new_last_card->set_turned(turn_new_last);
            if(deck_from->get_type() == DeckType::Foundation) {
                move_score += 5;
            }
        }
    } catch(...) {
        // the deck is empty now
    }

    if(deck_from->get_type() == DeckType::Waste && deck_to->get_type() == DeckType::Stack) {
        move_score += 5;
    } else if(deck_from->get_type() == DeckType::Waste && deck_to->get_type() == DeckType::Foundation) {
        move_score += 10;
    } else if(deck_from->get_type() == DeckType::Stack && deck_to->get_type() == DeckType::Foundation) {
        move_score += 10;
    } else if(deck_from->get_type() == DeckType::Foundation && deck_to->get_type() == DeckType::Stack) {
        move_score += -15;
    }
    this->score += move_score * (is_undo ? -1 : 1);
    this->score = this->score < 0 ? 0 : this->score;
    this->update_score();

    this->check_win();
}

void Game::reveal() {
    try {
        this->game_move(std::make_pair(std::make_tuple(DeckType::Heap, 0, 0), std::make_tuple(DeckType::Waste, 0)), true, true, false);
    } catch (...) {
        this->reset_heap();
    }
}

void Game::reset_heap() {
    if(this->get_heap()->count() != 0) {
        throw "Heap not empty";
    }

    while(this->get_waste()->count() != 0) {
        this->game_move(this->get_waste()->get_last(), this->get_waste(), this->get_heap(), true, false, false);
    }
}


GameMove Game::reverse_move(GameMove move) {
    return std::make_pair(std::make_tuple(
                              std::get<0>(move.second),
                              std::get<1>(move.second),
                              std::get<2>(move.first)
                          ), std::make_tuple(
                              std::get<0>(move.first),
                              std::get<1>(move.first)
                          ));
}

GameMove Game::get_last_move() {
     return this->moves.last();
}

void Game::undo_last_move() {
    if(this->moves.count() <= 0) {
        throw "No previous moves";
    }


    GameMove m = this->get_last_move();
    this->moves.pop_back();
    GameMove rm = this->reverse_move(m);
    Deck* deck_to= this->type_to_deck(std::get<0>(rm.second), std::get<1>(rm.second));
    if(deck_to->count()) {
        deck_to->get_last()->set_turned(false);
    }
    this->game_move(rm, true, std::get<0>(rm.second) == DeckType::Heap ? false : true, true, false, true);
}

std::string Game::move_to_string(GameMove move) {
    string deck_from, deck_to;

    switch (std::get<0>(move.first)) {
        case DeckType::Waste:
            deck_from = "waste";
            break;
        case DeckType::Stack:
            deck_from = "stack";
            break;
        case DeckType::Foundation:
            deck_from = "foundation";
            break;
        case DeckType::Heap:
            deck_from = "heap";
            break;
    }

    switch (std::get<0>(move.second)) {
        case DeckType::Waste:
            deck_to = "waste";
            break;
        case DeckType::Stack:
            deck_to = "stack";
            break;
        case DeckType::Foundation:
            deck_to = "foundation";
            break;
        case DeckType::Heap:
            deck_to = "heap";
            break;
    }

    std::stringstream ss;
    ss << "move " << deck_from;
    if(std::get<0>(move.first) != DeckType::Waste) {
        ss << " " << std::get<1>(move.first) << " " << std::get<2>(move.first);
    }
    ss << " " << deck_to << " " << std::get<1>(move.second) << endl;

    return ss.str();
}

vector<GameMove> Game::hint() {
    std::vector<GameMove> moves;

    // Find any card, that goes to any foundation
    int i = -1;
    for(auto &foundation : *this->get_foundations()) {
        i++;
        if(foundation->count() == 0) {
            // this foundation is empty. Is there any Ace in any of the stacks or in the waste?
            if(this->get_waste()->count() > 0 && this->get_waste()->get_last()->get_rank() == CardRank::Ace) {
                // Found it...
                moves.push_back(std::make_pair(std::make_tuple(DeckType::Waste, 0, 0), std::make_tuple(DeckType::Foundation, i)));
            } else {
                int j = -1;
                for(auto &stack : *this->get_stacks()) {
                    j++;
                    if(stack->count() > 0 && stack->get_last()->get_rank() == CardRank::Ace) {
                        // Found it...
                        moves.push_back(std::make_pair(std::make_tuple(DeckType::Stack, j, 0), std::make_tuple(DeckType::Foundation, i)));
                    }
                }
            }
        } else {
            // foundation not empty. Is there, in any stack a card of the same suite with a rank of one higher?
            Card* last_foundation_card = foundation->get_last();
            if(this->get_waste()->count() > 0 && this->get_waste()->get_last()->get_suite() == last_foundation_card->get_suite() && this->get_waste()->get_last()->get_rank() == (CardRank)((int)last_foundation_card->get_rank() + 1)) {
                // Found it...
                moves.push_back(std::make_pair(std::make_tuple(DeckType::Waste, 0, 0), std::make_tuple(DeckType::Foundation, i)));
            } else {
                int j = -1;
                for(auto &stack : *this->get_stacks()) {
                    j++;
                    if(stack->count() <= 0) {
                        continue;
                    }
                    Card* last_stack_card = stack->get_last();
                    if(last_stack_card->get_suite() == last_foundation_card->get_suite() && last_stack_card->get_rank() == (CardRank)((int)last_foundation_card->get_rank() + 1)) {
                        // Found it...
                        moves.push_back(std::make_pair(std::make_tuple(DeckType::Stack, j, 0), std::make_tuple(DeckType::Foundation, i)));
                    }
                }
            }
        }
    }

    // No suitable card found for the foundations
    // Check stacks
    i = -1;
    for(auto stacks_it = this->get_stacks()->begin(); stacks_it != this->get_stacks()->end(); stacks_it++) {
        i++;
        Deck* stack = *stacks_it;

        CardColor color_required;
        CardRank rank_required;

        if(stack->count() == 0) {
            // TODO: Should find a King of any colour
            color_required = CardColor::Any;
            rank_required = CardRank::King;
        } else {
            Card* last_stack_card = stack->get_last();
            if(last_stack_card->get_rank() == CardRank::Ace) {
                continue;
            }
            // required color is different from current
            color_required = last_stack_card->get_color() == CardColor::Red ? CardColor::Black : CardColor::Red;
            // required rank is one smaller than current
            rank_required = (CardRank)((int)last_stack_card->get_rank() - 1);
        }

        // first, check the waste
        if(this->get_waste()->count() > 0 && this->get_waste()->get_last()->get_rank() == rank_required && this->get_waste()->get_last()->get_color() == color_required) {
            // Found it...
            moves.push_back(std::make_pair(std::make_tuple(DeckType::Waste, 0, 0), std::make_tuple(DeckType::Stack, i)));
        }

        int j = -1;
        for(auto inner_stacks_it = this->get_stacks()->begin(); inner_stacks_it != this->get_stacks()->end(); inner_stacks_it++) {
            j++;
            Deck* inner_stack = *inner_stacks_it;

            if(&inner_stack == &stack) {
                continue;
            }
            Card* found;
            int n;
            std::tie(found, n) = inner_stack->find_card(color_required, rank_required);
            if(found != nullptr && found->is_turned()) {
                // Found it...
                moves.push_back(std::make_pair(std::make_tuple(DeckType::Stack, j, n), std::make_tuple(DeckType::Stack, i)));
            }
        }
    }

    return moves;
}

void Game::print_game() {
    cout << "\033[1;37mScore: \033[0m" << this->score << endl;
    if(this->get_heap()->count() == 0) {
        cout << "Heap: Empty" << endl;
    } else {
        cout << "Heap : " << (this->get_heap()->count() == 0 ? "Empty" : "Not empty") << endl;
        // cout << "Heap (" << this->get_heap()->count() << "): " << this->get_heap()->to_string().c_str() << endl;
    }

    if(this->get_waste()->count() == 0) {
        cout << "Waste: Empty" << endl;
    } else {
        cout << "Waste : " << this->get_waste()->get_last()->to_string().c_str() << endl;
        // cout << "Waste (" << this->get_waste()->count() << "): " << this->get_waste()->to_string().c_str() << endl;
    }
    cout << endl;

    for(int i = 0; i < 4; i++) {
        if(this->get_foundations()->at(i)->count() == 0) {
            cout << "Foundation #" << i << ": Empty" << endl;
        } else {
            cout << "Foundation #" << i << " : " << this->get_foundations()->at(i)->get_last()->to_string().c_str() << endl;
            // cout << "Foundation #" << i << " (" << this->get_foundations()->at(i)->count() << "): " << this->get_foundations()->at(i)->to_string().c_str() << endl;
        }
    }
    cout << endl;

    for(int i = 0; i < 7; i++) {
        if(this->get_stacks()->at(i)->count() == 0) {
            cout << "Stack #" << i << ": Empty" << endl;
        } else {
            cout << "Stack #" << i << ": " << this->get_stacks()->at(i)->to_string().c_str() << endl;
        }
    }
}

Deck* Game::type_to_deck(DeckType type, int n) {
    switch (type) {
        case DeckType::Heap:
            return this->get_heap();
            break;
        case DeckType::Waste:
            return this->get_waste();
            break;
        case DeckType::Foundation:
            if(n < 0 && n > 3) {
                throw "No such deck";
            }
            return this->get_foundations()->at(n);
            break;
        case DeckType::Stack:
            if(n < 0 && n > 6) {
                throw "No such deck";
            }
            return this->get_stacks()->at(n);
            break;
        default:
            throw "No such deck";
            break;
    }
}

void Game::check_win() {
    if(this->have_won()) {
        this->celebrate();
    }
}

bool Game::have_won() {
    for(auto &foundation : *this->get_foundations()) {
        try {
            if(foundation->get_last()->get_rank() != CardRank::King) {
                return false;
            }
        } catch(...) {
            return false;
        }
    }

    return true;
}

void Game::celebrate() {
    std::cout << "             ___________" << std::endl;
    std::cout << "            '._==_==_=_.'" << std::endl;
    std::cout << "            .-\\:      /-." << std::endl;
    std::cout << "           | (|:.     |) |" << std::endl;
    std::cout << "            '-|:.     |-'" << std::endl;
    std::cout << "              \\::.    /" << std::endl;
    std::cout << "               '::. .'" << std::endl;
    std::cout << "                 ) (" << std::endl;
    std::cout << "               _.' '._" << std::endl;
    std::cout << "          ICP`\"\"\"\"\"\"\"`" << std::endl;
}

Deck* Game::get_heap() {
    return this->heap;
}

Deck* Game::get_waste() {
    return this->waste;
}

std::array<Deck*, 4>* Game::get_foundations() {
    return &this->foundations;
}

std::array<Deck*, 7>* Game::get_stacks() {
    return &this->stacks;
}

void Game::save_game(QString filename) {
    QFile saveFile(filename);
    if (!saveFile.open(QIODevice::WriteOnly)) {
        throw "Couldn't open save file.";
    }

    QJsonObject game;
    this->serialize(game);
    QJsonDocument saveDoc(game);
    saveFile.write(saveDoc.toJson());

}

void Game::serialize(QJsonObject &json) {
    QJsonObject heap;
    this->get_heap()->serialize(heap);
    json["heap"] = heap;

    QJsonObject waste;
    this->get_waste()->serialize(waste);
    json["waste"] = waste;

    QJsonArray foundations;
    for(auto &foundation : *this->get_foundations()) {
        QJsonObject foundation_json;
        foundation->serialize(foundation_json);
        foundations.append(foundation_json);
    }
    json["foundations"] = foundations;

    QJsonArray stacks;
    for(auto &stack : *this->get_stacks()) {
        QJsonObject stack_json;
        stack->serialize(stack_json);
        stacks.append(stack_json);
    }
    json["stacks"] = stacks;
}

void Game::load_from_file(QString filename) {
    QFile loadFile(filename);

    if (!loadFile.open(QIODevice::ReadOnly)) {
        throw "Couldn't open save file.";
        return;
    }

    QByteArray data = loadFile.readAll();

    QJsonDocument doc(QJsonDocument::fromJson(data));

    QJsonObject game_json = doc.object();
    this->load(game_json);
}

void Game::load(QJsonObject &json) {
    this->heap = Deck::load(json["heap"].toObject());
    this->waste = Deck::load(json["waste"].toObject());

    QJsonArray foundations = json["foundations"].toArray();
    if(foundations.size() != FOUNDATIONS_COUNT) {
        throw "Invalid file";
    }
    for (int i = 0; i < foundations.size(); i++) {
        QJsonObject foundation = foundations[i].toObject();
        this->get_foundations()->at(foundation["n"].toInt()) = Deck::load(foundation);
    }

    QJsonArray stacks = json["stacks"].toArray();
    if(stacks.size() != STACKS_COUNT) {
        throw "Invalid file";
    }
    for (int i = 0; i < stacks.size(); i++) {
        QJsonObject stack = stacks[i].toObject();
        this->get_stacks()->at(stack["n"].toInt()) = Deck::load(stack);
    }
}

void Game::update_score() { }
