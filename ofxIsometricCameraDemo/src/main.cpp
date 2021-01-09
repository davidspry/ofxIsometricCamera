#include "ofMain.h"
#include "Sketch.hpp"

constexpr int W = 1100;
constexpr int H = 1100;

int main()
{
    ofSetupOpenGL(W, H, OF_WINDOW);
    ofSetWindowPosition(35, 65);
    ofSetCircleResolution(256);
    ofEnableAntiAliasing();
    ofEnableSmoothing();
    ofSetFrameRate(60);
    ofBackground(15);

    ofRunApp(new Sketch());
}
