cmake_minimum_required(VERSION 3.26)
project(squasher_LD54)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -static-libstdc++ -static-libgcc")

if (${WIN32})

    set(SDL2_INCLUDE_DIR C:/SDL2_64/include)
    set(SDL2_LIB_DIR C:/SDL2_64/lib)

    include_directories(${SDL2_INCLUDE_DIR})
    link_directories(${SDL2_LIB_DIR})

endif ()

file(
        GLOB SOURCES LIST_DIRECTORIES false
        ${CMAKE_CURRENT_LIST_DIR}/source/*.cpp
)

add_executable(squasher_LD54 ${SOURCES})

set_target_properties(squasher_LD54 PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/bin")

if (${WIN32})
    target_link_libraries(squasher_LD54 mingw32 SDL2main SDL2 SDL2_image SDL2_ttf zlib1)
else ()
    target_link_libraries(squasher_LD54 SDL2main SDL2 SDL2_image SDL2_ttf)
endif ()