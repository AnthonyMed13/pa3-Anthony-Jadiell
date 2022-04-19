#include "PauseState.h"
#include "GameState.h"

PauseState::PauseState() {
	startButton = new Button(ofGetWidth()/2, ofGetHeight()/2, 64, 50, "UnPause Game");
	img1.load("images/pacman.png");
	vector<ofImage> rightAnimframes;
    ofImage temp;
	for(int i=0; i<3; i++){
        temp.cropFrom(img1, i*16, 0, 16, 16);
        rightAnimframes.push_back(temp);
    }
	anim = new Animation(10,rightAnimframes);

}
void PauseState::tick() {
	startButton->tick();
	anim->tick();
	if(startButton->wasPressed()){
		setNextState("Game");
		setFinished(true);
	}
}
void PauseState::render() {
    string status = "Game is Currently Paused";
	ofDrawBitmapString(status, ofGetWidth()/2-4*status.size(), ofGetHeight()/2-300, 100);
	ofSetBackgroundColor(12, 0, 100);
	ofSetColor(256, 256, 256);
	anim->getCurrentFrame().draw(ofGetWidth()/2, ofGetHeight()/2-100, 100, 100);
	startButton->render();


}

void PauseState::keyPressed(int key){
    switch(key)
    {
        case 'q':
        setFinished(true);
		setNextState("Menu");
		break;
    }
}

void PauseState::mousePressed(int x, int y, int button){
	startButton->mousePressed(x, y);
}

void PauseState::reset(){
	setFinished(false);
	setNextState("");
	startButton->reset();
}

void PauseState::setScore(int sc){
    score = sc;
}

PauseState::~PauseState(){
	delete startButton;
	delete anim;
}

