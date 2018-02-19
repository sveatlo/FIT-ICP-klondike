/**
 *  @file deckwidget.cpp
 *  @brief DeckWidget class implementation
 *  @author Svätopluk Hanzel (xhanze10), FIT VUT, 2BIT, a.y. 2016/2017
 */

#include <QDebug>
#include <QMessageBox>
#include <QPainter>
#include <QHBoxLayout>
#include <iostream>
#include "deckwidget.h"
#include "tableauwidget.h"

DeckWidget::DeckWidget(QWidget *parent) : QFrame(parent), Deck(DeckType::Heap, 0) {
    this->setAcceptDrops(true);
    this->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
    this->setLineWidth(2);

    this->overlay = new QWidget();
    overlay->move(0,0);
    QPalette pal = palette();
    pal.setColor(QPalette::Background,  QColor::fromRgb(100, 100, 100, 200));
    overlay->setAutoFillBackground(true);
    overlay->setPalette(pal);

}

DeckWidget::~DeckWidget() { }

void DeckWidget::set_game(TableauWidget* _game) {
    this->game = _game;
}

TableauWidget* DeckWidget::get_game() {
    return this->game;
}

void DeckWidget::add_card(Card* card) {
    CardWidget* card_widget;
    if((card_widget = static_cast<CardWidget*>(card)) != nullptr) {
        this->add_card(card_widget, false);
    }
}

void DeckWidget::add_card(Card* card, bool force) {
    CardWidget* card_widget;
    if((card_widget = static_cast<CardWidget*>(card)) != nullptr) {
        this->add_card(card_widget, force);
    }
}

void DeckWidget::add_card(CardWidget* card, bool force) {
    this->Deck::add_card(card, force);
    card->setParent(this);
    card->set_n(this->count() - 1);
    card->hide();
    this->move_cards();
}

void DeckWidget::remove_card(Card* card) {
    this->Deck::remove_card(card);
    this->move_cards();
}

void DeckWidget::move_cards() {
    int width = 1, height = 1;
    if(this->count() > 0) {
        width = CardWidget::default_width > this->width() ? this->width() : CardWidget::default_width;
        height = width*CardWidget::default_ratio;

        if(height > this->height()) {
            double ratio = (float)this->height() / (float)height;
            height = this->height();
            width = (int)(width * ratio);
        }
    }

    for(auto &card : *this->get_cards()) {
        CardWidget* card_widget = static_cast<CardWidget*>(card);
        if(card_widget == nullptr) {
            return;
        }

        int x_pos = (this->width() - width) / 2;
        int y_pos = (this->height() - height) / 2;

        card_widget->resize(width, height);
        card_widget->move(x_pos, y_pos);
    }
    try {
        CardWidget* card_widget = static_cast<CardWidget*>(this->get_last());
        if(card_widget == nullptr) {
            return;
        }
        card_widget->show();
    } catch(...) { }

}

int DeckWidget::get_current_gap() {
    return this->gap;
}

void DeckWidget::dragEnterEvent(QDragEnterEvent *event) {
    if (!event->mimeData()->hasFormat("application/x-card")) {
        return;
    }

    CardWidget* src = (CardWidget*)event->source();
    if(src == 0) {
        return;
    }

    if(this->can_add_card(src)) {
        event->accept();

        try {
            CardWidget* last_card = static_cast<CardWidget*>(this->get_last());
            this->overlay->setParent(last_card);
            this->overlay->show();
        } catch(...) {

        }
    } else {
        event->ignore();
    }
}

void DeckWidget::dragLeaveEvent(QDragLeaveEvent *event) {
    (void)event;
    this->overlay->hide();
}

void DeckWidget::dropEvent(QDropEvent *event) {
    if (!event->mimeData()->hasFormat("application/x-card")) {
        return;
    }

    CardWidget* card = (CardWidget*)event->source();
    if(card == 0) {
        return;
    }

    if(!this->can_add_card(card)) {
        event->ignore();
        return;
    }

    event->accept();
    DeckWidget* src_deck = (DeckWidget*)card->parentWidget();
    try {
        card->move(event->pos());
        this->game->game_move(std::make_pair(std::make_tuple(src_deck->get_type(), src_deck->get_n(), src_deck->count() - 1 - card->get_n()), std::make_tuple(this->get_type(), this->get_n())));
        this->overlay->hide();
    } catch(...) {
        QMessageBox info_box;
        info_box.setWindowTitle("Unknown error");
        info_box.setText("An exception was thrown while processing move");
        info_box.exec();
        this->overlay->hide();
        card->show();
        src_deck->move_cards();

    }
}

void DeckWidget::resizeEvent(QResizeEvent *event) {
    (void)event;
    this->move_cards();
}
