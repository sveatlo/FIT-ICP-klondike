/**
 *  @file stackwidget.cpp
 *  @brief StackWidget class implementation
 *  @author Svätopluk Hanzel (xhanze10), FIT VUT, 2BIT, a.y. 2016/2017
 */
#include <QJsonArray>
#include "stackwidget.h"

StackWidget::StackWidget(int _n) {
    this->type = DeckType::Stack;
    this->n = _n;
}

StackWidget* StackWidget::load(QJsonObject &json) {
    StackWidget* deck = new StackWidget(json["n"].toInt());

    QJsonArray cards = json["cards"].toArray();
    for(int i = 0; i < cards.size(); i++) {
        QJsonObject card_json = cards[i].toObject();
        deck->add_card(CardWidget::load(card_json), true);
    }

    return deck;
}

void StackWidget::move_cards() {
    int count = this->count();
    int width = 1, height = 1;

    if(count > 0) {
        width = CardWidget::default_width > this->width() ? this->width() : CardWidget::default_width;
        height = width*CardWidget::default_ratio;

        this->gap = (this->height() - height) / count;
        gap = gap < 10 ? 10 : (gap > 50 ? 50 : gap);
    }
    int x_pos = (this->width() - width) / 2;

    // dynamic gap count
    int i = 0;
    for(auto &card : *this->get_cards()) {
        CardWidget* card_widget = static_cast<CardWidget*>(card);
        if(card_widget == nullptr) {
            return;
        }
        card_widget->show();

        // QPropertyAnimation *animation = new QPropertyAnimation(card_widget, "geometry");
        // animation->setDuration(100);
        // animation->setStartValue(geometry);
        // animation->setEndValue(QRect(x_pos, i * gap, width, height));
        // animation->start();
        card_widget->resize(width, height);
        card_widget->move(x_pos, i * gap);

        i++;
    }
}
