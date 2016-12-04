
#ifndef TD2D_h
#define TD2D_h

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdarg.h>
#include <assert.h>
#include <time.h>
#include <math.h>

typedef int8_t   i8;
typedef uint8_t  u8;
typedef int16_t  i16;
typedef uint16_t u16;
typedef int32_t  i32;
typedef uint32_t u32;
typedef int64_t  i64;
typedef uint64_t u64;

typedef float  f32;
typedef double f64;

typedef i8   b8;
typedef i16 b16;
typedef i32 b32;

typedef size_t    usize;
typedef ptrdiff_t offset;

#if !defined(__cplusplus)
    #if !defined(__STDC_VERSION__)
    #define inline __inline__
    #else
    #define inline
    #endif
#endif

#ifndef __cplusplus
// Boolean type
    #ifndef __APPLE__
        #if !defined(_STDBOOL_H)
            typedef enum { false, true } bool;
            #define _STDBOOL_H
        #endif
    #else
        #include <stdbool.h>
    #endif
#endif

//----------------------------------------------------------------------------------
// Some basic Defines
//----------------------------------------------------------------------------------

#ifndef TAU
    #define TAU 6.28318530717958647692528676655900576f
#endif

#ifndef PI
    #define PI 3.14159265358979323846f
#endif

#define DEG2RAD (TAU/360.0f)
#define RAD2DEG (360.0f/TAU)
#define BIT_CHECK(a,b) ((a) & (1<<(b)))

typedef enum {
    UNCOMPRESSED_GRAYSCALE = 1,     // 8 bit per pixel (no alpha)
    UNCOMPRESSED_GRAY_ALPHA,        // 16 bpp (2 channels)
    UNCOMPRESSED_R5G6B5,            // 16 bpp
    UNCOMPRESSED_R8G8B8,            // 24 bpp
    UNCOMPRESSED_R5G5B5A1,          // 16 bpp (1 bit alpha)
    UNCOMPRESSED_R4G4B4A4,          // 16 bpp (4 bit alpha)
    UNCOMPRESSED_R8G8B8A8,          // 32 bpp
} TextureFormat;

// Vector2 type
typedef struct V2 {
    f32 x;
    f32 y;
} V2;

// While td2d focuses on everything in 2d the renderer still is 3 dimentional.
typedef union V3 {
    struct { f32 x, y, z; };
    V2  xy;
    f32 e[3];
} V3;
// Color type, RGBA (32bit)
typedef union Color {
    struct { u8 r, g, b, a; };
    u32    rgba;
} Color;

// Rectangle type
typedef struct Rect {
    f32 x, y, width, height;
} Rect;

// Rectangle type
typedef struct BoundingBox {
    V2 topLeft;
    V2 bottomRight;
} BoundingBox;

// Image type, bpp always RGBA (32bit)
// NOTE: Data stored in CPU memory (RAM)
typedef struct Image {
    void *data;             // Image raw data
    i32 width;              // Image base width
    i32 height;             // Image base height
    i32 mipmaps;            // Mipmap levels, 1 by default
    TextureFormat format;   // Data format (TextureFormat)
} Image;

// NOTE: Data stored in GPU memory
typedef struct Texture {
    u32 id;                 // OpenGL texture id
    i32 width;              // Texture base width
    i32 height;             // Texture base height
    i32 mipmaps;            // Mipmap levels, 1 by default
    TextureFormat format;   // Data format (TextureFormat)
} Texture;

// Quaternion type
typedef struct Quaternion {
    f32 x, y, z, w;
} Quaternion;

typedef struct Camera {
    Rect target;
} Camera;

// Some Basic Colors
#define LIGHTGRAY  (Color){ 200, 200, 200, 255 }   // Light Gray
#define GRAY       (Color){ 130, 130, 130, 255 }   // Gray
#define DARKGRAY   (Color){ 80, 80, 80, 255 }      // Dark Gray
#define YELLOW     (Color){ 253, 249, 0, 255 }     // Yellow
#define GOLD       (Color){ 255, 203, 0, 255 }     // Gold
#define ORANGE     (Color){ 255, 161, 0, 255 }     // Orange
#define PINK       (Color){ 255, 109, 194, 255 }   // Pink
#define RED        (Color){ 230, 41, 55, 255 }     // Red
#define MAROON     (Color){ 190, 33, 55, 255 }     // Maroon
#define GREEN      (Color){ 0, 228, 48, 255 }      // Green
#define LIME       (Color){ 0, 158, 47, 255 }      // Lime
#define DARKGREEN  (Color){ 0, 117, 44, 255 }      // Dark Green
#define SKYBLUE    (Color){ 102, 191, 255, 255 }   // Sky Blue
#define BLUE       (Color){ 0, 121, 241, 255 }     // Blue
#define DARKBLUE   (Color){ 0, 82, 172, 255 }      // Dark Blue
#define PURPLE     (Color){ 200, 122, 255, 255 }   // Purple
#define VIOLET     (Color){ 135, 60, 190, 255 }    // Violet
#define DARKPURPLE (Color){ 112, 31, 126, 255 }    // Dark Purple
#define BEIGE      (Color){ 211, 176, 131, 255 }   // Beige
#define BROWN      (Color){ 127, 106, 79, 255 }    // Brown
#define DARKBROWN  (Color){ 76, 63, 47, 255 }      // Dark Brown

