/**
 *  @file tableauwidget.h
 *  @brief TableauWidget class declaration
 *  @author Svätopluk Hanzel (xhanze10), FIT VUT, 2BIT, a.y. 2016/2017
 */
#ifndef TABLEAUWIDGET_H
#define TABLEAUWIDGET_H

#include <QWidget>
#include <QLCDNumber>
#include "game.h"
#include "cardwidget.h"
#include "foundationwidget.h"
#include "stackwidget.h"
#include "heapwidget.h"
#include "wastewidget.h"

namespace Ui {
class TableauWidget;
}

class TableauWidget : public QWidget, public Game {
    Q_OBJECT

public:
    explicit TableauWidget(QWidget *parent = 0);
    ~TableauWidget();

    void initialize();
    void load(QJsonObject &json);

private:
    Ui::TableauWidget *ui;
    QLCDNumber* score_counter;

    void generate_decks();
    void generate_cards();

    std::string move_to_string(GameMove move);
    void celebrate();
    void update_score();

private slots:
    void on_close_button_clicked();

    void on_undo_button_clicked();

    void on_hint_button_clicked();
    void on_save_clicked();
};

#endif // TABLEAUWIDGET_H
