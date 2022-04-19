#pragma once

#include "State.h"
#include "Button.h"
#include "Animation.h" 
#include "Player.h"

class ChoosePlayerState : public State {
private:
	ofImage img1;
	ofImage img2;
	Button *pacmanButton;
	Button *missPacmanButton;
	Animation* anim;
	Animation* anim2;
	bool skin;

public:
	ChoosePlayerState(Player*);
	Player* play;
	~ChoosePlayerState();
	void tick();
	void render();
	void keyPressed(int key);
	void mousePressed(int x, int y, int button);
	void reset();
	bool getSkin(){return skin;}
	void setSkin(bool skins){skin=skins;}
};