#define WHITE      (Color){ 255, 255, 255, 255 }   // White
#define BLACK      (Color){ 0, 0, 0, 255 }         // Black
#define BLANK      (Color){ 0, 0, 0, 0 }           // Blank (Transparent)
#define MAGENTA    (Color){ 255, 0, 255, 255 }     // Magenta


/**API*****************************/
/*                                */
/*       ###    ########  ####    */
/*      ## ##   ##     ##  ##     */
/*     ##   ##  ##     ##  ##     */
/*    ##     ## ########   ##     */
/*    ######### ##         ##     */
/*    ##     ## ##         ##     */
/*    ##     ## ##        ####    */
/*                                */
/**********************************/
#define API extern

#ifdef __cplusplus
extern "C" {            // Prevents name mangling of functions
#endif

API void InitWindow(i32 width, i32 height, const char* title);                      // Initialize Window and OpenGL Graphics
API void CloseWindow(void);                                                         // Close Window and Terminate Context
API b32 WindowShouldClose(void);                                                    // Detect if KEY_ESCAPE pressed or Close icon pressed
API b32 IsWindowMinimized(void);                                                    // Detect if window is minimized (or lost focus)
API V2 GetWindowDimentions(void);                                                   // Returns the current dimentions of the window
API void ToggleFullscreen(void);                                                    // Fullscreen toggle

API V2 GetMousePosition(void);                                                      // Returns the current mouse position

API b32 IsKeyPressed(i32 key);                                                      // Detect if a key has been pressed once
API b32 IsKeyDown(i32 key);                                                         // Detect if a key is being pressed
API b32 IsKeyReleased(i32 key);                                                     // Detect if a key has been released once
API b32 IsKeyUp(i32 key);                                                           // Detect if a key is NOT being pressed
API i32 GetKeyPressed(void);                                                        // Get latest key pressed
API void SetExitKey(i32 key);                                                       // Set a custom key to exit program (default is ESC)

API void ClearBackground(Color color);                                              // Sets Background Color
API void BeginFrame(void);                                                          // Setup drawing canvas to start drawing
API void EndFrame(void);                                                            // End canvas drawing and Swap Buffers (Double Bufferi
API f64 GetTime(void);                                                              // Returns the time since InitTimer() was cal

API void SetLineWidth(f32 width);                                                   // Set the width of the lines drawn

API void DrawPoint(f32 x, f32 y, Color color);                                      // Draw a single 'point'

API void DrawTri(V2 v1, V2 v2, V2 v3, Color color);                                 // Draw a Triangle outline
API void FillTri(V2 v1, V2 v2, V2 v3, Color color);                                 // Fill a Triangle

API void DrawRect(Rect rect, Color color);                                          // Draw a Rectangle outline
API void FillRect(Rect rect, Color color);                                          // Fill a Rectangle

API void FillPoly(V2 center, i32 sides, f32 radius, Color color);
API void FillCircle(V2 center, f32 radius, Color color);

API void DrawTriXY(f32 x1, f32 y1, f32 x2, f32 y2, f32 x3, f32 y3, Color color);                    // Draw a Triangle outline
API void FillTriXY(f32 x1, f32 y1, f32 x2, f32 y2, f32 x3, f32 y3, Color color);                    // Fill a Triangle

API void DrawRectXY(f32 x1, f32 y1, f32 x2, f32 y2, f32 x3, f32 y3, f32 x4, f32 y4, Color color);   // Draw a Rectangle outline
API void FillRectXY(f32 x1, f32 y1, f32 x2, f32 y2, f32 x3, f32 y3, f32 x4, f32 y4, Color color);   // Fill a Rectangle

#ifdef __cplusplus
} // extern "C"
#endif

/**INTERNAL*****************************************************************/
/*                                                                         */
/*  #### ##    ## ######## ######## ########  ##    ##    ###    ##        */
/*   ##  ###   ##    ##    ##       ##     ## ###   ##   ## ##   ##        */
/*   ##  ####  ##    ##    ##       ##     ## ####  ##  ##   ##  ##        */
/*   ##  ## ## ##    ##    ######   ########  ## ## ## ##     ## ##        */
/*   ##  ##  ####    ##    ##       ##   ##   ##  #### ######### ##        */
/*   ##  ##   ###    ##    ##       ##    ##  ##   ### ##     ## ##        */
/*  #### ##    ##    ##    ######## ##     ## ##    ## ##     ## ########  */
/*                                                                         */
/***************************************************************************/

#if defined(TD2D_IMPLEMENTATION) && !defined(TD2D_IMPLEMENTATION_DONE)
#define TD2D_IMPLEMENTATION_DONE

// Include GLEW first; It's magic
#include <glad/glad.h>

// Include GLFW
#undef GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>

/*****************************************************************/
/*                                                               */
/*    ######   ##        #######  ########     ###    ##         */
/*   ##    ##  ##       ##     ## ##     ##   ## ##   ##         */
/*   ##        ##       ##     ## ##     ##  ##   ##  ##         */
/*   ##   #### ##       ##     ## ########  ##     ## ##         */
/*   ##    ##  ##       ##     ## ##     ## ######### ##         */
/*   ##    ##  ##       ##     ## ##     ## ##     ## ##         */
/*    ######   ########  GLOBALS  ########  ##     ## ########   */
/*                                                               */
/*****************************************************************/

