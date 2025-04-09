cmake_minimum_required(VERSION 3.10)
project(beeGame)

set(TARGET bee)

file(GLOB SRC "src/*.c")

add_executable(${TARGET} ${SRC})

if (WIN32)
    set(SDL2_PATH "${CMAKE_SOURCE_DIR}/third_party/SDL2")
    set(SDL2_IMAGE_PATH "${CMAKE_SOURCE_DIR}/third_party/SDL2_image")
    set(SDL2_TTF_PATH "${CMAKE_SOURCE_DIR}/third_party/SDL2_ttf")

    include_directories(
        ${SDL2_PATH}/include
        ${SDL2_IMAGE_PATH}/include
        ${SDL2_TTF_PATH}/include
    )

    link_directories(
        ${SDL2_PATH}/lib
        ${SDL2_IMAGE_PATH}/lib
        ${SDL2_TTF_PATH}/lib
    )

    target_link_libraries(${TARGET}
        SDL2 SDL2main SDL2_image SDL2_ttf
    )
else()
    # Linux - assume SDL installed via package manager
    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
    find_package(SDL2_ttf REQUIRED)

    include_directories(
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        ${SDL2_TTF_INCLUDE_DIRS}
    )

    target_link_libraries(${TARGET}
        ${SDL2_LIBRARIES}
        SDL2_image SDL2_ttf m
    )
endif()

set_target_properties(${TARGET} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)





