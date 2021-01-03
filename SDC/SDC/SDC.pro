TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        NotificationWidget.cpp \
        Session.cpp \
        main1.cpp \
        notification.cpp


INCLUDEPATH += C:/Boost/include/boost-1_67 \
               C:/wt-4.4.0/src \
               C:/wt-4.4.0

LIBS += -LC:/wt-4.4.0/src/http -llibwthttp \
                -LC:/wt-4.4.0/src -llibwt \
                -LC:/wt-4.4.0/src/Wt/Dbo -llibwtdbo \
                -LC:/wt-4.4.0/src/Wt/Dbo/backend -llibwtdbosqlite3

LIBS += -lole32

LIBS += -LC:/Boost/lib \
                -llibboost_locale-mgw73-mt-x64-1_67 \
                -llibboost_thread-mgw73-mt-x64-1_67 \
                -llibboost_program_options-mgw73-mt-x64-1_67 \
                -llibboost_filesystem-mgw73-mt-x64-1_67 \
                -llibboost_system-mgw73-mt-x64-1_67

LIBS += -LC:/Qt/Tools/mingw730_32/i686-w64-mingw32/lib \
                -llibws2_32 \
                -llibwsock32

HEADERS += \
    NotificationWidget.h \
    Session.h \
    notification.h

DISTFILES += \
    CSS/style.css
