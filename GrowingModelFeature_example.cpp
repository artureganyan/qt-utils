/******************************************************************************
 * Copyright (c) 2015 Artur Eganyan
 *
 * This software is provided "AS IS", WITHOUT ANY WARRANTY, express or implied.
 ******************************************************************************/

#include "GrowingModelFeature.h"
#include "placeholderitemdelegate.h"
#include <QApplication>
#include <QWidget>
#include <QStandardItemModel>
#include <QTableView>
#include <QTreeView>
#include <QVBoxLayout>


namespace GrowingModelFeature_example {

// PlaceholderItemDelegate can be reimplemented to display placeholders
// for empty rows only (used in the Window class below)
class EmptyRowPlaceholderDelegate : public QtUtils::PlaceholderItemDelegate
{
protected:
    bool isPlaceholderVisible( const QModelIndex& index ) const
    {
        const int columnCount = index.model()->columnCount(index.parent());
        for (int c = 0; c < columnCount; ++ c) {
            QModelIndex item = index.sibling(index.row(), c);
            if (!item.data().toString().isEmpty()) {
                return false;
            }
        }
        return true;
    }
};

class Window : public QWidget
{
public:
    Window()
    {
        QStandardItemModel* model1 = new QStandardItemModel(0, 3);
        QTableView* table = new QTableView();
        table->setModel(model1);

        QStandardItemModel* model2 = new QStandardItemModel(1, 3);
        model2->insertColumns(0, 3, model2->index(0, 0));
        model2->insertRows(0, 1, model2->index(0, 0));

        QTreeView* tree = new QTreeView();
        tree->setModel(model2);
        tree->setAlternatingRowColors(true);

        QVBoxLayout* vbox = new QVBoxLayout(this);
        vbox->addWidget(table);
        vbox->addWidget(tree);

        QtUtils::GrowingModelFeature* feature = new QtUtils::GrowingModelFeature();
        feature->install(model1);
        feature->install(model2);

        // Uncomment this to set placeholders
        /*
        EmptyRowPlaceholderDelegate* delegate = new EmptyRowPlaceholderDelegate();
        delegate->setText("<Enter text>");
        delegate->setTextColor(Qt::gray);
        table->setItemDelegate(delegate);
        */

        resize(640, 480);
    }
};

int main( int argc, char** argv )
{
    QApplication a(argc, argv);

    Window window;
    window.show();

    return a.exec();
}

} // namespace GrowingModelFeature_example
