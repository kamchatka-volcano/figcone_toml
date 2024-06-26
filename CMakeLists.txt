cmake_minimum_required(VERSION 3.18)

project(figcone_toml VERSION 1.1.0 DESCRIPTION "toml11 parser adapter for figcone library")
include(external/seal_lake)

SealLake_IsInstallEnabled(INSTALL_FIGCONE_TREE)
SealLake_Import(
        figcone_tree 2.1.0
        GIT_REPOSITORY https://github.com/kamchatka-volcano/figcone_tree.git
        GIT_TAG        v2.1.0
)

SealLake_Bundle(
        NAME figcone_toml11
        SKIP_LOAD
        GIT_REPOSITORY https://github.com/ToruNiina/toml11.git
        GIT_TAG        v3.7.1
        TEXT_REPLACEMENTS
            "toml::" "figcone::toml::"
            "namespace toml" "namespace figcone::toml"
            "figcone::toml_" "toml_"
)

SealLake_ObjectLibrary(
        NAMESPACE figcone
        COMPILE_FEATURES cxx_std_17
        SOURCES
            src/parser.cpp
            src/datetime.cpp
        INCLUDES "${SEAL_LAKE_SOURCE_figcone_toml11}"
        INTERFACE_LIBRARIES figcone::figcone_tree
        DEPENDENCIES
            figcone_tree 2.1.0
)

SealLake_OptionalSubProjects(tests)
