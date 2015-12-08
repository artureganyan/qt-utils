TEMPLATE = app
TARGET = qt_utils

QT += core gui widgets
CONFIG += console c++11

SOURCES += example.cpp
SOURCES += GrowingModelFeature.cpp
SOURCES += GrowingModelFeature_example.cpp
SOURCES += PlaceholderItemDelegate.cpp
SOURCES += PlaceholderItemDelegate_example.cpp

HEADERS += GrowingModelFeature.h
HEADERS += PlaceholderItemDelegate.h
