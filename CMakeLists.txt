cmake_minimum_required(VERSION 3.21)

project(foo VERSION 1.0.0 LANGUAGES CXX)

if(NOT DEFINED MY_NS)
    set(MY_NS ${PROJECT_NAME})
endif()

string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPER)

include(GNUInstallDirs)

add_library(${PROJECT_NAME} src/foo.cpp)

target_include_directories(${PROJECT_NAME}
    INTERFACE PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# Generate API decl header
include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME}
    EXPORT_MACRO_NAME ${PROJECT_NAME_UPPER}_EXPORT
    EXPORT_FILE_NAME ${CMAKE_CURRENT_SOURCE_DIR}/include/${MY_NS}/${PROJECT_NAME}-export.h
)

# Install targets
install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/${MY_NS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(FILES
    $<TARGET_PDB_FILE:${PROJECT_NAME}>
    DESTINATION ${CMAKE_INSTALL_BINDIR} OPTIONAL
)

# Export targets
install(EXPORT ${PROJECT_NAME}-targets
    FILE ${PROJECT_NAME}-targets.cmake
    NAMESPACE ${MY_NS}::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

# Export configuration files
include(CMakePackageConfigHelpers)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.cmake.in
    ${CMAKE_BINARY_DIR}/cmake/${PROJECT_NAME}-config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

write_basic_package_version_file(
    ${CMAKE_BINARY_DIR}/cmake/${PROJECT_NAME}-config-version.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

install(
    FILES
        ${CMAKE_BINARY_DIR}/cmake/${PROJECT_NAME}-config.cmake
        ${CMAKE_BINARY_DIR}/cmake/${PROJECT_NAME}-config-version.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

# Final export
export(EXPORT ${PROJECT_NAME}-targets
    FILE ${CMAKE_BINARY_DIR}/cmake/${PROJECT_NAME}-targets.cmake
    NAMESPACE ${MY_NS}::
)