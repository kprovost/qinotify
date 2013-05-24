cmake_minimum_required(VERSION 2.8)

project(qinotify)
find_package(Qt4 REQUIRED)

set(SRC src/main.cpp)
#set(SRC src/main.cpp src/viewer.cpp)
#set(HDR src/viewer.h)

qt4_wrap_cpp(HDR_MOC ${SRC})

include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

add_executable(qinotify ${SRC} ${HDR_MOC})
target_link_libraries(qinotify ${QT_LIBRARIES})
