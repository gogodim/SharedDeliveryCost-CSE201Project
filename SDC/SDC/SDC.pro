TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
#QT += gui widgets xml

SOURCES += \
        Bucket.cpp \
        Company.cpp \
        Coordinate.cpp \
        Database.cpp \
        Order.cpp \
        OrderPage.cpp \
        User.cpp \
        main.cpp \
        registerpage.cpp

INCLUDEPATH += C:/Boost/include/boost-1_67 \
               C:/wt-4.4.0/src \
               C:/wt-4.4.0

LIBS += -LC:/wt-4.4.0/src/http -llibwthttp \
                -LC:/wt-4.4.0/src -llibwt \
                -LC:/wt-4.4.0/src/Wt/Dbo -llibwtdbo \
                -LC:/wt-4.4.0/src/Wt/Dbo/backend -llibwtdbosqlite3

LIBS += -lole32

LIBS  +=  -LC:/Boost/lib \
                -llibboost_locale-mgw73-mt-x64-1_67 \
                -llibboost_thread-mgw73-mt-x64-1_67 \
                -llibboost_program_options-mgw73-mt-x64-1_67 \
                -llibboost_filesystem-mgw73-mt-x64-1_67 \
                -llibboost_system-mgw73-mt-x64-1_67

LIBS  +=  -LC:/Qt/Tools/mingw730_64/i686-w64-mingw32/lib  \
                -llibws2_32 \
                -llibwsock32

HEADERS += \
    Bucket.h \
    Company.h \
    Coordinate.h \
    Database.h \
    Order.h \
    OrderPage.h \
    User.h \
    registerpage.h

DISTFILES += \
    css/shared.css \
    css/shared.css \
    images/logo.png \
    resources/form.css \
    resources/html4_default.css \
    resources/moz-transitions.css \
    resources/transitions.css \
    resources/webkit-transitions.css \
    shared.css
