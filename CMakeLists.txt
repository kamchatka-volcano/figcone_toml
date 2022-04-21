cmake_minimum_required(VERSION 3.18)

project(figcone_toml VERSION 0.9.0 DESCRIPTION "toml11 parser adapter for figcone library")

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(FIGCONE_TOML_SUBPROJECT OFF)
else()
    set(FIGCONE_TOML_SUBPROJECT ON)
endif()

find_package(figcone_tree 0.9.0 QUIET)
if (NOT figcone_tree_FOUND)
    message("Configuration info: figcone_tree library wasn't found on your system, downloading it from the GitHub repository")
    include (external/figcone_tree)
endif()

find_package(toml11 3.7.1 QUIET)
if (NOT toml11_FOUND)
    message("Configuration info: toml11 library wasn't found on your system, downloading it from the GitHub repository")
    include(external/toml)
endif()


add_library(figcone_toml INTERFACE)
add_library(figcone::figcone_toml ALIAS figcone_toml)

target_compile_features(figcone_toml INTERFACE cxx_std_17)
target_include_directories(
        figcone_toml
        INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_link_libraries(figcone_toml INTERFACE figcone::figcone_tree toml11::toml11)

option(ENABLE_TESTS "Enable tests" OFF)
if (ENABLE_TESTS AND NOT FIGCONE_TOML_SUBPROJECT)
    enable_testing()
    add_subdirectory(tests)
endif()

option(INSTALL_FIGCONE_TOML "Install figcone_toml library unconditionally" OFF)
if (NOT FIGCONE_TOML_SUBPROJECT OR INSTALL_FIGCONE_TOML)
    include(GNUInstallDirs)
    install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/figcone_toml DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

    set(FIGCONE_TOML_PACK_PATH ${CMAKE_INSTALL_LIBDIR}/cmake/figcone_toml)
    install(TARGETS figcone_toml
            EXPORT figcone_toml-targets
            PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/figcone_toml)
    install(EXPORT figcone_toml-targets
            FILE figcone_tomlTargets.cmake
            NAMESPACE figcone::
            DESTINATION ${FIGCONE_TOML_PACK_PATH})

    include(CMakePackageConfigHelpers)
    write_basic_package_version_file(
            ${CMAKE_CURRENT_BINARY_DIR}/figcone_tomlConfigVersion.cmake
            COMPATIBILITY SameMajorVersion
            ARCH_INDEPENDENT
    )

    configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/cmake/figcone_tomlConfig.cmake.in
            ${CMAKE_CURRENT_BINARY_DIR}/figcone_tomlConfig.cmake
            INSTALL_DESTINATION ${FIGCONE_TOML_PACK_PATH}
    )

    install(FILES
            ${CMAKE_CURRENT_BINARY_DIR}/figcone_tomlConfig.cmake
            ${CMAKE_CURRENT_BINARY_DIR}/figcone_tomlConfigVersion.cmake
            DESTINATION ${FIGCONE_TOML_PACK_PATH}
    )
endif()
