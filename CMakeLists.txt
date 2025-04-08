cmake_minimum_required(VERSION 3.10)
project(beeGame)

set(TARGET bee)

file(GLOB SRC "src/*.c")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})

add_executable(${TARGET} ${SRC})

target_link_libraries(${TARGET} ${SDL2_LIBRARIES} SDL2_image SDL2_ttf m)

set_target_properties(${TARGET} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)

