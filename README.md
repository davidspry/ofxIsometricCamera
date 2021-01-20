# ofxIsometricCamera

An add-on for [openFrameworks](https://github.com/openframeworks/openFrameworks) that provides a simple interface to an orthographic isometric camera.

To use this add-on with openFrameworks:
  - Download the repository;
  - Move the contents of the repository to `{OF_ROOT}/addons/ofxIsometricCamera/`;
  - Add ofxIsometricCamera as an add-on to your project using the openFrameworks project generator.
  
See the included Xcode project, 'ofxIsometricCameraDemo', for a simple usage demo.
  
## Usage

Add an instance of the camera to your project.

```cpp
#include "ofxIsometricCamera.hpp"

ofxIsometricCamera camera;
```

Draw between the camera's `begin` and `end` methods.
```cpp
void ofApp::draw()
{
    camera.begin();
    
    // ...
    
    camera.end();
}
```
## Changing the camera's view
By default, the camera's view should be indistinguishable from openFrameworks' default view. However, it can be changed in the following ways.

```cpp
// Set the centre-point of the camera's view.
camera.setOrigin(xyz);

// Use an orthographic top-down view, as in the default view shown by openFrameworks.
camera.viewFromAbove();

// Use an isometric view.
camera.viewIsometric();
```

Incidentally, the camera can transition smoothly between its two views.

```cpp
// Smoothly oscillate between 0.0 and 1.0.
phase = phase + 0.005f;
phase = phase - static_cast<int>(phase > TWO_PI) * TWO_PI;
const float t = std::abs(std::sinf(phase));

// Set the camera's transition point to a value between 0.0 and 1.0
camera.transition(t);
```

Finally, the camera can face the origin from the left or from the right.
```cpp
// Use a right-facing orientation.
camera.setIsometricOrientation(0);
camera.setIsometricOrientation(ofxIsometricCamera::IsometricOrientation::R);

// Use a left-facing orientation.
camera.setIsometricOrientation(1);
camera.setIsometricOrientation(ofxIsometricCamera::IsometricOrientation::L);
```
