/**
 *  @file deck.h
 *  @brief Deck class declaration
 *  @author Svätopluk Hanzel (xhanze10), FIT VUT, 2BIT, a.y. 2016/2017
 */
#ifndef DECK_H
#define DECK_H

#include <QJsonObject>
#include <QList>
#include <string>
#include <vector>
#include "card.h"
#include "decktype.h"

// forward declarations
class Game;
class TableauWidget;

/**
 * Deck represents any card deck in the game regardless of type of the cards in it,
 * their color, suit or ranks.
 * Besides the Deck class, some more specific decks are used: FoundationDeck, Stack, Heap.
 * @brief The Deck class is used to represent any card deck in the game.
 */
class Deck
{

    friend class Game;
    friend class TableauWidget;
public:
    Deck(DeckType type, int _n);
    virtual ~Deck();

    static Deck* load(QJsonObject json);

    /**
     * @brief add_card adds a new card to the end of the deck
     * @param card
     */
    virtual void add_card(Card* card);

    /**
     * @brief Removes card from deck
     * @param card
     */
    virtual void remove_card(Card* card);

    /**
     * @brief Returns pointer to the last card in deck
     * @return Pointer to the last card
     */
    Card* get_last();

    /**
     * @brief Returns a pointer to the nth card from end
     * @param n Number of cards to skip from end
     * @return Pointer to the last card
     */
    Card* get_last(int n);

    /**
     * @brief Removes last card in the deck
     */
    void remove_last();

    /**
     * @brief Shuffles cards
     */
    void shuffle();

    /**
     * @brief Returns number of cards in deck
     * @return Number of cards in deck
     */
    int count();

    /**
     * @brief Return a string representing this deck's current status
     * @return A string representing this deck
     */
    std::string to_string();

    /**
     * This function is useful for finding next appropriate card for stacks.
     * Eg. Red Ace.
     * @brief Finds first card in this deck by color and rank.
     * @param color Color the card should have (Red/Black)
     * @param rank  Rank of the card (Ace-King)
     * @return Pointer to the card, nullptr if none is found
     */
    std::pair<Card*, int> find_card(CardColor color, CardRank rank);

    /**
     * @brief Returns this decks type from enum
     * @return DeckType of this deck
     */
    DeckType get_type();

    /**
     * @brief Retrieve n
     * @return Integer representing order of deck of its type
     */
    int get_n();

    /**
     * @brief Serializes deck, so it can be saved in JSON format
     * @param json QJsonObject to which all new data should be written to
     */
    void serialize(QJsonObject &json);

protected:
    std::vector<Card*> cards;
    DeckType type;
    /**
     * @brief This deck is nth of its type in current game
     */
    int n;

    /**
     * @brief Function, that decides whether it is possible to add some card to the deck
     * @param card The Card to add
     * @return True in case the card can be added to the end of the deck. False otherwise.
     */
    virtual bool can_add_card(Card* card);

    /**
     * @brief Adds a new card to the end of the deck
     * @param card  Card to add to the end of the deck
     * @param force Check whether the card can be added?
     */
    virtual void add_card(Card* card, bool force);

    /**
     * @brief Returns all cards in this deck
     * @return Pointer to QList of card pointers to cards in this deck
     */
    std::vector<Card*>* get_cards();
};

#endif // DECK_H
