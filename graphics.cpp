#include "graphics.h"
#include "rect.h"
#include "sprite.h"
#include "lineDrawer.h"
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

GLdouble width, height;
Rect windowHidden;
Rect windowPane1;
Rect windowPane2;
Rect windowPane3;
Rect windowPane4;
Rect windowPane5;
Rect windowPane6;
Rect windowPane7;
Rect windowPane8;
Rect windowPane9;
Rect windowPane10;
Rect windowPane11;
Rect windowPane12;
color grassGreen(114, 117, 27);

Rect userHidden;
Sprite user;
Sprite userCursor = initSprite("cursor0.png");
Sprite userClick = initSprite("cursorClick.png");
Sprite userGrab = initSprite("cursorGrab.png");
Sprite userGrabbing = initSprite("cursorGrabbing.png");
bool isClicking;

Sprite player;
double xDelta;
double yDelta;
bool wPressed;
bool aPressed;
bool sPressed;
bool dPressed;
Sprite playerIdle1 = initSprite("knight1.png");
Sprite playerIdle2 = initSprite("knight2.png");
Sprite playerIdle3 = initSprite("knight3.png");
Sprite playerIdle4 = initSprite("knight4.png");
Sprite playerIdle5 = initSprite("knight5.png");
Sprite playerIdle6 = initSprite("knight6.png");
Sprite playerIdle7 = initSprite("knight7.png");
Sprite playerIdle8 = initSprite("knight8.png");
Sprite playerAim1 = initSprite("knightAim1.png");
Sprite playerAim2 = initSprite("knightAim2.png");
Sprite playerAim3 = initSprite("knightAim3.png");
Sprite playerAim4 = initSprite("knightAim4.png");
Sprite playerAim5 = initSprite("knightAim5.png");
Sprite playerAim6 = initSprite("knightAim6.png");
Sprite playerAim7 = initSprite("knightAim7.png");
Sprite playerAim8 = initSprite("knightAim8.png");

vector<unique_ptr<Sprite>> grassTileSet;
int mapTileWidth;
int mapTileHeight;
vector<vector<int>> grassCalcVec;
vector<vector<optional<Sprite>>> grassDrawVec;
Sprite mapBorder = initSprite("mapBorder.png");

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
    mapTileWidth = 25;
    mapTileHeight = 14;
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

void initPlayer() {
    player.setVec(playerIdle1.vec);
    player.setSize(64, 64);
    player.setScale(4);
    player.setCenter(width/2, height/2);
}

void initUI() {
    windowHidden.setSize(width, height);
    windowHidden.setCenter(width/2, height/2);
    windowPane1.setSize(width/2, height/2);
    windowPane1.setCenter(width/4, height/4);
    windowPane2.setSize(width/2, height/2);
    windowPane2.setCenter(3*width/4, height/4);
    windowPane3.setSize(width/2, height/2);
    windowPane3.setCenter(width/4, 3*height/4);
    windowPane4.setSize(width/2, height/2);
    windowPane4.setCenter(3*width/4, 3*height/4);
    windowPane5.setSize(width/4, height/4);
    windowPane5.setCenter(3*width/8, height/8);
    windowPane6.setSize(width/4, height/4);
    windowPane6.setCenter(5*width/8, height/8);
    windowPane7.setSize(width/4, height/4);
    windowPane7.setCenter(width/8, 3*height/8);
    windowPane8.setSize(width/4, height/4);
    windowPane8.setCenter(7*width/8, 3*height/8);
    windowPane9.setSize(width/4, height/4);
    windowPane9.setCenter(width/8, 5*height/8);
    windowPane10.setSize(width/4, height/4);
    windowPane10.setCenter(7*width/8, 5*height/8);
    windowPane11.setSize(width/4, height/4);
    windowPane11.setCenter(3*width/8, 7*height/8);
    windowPane12.setSize(width/4, height/4);
    windowPane12.setCenter(5*width/8, 7*height/8);
    mapBorder.setScale(4);
    mapBorder.setSize(2240, 1256);
    mapBorder.setCenter(2240/2, 1256/2);
}

