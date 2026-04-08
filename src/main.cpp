#include <r3d/r3d.h>
#include <raymath.h>
#include "level/Level.hpp"
#include "level/tile_constants.hpp"


const int MAP_SIZE_X = 50;
const int MAP_SIZE_Z = 50;

const int ROOM_MIN_SIZE_X = 5;
const int ROOM_MIN_SIZE_Z = 5;

int main(void)
{
    InitWindow(800, 600, "R3D Example");
    SetTargetFPS(60);

    R3D_Init(800, 600);

    R3D_ENVIRONMENT_SET(ambient.color, (Color){0, 0, 0, 255});
    R3D_SetTextureFilter(TEXTURE_FILTER_POINT);
    

    R3D_Mesh floorMesh = R3D_GenMeshPlane(TILE_SIZE, TILE_SIZE, 1, 1);
    R3D_Material floorMaterial = R3D_GetDefaultMaterial();
    floorMaterial.albedo = R3D_LoadAlbedoMap("resources/floor.png", WHITE);

    R3D_Mesh wallMesh = R3D_GenMeshPlane(TILE_SIZE, TILE_SIZE, 1, 1);
    R3D_Material wallMaterial = R3D_GetDefaultMaterial();
    wallMaterial.albedo = R3D_LoadAlbedoMap("resources/wall.png", WHITE);
    
    //Setup level
    Level* level = Level::createLevel({MAP_SIZE_X, MAP_SIZE_Z}, {ROOM_MIN_SIZE_X, ROOM_MIN_SIZE_Z});

    Vector3 target = { 0, 5, 0};

    // Background
    R3D_EnvBackground bgSettings = R3D_GetEnvironment()->background;
    bgSettings.color = BLACK;
    R3D_GetEnvironment()->background = bgSettings;

    // Setup lighting
    R3D_Light light = R3D_CreateLight(R3D_LIGHT_OMNI);
    R3D_SetLightPosition(light, target);
    R3D_SetLightColor(light, Color{255, 120, 100, 255});
    R3D_SetLightEnergy(light, 8.0f);
    R3D_SetShadowUpdateMode(light, R3D_SHADOW_UPDATE_CONTINUOUS);
    R3D_EnableShadow(light);
    R3D_SetShadowSoftness(light, 100);
    R3D_SetLightActive(light, true);

    // Camera setup
    Camera3D camera = {
        .position = Vector3{30, 30, 30} + target,
        .target = target,
        .up = {0, 1, 0},
        .fovy = 60.0f,
        .projection = CAMERA_PERSPECTIVE
    };

    // Main loop
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        //UpdateCamera(&camera, CAMERA_ORBITAL);

        if (IsKeyPressed(KEY_ENTER)) {
            delete level;
            level = Level::createLevel({MAP_SIZE_X, MAP_SIZE_Z}, {ROOM_MIN_SIZE_X, ROOM_MIN_SIZE_Z});
        }

        Vector3 direction = {0, 0, 0};
        if (IsKeyDown(KEY_W)) {
            direction.z -= 30;
        }
        if (IsKeyDown(KEY_A)) {
            direction.x -= 30;
        }
        if (IsKeyDown(KEY_S)) {
            direction.z += 30;
        }
        if (IsKeyDown(KEY_D)) {
            direction.x += 30;
        }


        target += direction * dt;
        R3D_SetLightPosition(light, target);
        camera.position = Vector3{30, 30, 30} + target;
        camera.target = target;

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