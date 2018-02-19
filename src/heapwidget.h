/**
 *  @file heapwidget.h
 *  @brief HeapWidget class declaration
 *  @author Svätopluk Hanzel (xhanze10), FIT VUT, 2BIT, a.y. 2016/2017
 */
#ifndef HEAPWIDGET_H
#define HEAPWIDGET_H

#include <QJsonObject>
#include "deckwidget.h"

/**
 * @brief DeckWidget's inherited class for Graphical representation of heap deck
 */
class HeapWidget : public DeckWidget
{
public:
    HeapWidget();

    static HeapWidget* load(QJsonObject &json);

private:
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // STACKWIDGET_H
