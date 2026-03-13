#include <r3d/r3d.h>
#include <raymath.h>
#include "level/Level.hpp"
#include "level/tile_constants.hpp"


const int MAP_SIZE_X = 50;
const int MAP_SIZE_Z = 50;

int main(void)
{
    InitWindow(800, 600, "R3D Example");
    SetTargetFPS(60);

    R3D_Init(800, 600);

    R3D_ENVIRONMENT_SET(ambient.color, (Color){10, 10, 10, 255});
    R3D_SetTextureFilter(TEXTURE_FILTER_POINT);

    R3D_Mesh floorMesh = R3D_GenMeshPlane(TILE_SIZE_X, TILE_SIZE_Z, 1, 1);
    R3D_Material floorMaterial = R3D_GetDefaultMaterial();
    floorMaterial.albedo = R3D_LoadAlbedoMap("resources/floor.png", WHITE);

    R3D_Mesh wallMesh = R3D_GenMeshPlane(TILE_SIZE_X, TILE_SIZE_Z, 1, 1);
    R3D_Material wallMaterial = R3D_GetDefaultMaterial();
    wallMaterial.albedo = R3D_LoadAlbedoMap("resources/wall.png", WHITE);
    
    //Setup level
    Level* level = Level::createLevel({MAP_SIZE_X, MAP_SIZE_Z}, {ROOM_MIN_SIZE_X, ROOM_MIN_SIZE_Z});

    // Setup lighting
    // R3D_Light light = R3D_CreateLight(R3D_LIGHT_DIR);
    // R3D_SetLightDirection(light, (Vector3){-1, -1, -1});
    // R3D_SetLightActive(light, true);
    R3D_Light light = R3D_CreateLight(R3D_LIGHT_OMNI);
    R3D_SetLightPosition(light, { 10, 5, 10});
    R3D_SetLightColor(light, Color{255, 120, 100, 255});
    //R3D_SetLightDirection(light, (Vector3){-1, -1, -1});
    R3D_SetLightActive(light, true);

    // Camera setup
    Camera3D camera = {
        .position = {3, 3, 3},
        .target = {0, 0, 0},
        .up = {0, 1, 0},
        .fovy = 60.0f,
        .projection = CAMERA_PERSPECTIVE
    };

    // Main loop
    while (!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_ORBITAL);

        if (IsKeyPressed(KEY_ENTER)) {
            delete level;
            level = Level::createLevel({MAP_SIZE_X, MAP_SIZE_Z}, {ROOM_MIN_SIZE_X, ROOM_MIN_SIZE_Z});
        }

        BeginDrawing();
            R3D_Begin(camera);
                for (int i = 0; i < level->tileListSize; i++) {
                    R3D_DrawMesh(floorMesh, floorMaterial, level->tileList[i].position, 1.0f);
                }
                for (int i = 0; i < level->wallListSize; i++) {
                    R3D_DrawMeshEx(wallMesh, wallMaterial, level->wallList[i].position, level->wallList[i].direction, {1, 1, 1});
                }
            R3D_End();
        EndDrawing();
    }

    R3D_UnloadMesh(floorMesh);
    R3D_UnloadAlbedoMap(floorMaterial.albedo);
    R3D_Close();
    CloseWindow();
    return 0;
}