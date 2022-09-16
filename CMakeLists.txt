cmake_minimum_required(VERSION 3.21)

project(foo VERSION 1.0.0 LANGUAGES CXX)

set(MY_NS ${PROJECT_NAME})

include(GNUInstallDirs)

add_library(${PROJECT_NAME} SHARED src/foo.cpp)

# Generate API decl header
include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME}
    EXPORT_MACRO_NAME ${PROJECT_NAME_UPPER}_EXPORT
    EXPORT_FILE_NAME ${CMAKE_CURRENT_SOURCE_DIR}/include/${MY_NS}/${PROJECT_NAME}-export.h
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/${MY_NS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
