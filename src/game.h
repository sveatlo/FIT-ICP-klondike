/**
 *  @file game.h
 *  @brief Game class declaration
 *  @author Svätopluk Hanzel (xhanze10), FIT VUT, 2BIT, a.y. 2016/2017
 */
#ifndef GAME_H
#define GAME_H

#define FOUNDATIONS_COUNT 4
#define STACKS_COUNT 7

#include <tuple>
#include <array>
#include <vector>
#include "deck.h"
#include "decktype.h"
#include "string.h"

/**
 * GameMove is a pair of 2 tuples:
 * 1. tuple's content:
 *      1. DeckType - type of the deck to move from
 *      2. int - number of the deck in DeckType's vector
 *      3. int - number of cards to skip from the end
 *                  to get to the card you want to move
 * 2. tuple's content:
 *      1. DeckType - type of the deck to move the card to
 *      2. int - number of the deck in DeckType's vector
 * @brief GameMove is a data type to save game moves to
 * @see Game::type_to_deck
 */
typedef std::pair<std::tuple<DeckType, int, int>, std::tuple<DeckType, int>> GameMove;

/**
 * @brief The Game class represents one game regardless of UI.
 */
class Game
{
public:
    Game();
    virtual ~Game();

    void print_game();

    /**
     * @brief Moves cards from one deck to other
     * @param move  The GameMove to perform
     */
    void game_move(GameMove move);

    /**
     * Moves a card from one deck to another. Deck can also be Foundation or Stack.
     * Throws an exception if the move is not possible:
     * int(1) if the card cannot be added to the deck_to deck and
     * int(2) if the card cannot be removed from the deck_from deck.
     * If the card cannot be removed from the old deck, it is not added to the new deck.
     * If the card cannot be added to the new deck, it is not removed from the old deck.
     *
     * @brief Move a card from one deck to another.
     *
     * @param card          Pointer to the card to move
     * @param deck_from     Deck from which the card should be removed
     * @param deck_to       Deck to which the card should be added
     * @param force         Do not check move compatibility if true
     * @param new_turned    New turned value for the card
     */
    void game_move(Card* card, Deck* deck_from, Deck* deck_to, bool force = false, bool new_turned = true, bool turn_new_last = true, bool is_undo = false);

    /**
     * @brief Reveals heap card by moving it from heap to waste
     */
    void reveal();

    std::string move_to_string(GameMove move);

    /**
     * @brief Reverses GameMove
     * @param move The move to reverse
     * @return The reversed move
     */
    GameMove reverse_move(GameMove move);

    /**
     * @brief Returns last move from game history
     * @return Last performed move
     */
    GameMove get_last_move();

    /**
     * @brief Reverses last move if possible
     */
    void undo_last_move();

    /**
     * @brief Resets Heap by adding all cards from waste back to heap
     */
    void reset_heap();

    /**
     * First checks if any card can be moved to any of the foundations
     * @brief Finds next possible move in this game.
     */
    std::vector<GameMove> hint();

    /**
     * Creates all the required decks, creates cards, etc.
     * @brief Initializes this game
     */
    virtual void initialize();

    /**
     * @brief Checks whether this game has been won. Returns boolean accordingly.
     * @return true if game has been won, false otherwise
     */
    bool have_won();

    /**
    * @brief Saves game to a file
    * @param name Name of the file to which, the game should be saved
    */
   void save_game(QString filename);

   /**
    * @brief Loads saved game from file
    * @param filename Name of the file from which the should be loaded
    */
   void load_from_file(QString filename);

protected:
    Deck* heap;
    Deck* waste;
    std::array<Deck*, FOUNDATIONS_COUNT> foundations;
    std::array<Deck*, STACKS_COUNT> stacks;

    /**
     * Keeps track of current game's score
     */
    int score = 0;

    QList<GameMove> moves;

    /**
     * @brief move
     * @param move
     * @param force Do not check move compatibility if true
     */
    void game_move(GameMove move, bool force, bool new_turned = true, bool turn_new_last = true, bool save_move = true,  bool is_undo = false);

    /**
     * @brief type_to_deck Returns a pointer to the nth deck of DeckType type in current game
     * @param deck_data
     * @return Pointer to the deck requested
     */
    Deck* type_to_deck(DeckType type, int n);

    /**
     * @brief Serializes game, so it can be saved in JSON format
     * @param json QJsonObject to which all new data should be written to
     */
    void serialize(QJsonObject &json);

    virtual void load(QJsonObject &json);

    /**
     * @brief Checks whether the game has been won, if so it calls celebrate.
     */
    void check_win();

    /**
     * @brief Runs celebration routine
     */
    virtual void celebrate();

    virtual Deck* get_heap();
    virtual Deck* get_waste();
    virtual std::array<Deck*, 4>* get_foundations();
    virtual std::array<Deck*, 7>* get_stacks();

    virtual void generate_decks();
    virtual void generate_cards();
    void deal_cards();
    virtual void update_score();
};

#endif // GAME_H
