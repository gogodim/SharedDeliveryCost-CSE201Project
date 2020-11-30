TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        Orderpage.cpp \
        Session.cpp \
        User.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += C:/Boost/include/boost-1_67 \
               C:/wt-4.4.0/src \
               C:/wt-4.4.0

win32: LIBS += -LC:/wt-4.4.0/src/http -llibwthttp \
                -LC:/wt-4.4.0/src -llibwt \
                -LC:/wt-4.4.0/src/Wt/Dbo -llibwtdbo \
                -LC:/wt-4.4.0/src/Wt/Dbo/backend -llibwtdbosqlite3

win32: LIBS += -lole32

win32: LIBS += -LC:/Boost/lib \
                -llibboost_locale-mgw73-mt-x32-1_67 \
                -llibboost_thread-mgw73-mt-x32-1_67 \
                -llibboost_program_options-mgw73-mt-x32-1_67 \
                -llibboost_filesystem-mgw73-mt-x32-1_67 \
                -llibboost_system-mgw73-mt-x32-1_67

win32: LIBS += -LC:/Qt/Tools/mingw730_32/i686-w64-mingw32/lib \
                -llibws2_32 \
                -llibwsock32

HEADERS += \
    Orderpage.h \
    User.h \
    Session.h
