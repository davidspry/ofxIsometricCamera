#pragma once

#include "Grid.h"
#include "ofMain.h"

#include "ofxIsometricCamera.hpp"

class Sketch: public ofBaseApp
{
public:
    Sketch();

public:
    void setup()  override;
    void update() override;
    void draw()   override;

public:
    void keyPressed (int key) override;
    void mousePressed (int x, int y, int button) override;
    void mouseDragged (int x, int y, int button) override;
    void windowResized(int w, int h) override;
    
private:
    glm::vec2 centre;
    float phase = 0.0f;

private:
    Grid grid;
    ofxIsometricCamera camera;
};
