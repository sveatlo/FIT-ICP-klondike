/**
 *  @file heapwidget.cpp
 *  @brief HeapWidget class implementation
 *  @author Svätopluk Hanzel (xhanze10), FIT VUT, 2BIT, a.y. 2016/2017
 */
#include <QJsonArray>
#include "heapwidget.h"
#include "tableauwidget.h"

HeapWidget::HeapWidget() {
    this->type = DeckType::Heap;
    this->n = 0;
}

void HeapWidget::mousePressEvent(QMouseEvent *event) {
    (void)event;

    try {
        this->game->reveal();
    } catch(int err) {
        qDebug() << "Error while revealing card from heap:" << err;
    } catch(const char* err) {
        qDebug() << "Error while revealing card from heap:" << err;
    }
}

HeapWidget* HeapWidget::load(QJsonObject &json) {
    HeapWidget* deck = new HeapWidget();

    QJsonArray cards = json["cards"].toArray();
    for(int i = 0; i < cards.size(); i++) {
        QJsonObject card_json = cards[i].toObject();
        deck->add_card(CardWidget::load(card_json), true);
    }

    return deck;
}
