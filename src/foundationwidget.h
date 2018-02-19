/**
 *  @file foundationwidget.h
 *  @brief FoundationWidget class declaration
 *  @author Svätopluk Hanzel (xhanze10), FIT VUT, 2BIT, a.y. 2016/2017
 */
#ifndef FOUNDATIONWIDGET_H
#define FOUNDATIONWIDGET_H

#include "deckwidget.h"

/**
 * @brief DeckWidget's inherited class for Graphical representation of foundation decks
 */
class FoundationWidget : public DeckWidget
{
public:
    FoundationWidget(int _n);

    static FoundationWidget* load(QJsonObject &json);
};

#endif // FOUNDATIONWIDGET_H
