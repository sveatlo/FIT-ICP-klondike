/**
 *  @file cardrank.h
 *  @brief Definition of the CardRank enum
 *  @author Svätopluk Hanzel (xhanze10), FIT VUT, 2BIT, a.y. 2016/2017
 */
#ifndef CARDRANK_H
#define CARDRANK_H

/**
 * @brief The CardRank enum is used to identify card's rank (A->Q)
 */
enum class CardRank {
    Ace = 1,
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King
};

#endif // CARDRANK_H
