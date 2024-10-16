QT       += core gui charts sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    databaseapi.cpp \
    models/adminuser.cpp \
    models/memberuser.cpp \
    models/user.cpp \
    pages/adminpage.cpp \
    main.cpp \
    mainwindow.cpp \
    pages/attendancepage.cpp \
    pages/dashboard.cpp \
    pages/homepage.cpp \
    pages/registerpage.cpp \
    pages/scheduleclasspaage.cpp \
    pages/viewsubscription.cpp \
    pages/settingspage.cpp \
    sidebar.cpp \
    userBusinessLogic/userbusinesslogic.cpp

HEADERS += \
    databaseapi.h \
    models/adminuser.h \
    models/memberuser.h \
    models/user.h \
    pages/adminpage.h \
    mainwindow.h \
    pages/attendancepage.h \
    pages/dashboard.h \
    pages/homepage.h \
    pages/registerpage.h \
    pages/scheduleclasspaage.h \
    pages/viewsubscription.h \
    pages/settingspage.h \
    sidebar.h \
    userBusinessLogic/userbusinesslogic.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