//-----------------------------------------------------------------
// Stuff
//-----------------------------------------------------------------

u8 configFlags;

GLFWwindow* window;

i32 screenWidth, screenHeight;
i32 displayWidth, displayHeight;
i32 renderWidth, renderHeight;

// Register Mouse States
i8 previousMouseState[GLFW_MOUSE_BUTTON_LAST] = { 0 };
i8 currentMouseState[GLFW_MOUSE_BUTTON_LAST]  = { 0 };
i32 previousMouseWheelY = 0;
i32 currentMouseWheelY  = 0;

// Register Keyboard States
i8 previousKeyState[GLFW_KEY_LAST] = { 0 };
i8 currentKeyState[GLFW_KEY_LAST]  = { 0 };

i32 lastKeyPressed = -1;

V2 mousePosition;

f64 currentTime, previousTime;    // Used to track timmings
f64 updateTime, drawTime;         // Time measures for update and draw
f64 frameTime;                    // Time measure for one frame
f64 targetTime = 0.0;             // Desired time for one frame, if 0 not applied

i32 exitKey = GLFW_KEY_ESCAPE;

//-----------------------------------------------------------------
// OpenGL STUFF
//-----------------------------------------------------------------

typedef struct Shader {
    u32 id;        // Shader program id

    // Vertex attributes locations (default locations)
    i32 positionLoc;
    i32 texcoordLoc;
    i32 colorLoc;

    i32 cameraLoc;
} Shader;

// typically (GL_POINTS | GL_LINES | GL_LINE_LOOP | GL_TRIANGLES | GL_TRIANGLE_STRIP)
// Buffers used for storing vertices from Draw & Fill calls before unloading to GPU
typedef struct {
    i32 max;                // max number of vertices stored in the Buffer
    i32 storedPerShape;     // number of vertices stored per shape
    i32 renderedPerShape;   // number of vertices rendered per shape
    i32 count;              // number of vertices in the buffer

    // TODO(vdka): we will need more once we support textures
    V2* vertices;           // vertex position
    Color* colors;          // vertex colors (RGBA - 4 components per vertex)
    u32 *indices;           // vertex indices (in case vertex data comes indexed) (6 indices per quad)

    i32 mode;               // The draw mode to use for OpenGL
    u32 vao;                // OpenGL Vertex Array Object
    u32 vbo[3];             // OpenGL Vertex Buffer Object (1 for color, 1 for positions, 1 for indices)
} RenderBuffer;

RenderBuffer pixels;               // Default dynamic buffer for pixel data
RenderBuffer lines;                // Default dynamic buffer for lines data
RenderBuffer connectedLines;       // Default dynamic buffer for connnected lines data
RenderBuffer triangles;            // Default dynamic buffer for triangles data
RenderBuffer quads;                // Default dynamic buffer for quads data (used to draw textures)

Shader currentShader;
RenderBuffer* currentRenderBuffer;
Color currentColor;
Camera currentCamera;

f32 minLineWidth;
f32 maxLineWidth;

u32 whiteTexture;

/**SHADERS*******************************************************************/
/*                                                                          */
/*     ######  ##     ##    ###    ########  ######## ########   ######     */
/*    ##    ## ##     ##   ## ##   ##     ## ##       ##     ## ##    ##    */
/*    ##       ##     ##  ##   ##  ##     ## ##       ##     ## ##          */
/*     ######  ######### ##     ## ##     ## ######   ########   ######     */
/*          ## ##     ## ######### ##     ## ##       ##   ##         ##    */
/*    ##    ## ##     ## ##     ## ##     ## ##       ##    ##  ##    ##    */
/*     ######  ##     ## ##     ## ########  ######## ##     ##  ######     */
/*                                                                          */
/****************************************************************************/

#define GLSL(src) "#version 400 core\n" #src

const char* vertexShaderSource = GLSL(
    in vec2 vertexPosition;
    in vec2 vertexTexCoord;
    in vec4 vertexColor;
    out vec2 fragTexCoord;
    out vec4 fragColor;

    uniform vec4 camera;

    void main() {
        fragTexCoord = vertexTexCoord;
        fragColor = vertexColor;

        vec2 camPos = vec2(-camera.x + vertexPosition.x, -camera.y + vertexPosition.y);
        vec2 renPos = vec2(camPos.x * 2 / camera.z, camPos.y * 2 / camera.w);
        gl_Position = vec4(renPos, 0.0, 1.0);
    }
);

const char* fragmentShaderSource = GLSL(
    in vec2 fragTexCoord;
    in vec4 fragColor;
    out vec4 finalColor;

    uniform sampler2D texture0;

    void main() {
        finalColor = fragColor;
    }
);

/**UTILITIES*********************************************************************/
/*                                                                              */
/*    ##     ## ######## #### ##       #### ######## #### ########  ######      */
/*    ##     ##    ##     ##  ##        ##     ##     ##  ##       ##    ##     */
/*    ##     ##    ##     ##  ##        ##     ##     ##  ##       ##           */
/*    ##     ##    ##     ##  ##        ##     ##     ##  ######    ######      */
/*    ##     ##    ##     ##  ##        ##     ##     ##  ##             ##     */
/*    ##     ##    ##     ##  ##        ##     ##     ##  ##       ##    ##     */
/*     #######     ##    #### ######## ####    ##    #### ########  ######      */
/*                                                                              */
/********************************************************************************/

