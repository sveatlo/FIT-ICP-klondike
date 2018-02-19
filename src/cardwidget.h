/**
 *  @file cardwidget.h
 *  @brief CardWidget class declaration
 *  @author Svätopluk Hanzel (xhanze10), FIT VUT, 2BIT, a.y. 2016/2017
 */
#ifndef CARDWIDGET_H
#define CARDWIDGET_H

#include <QJsonObject>
#include <QSvgWidget>
#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QPixmap>
#include "card.h"

/**
 * @brief CardWidget is the representation of Card in GUI
 */
class CardWidget : public QSvgWidget, public Card
{
public:
    CardWidget(CardSuite _suit, CardRank _rank);
    CardWidget(Card* card);

    static CardWidget* load(QJsonObject &json);

    static const int default_width = 209;
    static const int default_height = 303;
    static constexpr double default_ratio = 1.449760765550239f;

    /**
     * Overriden Card::set_turned method - sets the new turned value and reloads its image
     * @param _turned Boolean representing card's turned property
     */
    void set_turned(bool _turned);

    /**
     * [set_n description]
     * @param _n Card's order in deck, i.e. this card is the _nth card in its deck
     */
    void set_n(int _n);

    /**
     * Return Card's n
     * @return Number representing card's order in deck
     */
    int get_n();

    std::string get_image_path();

private:
    /**
     * @brief Used to mark position when mousePressEvent occured
     * to distinguish drag and click
     */
    QPoint drag_start_position;

    /**
     * @brief This is the nth card in its current deck
     */
    int n;

    /**
     * Reload card's image representation
     */
    void load_image();

    /**
     * Handler for events fired on mouse press
     * @param event Informations about event
     */
    void mousePressEvent(QMouseEvent *event) override;

    /**
     * Handler for events fired on mouse move
     * @param event Informations about the event
     */
    void mouseMoveEvent(QMouseEvent *event) override;
};

#endif // CARDWIDGET_H
