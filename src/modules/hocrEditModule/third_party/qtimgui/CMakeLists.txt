cmake_minimum_required(VERSION 3.1)

set(project_name qtimgui)
project(${project_name} VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(lib_static_name ${project_name})

find_package(Qt5Widgets REQUIRED)
set(CMAKE_AUTOMOC ON)

set(SOURCES ${SOURCES}
  qtimgui/QtImGui.cpp
  qtimgui/ImGuiRenderer.cpp

  qtimgui/QtImGui.h
  qtimgui/ImGuiRenderer.h
)

add_library(${lib_static_name} STATIC ${SOURCES})

target_include_directories(${lib_static_name} PUBLIC
  ../imgui/include/
)

target_link_libraries(${lib_static_name} PUBLIC
    # QT5
    Qt5::Widgets
)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Post Build
# Copy default setttings
add_custom_command(TARGET ${lib_static_name} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${PROJECT_SOURCE_DIR}/include/")
add_custom_command(TARGET ${lib_static_name} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${PROJECT_SOURCE_DIR}/include/${project_name}/")
add_custom_command(TARGET ${lib_static_name} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${PROJECT_SOURCE_DIR}/lib/")
add_custom_command(TARGET ${lib_static_name} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_SOURCE_DIR}/qtimgui/QtImGui.h" "${PROJECT_SOURCE_DIR}/include/${project_name}/")
add_custom_command(TARGET ${lib_static_name} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_SOURCE_DIR}/qtimgui/ImGuiRenderer.h" "${PROJECT_SOURCE_DIR}/include/${project_name}/")
add_custom_command(TARGET ${lib_static_name} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${lib_static_name}> "${PROJECT_SOURCE_DIR}/lib/")
