
#define TD2D_IMPLEMENTATION
#include "fard2d.h"

int main() {

    InitWindow(640, 480, "hello lib!");

    Camera cam = {{0, 0, 3.2, 2.4}};

    setCamera(cam);

    while (!WindowShouldClose()) {

        if (IsKeyDown(GLFW_KEY_D)) cam.target.x += 1 * frameTime;
        if (IsKeyDown(GLFW_KEY_A)) cam.target.x -= 1 * frameTime;
        if (IsKeyDown(GLFW_KEY_W)) cam.target.y += 1 * frameTime;
        if (IsKeyDown(GLFW_KEY_S)) cam.target.y -= 1 * frameTime;

        setCamera(cam);

        V2 mouse = WorldToCamera(GetMousePosition());

        if (previousMouseWheelY) {
            cam.target.width += (f32) previousMouseWheelY / 1000 * cam.target.width;
            cam.target.height += (f32) previousMouseWheelY / 1000 * cam.target.height;
            setCamera(cam);
        }

        BeginFrame();
        {
            FillTriXY(.0, .0, .0, .5, .25, .25, RED);
            FillTriXY(.0, .0, .25, .25, .5, .0, GREEN);
            FillTriXY(.5, .0, .5, .5, .0, .5, BLUE);

            FillRect((Rect){-.5, -.5, .25, .25}, RED);
            FillRect((Rect){  0, -.5, .25, .25}, GREEN);
            FillRect((Rect){ .5, -.5, .25, .25}, BLUE);

            FillCircle(mouse, .05, ORANGE);
            // FillRect((Rect){mouse.x, mouse.y, .5, .5}, (Color){fabs(mouse.x) * 80, fabs(mouse.y) * 100, 0, 1});
        }
        EndFrame();
    }
    return 0;
}
