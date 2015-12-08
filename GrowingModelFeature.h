/******************************************************************************
 * Copyright (c) 2015 Artur Eganyan
 *
 * This software is provided "AS IS", WITHOUT ANY WARRANTY, express or implied.
 ******************************************************************************/

#include <QAbstractItemModel>
#include <QSet>


namespace QtUtils {

/**
 * The GrowingModelFeature class automatically appends rows in item models.
 *
 * You can install() or remove() this feature on a model. Once installed, it
 * appends empty rows on all model levels (by the first column, like a tree
 * view). Later, when the user enters some data in the empty row, a new one
 * added, and so on. When some row becomes empty, it is removed. A row is
 * considered empty if isRowEmpty() returns true. Appended rows are initialized
 * with initRow(), which does nothing by default and can be reimplemented.
 *
 * \code
 * QStandardItemModel* model = new QStandardItemModel(0, 3);
 * GrowingModelFeature* feature = new GrowingModelFeature();
 * feature->install(model);
 * \endcode
 */

class GrowingModelFeature : public QObject
{
    Q_OBJECT

public:
    /**
     * Installs the feature on the \a model.
     *
     * \note Empty rows will be removed.
     */
    void install( QAbstractItemModel* model );

    /**
     * Removes the feature from the \a model.
     */
    void remove( QAbstractItemModel* model );

protected:
    /**
     * Returns true if the \a row of the \a model and \a parent is considered
     * empty, otherwise returns false. By default, a row is empty if all its
     * items contain empty strings under Qt::DisplayRole.
     */
    virtual bool isRowEmpty( QAbstractItemModel* model, int row, const QModelIndex& parent ) const;

    /**
     * Initializes the new \row of the \a model and \a parent. The default
     * implementation does nothing.
     */
    virtual void initRow( QAbstractItemModel* model, int row, const QModelIndex& parent );

private slots:
    void on_dataChanged( const QModelIndex& topLeft, const QModelIndex& bottomRight,
                         const QVector<int>& roles );

private:
    void checkRows( QAbstractItemModel* model, int top, int bottom,
                    const QModelIndex& parent = QModelIndex() );

private:
    QSet<QAbstractItemModel*> m_models;
};

} // namespace QtUtils
