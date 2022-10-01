cmake_minimum_required(VERSION 3.18)

project(figcone_toml VERSION 0.11.0 DESCRIPTION "toml11 parser adapter for figcone library")
include(GNUInstallDirs)
include(external/seal_lake)

set(INSTALL_FIGCONE_TREE ON)

SealLake_FindOrDownload(
        figcone_tree 0.11.0
        GIT_REPOSITORY https://github.com/kamchatka-volcano/figcone_tree.git
        GIT_TAG        cmake_maintenance
)

unset(toml11_INSTALL)
SealLake_FindOrDownload(
        toml11 3.7.1
        GIT_REPOSITORY https://github.com/ToruNiina/toml11.git
        GIT_TAG        v3.7.1
)

SealLake_HeaderOnlyLibrary(
        NAMESPACE figcone
        COMPILE_FEATURES cxx_std_17
        INCLUDES figcone_toml/detail/external
        BUILD_STAGE_INCLUDES ${toml11_SOURCE_DIR}
        LIBRARIES figcone::figcone_tree
)

SealLake_OptionalBuildSteps(
        IF_ENABLED_AND_STANDALONE tests
)

SealLake_Install(
        PATH figcone_toml/detail/external
        DIRECTORIES ${toml11_SOURCE_DIR}/toml
        FILES ${toml11_SOURCE_DIR}/toml.hpp
)
