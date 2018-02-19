/**
 *  @file cardcolor.h
 *  @brief Definition of the CardColor enum
 *  @author Svätopluk Hanzel (xhanze10), FIT VUT, 2BIT, a.y. 2016/2017
 */
#ifndef CARDCOLOR_H
#define CARDCOLOR_H


/**
 * @brief The CardColor enum represents color (black or red) of a card's suit
 */
enum class CardColor {
    Any = 0b11,
    Black = 0b01,
    Red = 0b10
};

#endif // CARDCOLOR_H
