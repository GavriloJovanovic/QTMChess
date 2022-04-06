cmake_minimum_required(VERSION 3.5)

project(QTMChess VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(BUILD_PATH "${CMAKE_CURRENT_SOURCE_DIR}/build")
set(EXECUTABLE_OUTPUT_PATH "${BUILD_PATH}")

set(PROJECT_SOURCES
    ai.cpp
    CBoard.cpp
    CMove.cpp
    CMoveList.cpp
    main.cpp
    mainwindow.cpp
    qtboard.cpp
    qtcell.cpp
    qtscene.cpp
    ai.h
    CBoard.h
    CMove.h
    CMoveList.h
    CSquare.h
    mainwindow.h
    qtboard.h
    qtcell.h
    qtscene.h
)

set(UIS
    mainwindow.ui
)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(QTMChess
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

else()
    if(ANDROID)
        add_library(QTMChess SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(QTMChess
            ${PROJECT_SOURCES}
            ${UIS}
        )
    endif()
endif()

target_link_libraries(QTMChess PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(QTMChess PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(QTMChess)
endif()