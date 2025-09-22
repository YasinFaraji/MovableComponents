cmake_minimum_required(VERSION 3.14)

project(MovableComponents VERSION 1.0)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Qml Quick REQUIRED)

if(ANDROID)
    add_library(MovableComponents SHARED
      main.cpp
      Core/DataGenerator.h
      Core/DataGenerator.cpp
      Core/MainController.h
      Core/MainController.cpp
    )
else()
    add_executable(MovableComponents
      main.cpp
      Core/DataGenerator.h
      Core/DataGenerator.cpp
      Core/MainController.h
      Core/MainController.cpp
    )
endif()

target_compile_definitions(MovableComponents
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(MovableComponents
  PRIVATE Qt5::Core Qt5::Qml Qt5::Quick)

qt5_add_resources(QML_RESOURCES qml.qrc)
qt5_add_resources(CONFIG_RESOURCES assets/config/config.qrc)

target_sources(${PROJECT_NAME} PRIVATE ${QML_RESOURCES} ${CONFIG_RESOURCES})
