
# @公羽向阳 2021-06-08T13:31:29

QT += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = password_generator
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    crypto.cpp

HEADERS += \
    mainwindow.h \
    crypto.h

FORMS += \
    mainwindow.ui

VERSION = 1.0.0.0

win32 {
    # gbk
    QMAKE_TARGET_PRODUCT = \xc3\xdc\xc2\xeb\xc9\xfa\xb3\xc9\xc6\xf7
    QMAKE_TARGET_COMPANY = \xb9\xab\xd3\xf0\xcf\xf2\xd1\xf4
    QMAKE_TARGET_DESCRIPTION = \xd2\xbb\xb8\xf6\xc3\xdc\xc2\xeb\xc9\xfa\xb3\xc9\xb9\xa4\xbe\xdf
    QMAKE_TARGET_COPYRIGHT = @\xb9\xab\xd3\xf0\xcf\xf2\xd1\xf4
}else {
    QMAKE_TARGET_PRODUCT = 密码生成器
    QMAKE_TARGET_COMPANY = 公羽向阳
    QMAKE_TARGET_DESCRIPTION = 一个密码生成工具
    QMAKE_TARGET_COPYRIGHT = ©公羽向阳
}