typedef enum { VERBOSE, INFO, WARNING, ERROR } LogLevel;
static void Log(LogLevel msgType, const char *text, ...) {
#ifdef MINLOGLEVEL
    if (msgType < MINLOGLEVEL) return;
#endif

    va_list args;

    switch(msgType) {
        case VERBOSE: fprintf(stdout, "VERBOSE: "); break;
        case INFO: fprintf(stdout, "INFO: "); break;
        case WARNING: fprintf(stdout, "WARNING: "); break;
        case ERROR: fprintf(stdout, "ERROR: "); break;
    }

    va_start(args, text);
    vfprintf(stdout, text, args);
    va_end(args);

    fprintf(stdout, "\n");

    fflush(stdout);
    // exit on ERROR
    if (msgType == ERROR) exit(1);
}

// converts window coordinates into 'world' coordinates
// TODO(vdka): Currently ignores camera position (assumes 0, 0)
static V2 WindowToWorld(V2 point) {
    V2 windowSize = GetWindowDimentions();
    f64 vertScale = currentCamera.target.width / windowSize.x;
    f64 horzScale = currentCamera.target.height / windowSize.y;

    V2 windowCenter = {windowSize.x / 2, windowSize.y / 2};
    V2 dWorldCenter = {point.x - windowCenter.x, point.y - windowCenter.y};


    V2 result = {dWorldCenter.x * horzScale, -dWorldCenter.y * vertScale};

    return result;
}

static V2 WorldToCamera(V2 point) {

    V2 result = {currentCamera.target.x + point.x, currentCamera.target.y + point.y};

    return result;
}

// Initializes hi-resolution timer
static void InitTimer(void) {
    srand((u32) time(NULL));

    previousTime = GetTime(); // seed our timer.
}

static b32 GetKeyStatus(i32 key) {
    return glfwGetKey(window, key);
}

// Get one mouse button state
static b32 GetMouseButtonStatus(i32 button) {
    return glfwGetMouseButton(window, button);
}

// Poll (store) all input events
static void PollInputEvents(void) {

    // Reset last key pressed registered
    lastKeyPressed = -1;

    // Mouse input polling
    f64 mouseX;
    f64 mouseY;

    glfwGetCursorPos(window, &mouseX, &mouseY);

    mousePosition.x = (f32) mouseX;
    mousePosition.y = (f32) mouseY;

    // Keyboard input polling (automatically managed by GLFW3 through callback)

    // Register previous keys states
    for (int i = 0; i < 512; i++) previousKeyState[i] = currentKeyState[i];

    // Register previous mouse states
    for (int i = 0; i < 3; i++) previousMouseState[i] = currentMouseState[i];

    previousMouseWheelY = currentMouseWheelY;
    currentMouseWheelY = 0;
}

static void ErrorCallback(int error, const char *description) {
    Log(WARNING, "[GLFW3 Error] Code: %i Decription: %s", error, description);
}

static void KeyCallback(GLFWwindow *window, i32 key, i32 scancode, i32 action, i32 mods) {
    // TODO(vdka): Support for reading on that mods bitfield
    if (key == exitKey && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    } else {
        currentKeyState[key] = action;
        if (action == GLFW_PRESS) lastKeyPressed = key;
    }
}

static void MouseButtonCallback(GLFWwindow *window, i32 button, i32 action, i32 mods) {
    // TODO(vdka): Support for reading on that mods bitfield
    currentMouseState[button] = action;
}

static void ScrollCallback(GLFWwindow *window, f64 xoffset, f64 yoffset) {
    currentMouseWheelY = (i32) yoffset;
}


static i32 CreateTexture(void *data, i32 width, i32 height, TextureFormat format, i32 mipmapCount) {
    glBindTexture(GL_TEXTURE_2D, 0); // free past binding

    u32 id = 0;

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    switch (format) {
        case UNCOMPRESSED_R8G8B8A8: glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (u8*) data); break;
        default: Log(WARNING, "Texture format not recognized");
    }

    return id;
}

static u32 LoadShader(u32 type, const char* source) {

    u32 shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    // check for compile errors
    i32 params = -1;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &params);
    if (params != GL_TRUE) {
        i32 msgLen = 0;
        i32 maxLen = 2048;
        char msg[maxLen];
        glGetShaderInfoLog(shader , maxLen, &msgLen, msg);

        if (type == GL_VERTEX_SHADER)
            Log(WARNING, "Error compiling vertex shader! %s", msg);
        else if (type == GL_FRAGMENT_SHADER)
            Log(WARNING, "Error compiling fragment shader! %s", msg);
        else
            Log(WARNING, "Error compiling shader of unknown kind! %s", msg);
    }

    return shader;
}

