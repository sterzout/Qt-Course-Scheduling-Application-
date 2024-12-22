QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    admincoursedecision.cpp \
    adminselectaction.cpp \
    adminstudentaction.cpp \
    course.cpp \
    coursecatalog.cpp \
    coursepage.cpp \
    coursetimetable.cpp \
    createaccountpage.cpp \
    falltermpage.cpp \
    loginorcreate.cpp \
    main.cpp \
    mainwindow.cpp \
    notifications.cpp \
    prerequisitepage.cpp \
    student.cpp \
    studentprogresscheck.cpp \
    user.cpp \
    wintertermpage.cpp

HEADERS += \
    Admin.h \
    admincoursedecision.h \
    adminproxy.h \
    adminselectaction.h \
    adminstudentaction.h \
    course.h \
    coursecatalog.h \
    coursepage.h \
    coursetimetable.h \
    createaccountpage.h \
    falltermpage.h \
    loginorcreate.h \
    mainwindow.h \
    notifications.h \
    prerequisitepage.h \
    student.h \
    studentprogresscheck.h \
    user.h \
    wintertermpage.h

FORMS += \
    admincoursedecision.ui \
    adminselectaction.ui \
    adminstudentaction.ui \
    coursepage.ui \
    coursetimetable.ui \
    createaccountpage.ui \
    falltermpage.ui \
    loginorcreate.ui \
    mainwindow.ui \
    notifications.ui \
    prerequisitepage.ui \
    studentprogresscheck.ui \
    wintertermpage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    courses.txt \
    notifications.txt \
    studentCourseInfo.txt \
    tempfile.txt \
    userlogininfo.txt
