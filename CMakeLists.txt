include(FetchContent)
cmake_minimum_required(VERSION 3.15)

project(MyRaylibGame LANGUAGES CXX C)

#C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Jolt
set(OBJECT_LAYER_BITS 16)

#raylib
# Configure raylib similar to r3d's vendored setup to avoid symbol clashes
set(CUSTOMIZE_BUILD ON CACHE BOOL "" FORCE)
set(SUPPORT_FILEFORMAT_OBJ OFF CACHE BOOL "" FORCE)
set(SUPPORT_FILEFORMAT_MTL OFF CACHE BOOL "" FORCE)
set(SUPPORT_FILEFORMAT_IQM OFF CACHE BOOL "" FORCE)
set(SUPPORT_FILEFORMAT_GLTF OFF CACHE BOOL "" FORCE)
set(SUPPORT_FILEFORMAT_VOX OFF CACHE BOOL "" FORCE)
set(SUPPORT_FILEFORMAT_M3D OFF CACHE BOOL "" FORCE)
set(SUPPORT_MESH_GENERATION OFF CACHE BOOL "" FORCE)

#assimp
# assimp knobs (leaner build; keep install/tests off)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_NO_EXPORT ON CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)


file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}")


# ============ FETCH ============

FetchContent_Declare(
    JoltPhysics
    GIT_REPOSITORY "https://github.com/jrouwe/JoltPhysics"
    GIT_TAG "v5.3.0"
    SOURCE_SUBDIR "Build"
)
FetchContent_MakeAvailable(JoltPhysics)

FetchContent_Declare(
    EnTT
    GIT_REPOSITORY "https://github.com/skypjack/entt"
    GIT_TAG "v3.15.0"
)
FetchContent_MakeAvailable(EnTT)

# FetchContent_Declare(
#     raylib
#     GIT_REPOSITORY "https://github.com/raysan5/raylib"
#     GIT_TAG "5.5"
# )
# FetchContent_MakeAvailable(raylib)

# # Fetch Assimp
# FetchContent_Declare(
#     assimp
#     GIT_REPOSITORY "https://github.com/assimp/assimp"
#     GIT_TAG "v6.0.2"
# )
# FetchContent_MakeAvailable(assimp)



# Fetch R3D
FetchContent_Declare(
    r3d
    GIT_REPOSITORY "https://github.com/Bigfoot71/r3d"
    GIT_TAG "v0.8"
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(r3d)


file(
    GLOB_RECURSE SOURCE_FILES
    CONFIGURE_DEPENDS  # Automatically reconfigure if source files are added/removed.
    ${PROJECT_SOURCE_DIR}/src/*.cpp
    ${PROJECT_SOURCE_DIR}/src/*.c
    ${PROJECT_SOURCE_DIR}/src/*.hpp
)

add_executable(${PROJECT_NAME} "${SOURCE_FILES}")

# r3d doesn't currently expose its public headers via target properties,
# so add its include directory explicitly for the application target.
if(NOT r3d_SOURCE_DIR)
    FetchContent_GetProperties(r3d)
endif()

if(NOT raylib_SOURCE_DIR)
    FetchContent_GetProperties(raylib)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
    r3d
    # raylib
    # assimp
    EnTT::EnTT
    Jolt
)

if (APPLE)
    find_library(COCOA_LIBRARY Cocoa REQUIRED)
    find_library(IOKIT_LIBRARY IOKit REQUIRED)
    find_library(COREVIDEO_LIBRARY CoreVideo REQUIRED)
    find_library(COREGRAPHICS_LIBRARY CoreGraphics REQUIRED)
    find_library(APPKIT_LIBRARY AppKit REQUIRED)

    target_link_libraries(${PROJECT_NAME} PRIVATE
        ${COCOA_LIBRARY}
        ${IOKIT_LIBRARY}
        ${COREVIDEO_LIBRARY}
        ${COREGRAPHICS_LIBRARY}
        ${APPKIT_LIBRARY}
    )
endif()

file(COPY "${PROJECT_SOURCE_DIR}/src/resources" DESTINATION "${CMAKE_BINARY_DIR}/resources/")
