/**
 *  @file card.h
 *  @brief Card class declaration
 *  @author Svätopluk Hanzel (xhanze10), FIT VUT, 2BIT, a.y. 2016/2017
 */
#ifndef CARD_H
#define CARD_H

#include <QJsonObject>
#include <string>
#include "cardrank.h"
#include "cardsuite.h"
#include "cardcolor.h"

// forward declaration
class Deck;

/**
 * @brief The Card class is used to represent 1 playing card from the standard 52pcs poker card deck
 */
class Card
{
    friend class Deck;
public:
    /**
     * @brief Card constructor to create a new card
     * @param _suit Specifies the suit of the new card
     * @param _rank Specifies rand of this card
     */
    Card(CardSuite _suit, CardRank _rank);
    virtual ~Card();

    static Card* load(QJsonObject json);

    /**
     * @brief get_suite Used to get card's suit
     * @return CardSuite
     */
    CardSuite get_suite();

    /**
     * @brief get_rank Used to get card's rank
     * @return CardRank
     */
    CardRank get_rank();

    /**
     * @brief get_color Used to get card's current color
     * @return CardColor
     */
    CardColor get_color();

    /**
     * @brief to_string returns a string representing this card
     * @param show_unturned defines whether cards, that have not been revealed yet should be displayed
     * @return String representing the card
     */
    std::string to_string(bool show_unturned = false, bool colored = true);

    /**
     * @brief is_turned returns a boolean value indicating whether the card's face can be seen
     * @return
     */
    bool is_turned();

    /**
     * @brief set_turned sets a new value for the "is_turned" attribute
     * @param _turned the new "is_turned" value
     */
    virtual void set_turned(bool _turned);

    /**
     * @brief Serializes card, so it can be saved in JSON format
     * @param json QJsonObject to which all new data should be written to
     */
    void serialize(QJsonObject &json);


protected:
    /**
     * @brief Returns short code of the card, eg. "AS" - Ace of Spades
     * @return Code string
     */
    std::string get_code();

private:
    /**
     * @brief Card's suite
     * @see CardSuite
     */
    CardSuite suite;

    /**
     * @brief Card's rank
     * @see CardRank
     */
    CardRank rank;

    /**
     * @brief Is card turned?
     */
    bool turned = false;
};

#endif // CARD_H