static u32 CreateShaderProgram(u32 vert, u32 frag) {

    u32 program = glCreateProgram();

    if (vert) glAttachShader(program, vert);
    if (frag) glAttachShader(program, frag);

    glLinkProgram(program);

    // check if link was successful
    int params = -1;
    glGetProgramiv(program, GL_LINK_STATUS, &params);
    if (GL_TRUE != params) {

        i32 msgLen = 0;
        i32 maxLen = 2048;
        char msg[maxLen];
        glGetProgramInfoLog(program, maxLen, &msgLen, msg);
        Log(WARNING, "Error linking shader! %s", msg);
    }
    return program;
}

static void InitBuffer(i32 stored, i32 rendered, i32 mode, i32 maxVerts, RenderBuffer* buffer) {
    buffer->max = maxVerts;
    buffer->storedPerShape = stored;
    buffer->renderedPerShape = rendered;
    buffer->count = 0;

    buffer->mode = mode;

    buffer->vertices = (V2*) malloc(sizeof(V2) * maxVerts);
    buffer->colors   = (Color*) malloc(sizeof(Color) * maxVerts);
    buffer->indices  = NULL;

    glGenVertexArrays(1, &buffer->vao);
    glBindVertexArray(buffer->vao);

    // Vertex position buffer (shader-location = 0)
    glGenBuffers(1, &buffer->vbo[0]);
    glBindBuffer(GL_ARRAY_BUFFER, buffer->vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(V2) * maxVerts, buffer->vertices, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(currentShader.positionLoc);
    glVertexAttribPointer(currentShader.positionLoc, 2, GL_FLOAT, false, 0, NULL);

    // Vertex color buffer (shader-location = 3)
    glGenBuffers(1, &buffer->vbo[1]);
    glBindBuffer(GL_ARRAY_BUFFER, buffer->vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Color) * maxVerts, buffer->colors, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(currentShader.colorLoc);
    glVertexAttribPointer(currentShader.colorLoc, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, NULL);

    // unbind the vertex array
    glBindVertexArray(0);
}

static void LoadDefaultBuffers() {

    // TODO(vdka): Allow macro's to define the buffer sizes

    InitBuffer(1, 1, GL_POINT,     2048, &pixels);
    InitBuffer(2, 2, GL_LINES,     4096, &lines);
    InitBuffer(2, 2, GL_LINE_LOOP, 4096, &connectedLines);
    InitBuffer(3, 3, GL_TRIANGLES, 2048 * 3, &triangles);
    InitBuffer(4, 6, GL_TRIANGLES, 2048 * 4, &quads);

    quads.indices = (u32*) malloc(sizeof(u32) * 1024 * 6);
    for (int i = 0, k = 0; i < 1024 * 6; i += 6, k++) {
        quads.indices[i]     = 4 * k;
        quads.indices[i + 1] = 4 * k + 1;
        quads.indices[i + 2] = 4 * k + 2;
        quads.indices[i + 3] = 4 * k;
        quads.indices[i + 4] = 4 * k + 2;
        quads.indices[i + 5] = 4 * k + 3;
    }

    glGenBuffers(1, &quads.vbo[2]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quads.vbo[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32) * 1024 * 6, quads.indices, GL_STATIC_DRAW);

    free(quads.indices); // we can free these from CPU now they are on the GPU
}

// Update default internal buffers (VBOs) with vertex array data
// NOTE: If there is not vertex data, buffers doesn't need to be updated (vertexCount > 0)
// TODO: If no data changed on the CPU arrays --> No need to re-update GPU arrays (change flag required)
static void UpdateBuffer(RenderBuffer* buffer) {

    // Update lines vertex buffers
    if (buffer->count > 0) {
        glBindVertexArray(buffer->vao);

        // vertex positions buffer
        glBindBuffer(GL_ARRAY_BUFFER, buffer->vbo[0]);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(V2) * buffer->count, buffer->vertices);

        // colors buffer
        glBindBuffer(GL_ARRAY_BUFFER, buffer->vbo[1]);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Color) * buffer->count, buffer->colors);

        // Unbind the current VAO
        glBindVertexArray(0);
    }
}

static void UpdateDefaultBuffers() {
    UpdateBuffer(&pixels);
    UpdateBuffer(&lines);
    UpdateBuffer(&connectedLines);
    UpdateBuffer(&triangles);
    UpdateBuffer(&quads);
}

static void DrawBuffer(RenderBuffer* buffer) {

    if (buffer->count > 0) {
        glBindTexture(GL_TEXTURE_2D, whiteTexture);

        glBindVertexArray(buffer->vao);

        if (buffer->indices != NULL) {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->vbo[2]);
            glDrawElements(buffer->mode, buffer->renderedPerShape * buffer->count / buffer->storedPerShape, GL_UNSIGNED_INT, 0);
        } else {
            glDrawArrays(buffer->mode, 0, buffer->count);
        }

        // reset buffer count
        buffer->count = 0;

        // unbind
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindVertexArray(0);
    }
}

static void DrawDefaultBuffers() {
    DrawBuffer(&pixels);
    DrawBuffer(&lines);
    DrawBuffer(&connectedLines);
    DrawBuffer(&triangles);
    DrawBuffer(&quads);
}

