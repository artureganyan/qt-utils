/******************************************************************************
 * Copyright (c) 2015 Artur Eganyan
 *
 * This software is provided "AS IS", WITHOUT ANY WARRANTY, express or implied.
 ******************************************************************************/

#include "PlaceholderItemDelegate.h"
#include <QApplication>
#include <QWidget>
#include <QStandardItemModel>
#include <QTableView>
#include <QTreeView>
#include <QVBoxLayout>


namespace PlaceholderItemDelegate_example {

class Window : public QWidget
{
public:
    Window()
    {
        int placeholderRole = Qt::UserRole + 1;

        // Example model
        QStandardItemModel* model = new QStandardItemModel(3, 3);
        model->setData(model->index(0, 2), "Hint for item", placeholderRole);

        // Table view
        QTableView* table = new QTableView();
        table->setModel(model);

        // Placeholder delegate
        QtUtils::PlaceholderItemDelegate* placeholder = new QtUtils::PlaceholderItemDelegate();
        placeholder->setTextForColumn(0, "Column hint 1");
        placeholder->setTextForColumn(1, "Column hint 2");
        placeholder->setTextForRow(2, "Row hint");
        placeholder->setTextColor(Qt::gray);
        placeholder->setDataRole(placeholderRole);

        table->setItemDelegate(placeholder);

        // Layout
        QVBoxLayout* vbox = new QVBoxLayout(this);
        vbox->addWidget(table);

        resize(640, 480);
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Window window;
    window.show();

    return a.exec();
}

} // namespace PlaceholderItemDelegate_example