void initUser() {
    // Initialize the user to be a 20x20 white block
    // centered in the top left corner of the graphics window
    userHidden.setSize(1, 1);
    userHidden.setCenter(0, 0);
    user.setVec(userCursor.vec);
    user.setCenter(0, 0);
    isClicking = false;
    xDelta = 0;
    yDelta = 0;
    wPressed = false;
    aPressed = false;
    sPressed = false;
    dPressed = false;
}

void init() {
    width = 640;
    height = 360;
    srand(time(nullptr));
    initUI();
    initUser();
    initGrass();
    initPlayer();
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
                tempSprite->setCenter(((j*64)+32-xDelta), ((i*64)+32-yDelta));
                if (tempSprite->isOverlapping(windowHidden)) tempSprite->draw();
            }
        }
    }
    player.draw();
    mapBorder.draw();
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

    // W
    if (key == GLFW_KEY_W && action == GLFW_PRESS) {
        wPressed = true;
    }
    if (key == GLFW_KEY_W && action == GLFW_RELEASE) {
        wPressed = false;
    }

    // A
    if (key == GLFW_KEY_A && action == GLFW_PRESS) {
        aPressed = true;
    }
    if (key == GLFW_KEY_A && action == GLFW_RELEASE) {
        aPressed = false;
    }

    // S
    if (key == GLFW_KEY_S && action == GLFW_PRESS) {
        sPressed = true;
    }
    if (key == GLFW_KEY_S && action == GLFW_RELEASE) {
        sPressed = false;
    }

    // D
    if (key == GLFW_KEY_D && action == GLFW_PRESS) {
        dPressed = true;
    }
    if (key == GLFW_KEY_D && action == GLFW_RELEASE) {
        dPressed = false;
    }
}

void cursor(GLFWwindow* window, double x, double y) {
    // Set the user's center point to be the coordinates
    // passed in as parameters to this function. This will make
    // the user block move with the mouse.
    glfwGetCursorPos(window, &x, &y);
    user.setCenter(x+8, y+8);
    userHidden.setCenter(x, y);
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        if (userHidden.isOverlapping(windowPane1)) {
            if (userHidden.isOverlapping(windowPane5)) player.setVec(playerAim7.vec);
            else if (userHidden.isOverlapping(windowPane7)) player.setVec(playerAim5.vec);
            else player.setVec(playerAim6.vec);
        }
        else if (userHidden.isOverlapping(windowPane2)) {
            if (userHidden.isOverlapping(windowPane6)) player.setVec(playerAim7.vec);
            else if (userHidden.isOverlapping(windowPane8)) player.setVec(playerAim1.vec);
            else player.setVec(playerAim8.vec);
        }
        else if (userHidden.isOverlapping(windowPane3)) {
            if (userHidden.isOverlapping(windowPane9)) player.setVec(playerAim5.vec);
            else if (userHidden.isOverlapping(windowPane11)) player.setVec(playerAim3.vec);
            else player.setVec(playerAim4.vec);
        }
        else if (userHidden.isOverlapping(windowPane4)) {
            if (userHidden.isOverlapping(windowPane10)) player.setVec(playerAim1.vec);
            else if (userHidden.isOverlapping(windowPane12)) player.setVec(playerAim3.vec);
            else player.setVec(playerAim2.vec);
        }
    }
    else {
        if (userHidden.isOverlapping(windowPane1)) {
            if (userHidden.isOverlapping(windowPane5)) player.setVec(playerIdle7.vec);
            else if (userHidden.isOverlapping(windowPane7)) player.setVec(playerIdle5.vec);
            else player.setVec(playerIdle6.vec);
        }
        else if (userHidden.isOverlapping(windowPane2)) {
            if (userHidden.isOverlapping(windowPane6)) player.setVec(playerIdle7.vec);
            else if (userHidden.isOverlapping(windowPane8)) player.setVec(playerIdle1.vec);
            else player.setVec(playerIdle8.vec);
        }
        else if (userHidden.isOverlapping(windowPane3)) {
            if (userHidden.isOverlapping(windowPane9)) player.setVec(playerIdle5.vec);
            else if (userHidden.isOverlapping(windowPane11)) player.setVec(playerIdle3.vec);
            else player.setVec(playerIdle4.vec);
        }
        else if (userHidden.isOverlapping(windowPane4)) {
            if (userHidden.isOverlapping(windowPane10)) player.setVec(playerIdle1.vec);
            else if (userHidden.isOverlapping(windowPane12)) player.setVec(playerIdle3.vec);
            else player.setVec(playerIdle2.vec);
        }
    }
}

