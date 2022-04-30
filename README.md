**figcone_toml** - is a [`toml11`](https://github.com/ToruNiina/toml11) configuration parser adapter for [`figcone`](https://github.com/kamchatka-volcano/figcone) library. 


## Installation
Download and link the library from your project's CMakeLists.txt:
```
cmake_minimum_required(VERSION 3.14)

include(FetchContent)
FetchContent_Declare(figcone_toml
    GIT_REPOSITORY "https://github.com/kamchatka-volcano/figcone_toml.git"
    GIT_TAG "origin/master"
)
#uncomment if you need to install figcone_toml with your target
#set(INSTALL_FIGCONE_TOML ON)
FetchContent_MakeAvailable(figcone_toml)

add_executable(${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} PRIVATE figcone::figcone_toml)
```

For the system-wide installation use these commands:
```
git clone https://github.com/kamchatka-volcano/figcone_toml.git
cd figcone_toml
cmake -S . -B build
cmake --build build
cmake --install build
```

Afterwards, you can use find_package() command to make the installed library available inside your project:
```
find_package(figcone_toml 0.9.0 REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE figcone::figcone_toml)
```

## Running tests
```
cd figcone_toml
cmake -S . -B build -DENABLE_TESTS=ON
cmake --build build
cd build/tests && ctest
```

## License
**figcone_toml** is licensed under the [MS-PL license](/LICENSE.md)  
