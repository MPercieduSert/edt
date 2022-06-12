QT += widgets sql

CONFIG += c++17
CONFIG += link_prl

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../library/release/ -llibrary
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../library/debug/ -llibrary
else:unix: LIBS += -L$$OUT_PWD/../library/ -llibrary

INCLUDEPATH += $$PWD/../library
DEPENDPATH += $$PWD/../library

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../library/release/liblibrary.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../library/debug/liblibrary.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../library/release/library.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../library/debug/library.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../library/liblibrary.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../compilation/libmps/entities/release/ -lentities
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../compilation/libmps/entities/debug/ -lentities
else:unix: LIBS += -L$$PWD/../../compilation/libmps/entities/ -lentities

INCLUDEPATH += $$PWD/../../libmps/entities
DEPENDPATH += $$PWD/../../libmps/entities

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../compilation/libmps/entities/release/libentities.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../compilation/libmps/entities/debug/libentities.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../compilation/libmps/entities/release/entities.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../compilation/libmps/entities/debug/entities.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../compilation/libmps/entities/libentities.a


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../compilation/libmps/manager/release/ -lmanager
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../compilation/libmps/manager/debug/ -lmanager
else:unix: LIBS += -L$$PWD/../../compilation/libmps/manager/ -lmanager

INCLUDEPATH += $$PWD/../../libmps/manager
DEPENDPATH += $$PWD/../../libmps/manager

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../compilation/libmps/manager/release/libmanager.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../compilation/libmps/manager/debug/libmanager.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../compilation/libmps/manager/release/manager.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../compilation/libmps/manager/debug/manager.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../compilation/libmps/manager/libmanager.a


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../compilation/libmps/widget/release/ -lwidget
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../compilation/libmps/widget/debug/ -lwidget
else:unix: LIBS += -L$$PWD/../../compilation/libmps/widget/ -lwidget

INCLUDEPATH += $$PWD/../../libmps/widget
DEPENDPATH += $$PWD/../../libmps/widget

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../compilation/libmps/widget/release/libwidget.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../compilation/libmps/widget/debug/libwidget.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../compilation/libmps/widget/release/widget.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../compilation/libmps/widget/debug/widget.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../compilation/libmps/widget/libwidget.a


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../compilation/libmps/model/release/ -lmodel
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../compilation/libmps/model/debug/ -lmodel
else:unix: LIBS += -L$$PWD/../../compilation/libmps/model/ -lmodel

INCLUDEPATH += $$PWD/../../libmps/model
DEPENDPATH += $$PWD/../../libmps/model

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../compilation/libmps/model/release/libmodel.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../compilation/libmps/model/debug/libmodel.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../compilation/libmps/model/release/model.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../compilation/libmps/model/debug/model.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../compilation/libmps/model/libmodel.a


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../compilation/libmps/fen/release/ -lfen
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../compilation/libmps/fen/debug/ -lfen
else:unix: LIBS += -L$$PWD/../../compilation/libmps/fen/ -lfen

INCLUDEPATH += $$PWD/../../libmps/fen
DEPENDPATH += $$PWD/../../libmps/fen

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../compilation/libmps/fen/release/libfen.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../compilation/libmps/fen/debug/libfen.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../compilation/libmps/fen/release/fen.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../compilation/libmps/fen/debug/fen.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../compilation/libmps/fen/libfen.a

