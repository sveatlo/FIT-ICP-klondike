/**
 *  @file stackwidget.h
 *  @brief StackWidget class declaration
 *  @author Svätopluk Hanzel (xhanze10), FIT VUT, 2BIT, a.y. 2016/2017
 */
#ifndef STACKWIDGET_H
#define STACKWIDGET_H

#include "deckwidget.h"

class StackWidget : public DeckWidget
{
public:
    StackWidget(int _n);

    static StackWidget* load(QJsonObject &json);

private:
    void move_cards();
};

#endif // STACKWIDGET_H
