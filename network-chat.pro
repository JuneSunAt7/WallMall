HEADERS       = chatdialog.h \
                client.h \
                connection.h \
                crypttraffic.h \
                peermanager.h \
                server.h
SOURCES       = chatdialog.cpp \
                client.cpp \
                connection.cpp \
                crypttraffic.cpp \
                features_march.cpp \
                features_ver2.cpp \
                main.cpp \
                peermanager.cpp \
                server.cpp
FORMS         = chatdialog.ui
QT           += network widgets

QT += webenginewidgets
QT += network
DEFINES += QT_DEPRECATED_WARNINGS
LIBS += -LD:/Programs/OpenSSL-Win64/lib -llibcrypto
LIBS += -LD:/Programs/OpenSSL-Win64/lib -llibssl
requires(qtConfig(udpsocket))
requires(qtConfig(listwidget))

# install
target.path = $$[QT_INSTALL_EXAMPLES]/network/network-chat
INSTALLS += target
win32: RC_ICONS = $$PWD/mainicon.ico


INCLUDEPATH += \
     D:/Programs/OpenSSL-Win64/include
     D:/Programs/CryptFileDevice/src


