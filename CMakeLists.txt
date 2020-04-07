cmake_minimum_required(VERSION 3.1)

project(BookFiler-Recognize VERSION 1.0.0 LANGUAGES CXX)
set(BIN_NAME BookFiler-Recognize)

# Configurable Options
OPTION(BUILD_SHARED_LIBS "Build shared libraries" ON)
OPTION(BUILD_STATIC_LIBS "Build static libraries" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.10")

find_package(Qt5Widgets REQUIRED)
find_package(Boost 1.56 REQUIRED COMPONENTS
             system filesystem)

# TODO: Use Verdigris so no MOC needed
# TODO: Explicitly call RCC tool in prebuild command
# QT tools
# Automatically compile .ui to .h
# set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
# set(CMAKE_INCLUDE_CURRENT_DIR ON)
# set(QTDIR $ENV{QTDIR})
# set(CMAKE_PREFIX_PATH ${QTDIR})
# set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/Modules)

include_directories(
  third_party/rapidjson/include/
  third_party/Module-Manager/include/
  third_party/Settings-Manager/include/
  src/modules
)

link_directories(
   lib/
   third_party/Module-Manager/lib/
   third_party/Settings-Manager/lib/
)

# MODULES
add_subdirectory(src/modules/)
add_subdirectory(third_party/Module-Manager/)
add_subdirectory(third_party/Settings-Manager/)

set(SOURCES ${SOURCES}
  src/UI/main.cpp
  src/UI/Application.cpp
  src/UI/MainWindow.cpp

  src/UI/Application.hpp
  src/UI/MainWindow.hpp
  src/UI/ui_main.hpp
  src/core/config.hpp
)

set(RESOURCES ${RESOURCES}
  resources/icons_file.qrc
)

add_executable(${BIN_NAME} ${SOURCES} ${RESOURCES})

set(LIBRARIES ${LIBRARIES}
  # QT5
  Qt5::Widgets

  # Boost
  Boost::system
  Boost::filesystem

  # bradosia
  ModuleManager
  SettingsManager
)

if(WIN32)
    set(LIBRARIES ${LIBRARIES}
        # Windows Libraries
        z
        stdc++
        gcc
        uuid

        windowscodecs
        opengl32
        gdi32
        comdlg32
        oleaut32
        imm32
        winmm
        winspool
        kernel32
        user32
        shell32
        ole32
        advapi32
        ws2_32
        mingw32
        rpcrt4
    )
elseif(UNIX)
    set(LIBRARIES ${LIBRARIES}
        # Unix Libraries
        z
        stdc++
        gcc
        uuid

        pthread
        glib-2.0
        gthread-2.0
        dl
        m
    )
endif()

target_link_libraries(${BIN_NAME} PRIVATE ${LIBRARIES})

# OS-Architecture specific libraries
if(APPLE)
  find_library(COCOA_FRAMEWORK Cocoa)
  target_link_libraries(${BIN_NAME} ${COCOA_FRAMEWORK})
endif()

# OS-Architecture specific properties
if(WIN32)
  set_target_properties(${BIN_NAME} PROPERTIES
    WIN32 TRUE
  )
elseif(APPLE)
  set_target_properties(${BIN_NAME} PROPERTIES
    MACOSX_BUNDLE TRUE
    RESOURCE "${RESOURCES}"
  )
endif()

# Post Build
# Copy default setttings
add_custom_command(TARGET ${BIN_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_SOURCE_DIR}/resources/settings.json" "${CMAKE_BINARY_DIR}")
add_custom_command(TARGET ${BIN_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/resources/traineddata/" "${CMAKE_BINARY_DIR}/traineddata/")
