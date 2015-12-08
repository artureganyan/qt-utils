/******************************************************************************
 * Copyright (c) 2015 Artur Eganyan
 *
 * This software is provided "AS IS", WITHOUT ANY WARRANTY, express or implied.
 ******************************************************************************/

#include <QStyledItemDelegate>
#include <QStyleOptionViewItem>
#include <QPainter>
#include <QColor>


namespace QtUtils {

/**
 * The PlaceholderItemDelegate class provides placeholders for model items.
 *
 * Placeholder text is set with setTextForItem(), setTextForRow(), setTextForColumn()
 * and setTextForAllItems() methods. It can also be stored in an item data under
 * the role specified by setDataRole() (this can be useful to display error messages
 * for particular items). If there are many placeholders for one item, the following
 * priority is used: item data, text for item, for row, for column and for all items.
 *
 * A placeholder is displayed if isPlaceholderVisible() returns true for the item,
 * with the color specified by setTextColor(). By default, it is displayed if the
 * item data under Qt::DisplayRole is (or convertable to) an empty string. Note
 * that if the placeholder text is an empty string, the item is drawn as usual.
 *
 * \code
 * PlaceholderItemDelegate* placeholder = new PlaceholderItemDelegate();
 * placeholder->setTextForRow(0, "Row hint");
 * placeholder->setTextForColumn(1, "Column hint");
 * placeholder->setTextForItem(0, 2, "Item hint");
 * placeholder->setTextForAllItems("Table hint");
 * placeholder->setTextColor(Qt::gray);
 *
 * QStandardItemModel* model = new QStandardItemModel(3, 3);
 * model->setItemDelegate(placeholder);
 * \endcode
 */

class PlaceholderItemDelegate : public QStyledItemDelegate
{
public:
    /**
     * Sets the placeholder \a text for the \a column.
     */
    void setTextForColumn( int column, const QString& text );

    /**
     * Sets the placeholder \a text for the \a row.
     */
    void setTextForRow( int row, const QString& text );

    /**
     * Sets the placeholder \a text for the item at \a row and \a column.
     */
    void setTextForItem( int row, int column, const QString& text );

    /**
     * Sets the placeholder \a text for all items.
     */
    void setTextForAllItems( const QString& text );

    /**
     * Sets the data role for placeholders to \a role.
     */
    void setDataRole( int role );

    /**
     * Returns the data role for placeholders.
     */
    int dataRole() const;

    /**
     * Set the placeholder text \a color.
     */
    void setTextColor( const QColor& color );

    /**
     * Returns the placeholder text color.
     */
    QColor textColor() const;

    void paint( QPainter*, const QStyleOptionViewItem&, const QModelIndex& ) const;

protected:
    /**
     * Returns true if a placeholder should be displayed for the \a index,
     * otherwise returns false. By default, it returns true if the item data
     * under Qt::DisplayRole is (or convertable to) an empty string.
     */
    virtual bool isPlaceholderVisible( const QModelIndex& index ) const;

    /**
     * Returns the placeholder text for the \a index.
     */
    QString placeholderText( const QModelIndex& index ) const;

private:
    QMap<int /*row*/, QMap<int /*column*/, QString>> m_text;
    QColor m_textColor;
    int m_dataRole = -1;
};

} // namespace QtUtils
