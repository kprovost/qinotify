cmake_minimum_required(VERSION 2.8)

project(qinotify)
find_package(Qt4 REQUIRED QtCore QtGui QtWebKit)

set(SRC src/main.cpp src/mainwindow.cpp src/viewer.cpp src/inotifier.cpp)
set(HDR src/mainwindow.h src/viewer.h src/inotifier.h)

qt4_wrap_cpp(HDR_MOC ${HDR})

include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

add_executable(qinotify ${SRC} ${HDR_MOC})
target_link_libraries(qinotify ${QT_LIBRARIES})
