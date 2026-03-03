cmake_minimum_required(VERSION 3.15)
project(MyRaylibGame LANGUAGES CXX C)

# ===============
# GLOBAL SETTINGS
# ===============
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

set(CUSTOMIZE_BUILD ON CACHE BOOL "" FORCE)
set(SUPPORT_MESH_GENERATION OFF CACHE BOOL "" FORCE)
foreach(fmt OBJ MTL IQM GLTF VOX M3D)
    set(SUPPORT_FILEFORMAT_${fmt} OFF CACHE BOOL "" FORCE)
endforeach()

set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_NO_EXPORT ON CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
set(R3D_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(R3D_RAYLIB_VENDORED OFF CACHE BOOL "" FORCE)
set(R3D_ASSIMP_VENDORED OFF CACHE BOOL "" FORCE)


find_package(Python3 COMPONENTS Interpreter REQUIRED)
set(PYTHON_EXECUTABLE "${Python3_EXECUTABLE}" CACHE FILEPATH "" FORCE)

# ============
# FETCHCONTENT
# ============
include(FetchContent)

macro(FetchDependency NAME REPO TAG)
    FetchContent_Declare(${NAME} GIT_REPOSITORY ${REPO} GIT_TAG ${TAG} ${ARGN})
    FetchContent_MakeAvailable(${NAME})
endmacro()

FetchDependency(JoltPhysics "https://github.com/jrouwe/JoltPhysics" "v5.3.0" SOURCE_SUBDIR "Build")
FetchDependency(EnTT        "https://github.com/skypjack/entt"      "v3.15.0")
FetchDependency(raylib      "https://github.com/raysan5/raylib"     "5.5" OVERRIDE_FIND_PACKAGE)
FetchDependency(assimp      "https://github.com/assimp/assimp"      "v6.0.2" OVERRIDE_FIND_PACKAGE)
FetchDependency(r3d         "https://github.com/Bigfoot71/r3d"      "v0.8" GIT_SHALLOW TRUE)


if(TARGET raylib AND APPLE)
    target_compile_definitions(raylib PRIVATE "assert(x)=((void)0)" "MAX_MESH_VERTEX_BUFFERS=9")
    target_compile_options(raylib PRIVATE "-Wno-error=implicit-function-declaration")
endif()


if(TARGET r3d)
    target_include_directories(r3d PRIVATE 
        "${raylib_SOURCE_DIR}/src"
        "${assimp_SOURCE_DIR}/include"
        "${assimp_BINARY_DIR}/include"
    )
    if(MSVC)
        target_compile_options(r3d PRIVATE "/FIstdlib.h")
    else()
        target_compile_options(r3d PRIVATE "-include" "stdlib.h")
    endif()
endif()

# ==================
# APPLICATION TARGET
# ==================
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "src/*.cpp" "src/*.hpp" "src/*.c" "src/*.h")
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE 
    "src"
    "${r3d_SOURCE_DIR}/include"
    "${raylib_SOURCE_DIR}/src"
    "${assimp_SOURCE_DIR}/include"
    "${assimp_BINARY_DIR}/include"
)

target_link_libraries(${PROJECT_NAME} PRIVATE r3d assimp raylib EnTT::EnTT Jolt)

if(APPLE)
    target_link_options(${PROJECT_NAME} PRIVATE "-Wl,-undefined,dynamic_lookup")
    target_link_libraries(${PROJECT_NAME} PRIVATE "-framework Cocoa" "-framework IOKit" "-framework CoreVideo" "-framework CoreGraphics" "-framework AppKit")
endif()

file(COPY "${PROJECT_SOURCE_DIR}/src/resources" DESTINATION "${CMAKE_BINARY_DIR}/")
