QT += core network
QT -= gui

CONFIG += c++11

TARGET = pclsphere
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = vcapp

SOURCES += main.cpp frame_processor.cpp net_adapter.cpp point_viewer.cpp
HEADERS += frame_processor.h net_adapter.h point_viewer.h
