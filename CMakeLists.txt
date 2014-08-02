cmake_minimum_required(VERSION 2.6)

project(phyloviz)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cMake")

find_package(PkgConfig)
find_package(Qt4 REQUIRED)
find_package(Coin3D REQUIRED)
find_package(SoQt REQUIRED)
INCLUDE(${QT_USE_FILE})

# add_subdirectory(src/ev-iv)
ADD_EXECUTABLE(ev-iv src/ev-iv/ev-iv.cc)
TARGET_LINK_LIBRARIES(ev-iv ${QT_LIBRARIES} ${SOQT_LIBRARIES} ${COIN3D_LIBRARIES})


ADD_EXECUTABLE(ph2iv src/ph2iv/ph2iv.c)

IF(UNIX)
  TARGET_LINK_LIBRARIES(ph2iv m)
ENDIF(UNIX)
# TARGET_LINK_LIBRARIES(ph2iv ${QT_LIBRARIES} ${SOQT_LIBRARIES} ${COIN3D_LIBRARIES})