static u32 LoadTexture(void *data, i32 width, i32 height, TextureFormat textureFormat, i32 mipmapCount) {
    glBindTexture(GL_TEXTURE_2D, 0);    // Free any old binding

    u32 id = 0;

    glGenTextures(1, &id);              // Generate Pointer to the texture

    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);       // Set texture to repeat on x-axis
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);       // Set texture to repeat on y-axis

    // Magnification and minification filters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  // Alternative: GL_LINEAR
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);  // Alternative: GL_LINEAR

    if (mipmapCount > 1) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);   // Activate Trilinear filtering for mipmaps (must be available)
    }

    // At this point we have the texture loaded in GPU and texture parameters configured

    // NOTE: If mipmaps were not in data, they are not generated automatically

    // Unbind current texture
    glBindTexture(GL_TEXTURE_2D, 0);

    if (id > 0) Log(INFO, "[TEX ID %i] Texture created successfully (%ix%i)", id, width, height);
    else Log(WARNING, "Texture could not be created");

    return id;
}

static void InitGraphicsDevice(i32 width, i32 height, const char* title) {

    screenWidth = width;
    screenHeight = height;

    glfwSetErrorCallback(ErrorCallback);

    if (!glfwInit()) Log(ERROR, "Failed to initialize GLFW");

    glfwDefaultWindowHints();

    // VERSION
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // MISC HINTS
    glfwWindowHint(GLFW_RESIZABLE, false);
    glfwWindowHint(GLFW_SAMPLES, 4);


    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *mode = glfwGetVideoMode(monitor);

    displayWidth = mode->width;
    displayHeight = mode->height;

    if (screenWidth <= 0) screenWidth = displayWidth;
    if (screenHeight <= 0) screenHeight = displayHeight;


    window = glfwCreateWindow(width, height, title, NULL, NULL);

    if (window == NULL) {
        glfwTerminate();
        Log(ERROR, "Failed to open GLFW window. If you have an Intel GPU they are not compatible with OpenGL 3.3");
    } else {
        Log(INFO, "Display device initialized successfully");
        Log(INFO, "Display size: %i x %i", displayWidth, displayHeight);
        Log(INFO, "Render size: %i x %i", renderWidth, renderHeight);
        Log(INFO, "Screen size: %i x %i", screenWidth, screenHeight);
    }

    // Set our current OpenGL Context to that of the windows
    glfwMakeContextCurrent(window);

    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    gladLoadGL();
    if(!gladLoadGL()) Log(ERROR, "Failed to initialize GLAD");

#ifdef __APPLE__
    // Get framebuffer size of current window. Required to handle HiDPI display correctly.
    i32 fbWidth, fbHeight;
    glfwGetFramebufferSize(window, &fbWidth, &fbHeight);

    glViewport(0, 0, fbWidth, fbHeight);
#else
    glViewport(0, 0, renderWidth, renderHeight);
#endif

    // TODO(vdka): Set window callbacks

    glfwSetKeyCallback(window, KeyCallback);
    glfwSetMouseButtonCallback(window, MouseButtonCallback);
    glfwSetScrollCallback(window, ScrollCallback);
    // glfwSetCursorPosCallback(window, CursorPosCallback);

    // Disable VSync by default
    glfwSwapInterval(0);

    // setup culling
    // glEnable(GL_CULL_FACE);
    // glCullFace(GL_BACK);
    // glFrontFace(GL_CW);

    // TODO(vdka): enable VSYNC?

    f32 lineWidthRange[2];
    glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, lineWidthRange);
    minLineWidth = lineWidthRange[0];
    maxLineWidth = lineWidthRange[1];

    // Platform details

    Log(INFO, "GPU: Vendor:   %s", glGetString(GL_VENDOR));
    Log(INFO, "GPU: Renderer: %s", glGetString(GL_RENDERER));
    Log(INFO, "GPU: Version:  %s", glGetString(GL_VERSION));
    Log(INFO, "GPU: GLSL:     %s", glGetString(GL_SHADING_LANGUAGE_VERSION));

    u32 vertexShader   = LoadShader(GL_VERTEX_SHADER, vertexShaderSource);
    u32 fragmentShader = LoadShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    // u32 geometryShader = LoadShader(GL_GEOMETRY_SHADER, geometryShaderSource);

    currentShader.id = CreateShaderProgram(vertexShader, fragmentShader);

    currentShader.positionLoc = glGetAttribLocation(currentShader.id, "vertexPosition");
    currentShader.texcoordLoc = glGetAttribLocation(currentShader.id, "vertexTexCoord");
    currentShader.colorLoc    = glGetAttribLocation(currentShader.id, "vertexColor");

    currentShader.cameraLoc   = glGetUniformLocation(currentShader.id, "camera");

    LoadDefaultBuffers();

    u8 pixels[4] = { 255, 255, 255, 255 };

    whiteTexture = LoadTexture(pixels, 1, 1, UNCOMPRESSED_R8G8B8A8, 1);

    if (whiteTexture != 0) Log(INFO, "[TEX ID %i] Base white texture loaded successfully", whiteTexture);
    else Log(WARNING, "Base white texture could not be loaded");

    ClearBackground(WHITE);
}

// Bumps the call count on the buffer
static void setBuffer(RenderBuffer* buffer) {
    currentRenderBuffer = buffer;
}

static void vertex(f32 x, f32 y) {
    if (currentRenderBuffer == NULL) Log(ERROR, "Attempt to draw vertex without an active buffer");
    assert(currentRenderBuffer->count < currentRenderBuffer->max); // TODO(vdka): Render the buffer if it's full.

    currentRenderBuffer->vertices[currentRenderBuffer->count] = (V2){x, y};
    currentRenderBuffer->colors[currentRenderBuffer->count] = currentColor;
    currentRenderBuffer->count += 1;
}

