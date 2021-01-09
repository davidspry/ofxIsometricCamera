//  ofxIsometricCamera
//  Created by David Spry on 7/1/21.

#include "ofxIsometricCamera.hpp"

ofxIsometricCamera::ofxIsometricCamera():
isometricOrientation(&ofxIsometricCamera::orientationIsometricR)
{
    const float x = 0.5f * static_cast<float>(ofGetWidth());
    const float y = 0.5f * static_cast<float>(ofGetHeight());
    const float z = 0.0f;

    setOrigin(x, y, z);
    initialiseCamera();
    viewFromAbove();
}

ofxIsometricCamera::ofxIsometricCamera(glm::vec3 origin):
isometricOrientation(&ofxIsometricCamera::orientationIsometricR)
{
    setOrigin(origin);
    initialiseCamera();
    viewFromAbove();
}

void ofxIsometricCamera::initialiseCamera()
{
    camera.enableOrtho();
    camera.setFarClip (+10000);
    camera.setNearClip(-10000);
    camera.setScale(1.0f);
    camera.setVFlip(true);
}

void ofxIsometricCamera::begin() noexcept
{
    camera.begin();
}

void ofxIsometricCamera::end() noexcept
{
    camera.end();
}

void ofxIsometricCamera::transition(float t)
{
    if (t <= 0.0f) return viewFromAbove();
    if (t >= 1.0f) return viewIsometric();

    const glm::quat & a = ofxIsometricCamera::orientationFromAbove;
    const glm::quat & b = *(isometricOrientation);
    const glm::quat   k = glm::mix(a, b, t);
    
    setCameraOrientation(k);
}

void ofxIsometricCamera::viewFromAbove() noexcept
{
    viewingFromAbove = true;
    setCameraOrientation(ofxIsometricCamera::orientationFromAbove);
}

void ofxIsometricCamera::viewIsometric() noexcept
{
    viewingFromAbove = false;
    setCameraOrientation(*isometricOrientation);
}

bool ofxIsometricCamera::isViewingFromAbove() noexcept
{
    return viewingFromAbove;
}

void ofxIsometricCamera::setScale(float scale)
{
    camera.setScale(scale);
}

void ofxIsometricCamera::setIsometricOrientation(uint8_t orientation) noexcept
{
    const auto index = static_cast<bool>(orientation);
    const auto k = static_cast<IsometricOrientation>(index);
    
    setIsometricOrientation(k);
}

void ofxIsometricCamera::setIsometricOrientation(IsometricOrientation orientation) noexcept
{
    using IO = IsometricOrientation;
    switch (orientation)
    {
        case IO::L: { isometricOrientation = &(ofxIsometricCamera::orientationIsometricL); break; }
        case IO::R: { isometricOrientation = &(ofxIsometricCamera::orientationIsometricR); break; }
    }

    if (!isViewingFromAbove())
    {
        viewIsometric();
    }
}

void ofxIsometricCamera::setCameraOrientation(const glm::quat & orientation)
{
    camera.setGlobalOrientation(orientation);
}

void ofxIsometricCamera::setOrigin(const glm::vec2 & xy) noexcept
{
    camera.setPosition(xy.x, xy.y, 0.0f);
}

void ofxIsometricCamera::setOrigin(const glm::vec3 & xyz) noexcept
{
    camera.setGlobalPosition(xyz);
}

void ofxIsometricCamera::setOrigin(float x, float y, float z) noexcept
{
    camera.setGlobalPosition(x, y, z);
}

// MARK: - Coordinate space conversion

const glm::vec3 ofxIsometricCamera::screenToWorld(int x, int y) noexcept
{
    return screenToWorld({ x, y, camera.getPosition().z });
}

const glm::vec3 ofxIsometricCamera::screenToWorld(glm::vec3 xyz) noexcept
{
    return camera.screenToWorld(xyz);
}

const glm::vec3 ofxIsometricCamera::worldToScreen(glm::vec3 xyz) noexcept
{
    return camera.worldToScreen(xyz);
}

// MARK: - Orientations

const glm::quat ofxIsometricCamera::orientationFromAbove  = { 0, 0, 0, 0 };

const glm::quat ofxIsometricCamera::orientationIsometricL = { 0.880476236, 0.279848129,  0.115916878,  0.364705175 };

const glm::quat ofxIsometricCamera::orientationIsometricR = { 0.880476236, 0.279848129, -0.115916900, -0.364705235 };
