/******************************************************************************
 * Copyright (c) 2015 Artur Eganyan
 *
 * This software is provided "AS IS", WITHOUT ANY WARRANTY, express or implied.
 ******************************************************************************/

#include "PlaceholderItemDelegate.h"
#include <QApplication>
#include <QDebug>


namespace QtUtils {

void PlaceholderItemDelegate::setTextForColumn( int column, const QString& text )
{
    if (column < 0) return;
    m_text[-1][column] = text;
}

void PlaceholderItemDelegate::setTextForRow( int row, const QString& text )
{
    if (row < 0) return;
    m_text[row][-1] = text;
}

void PlaceholderItemDelegate::setTextForItem( int row, int column, const QString& text )
{
    if (row < 0 || column < 0) return;
    m_text[row][column] = text;
}

void PlaceholderItemDelegate::setTextForAllItems( const QString& text )
{
    m_text[-1][-1] = text;
}

void PlaceholderItemDelegate::setDataRole( int role )
{
    m_dataRole = role;
}

int PlaceholderItemDelegate::dataRole() const
{
    return m_dataRole;
}

void PlaceholderItemDelegate::setTextColor( const QColor& color )
{
    m_textColor = color;
}

QColor PlaceholderItemDelegate::textColor() const
{
    return m_textColor;
}

void PlaceholderItemDelegate::paint( QPainter* painter, const QStyleOptionViewItem& option,
                                     const QModelIndex& index ) const
{
    bool visible = isPlaceholderVisible(index);
    bool selected = option.state & QStyle::State_Selected;
    QString text = visible ? placeholderText(index) : QString();

    if (visible && !selected && !text.isEmpty()) {
        // Init style option
        QStyleOptionViewItem opt = option;
        initStyleOption(&opt, index);
        if (m_textColor.isValid()) {
            opt.palette.setColor(QPalette::Text, m_textColor);
        }

        // Get the view widget and its style. Note that opt.widget is not
        // documented, but without its style we can not draw the item
        // properly (opt.styleObject is NULL).
        const QWidget* widget = opt.widget;
        QStyle* style = widget ? widget->style() : QApplication::style();

        // Get margin and rect of the text
        const int margin = style->pixelMetric(QStyle::PM_FocusFrameHMargin, &opt, widget) + 1;
        QRect rect = style->subElementRect(QStyle::SE_ItemViewItemText, &opt, widget);
        rect.adjust(margin, 0, -margin, 0);

        // Draw the item and its placeholder. Currently, HighlightedText color
        // role is not used (placeholder is hidden for selected items).
        QPalette::ColorRole colorRole = selected ? QPalette::HighlightedText : QPalette::Text;
        style->drawControl(QStyle::CE_ItemViewItem, &opt, painter, widget);
        style->drawItemText(painter, rect, opt.displayAlignment, opt.palette,
            opt.state & QStyle::State_Enabled, text, colorRole);

    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}

bool PlaceholderItemDelegate::isPlaceholderVisible( const QModelIndex& index ) const
{
    QString itemString = index.data(Qt::DisplayRole).toString();
    return itemString.isEmpty();
}

QString PlaceholderItemDelegate::placeholderText( const QModelIndex& index ) const
{
    QString text;
    if (m_dataRole >= 0) {
        text = index.data(m_dataRole).toString();
    }
    if (text.isEmpty()) {
        const int column = index.column();
        const int row = index.row();
        if (m_text.contains(row)) {
            text = m_text[row].value(column, m_text[row][-1]);
        }
        if (text.isEmpty()) {
            text = m_text[-1].value(column, m_text[-1][-1]);
        }
    }
    return text;
}

} // namespace QtUtils
