/**
 *  @file card.cpp
 *  @brief Card class implementation
 *  @author Svätopluk Hanzel (xhanze10), FIT VUT, 2BIT, a.y. 2016/2017
 */
#include <QDebug>
#include <sstream>
#include "card.h"

using namespace std;

template <typename T>
std::string tmpl_to_string(T value) {
    std::ostringstream os ;
    os << value ;
    return os.str() ;
}

Card::Card(CardSuite _suite, CardRank _rank) {
    this->suite = _suite;
    this->rank = _rank;
}

Card::~Card() { }

CardColor Card::get_color() {
    if(this->suite == CardSuite::Diamonds || this->suite == CardSuite::Hearts) {
        return CardColor::Red;
    } else {
        return CardColor::Black;
    }
}

CardSuite Card::get_suite() {
    return this->suite;
}

CardRank Card::get_rank() {
    return this->rank;
}

std::string Card::to_string(bool show_unturned, bool colored) {
    if(this->turned == false && !show_unturned) {
        return "---";
    }

    std::string card_string = "";
    if(colored) {
        card_string = this->get_color() == CardColor::Red ? "\033[1;31m" : "";
    }

    switch (this->rank) {
        case CardRank::Ace:
            card_string += "Ace";
            break;
        case CardRank::Two:
            card_string += "Two";
            break;
        case CardRank::Three:
            card_string += "Three";
            break;
        case CardRank::Four:
            card_string += "Four";
            break;
        case CardRank::Five:
            card_string += "Five";
            break;
        case CardRank::Six:
            card_string += "Six";
            break;
        case CardRank::Seven:
            card_string += "Seven";
            break;
        case CardRank::Eight:
            card_string += "Eight";
            break;
        case CardRank::Nine:
            card_string += "Nine";
            break;
        case CardRank::Ten:
            card_string += "Ten";
            break;
        case CardRank::Jack:
            card_string += "Jack";
            break;
        case CardRank::Queen:
            card_string += "Queen";
            break;
        case CardRank::King:
            card_string += "King";
            break;
    }

    card_string += " of ";

    switch (this->suite) {
        case CardSuite::Spades:
            card_string += "spades";
            break;
        case CardSuite::Hearts:
            card_string += "hearts";
            break;
        case CardSuite::Diamonds:
            card_string += "diamonds";
            break;
        case CardSuite::Clubs:
            card_string += "clubs";
            break;
    }

    // if(this->turned) {
    //     card_string += " (turned)";
    // }

    if(colored) {
        card_string += "\033[0m";
    }

    return card_string;
}

std::string Card::get_code() {
    std::string code = "";

    switch(this->get_rank()) {
        case CardRank::Ace:
            code += "A";
            break;
        case CardRank::Jack:
            code += "J";
            break;
        case CardRank::Queen:
            code += "Q";
            break;
        case CardRank::King:
            code += "K";
            break;
        default:
            code += tmpl_to_string((int)this->get_rank());
            break;
    }

    switch (this->get_suite()) {
        case CardSuite::Hearts:
            code += "H";
            break;
        case CardSuite::Diamonds:
            code += "D";
            break;
        case CardSuite::Spades:
            code += "S";
            break;
        case CardSuite::Clubs:
            code += "C";
            break;
    }

    return code;
}

void Card::serialize(QJsonObject &json) {
    json["rank"] = (int)this->get_rank();
    json["suite"] = (int)this->get_suite();
    json["turned"] = this->is_turned();
}

Card* Card::load(QJsonObject json) {
    Card* card = new Card((CardSuite)json["suite"].toInt(), (CardRank)json["rank"].toInt());

    card->set_turned(json["turned"].toBool());

    return card;
}

bool Card::is_turned() {
    return this->turned;
}

void Card::set_turned(bool _turned) {
    this->turned = _turned;
}
