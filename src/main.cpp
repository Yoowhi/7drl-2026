#include <r3d/r3d.h>
#include <raymath.h>

int main(void)
{
    InitWindow(800, 600, "R3D Example");
    SetTargetFPS(60);

    R3D_Init(800, 600);

    R3D_ENVIRONMENT_SET(ambient.color, (Color){10, 10, 10, 255});
    R3D_SetTextureFilter(TEXTURE_FILTER_POINT);

    R3D_Mesh floorMesh = R3D_GenMeshPlane(5, 5, 1, 1);
    R3D_Material floorMaterial = R3D_GetDefaultMaterial();
    floorMaterial.albedo = R3D_LoadAlbedoMap("resources/floor.png", WHITE);

    // R3D_Mesh wallMesh = R3D_GenMeshPlane(1, 1, 1, 1);
    // R3D_Material wallMaterial = R3D_GetDefaultMaterial();
    // wallMaterial.albedo = R3D_LoadAlbedoMap("resources/wall.png", WHITE);
    


    // Setup lighting
    R3D_Light light = R3D_CreateLight(R3D_LIGHT_DIR);
    R3D_SetLightDirection(light, (Vector3){-1, -1, -1});
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

        BeginDrawing();
            R3D_Begin(camera);
                R3D_DrawMesh(floorMesh, floorMaterial, Vector3Zero(), 1.0f);
                //R3D_DrawMesh(wallMesh, wallMaterial, Vector3Zero(), 1.0f);
                //R3D_DrawMeshEx(wallMesh, wallMaterial, Vector3{0, 0, 0}, )
            R3D_End();
        EndDrawing();
    }

    R3D_UnloadMesh(floorMesh);
    R3D_UnloadAlbedoMap(floorMaterial.albedo);
    R3D_Close();
    CloseWindow();
    return 0;
}