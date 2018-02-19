/**
 *  @file wastewidget.cpp
 *  @brief WasteWidget class implementation
 *  @author Svätopluk Hanzel (xhanze10), FIT VUT, 2BIT, a.y. 2016/2017
 */
#include <QJsonArray>
#include "wastewidget.h"

WasteWidget::WasteWidget() {
    this->type = DeckType::Waste;
    this->n = 0;
}

WasteWidget* WasteWidget::load(QJsonObject &json) {
    WasteWidget* deck = new WasteWidget();

    QJsonArray cards = json["cards"].toArray();
    for(int i = 0; i < cards.size(); i++) {
        QJsonObject card_json = cards[i].toObject();
        deck->add_card(CardWidget::load(card_json), true);
    }

    return deck;
}
