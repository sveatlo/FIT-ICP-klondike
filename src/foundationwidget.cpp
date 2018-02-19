/**
 *  @file foundationwidget.cpp
 *  @brief FoundationWidget class implementation
 *  @author Svätopluk Hanzel (xhanze10), FIT VUT, 2BIT, a.y. 2016/2017
 */
#include <QJsonArray>
#include "foundationwidget.h"

FoundationWidget::FoundationWidget(int _n) {
    this->type = DeckType::Foundation;
    this->n = _n;
}

FoundationWidget* FoundationWidget::load(QJsonObject &json) {
    FoundationWidget* deck = new FoundationWidget(json["n"].toInt());

    QJsonArray cards = json["cards"].toArray();
    for(int i = 0; i < cards.size(); i++) {
        QJsonObject card_json = cards[i].toObject();
        deck->add_card(CardWidget::load(card_json), true);
    }

    return deck;
}
