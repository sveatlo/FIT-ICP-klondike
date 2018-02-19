/**
 *  @file cardwidget.cpp
 *  @brief CardWidget class implementation
 *  @author Svätopluk Hanzel (xhanze10), FIT VUT, 2BIT, a.y. 2016/2017
 */
#include <QDebug>
#include <QApplication>
#include <QSvgRenderer>
#include <QPainter>
#include "cardwidget.h"
#include "deckwidget.h"
#include "stackwidget.h"
#include "tableauwidget.h"

CardWidget::CardWidget(CardSuite _suit, CardRank _rank) : Card(_suit, _rank) {
    this->ensurePolished();
    this->load_image();
}

CardWidget* CardWidget::load(QJsonObject &json) {
    CardWidget* card = new CardWidget((CardSuite)json["suite"].toInt(), (CardRank)json["rank"].toInt());

    card->set_turned(json["turned"].toBool());

    return card;
}

void CardWidget::load_image() {
    this->QSvgWidget::load(QString(this->get_image_path().c_str()));
}

std::string CardWidget::get_image_path() {
    return ":/images/cards/" + (this->is_turned() ? this->get_code() : "back") + ".svg";
}
void CardWidget::set_n(int _n) {
    this->n = _n;
}

int CardWidget::get_n() {
    return this->n;
}

void CardWidget::set_turned(bool _turned) {
    this->Card::set_turned(_turned);
    this->load_image();
}

void CardWidget::mousePressEvent(QMouseEvent *event) {
    if (this->is_turned() && event->button() == Qt::LeftButton && this->geometry().contains(event->pos())) {
        this->drag_start_position = event->pos();
    } else if(static_cast<DeckWidget*>(this->parentWidget())->get_type() == DeckType::Heap) {
        static_cast<DeckWidget*>(this->parentWidget())->get_game()->reveal();
    }
}

void CardWidget::mouseMoveEvent(QMouseEvent *event) {
    if (!this->is_turned() || !(event->buttons() & Qt::LeftButton))
        return;
    if ((event->pos() - this->drag_start_position).manhattanLength() < QApplication::startDragDistance())
        return;


    QMimeData *mimeData = new QMimeData();
    mimeData->setData("application/x-card", this->get_code().c_str());

    DeckWidget* parent_deck = static_cast<DeckWidget*>(this->parentWidget());
    int card_n = parent_deck->count() - 1 - this->get_n();
    QPixmap pm(this->width(), this->height() + card_n * parent_deck->get_current_gap());
    QPainter painter(&pm);
    for(int i = card_n; i >= 0; i--) {
        CardWidget* card = static_cast<CardWidget*>(parent_deck->get_last(i));
        QSvgRenderer renderer(QString(card->get_image_path().c_str()));
        renderer.render(&painter, QRect(0, (card_n - i)* parent_deck->get_current_gap(), this->width(), this->height()));
        card->hide();
    }

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pm);
    drag->setHotSpot(event->pos());


    if(drag->exec(Qt::MoveAction) != Qt::MoveAction) {
        parent_deck->move_cards();
    }
}