// TODO(vdka): Determine a prefix
static void setColor(Color color) {

    currentColor = color;
}

static void setCamera(Camera camera) {

    currentCamera = camera;
    glUniform4f(currentShader.cameraLoc, camera.target.x, camera.target.y, camera.target.width, camera.target.height);
}

static i32 GetNumCircleSegments(f32 radius) {
    f32 cameraArea = currentCamera.target.width * currentCamera.target.height;
    f32 circleArea = TAU * (radius * radius) / 2;

    // TODO(vdka): tweak!
    i32 sides = 360 * sqrtf(circleArea) / sqrtf(cameraArea);

    if (sides < 16) return 16;
    if (sides > 90) return 90;
    return sides;
}

/**IMPLEMENTATION******************************************************************************************************************/
/*                                                                                                                                */
/*   #### ##     ## ########  ##       ######## ##     ## ######## ##    ## ########    ###    ######## ####  #######  ##    ##   */
/*    ##  ###   ### ##     ## ##       ##       ###   ### ##       ###   ##    ##      ## ##      ##     ##  ##     ## ###   ##   */
/*    ##  #### #### ##     ## ##       ##       #### #### ##       ####  ##    ##     ##   ##     ##     ##  ##     ## ####  ##   */
/*    ##  ## ### ## ########  ##       ######   ## ### ## ######   ## ## ##    ##    ##     ##    ##     ##  ##     ## ## ## ##   */
/*    ##  ##     ## ##        ##       ##       ##     ## ##       ##  ####    ##    #########    ##     ##  ##     ## ##  ####   */
/*    ##  ##     ## ##        ##       ##       ##     ## ##       ##   ###    ##    ##     ##    ##     ##  ##     ## ##   ###   */
/*   #### ##     ## ##        ######## ######## ##     ## ######## ##    ##    ##    ##     ##    ##    ####  #######  ##    ##   */
/*                                                                                                                                */
/**********************************************************************************************************************************/

#define DEF inline

DEF void InitWindow(i32 width, i32 height, const char* title) {
    Log(INFO, "Initializing ...");

    // Init graphics device (display device and OpenGL context)
    InitGraphicsDevice(width, height, title);

    glfwSetInputMode(window, GLFW_STICKY_KEYS, true);

    glUseProgram(currentShader.id);
}

DEF void CloseWindow(void) {
    glfwDestroyWindow(window);
    glfwTerminate();
}

DEF b32 WindowShouldClose(void) {
    PollInputEvents();
    return glfwWindowShouldClose(window) || glfwGetKey(window, exitKey) == GLFW_PRESS;
}

API b32 IsWindowMinimized(void);

API V2 GetWindowDimentions(void) {
    i32 w, h;
    glfwGetWindowSize(window, &w, &h);

    return (V2){w, h};
}

API void ToggleFullscreen(void);

DEF V2 GetMousePosition(void) {

    return WindowToWorld(mousePosition);
}

DEF b32 IsKeyPressed(i32 key) {
    if ((currentKeyState[key] != previousKeyState[key]) && (currentKeyState[key] == 1))
        return true;
    else
        return false;
}

// Detect if a key is being pressed (key held down)
DEF b32 IsKeyDown(i32 key) {
    if (GetKeyStatus(key) == 1) return true;
    else return false;
}

// Detect if a key has been released once
DEF b32 IsKeyReleased(i32 key) {
    b32 released = false;

    if ((currentKeyState[key] != previousKeyState[key]) && (currentKeyState[key] == 0)) released = true;
    else released = false;

    return released;
}

// Detect if a key is NOT being pressed (key not held down)
DEF b32 IsKeyUp(i32 key) {
    if (GetKeyStatus(key) == 0) return true;
    else return false;
}

// Get the last key pressed
DEF i32 GetKeyPressed(void) {
    return lastKeyPressed;
}

// Set a custom key to exit program
// NOTE: default exitKey is ESCAPE
DEF void SetExitKey(i32 key) {
    exitKey = key;
}

DEF void ClearBackground(Color color) {
    glClearColor(color.r, color.g, color.b, color.a);
}

