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
        int getX() {return xPos;}
        int getY() {return yPos;}
        string getText() {return GridText;}
    private:
        int xPos, yPos, width, height;
        ofImage GridImage;
        ofImage clickedButtonImage;
        int pressedCounter = -1;
        string GridText;
};