load(qt_module)

TARGET = qtmedia_fakeradio
QT += multimediakit-private
PLUGIN_TYPE = mediaservice

load(qt_plugin)
DESTDIR = $$QT.multimediakit.plugins/$${PLUGIN_TYPE}

HEADERS += \
  fakeradioserviceplugin.h \
  fakeradioservice.h \
  fakeradiotunercontrol.h

SOURCES += \
  fakeradioserviceplugin.cpp \
  fakeradioservice.cpp \
  fakeradiotunercontrol.cpp


target.path += $$[QT_INSTALL_PLUGINS]/$${PLUGIN_TYPE}
INSTALLS += target

