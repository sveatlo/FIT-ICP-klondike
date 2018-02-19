/**
 *  @file wastewidget.h
 *  @brief WasteWidget class declaration
 *  @author Svätopluk Hanzel (xhanze10), FIT VUT, 2BIT, a.y. 2016/2017
 */
#ifndef WASTEWIDGET_H
#define WASTEWIDGET_H

#include <QJsonObject>
#include "deckwidget.h"

class WasteWidget : public DeckWidget
{
public:
    WasteWidget();

    static WasteWidget* load(QJsonObject &json);
};

#endif // WASTEWIDGET_H
