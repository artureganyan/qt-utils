Qt utils
--------

Various Qt utils and helper classes. Compiled with mingw 5.1.0 and 
Qt 5.5.1.


PlaceholderItemDelegate
-----------------------

This delegate displays placeholder text in item views. The text can be 
specified for columns, rows or particular items. It can also be stored in
an item data under the custom role.

```cpp
QtUtils::PlaceholderItemDelegate* placeholder = new QtUtils::PlaceholderItemDelegate();
placeholder->setTextForRow(0, "Row hint");
placeholder->setTextForColumn(1, "Column hint");
placeholder->setTextForItem(0, 2, "Item hint");
placeholder->setTextForAllItems("Table hint");
placeholder->setTextColor(Qt::gray);

QStandardItemModel* model = new QStandardItemModel(3, 3);
model->setItemDelegate(placeholder);
```

![example](/images/PlaceholderItemDelegate.png)


GrowingModelFeature
-------------------

This feature automatically appends rows when existing ones are filled, and 
remove rows when they become empty.

```cpp
QStandardItemModel* model = new QStandardItemModel(0, 3);
QtUtils::GrowingModelFeature* feature = new QtUtils::GrowingModelFeature();
feature->install(model);
```

The feature can be combined with PlaceholderItemDelegate so that empty rows 
will hold a message like "Enter text" (see the example).

![example](/images/GrowingModelFeature.png)
