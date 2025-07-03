cmake_minimum_required(VERSION 3.18)

project(figcone_toml_deps)
include(seal_lake.cmake)

SealLake_v040_Bundle(
        NAME figcone_tree
        URL https://github.com/kamchatka-volcano/figcone_tree/releases/download/v2.2.0/figcone_tree-v2.2.0.zip
        SKIP_LOAD
        DESTINATION deps/figcone_tree
)

SealLake_v040_Bundle(
        NAME figcone_toml11
        SKIP_LOAD
        DIRECTORIES include
        DESTINATION deps/figcone_toml11/
        GIT_REPOSITORY https://github.com/ToruNiina/toml11.git
        GIT_TAG        v4.4.0
        GIT_SUBMODULES include #disable submodules by specifying an existing project directory that isn't a submodule
        TEXT_REPLACEMENTS
        "toml::" "figcone::toml::"
        "namespace toml" "namespace figcone::toml"
        "figcone::toml_" "toml_"
)