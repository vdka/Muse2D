
#define MUSE_IMPLEMENTATION
#include "muse.h"

inline V2 raycast(V2 rayStart, V2 rayEnd, V2 seg1, V2 seg2) {

    V2 rayDelta;
    rayDelta.x = rayEnd.x - rayStart.x;
    rayDelta.y = rayEnd.y - rayStart.y;

    V2 scale;
    scale.x = 1.f / rayDelta.x;
    scale.y = 1.f / rayDelta.y;

    V2 sign;
    sign.x = copysignf(1, scale.x);
    sign.y = copysignf(1, scale.y);

    V2 nearTime;
    nearTime.x = (seg1.x * sign.x - rayStart.x) * scale.x;
    nearTime.y = (seg1.y * sign.y - rayStart.y) * scale.y;

    V2 farTime;
    farTime.x = (seg2.x * sign.x - rayStart.x) * scale.x;
    farTime.y = (seg2.y * sign.y - rayStart.y) * scale.y;

    if (nearTime.x > farTime.y || nearTime.y > farTime.x) return rayEnd;

    f32 near = nearTime.x > nearTime.y ? nearTime.x : nearTime.y;
    f32 far  = farTime.x  > farTime.y  ? farTime.x  : farTime.y;

    if (near >= 1 || far <= 0) return rayEnd; // Collision does not lay upon the segment

    V2 collision;

    collision.x = rayDelta.x * near;
    collision.y = rayDelta.y * near;

    collision.x += rayStart.x;
    collision.y += rayStart.y;

    return collision;
}

int main() {

    InitWindow(640, 480, "hello lib!");

    Camera cam = {{0, 0, 3.2, 2.4}};

    setCamera(cam);

    u32 sprite = TextureLoad("data/player-sheet.png");

    while (!WindowShouldClose()) {

        if (IsKeyDown(GLFW_KEY_D)) cam.target.x += 1 * frameTime;
        if (IsKeyDown(GLFW_KEY_A)) cam.target.x -= 1 * frameTime;
        if (IsKeyDown(GLFW_KEY_W)) cam.target.y += 1 * frameTime;
        if (IsKeyDown(GLFW_KEY_S)) cam.target.y -= 1 * frameTime;

        setCamera(cam);

        V2 mouse = WorldToCamera(GetMousePosition());

        if (previousMouseWheelY) {
            cam.target.width += (f32) previousMouseWheelY / 10 * cam.target.width * frameTime;
            cam.target.height += (f32) previousMouseWheelY / 10 * cam.target.height * frameTime;
            setCamera(cam);
        }

        V2 endRay = raycast((V2){.0f, .0f}, mouse, (V2){.5f, .5f}, (V2){.5f, 1.f});

        BeginFrame();
        {
            ClearBackground(WHITE);
            FillTriXY(.0, .0, .0, .5, .25, .25, RED);
            FillTriXY(.0, .0, .25, .25, .5, .0, GREEN);
            FillTriXY(.5, .0, .5, .5, .0, .5, BLUE);

            DrawLine(0, 0, endRay.x, endRay.y, RED);

            FillRect((Rect){-.5, -.5, .25, .25}, RED);
            FillRect((Rect){  0, -.5, .25, .25}, GREEN);
            FillRect((Rect){ .5, -.5, .25, .25}, BLUE);

            FillCircle(mouse, .05, ORANGE);

            DrawTexture(sprite, (Rect){1.f, .6f, .36, .06});
            DrawTextureClip(sprite, (Rect){-1.f, .6f, .06f, .06f}, (Rect){0, 0, 6, 6});
            // FillRect((Rect){mouse.x, mouse.y, .5, .5}, (Color){fabs(mouse.x) * 80, fabs(mouse.y) * 100, 0, 1});
        }
        EndFrame();
    }
    return 0;
}