DEF void BeginFrame(void) {
    currentTime = GetTime();
    updateTime = currentTime - previousTime;
    previousTime = currentTime;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

DEF void EndFrame(void) {
    UpdateDefaultBuffers();
    DrawDefaultBuffers();

    glfwSwapBuffers(window);
    glfwPollEvents();

    // Frame time constrol system
    currentTime = GetTime();
    drawTime = currentTime - previousTime;
    previousTime = currentTime;

    frameTime = updateTime + drawTime;

    f64 extraTime = 0.0;

    while (frameTime < targetTime) {
        currentTime = GetTime();
        extraTime = currentTime - previousTime;
        previousTime = currentTime;
        frameTime += extraTime;
    }
}

DEF f64 GetTime(void) {
    return glfwGetTime();
}

DEF void SetLineWidth(f32 width) {

    if (minLineWidth > width || maxLineWidth < width) {
        // TODO(vdka): Don't let this stop us, use geometry!
        static b32 warned = false;
        if (!warned) {
            warned = true;
            Log(WARNING, "Attempt to set line width to %f outside of supported line width range of %f - %f",
                width, minLineWidth, maxLineWidth);
        }
        return;
    }

    // Render out lines with the current width
    UpdateBuffer(&lines);
    UpdateBuffer(&connectedLines);
    DrawBuffer(&lines);
    DrawBuffer(&connectedLines);

    glLineWidth(width);
}

API void DrawPoint(f32 x, f32 y, Color color) {
    setBuffer(&pixels);
    setColor(color);
    {
        vertex(x, y);
    }
    setBuffer(NULL);
}

DEF void DrawTri(V2 v1, V2 v2, V2 v3, Color color) {
    setBuffer(&connectedLines);
    setColor(color);
    {
        vertex(v1.x, v1.y);
        vertex(v2.x, v2.y);
        vertex(v3.x, v3.y);
    }
    setBuffer(NULL);
    UpdateBuffer(&connectedLines);
    DrawBuffer(&connectedLines);
}

DEF void FillTri(V2 v1, V2 v2, V2 v3, Color color) {
    setBuffer(&triangles);
    setColor(color);
    {
        vertex(v1.x, v1.y);
        vertex(v2.x, v2.y);
        vertex(v3.x, v3.y);
    }
    setBuffer(NULL);
}

DEF void DrawTriXY(f32 x1, f32 y1, f32 x2, f32 y2, f32 x3, f32 y3, Color color) {
    setBuffer(&connectedLines);
    setColor(color);
    {
        vertex(x1, y1);
        vertex(x2, y2);
        vertex(x3, y3);
    }
    setBuffer(NULL);
    UpdateBuffer(&connectedLines);
    DrawBuffer(&connectedLines);
}

DEF void FillTriXY(f32 x1, f32 y1, f32 x2, f32 y2, f32 x3, f32 y3, Color color) {
    setBuffer(&triangles);
    setColor(color);
    {
        vertex(x1, y1);
        vertex(x2, y2);
        vertex(x3, y3);
    }
    setBuffer(NULL);
}

DEF void DrawRect(Rect rect, Color color) {
    f32 halfWidth   = rect.width  / 2;
    f32 halfHeight  = rect.height / 2;

    setBuffer(&connectedLines);
    setColor(color);
    {
        vertex(rect.x + halfWidth, rect.y - halfHeight); // tr
        vertex(rect.x - halfWidth, rect.y - halfHeight); // tl
        vertex(rect.x - halfWidth, rect.y + halfHeight); // bl
        vertex(rect.x + halfWidth, rect.y + halfHeight); // br
        vertex(rect.x + halfWidth, rect.y - halfHeight); // tr
    }
    setBuffer(NULL);
    UpdateBuffer(&connectedLines);
    DrawBuffer(&connectedLines);
}

DEF void FillRect(Rect rect, Color color) {
    f32 halfWidth   = rect.width  / 2;
    f32 halfHeight  = rect.height / 2;

    setBuffer(&quads);
    setColor(color);
    {
        vertex(rect.x - halfWidth, rect.y + halfHeight); // tl
        vertex(rect.x - halfWidth, rect.y - halfHeight); // bl
        vertex(rect.x + halfWidth, rect.y - halfHeight); // br
        vertex(rect.x + halfWidth, rect.y + halfHeight); // tr
    }
    setBuffer(NULL);
}

DEF void FillPoly(V2 center, i32 sides, f32 radius, Color color) {
    if (sides < 3) sides = 3;

    setBuffer(&triangles);
    setColor(color);
    {
        f32 theta = 2 * 3.1415926 / (f32) sides;
        f32 c = cosf(theta);
        f32 s = sinf(theta);
        f32 t;

        //we start at angle = 0
        f32 x = radius;
        f32 y = 0;

        for(int ii = 0; ii < sides; ii++) {
            vertex(x + center.x, y + center.y);

            //apply the rotation matrix
            t = x;
            x = c * x - s * y;
            y = s * t + c * y;

            vertex(x + center.x, y + center.y);
            vertex(center.x, center.y);
        }
    }
    setBuffer(&triangles);
}

DEF void FillCircle(V2 center, f32 radius, Color color) {
    f32 sides = GetNumCircleSegments(radius);
    FillPoly(center, sides, radius, color);
}

DEF void DrawRectXY(f32 x1, f32 y1, f32 x2, f32 y2, f32 x3, f32 y3, f32 x4, f32 y4, Color color) {
    setBuffer(&connectedLines);
    setColor(color);
    {
        vertex(x1, y1);
        vertex(x2, y2);
        vertex(x3, y3);
        vertex(x4, y4);
        vertex(x1, y1);
    }
    setBuffer(NULL);
    UpdateBuffer(&connectedLines);
    DrawBuffer(&connectedLines);
}

DEF void FillRectXY(f32 x1, f32 y1, f32 x2, f32 y2, f32 x3, f32 y3, f32 x4, f32 y4, Color color) {
    setBuffer(&quads);
    setColor(color);
    {
        vertex(x1, y1);
        vertex(x2, y2);
        vertex(x3, y3);
        vertex(x4, y4);
    }
    setBuffer(NULL);
}

#endif
#endif // TD2D_h
