#include <stdio.h>
#include <glad/glad.h>
#include <glfw/glfw3.h>

typedef struct Render_color {
    float r;
    float g;
    float b;
    float solid;
} Render_color;

enum color {RED, GREEN, BLUE, NONE};

#define COLOR_STEP 0.000025f

int main (void) {

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(400, 400, "RGB", NULL, NULL);
    if (window == NULL) {
        printf("Window did not open\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    gladLoadGL();
    glViewport(0, 0, 400, 400);

    Render_color draw_color;
    draw_color.r = 0.0f;
    draw_color.g = 0.0f;
    draw_color.b = 0.0f;
    draw_color.solid = 1.0f;

    while (!glfwWindowShouldClose(window)) {

        glfwPollEvents();

        enum color active = NONE;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) active = RED;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) active = GREEN;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) active = BLUE;

        int shift_held = (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)  == GLFW_PRESS)||
                         (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS);

        float delta = shift_held ? -COLOR_STEP : COLOR_STEP;

        switch (active) {
            case RED:
                draw_color.r += delta;
                if (draw_color.r > 1.0f) draw_color.r = 1.0f;
                if (draw_color.r < 0.0f) draw_color.r = 0.0f;
                break;
            case GREEN:
                draw_color.g += delta;
                if (draw_color.g > 1.0f) draw_color.g = 1.0f;
                if (draw_color.g < 0.0f) draw_color.g = 0.0f;
                break;
            case BLUE:
                draw_color.b += delta;
                if (draw_color.b > 1.0f) draw_color.b = 1.0f;
                if (draw_color.b < 0.0f) draw_color.b = 0.0f;
                break;
            case NONE:
            default:
                break;
        }

        glClearColor(draw_color.r, draw_color.g, draw_color.b, draw_color.solid);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}