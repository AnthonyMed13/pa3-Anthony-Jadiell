#include "State.h"
#include "Button.h"
#include "Animation.h" 
#include "MapBuilder.h"
#pragma once

class PauseState: public State
{
    private:
	ofImage img1;
	Button *startButton;
	Animation* anim;
	int score=0;
    public:
        PauseState();
        ~PauseState();
        void tick();
	    void render();
	    void keyPressed(int key);
	    void mousePressed(int x, int y, int button);
	    void reset();
	    void setScore(int);
        bool isPause = false;
};