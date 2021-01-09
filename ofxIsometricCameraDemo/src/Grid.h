//  ofxIsometricCameraDemo
//  Created by David Spry on 7/1/21.

#ifndef GRID_H
#define GRID_H

#include "ofMain.h"

class Grid
{
public:
    Grid():
    shouldRedraw(true)
    {
        path.setFilled(false);
        path.setStrokeWidth(2.0f);
        path.setStrokeColor(ofColor::lightBlue);

        buffer.allocate(W * SPACE, H * SPACE, GL_RGB, buffer.maxSamples());
    }

public:
    inline void setShouldRedraw()
    {
        shouldRedraw = true;
    }
    
    /// @brief Select a square on the grid (if it underlies the given screen position).
    /// @param origin The origin point.
    /// @param x The x-coordinate of the desired screen position.
    /// @param y The y-coordinate of the desired screen position.

    inline void select(glm::vec2 origin, int x, int y) noexcept
    {
        const int originX = std::floor(origin.x - static_cast<float>(W * SPACE) * 0.5f);
        const int originY = std::floor(origin.y - static_cast<float>(H * SPACE) * 0.5f);

        if (x < originX + SPACE || y < originY + SPACE)
        {
            return;
        }
            
        if (x >= (originX + (W - 1) * SPACE) || y >= (originY + (H - 1) * SPACE))
        {
            return;
        }
        
        selected.first  = (x - originX) / SPACE;
        selected.second = (y - originY) / SPACE;
        setShouldRedraw();
    }
    
    /// @brief Draw the grid centred at the given origin.
    /// @param origin The origin point.

    inline void draw(glm::vec2 origin)
    {
        ofPushStyle();
        const int x = origin.x - static_cast<float>(W * SPACE) * 0.5f;
        const int y = origin.y - static_cast<float>(H * SPACE) * 0.5f;
        
        if (shouldRedraw)
        {
            shouldRedraw = false;
            buffer.begin();
            path.clear();
            ofClear(25);
            
            for (auto c = 1; c < W; ++c)
            {
                path.moveTo(SPACE * (1 - 0), c * SPACE);
                path.lineTo(SPACE * (W - 1), c * SPACE);
            }
            
            for (auto r = 1; r < H; ++r)
            {
                path.moveTo(r * SPACE, SPACE * (1 - 0));
                path.lineTo(r * SPACE, SPACE * (H - 1));
            }
            
            path.draw();
            
            ofSetColor(ofColor::yellow);
            const int row = selected.second * SPACE + SPACE * 0.5f - 8;
            const int col = selected.first  * SPACE + SPACE * 0.5f - 8;
            ofDrawRectangle(col, row, 16, 16);

            ofSetColor(ofColor::lightBlue);
            for (auto r = 1; r < H; ++r)
            for (auto c = 1; c < W; ++c)
            {
                std::stringstream label;
                const auto col = c * SPACE;
                const auto row = r * SPACE;
                label << x + col << "x" << '\n' << y + row << "y";
                ofDrawBitmapStringHighlight(label.str(), col - 16, row - 2);
            }

            buffer.end();
        }

        ofSetColor(255);
        buffer.draw(x, y);
        ofPopStyle();
    }

private:
    bool shouldRedraw;
    const unsigned int W = 15;
    const unsigned int H = 15;
    const unsigned int SPACE = 50;
    std::pair<int, int> selected {1, 1};
    
private:
    ofPath  path;
    ofFbo buffer;
};

#endif
