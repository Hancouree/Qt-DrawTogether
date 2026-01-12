QT += quick websockets

SOURCES += \
        main.cpp \
        requestmanager.cpp \
        socket.cpp \
        statemachine.cpp

resources.files = main.qml ConnectionPage.qml
resources.prefix = /$${TARGET}
RESOURCES += resources \
    resources.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    requestmanager.h \
    socket.h \
    statemachine.h

DISTFILES += \
    AuthenticationPage.qml \
    ConnectionPage.qml \
    MenuPage.qml
