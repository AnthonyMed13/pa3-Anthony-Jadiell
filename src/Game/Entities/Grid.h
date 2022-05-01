#pragma once

#include "ofMain.h"

class Grid{
    
    public:
        Grid();
        Grid(int, int, int, int, string);
        void mousePressed(int x, int y);
        void tick();
        void render();
        bool wasPressed();
        void reset();

    private:
        int xPos, yPos, width, height;
        ofImage GridImage;
        ofImage clickedButtonImage;
        int pressedCounter = -1;
        string GridText;
};