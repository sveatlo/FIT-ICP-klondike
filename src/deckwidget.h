/**
 *  @file deckwidget.h
 *  @brief DeckWidget class declaration
 *  @author Svätopluk Hanzel (xhanze10), FIT VUT, 2BIT, a.y. 2016/2017
 */
#ifndef DECKWIDGET_H
#define DECKWIDGET_H

#include <QDebug>
#include <QFrame>
#include <QPropertyAnimation>
#include "deck.h"
#include "card.h"
#include "cardwidget.h"

class TableauWidget;


/**
 * @brief DeckWidget is the representation of Deck in GUI
 */
class DeckWidget : public QFrame, public Deck
{
    Q_OBJECT

public:
    explicit DeckWidget(QWidget *parent = 0);
    ~DeckWidget();

    /**
     * Adds card to DeckWidget
     * @see Deck::add_card
     */
    virtual void add_card(Card* card);

    /**
     * Removes card to DeckWidget
     * @see Deck::add_card
     */
    virtual void remove_card(Card* card);

    /**
     * Sets reference to TableauWidget this deck is part of
     * @param _game Pointer to the TableauWidget object
     */
    void set_game(TableauWidget* _game);

    /**
     * Returns this deck's TableauWidget
     * @return Pointer to the TableauWidget object this deck belongs to
     */
    TableauWidget* get_game();

    /**
     * Get current gap between cards
     * @return Gap between cards' tops
     */
    int get_current_gap();

    /**
     * Move cards to best-fit the deck
     */
    virtual void move_cards();

protected:
    /**
     * Reference to the TableauWidget this deck belongs to
     */
    TableauWidget* game;

    /**
     * QWidget which is shown when a CardWidget is about to be dropped to this deck
     */
    QWidget* overlay;

    /**
     * Current gap between tops of cards
     */
    int gap = 0;

    void add_card(Card* card, bool force);
    void add_card(CardWidget* card, bool force);

    virtual void dragEnterEvent(QDragEnterEvent *event);
    virtual void dragLeaveEvent(QDragLeaveEvent *event);
    virtual void dropEvent(QDropEvent *event);
    virtual void resizeEvent(QResizeEvent *event);
};

#endif // DECKWIDGET_H
