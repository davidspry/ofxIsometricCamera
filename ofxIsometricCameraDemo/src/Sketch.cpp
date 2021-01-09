#include "Sketch.hpp"

Sketch::Sketch()
{
    windowResized(ofGetWidth(), ofGetHeight());
}

void Sketch::setup()
{
    ofSetColor(95);
}

void Sketch::update()
{
    phase = phase + 0.005f;
    phase = phase - static_cast<int>(phase > TWO_PI) * TWO_PI;
    const float t = std::abs(std::sinf(phase));
    camera.transition(t);
}

void Sketch::draw()
{
    camera.begin();
    
    ofDrawRectangle(ofGetCurrentViewport());
    
    grid.draw(centre);
    
    camera.end();
}

void Sketch::keyPressed(int key)
{
    if (key == 32)
    {
        if (camera.isViewingFromAbove())
             return camera.viewIsometric();
        else return camera.viewFromAbove();
    }

    switch (key)
    {
        case 49: return camera.setIsometricOrientation(0);
        case 50: return camera.setIsometricOrientation(1);
        default: return;
    }
}

void Sketch::mousePressed(int x, int y, int button)
{
    mouseDragged(x, y, button);
}

void Sketch::mouseDragged(int x, int y, int button)
{
    const auto xy = camera.screenToWorld(x, y);
    
    grid.select(centre, xy.x, xy.y);
}

void Sketch::windowResized(int w, int h)
{
    grid.setShouldRedraw();
    centre.x = static_cast<float>(w) * 0.5f;
    centre.y = static_cast<float>(h) * 0.5f;
    camera.setOrigin(centre);
}
