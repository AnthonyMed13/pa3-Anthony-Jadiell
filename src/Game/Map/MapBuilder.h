#pragma once

#include "ofMain.h" 
#include "Map.h"
#include "Dot.h"
#include "BigDot.h"
#include "Ghost.h"
#include "PowerUpCherry.h"
#include "PowerUpStraw.h"
#include "PowerUpRandom.h"
#include "PowerUpUltimate.h"

class MapBuilder {
    public:
        MapBuilder();
	    Map* createMap(ofImage);

	private:
        vector<ofImage> bound;
        int pixelMultiplier;
        bool oneLimit = false;
        bool oneLimit2 = false;
        bool oneLimit3= false;
        int counter =1;
        ofColor boundBoundBlock;
        ofColor pacman;
        ofColor ghostC;
	ofColor dotC;
	ofColor bigDotC;
        ofImage pacmanSpriteSheet;
        ofImage tempBound;
        ofImage getSprite(ofImage, int, int);
        EntityManager* entityManager;
        int xR;
};