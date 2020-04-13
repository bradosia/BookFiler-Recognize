cmake_minimum_required(VERSION 3.1)

set(project_name imgui)
project(${project_name} VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(lib_static_name ${project_name})

include_directories(
  imgui-1.75/
  glew-2.1.0/include
)

set(SOURCES ${SOURCES}
  imgui-1.75/imgui.cpp
  imgui-1.75/imgui_demo.cpp
  imgui-1.75/imgui_draw.cpp
  imgui-1.75/imgui_widgets.cpp
  imgui-1.75/examples/imgui_impl_opengl3.cpp
  #glew-2.1.0/src/glew.c

  imgui-1.75/imgui.h
  imgui-1.75/examples/imgui_impl_opengl3.h
  #glew-2.1.0/include/GL/glew.h
)

set(STATIC_COMPILE_DEFINITIONS
  -DSTATIC_LIBRARY
  #-DGLEW_STATIC
)

add_library(${lib_static_name} STATIC ${SOURCES})

# Compile Definitions
target_compile_definitions(${lib_static_name} PUBLIC ${STATIC_COMPILE_DEFINITIONS})

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Post Build
# Copy default setttings
add_custom_command(TARGET ${lib_static_name} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${PROJECT_SOURCE_DIR}/include/")
add_custom_command(TARGET ${lib_static_name} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${PROJECT_SOURCE_DIR}/include/${project_name}/")
add_custom_command(TARGET ${lib_static_name} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${PROJECT_SOURCE_DIR}/include/GL/")
add_custom_command(TARGET ${lib_static_name} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${PROJECT_SOURCE_DIR}/lib/")
add_custom_command(TARGET ${lib_static_name} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_SOURCE_DIR}/imgui-1.75/imgui.h" "${PROJECT_SOURCE_DIR}/include/${project_name}/")
add_custom_command(TARGET ${lib_static_name} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_SOURCE_DIR}/imgui-1.75/imconfig.h" "${PROJECT_SOURCE_DIR}/include/${project_name}/")
add_custom_command(TARGET ${lib_static_name} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_SOURCE_DIR}/imgui-1.75/examples/imgui_impl_opengl3.h" "${PROJECT_SOURCE_DIR}/include/${project_name}/")
add_custom_command(TARGET ${lib_static_name} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_SOURCE_DIR}/glew-2.1.0/include/GL/glew.h" "${PROJECT_SOURCE_DIR}/include/GL/")
add_custom_command(TARGET ${lib_static_name} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${lib_static_name}> "${PROJECT_SOURCE_DIR}/lib/")
