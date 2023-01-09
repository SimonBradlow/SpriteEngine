#include "graphics.h"
#include "rect.h"
#include "sprite.h"
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

GLdouble width, height;
Rect windowHidden;
color grassGreen(114, 117, 27);

Rect userHidden;
Sprite user;
Sprite userCursor = initSprite("cursor0.png");
Sprite userClick = initSprite("cursorClick.png");
Sprite userGrab = initSprite("cursorGrab.png");
Sprite userGrabbing = initSprite("cursorGrabbing.png");

vector<unique_ptr<Sprite>> grassTileSet;
int mapTileWidth;
int mapTileHeight;
vector<vector<int>> grassCalcVec;
vector<vector<optional<Sprite>>> grassDrawVec;

void initGrass() {
    grassTileSet.push_back(make_unique<Sprite>(initSprite("grass1.png")));
    grassTileSet.push_back(make_unique<Sprite>(initSprite("grass2.png")));
    grassTileSet.push_back(make_unique<Sprite>(initSprite("grass3.png")));
    grassTileSet.push_back(make_unique<Sprite>(initSprite("grass4.png")));
    grassTileSet.push_back(make_unique<Sprite>(initSprite("grass5.png")));
    grassTileSet.push_back(make_unique<Sprite>(initSprite("grass6.png")));
    grassTileSet.push_back(make_unique<Sprite>(initSprite("grass7.png")));
    grassTileSet.push_back(make_unique<Sprite>(initSprite("grass8.png")));
    grassTileSet.push_back(make_unique<Sprite>(initSprite("grass9.png")));
    grassTileSet.push_back(make_unique<Sprite>(initSprite("grass10.png")));
    grassTileSet.push_back(make_unique<Sprite>(initSprite("grass11.png")));
    grassTileSet.push_back(make_unique<Sprite>(initSprite("grass12.png")));
    grassTileSet.push_back(make_unique<Sprite>(initSprite("grass0.png")));
    mapTileWidth = 15;
    mapTileHeight = 10;
    for (int i=0; i<mapTileHeight; ++i) {
        vector<int> tempVec;
        tempVec.clear();
        for (int j=0; j<mapTileWidth; ++j) {
            int tileChange = rand() % 4;
            if (tileChange > 2) {
                int newTile = rand() % 13;
                //tempVec.push_back(make_optional(grassTileSet[newTile]));
                tempVec.push_back(newTile);
            }
            //else tempVec.push_back(grassTileSet[9]);
            else tempVec.push_back(12);
        }
        //grassDrawVec.push_back(tempVec);
        grassCalcVec.push_back(tempVec);
    }
}

void initUI() {
    windowHidden.setSize(width, height);
    windowHidden.setCenter(width/2, height/2);
}

void initUser() {
    // Initialize the user to be a 20x20 white block
    // centered in the top left corner of the graphics window
    userHidden.setSize(32, 32);
    userHidden.setCenter(0, 0);
    user.setVec(userCursor.vec);
    user.setCenter(0, 0);
}

void init() {
    width = 640;
    height = 360;
    srand(time(nullptr));
    initUI();
    initUser();
    initGrass();
}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(114.0/256.0, 117.0/256.0, 27.0/256.0, 1.0f);
}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
    // Tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width*2, height*2); // DO NOT CHANGE THIS LINE (unless you are running Catalina on Mac)

    // Do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION); // DO NOT CHANGE THIS LINE
    glLoadIdentity(); // DO NOT CHANGE THIS LINE
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f); // DO NOT CHANGE THIS LINE

    // Clear the color buffer with current clearing color
    glClear(GL_COLOR_BUFFER_BIT); // DO NOT CHANGE THIS LINE

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // DO NOT CHANGE THIS LINE

    // Enable alpha channel blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    /*
     * Draw here
     */
    for (int i=0; i<mapTileHeight; ++i) {
        for (int j=0; j<mapTileWidth; ++j) {
            int currTile = grassCalcVec[i][j];
            if (currTile < 13) {
                unique_ptr<Sprite> &tempSprite = grassTileSet[currTile];
                tempSprite->setVec(tempSprite->vec);
                tempSprite->setSize(64, 64);
                tempSprite->setScale(2);
                tempSprite->setCenter(((j*64)+32), ((i*64)+32));
                if (tempSprite->isOverlapping(windowHidden)) tempSprite->draw();
            }
        }
    }

    user.draw();

    glFlush();  // Render now
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // escape
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwTerminate();
        exit(0);
    }
    /*
    if (key == GLFW_KEY_W && action == GLFW_PRESS) {
        for (unique_ptr<Shape> &s : grassDrawVec) {
            // Move all the clouds to the left
            s->moveX(-0.4);
            // If a shape has moved off the screen
            if (s->getCenterX() < -48) {
                // Set it to the right of the screen so that it passes through again
                s->setCenterX(width + 48);
            }
        }
    }
    if (key == GLFW_KEY_A && action == GLFW_PRESS) {
    }
    if (key == GLFW_KEY_S && action == GLFW_PRESS) {
    }
    if (key == GLFW_KEY_D && action == GLFW_PRESS) {
    }
              */
}

void cursor(GLFWwindow* window, double x, double y) {
    // Set the user's center point to be the coordinates
    // passed in as parameters to this function. This will make
    // the user block move with the mouse.
    glfwGetCursorPos(window, &x, &y);
    user.setCenter(x+5, y+5);
    userHidden.setCenter(x+5, y+5);
}

void mouse(GLFWwindow* window, int button, int action, int mods) {
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        user.setVec(userClick.vec);
    }
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
        user.setVec(userCursor.vec);
    }
}

void moveTimer(int dummy, int direction) {
    for (unique_ptr<Sprite> &s : grassTileSet) {
        if (direction == 0) s->moveY(1);
        if (direction == 1) s->moveX(-1);
        if (direction == 2) s->moveY(-1);
        if (direction == 3) s->moveX(1);
    }
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
    init();
    if (!glfwInit()) exit(EXIT_FAILURE);

    GLFWwindow* window;
    window = glfwCreateWindow(width, height, "", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // Our own OpenGL initialization
    initGL();

    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glfwSetKeyCallback(window, kbd);
    // handles mouse movement
    glfwSetCursorPosCallback(window, cursor);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    // handles mouse clicks
    glfwSetMouseButtonCallback(window, mouse);

    // handles timer
    float time = 0.0167;
    float previous = glfwGetTime();

    // Enter the event-processing loop
    while (!glfwWindowShouldClose(window)) {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        float now = glfwGetTime();
        float delta = now - previous;
        previous = now;
        time -= delta;


        if (time <= 0.f) {
            display();
            glfwSwapBuffers(window);
            glfwPollEvents();
            time = 0.0167;
        }
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
    return 0;
}