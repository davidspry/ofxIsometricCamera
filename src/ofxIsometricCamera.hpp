//  ofxIsometricCamera
//  Created by David Spry on 7/1/21.

#ifndef OFXISOMETRICCAMERA_HPP
#define OFXISOMETRICCAMERA_HPP

#include "ofMain.h"

/// @brief A camera that simplifies top-down and isometric orthographic views with animatable transitions.

class ofxIsometricCamera
{
public:
    /// @brief Construct an orthographic camera with a top-down view centred on the application window's centre point.

    ofxIsometricCamera();
    
    /// @brief Construct an orthographic camera with a top-down view centred on the given point.
    /// @param origin The desired centre-point of the camera's view.

    ofxIsometricCamera(glm::vec3 origin);
    
public:
    /// @brief Begin using the camera.
    /// @note  This should be called once per frame prior to drawing.

    void begin() noexcept;
    
    /// @brief Finish using the camera.
    /// @note  This should be called once per frame after drawing.

    void end()   noexcept;

public:
    /// @brief Constants defining the available orientations of the camera from its isometric view.

    enum class IsometricOrientation { R, L };
    
    /// @brief Use the camera's top-down orthographic view.
    
    void viewFromAbove() noexcept;
    
    /// @brief Use the camera's isometric orthographic view.

    void viewIsometric() noexcept;
    
    /// @brief Indicate whether the camera is currently viewing from above.

    bool isViewingFromAbove() noexcept;
    
    /// @brief Set the orientation of the camera's isometric view.
    /// @param orientation The index of the direction that the camera should face in its isometric view.
    /// @note  An orientation of 0 evaluates to the right-facing orientation. An orientation of 1 evaluates to the left-facing orientation.

    void setIsometricOrientation(uint8_t orientation) noexcept;
    
    /// @brief Set the orientation of the camera's isometric view.
    /// @param orientation The direction that the camera should face in its isometric view.

    void setIsometricOrientation(IsometricOrientation orientation) noexcept;
    
    /// @brief Set the camera's scale.
    /// @param scale The camera's scaling factor.

    void setScale(float scale);
    
    /// @brief Smoothly transition between the camera's top-down and isometric views.
    /// @param t The transition factor. This number will be bound by the range [0, 1].
    /// @note  A transition factor of 0.0 yields the top-down view, and a factor of 1.0 yields the isometric view.

    void transition(float t);

    /// @brief Set the point that the camera's views should be oriented by.
    /// @param xy The point that the camera's views should be oriented by.

    void setOrigin(const glm::vec2 & xy) noexcept;
    
    /// @brief Set the point that the camera's views should be oriented by.
    /// @param xyz The point that the camera's views should be oriented by.

    void setOrigin(const glm::vec3 & xyz) noexcept;
    
    /// @brief Set the point that the camera's views should be oriented by.
    /// @param x The x-coordinate of the point that the camera's views should be oriented by.
    /// @param y The y-coordinate of the point that the camera's views should be oriented by.
    /// @param z The z-coordinate of the point that the camera's views should be oriented by.

    void setOrigin(float x, float y, float z) noexcept;
    
public:
    /// @brief Convert the given screen position to the camera's coordinate space.
    /// @param x The x-coordinate of the screen position to be converted.
    /// @param y The y-coordinate of the screen position to be converted.
    
    const glm::vec3 screenToWorld(int x, int y) noexcept;
    
    /// @brief Convert the given screen position to the camera's coordinate space.
    /// @param xyz The screen position to be converted.

    const glm::vec3 screenToWorld(glm::vec3 xyz) noexcept;
    
    /// @brief Convert the given world position to a position on the screen.
    /// @param xyz The world position to be converted.

    const glm::vec3 worldToScreen(glm::vec3 xyz) noexcept;

private:
    /// @brief Initialise the underlying `ofCamera`.

    void initialiseCamera();
    
    /// @brief Set the orientation of the underlying `ofCamera`.
    /// @param orientation The desired orientation.

    void setCameraOrientation(const glm::quat & orientation);

private:
    bool viewingFromAbove;

private:
    const glm::quat * isometricOrientation;
    const static glm::quat orientationFromAbove;
    const static glm::quat orientationIsometricL;
    const static glm::quat orientationIsometricR;

private:
    ofCamera camera;
};

#endif
