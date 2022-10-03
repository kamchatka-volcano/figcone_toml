cmake_minimum_required(VERSION 3.18)

project(figcone_toml VERSION 0.11.0 DESCRIPTION "toml11 parser adapter for figcone library")
include(GNUInstallDirs)
include(external/seal_lake)

set(INSTALL_FIGCONE_TREE ON)
SealLake_Import(
        figcone_tree 0.11.0
        GIT_REPOSITORY https://github.com/kamchatka-volcano/figcone_tree.git
        GIT_TAG        cmake_maintenance
)

SealLake_Download(
        toml11 3.7.1
        GIT_REPOSITORY https://github.com/ToruNiina/toml11.git
        GIT_TAG        v3.7.1
        DESTINATION include/figcone_toml/detail/external
        DIRECTORIES ${toml11_SOURCE_DIR}/toml
        FILES ${toml11_SOURCE_DIR}/toml.hpp
)

SealLake_HeaderOnlyLibrary(
        NAMESPACE figcone
        COMPILE_FEATURES cxx_std_17
        LIBRARIES figcone::figcone_tree
        DEPENDENCIES
            figcone_tree 0.11.0
)

SealLake_OptionalBuildSteps(tests)