void mouse(GLFWwindow* window, int button, int action, int mods) {
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        user.setVec(userClick.vec);
        isClicking = true;
        if (userHidden.isOverlapping(windowPane1)) {
            if (userHidden.isOverlapping(windowPane5)) player.setVec(playerAim7.vec);
            else if (userHidden.isOverlapping(windowPane7)) player.setVec(playerAim5.vec);
            else player.setVec(playerAim6.vec);
        }
        else if (userHidden.isOverlapping(windowPane2)) {
            if (userHidden.isOverlapping(windowPane6)) player.setVec(playerAim7.vec);
            else if (userHidden.isOverlapping(windowPane8)) player.setVec(playerAim1.vec);
            else player.setVec(playerAim8.vec);
        }
        else if (userHidden.isOverlapping(windowPane3)) {
            if (userHidden.isOverlapping(windowPane9)) player.setVec(playerAim5.vec);
            else if (userHidden.isOverlapping(windowPane11)) player.setVec(playerAim3.vec);
            else player.setVec(playerAim4.vec);
        }
        else if (userHidden.isOverlapping(windowPane4)) {
            if (userHidden.isOverlapping(windowPane10)) player.setVec(playerAim1.vec);
            else if (userHidden.isOverlapping(windowPane12)) player.setVec(playerAim3.vec);
            else player.setVec(playerAim2.vec);
        }
    }
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
        user.setVec(userCursor.vec);
        isClicking = false;
        if (userHidden.isOverlapping(windowPane1)) {
            if (userHidden.isOverlapping(windowPane5)) player.setVec(playerIdle7.vec);
            else if (userHidden.isOverlapping(windowPane7)) player.setVec(playerIdle5.vec);
            else player.setVec(playerIdle6.vec);
        }
        else if (userHidden.isOverlapping(windowPane2)) {
            if (userHidden.isOverlapping(windowPane6)) player.setVec(playerIdle7.vec);
            else if (userHidden.isOverlapping(windowPane8)) player.setVec(playerIdle1.vec);
            else player.setVec(playerIdle8.vec);
        }
        else if (userHidden.isOverlapping(windowPane3)) {
            if (userHidden.isOverlapping(windowPane9)) player.setVec(playerIdle5.vec);
            else if (userHidden.isOverlapping(windowPane11)) player.setVec(playerIdle3.vec);
            else player.setVec(playerIdle4.vec);
        }
        else if (userHidden.isOverlapping(windowPane4)) {
            if (userHidden.isOverlapping(windowPane10)) player.setVec(playerIdle1.vec);
            else if (userHidden.isOverlapping(windowPane12)) player.setVec(playerIdle3.vec);
            else player.setVec(playerIdle2.vec);
        }
    }
}

void moveTimer(int dummy) {
    if ((wPressed) && (yDelta > 0.0)) {
        yDelta += -4.0;
    }
    if ((aPressed) && (xDelta > 0.0)) {
        xDelta += -4.0;
    }
    if ((sPressed) && (yDelta < 540.0)) {
        yDelta += 4.0;
    }
    if ((dPressed) && (xDelta < 960.0)) {
        xDelta += 4.0;
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
            moveTimer(0);
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