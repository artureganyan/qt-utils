/******************************************************************************
 * Copyright (c) 2015 Artur Eganyan
 *
 * This software is provided "AS IS", WITHOUT ANY WARRANTY, express or implied.
 ******************************************************************************/

#include "GrowingModelFeature.h"


namespace QtUtils {

void GrowingModelFeature::install( QAbstractItemModel* model )
{
    if (!model || m_models.contains(model)) return;

    m_models << model;
    connect(model,
        SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&, const QVector<int>&)),
        SLOT(on_dataChanged(const QModelIndex&, const QModelIndex&, const QVector<int>&))
        );
    checkRows(model, 0, model->rowCount());
}

void GrowingModelFeature::remove( QAbstractItemModel* model )
{
    if (!model || !m_models.contains(model)) return;

    model->disconnect(this);
    m_models.remove(model);
}

bool GrowingModelFeature::isRowEmpty( QAbstractItemModel* model, int row,
                                      const QModelIndex& parent ) const
{
    const int columnCount = model->columnCount(parent);
    for (int c = 0; c < columnCount; ++ c) {
        const QModelIndex& item = model->index(row, c, parent);
        QString itemString = item.data(Qt::DisplayRole).toString();
        if (!itemString.isEmpty()) {
            return false;
        }
    }
    return true;
}

void GrowingModelFeature::initRow( QAbstractItemModel*, int, const QModelIndex& )
{
    // Nothing to do by default
}

void GrowingModelFeature::on_dataChanged( const QModelIndex& topLeft, const QModelIndex& bottomRight,
                                          const QVector<int>& /*roles*/ )
{
    if (topLeft.parent() != bottomRight.parent()) return;

    QAbstractItemModel* model = qobject_cast<QAbstractItemModel*>(QObject::sender());
    Q_ASSERT(model);

    checkRows(model, topLeft.row(), bottomRight.row(), topLeft.parent());
}

void GrowingModelFeature::checkRows( QAbstractItemModel* model, int top, int bottom,
                                     const QModelIndex& parent )
{
    // Remove empty rows
    for (int r = bottom; r >= top; -- r) {
        if (isRowEmpty(model, r, parent) && model->rowCount(parent) > 1) {
            model->removeRow(r, parent);
        } else {
            // Recursively check rows of the first item (for trees)
            QModelIndex newParent = model->index(0, r, parent);
            if (model->columnCount(newParent)) {
                checkRows(model, 0, model->rowCount(newParent) - 1, newParent);
            }
        }
    }
    // Check the last row and add a new one if needed
    const int rowCount = model->rowCount(parent);
    if (!rowCount || !isRowEmpty(model, rowCount - 1, parent)) {
        model->insertRow(rowCount, parent);
        initRow(model, rowCount, parent);
    }
}

} // namespace QtUtils
