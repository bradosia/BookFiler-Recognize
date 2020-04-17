cmake_minimum_required(VERSION 3.0)

message( STATUS )
message( STATUS "=============================================================================" )
message( STATUS "== MODULE Build Information                                        ==" )
message( STATUS "=============================================================================" )
message( STATUS "Version:           ${PROJECT_VERSION}")
if (CMAKE_BUILD_TYPE)
    message( STATUS "Build type:        ${CMAKE_BUILD_TYPE}")
endif(CMAKE_BUILD_TYPE)
message( STATUS "Using compiler:    ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}" )
message( STATUS "Architecture:      ${CMAKE_CXX_LIBRARY_ARCHITECTURE} / ${CMAKE_LIBRARY_ARCHITECTURE}" )
message( STATUS "System Name:       ${CMAKE_SYSTEM_NAME}" )
message( STATUS "Processor Name:    ${CMAKE_SYSTEM_PROCESSOR}" )
message( STATUS "Using Qt:          ${Qt5_VERSION}" )
message( STATUS "                     [at ${Qt5_DIR}]" )
message( STATUS "Installing to:     ${CMAKE_INSTALL_PREFIX}" )
message( STATUS "  " )
message( STATUS "Environment:" )
message( STATUS "CMAKE_INSTALL_BINDIR:       ${CMAKE_INSTALL_BINDIR}" )
message( STATUS "CMAKE_CURRENT_BINARY_DIR:   ${CMAKE_CURRENT_BINARY_DIR}" )
message( STATUS "CMAKE_BINARY_DIR:           ${CMAKE_BINARY_DIR}" )
message( STATUS "RELEASE_DIR:                ${RELEASE_DIR}" )
message( STATUS "=============================================================================" )
message( STATUS )

include(ExternalProject)

# ExternalProject_Add Arguments:
# TMP_DIR      = <prefix>/tmp
# STAMP_DIR    = <prefix>/src/<name>-stamp
# DOWNLOAD_DIR = <prefix>/src
# SOURCE_DIR   = <prefix>/src/<name>
# BINARY_DIR   = <prefix>/src/<name>-build
# INSTALL_DIR  = <prefix>
# LOG_DIR      = <STAMP_DIR>

ExternalProject_Add(BookFiler-Module-HocrEditor
  GIT_REPOSITORY "https://github.com/bradosia/BookFiler-Module-HocrEditor.git"
  PREFIX ${CMAKE_BINARY_DIR}
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR> -DPARENT_RELEASE_DIR=${RELEASE_DIR}
)

ExternalProject_Add(BookFiler-Module-HocrEditor
  GIT_REPOSITORY "https://github.com/bradosia/BookFiler-Module-HTTP-beast.git"
  PREFIX ${CMAKE_BINARY_DIR}
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR> -DPARENT_RELEASE_DIR=${RELEASE_DIR}
)

ExternalProject_Add(BookFiler-Module-HocrEditor
  GIT_REPOSITORY "https://github.com/bradosia/BookFiler-Module-OCR-Tesseract.git"
  PREFIX ${CMAKE_BINARY_DIR}
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR> -DPARENT_RELEASE_DIR=${RELEASE_DIR}
)

ExternalProject_Add(BookFiler-Module-HocrEditor
  GIT_REPOSITORY "https://github.com/bradosia/BookFiler-Module-PDF-PoDoFo.git"
  PREFIX ${CMAKE_BINARY_DIR}
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR> -DPARENT_RELEASE_DIR=${RELEASE_DIR}
)

ExternalProject_Add(BookFiler-Module-HocrEditor
  GIT_REPOSITORY "https://github.com/bradosia/BookFiler-Module-Recognize.git"
  PREFIX ${CMAKE_BINARY_DIR}
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR> -DPARENT_RELEASE_DIR=${RELEASE_DIR}
)

ExternalProject_Add(BookFiler-Module-HocrEditor
  GIT_REPOSITORY "https://github.com/bradosia/BookFiler-Module-Recognize-Database.git"
  PREFIX ${CMAKE_BINARY_DIR}
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR> -DPARENT_RELEASE_DIR=${RELEASE_DIR}
)
