/**
 *  @file deck.cpp
 *  @brief Deck class implementation
 *  @author Svätopluk Hanzel (xhanze10), FIT VUT, 2BIT, a.y. 2016/2017
 */
#include <QDebug>
#include <QJsonArray>
#include "deck.h"

Deck::Deck(DeckType type, int _n) {
    this->type = type;
    this->n = _n;
}

Deck::~Deck() {
    for(auto &item: *this->get_cards()) {
        delete item;
    }
}

DeckType Deck::get_type() {
    return this->type;
}

int Deck::get_n() {
    return this->n;
}

void Deck::add_card(Card* card) {
    this->add_card(card, false);
}

void Deck::add_card(Card *card, bool force) {
    if(force || this->can_add_card(card)) {
        this->get_cards()->push_back(card);
    } else {
        throw "Invalid move";
    }
}

void Deck::remove_card(Card* card) {
    int i = 0;
    for(auto it = this->get_cards()->begin(); it != this->get_cards()->end(); it++) {
        if((*it)->get_rank() == card->get_rank() && (*it)->get_suite() == card->get_suite()) {
            this->get_cards()->erase(it);
            return;
        }
        i++;
    }

    throw "No such card in this stack!!!";
}

Card* Deck::get_last() {
    return this->get_last(0);
}

Card* Deck::get_last(int n) {
    return this->count() == 0 ? throw "Empty" : *(this->get_cards()->rbegin() + n);
}

void Deck::remove_last() {
    this->get_cards()->pop_back();
}

std::pair<Card*, int> Deck::find_card(CardColor color, CardRank rank) {
    int i = 0;
    for(auto it = this->get_cards()->rbegin(); it != this->get_cards()->rend(); it++, i++) {
        if((color == CardColor::Any || (*it)->get_color() == color) && (*it)->get_rank() == rank) {
            // return if color and rank mathces the criteria
            return std::make_pair(*it, i);
        } else if(!(*it)->is_turned()) {
            // ignore this and any further cards if the card is not turned
            return std::make_pair(nullptr, i);
        }
    }

    return std::make_pair(nullptr, i);
}

int Deck::count() {
    return this->get_cards()->size();
}

void Deck::shuffle() {
    std::random_shuffle(this->get_cards()->begin(), this->get_cards()->end());
}

bool Deck::can_add_card(Card* card) {
    switch (this->type) {
        case DeckType::Heap:
            return false;
            break;
        case DeckType::Waste:
            return false;
            break;
        case DeckType::Foundation:
        {
            if(this->count() == 0) {
                // if foundation is empty, allow adding an Ace
                if(card->get_rank() == CardRank::Ace) {
                    return true;
                }

                return false;
            } else {
                // if foundation is no empty, allow adding a card of the same suite and a rank, which is one higher than the current top card
                Card* top_card = this->get_last();
                if(top_card->get_suite() == card->get_suite() && top_card->get_rank() == (CardRank)((int)card->get_rank() - 1)) {
                    return true;
                }

                return false;
            }

            break;
        }
        case DeckType::Stack:
        {
            if(this->count() == 0) {
                // stack's empty => only allow King
                if(card->get_rank() == CardRank::King) {
                    return true;
                }

                return false;
            } else {
                Card* top_card = this->cards.back();

                if(top_card->get_color() == card->get_color()) {
                    // colours must alternate
                    return false;
                } else if(top_card->get_rank() == (CardRank)((int)card->get_rank() + 1)) {
                    // top card's rank must be one higher than the card to be inserted
                    return true;
                }

                return false;
            }

            break;
        }
    }

    throw "The hell is the type of this deck?";
}

std::string Deck::to_string() {
    std::string res = "";

    for(auto &card : *this->get_cards()) {
        res += card->to_string() + ", ";
    }

    return res;
}

std::vector<Card*>* Deck::get_cards() {
    return &this->cards;
}

void Deck::serialize(QJsonObject &json) {
    json["type"] = (int)this->get_type();
    json["n"] = this->get_n();
    QJsonArray cards;
    for(auto &card : *this->get_cards()) {
        QJsonObject card_json;
        card->serialize(card_json);
        cards.append(card_json);
    }
    json["cards"] = cards;
}

Deck* Deck::load(QJsonObject json) {
    Deck* deck = new Deck((DeckType)json["type"].toInt(), json["n"].toInt());

    QJsonArray cards = json["cards"].toArray();
    for(int i = 0; i < cards.size(); i++) {
        deck->add_card(Card::load(cards[i].toObject()), true);
    }

    return deck;
}
