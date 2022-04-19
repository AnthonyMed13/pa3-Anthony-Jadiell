#include "ChoosePlayerState.h"
#include "globalStatus.h"

ChoosePlayerState::ChoosePlayerState(Player *played) {
	play = played;
	pacmanButton = new Button(ofGetWidth()/2-60, ofGetHeight()/2, 64, 50, "Pacman");
	missPacmanButton = new Button(ofGetWidth()/2+60, ofGetHeight()/2, 64, 50, "Ms Pacman");
	img1.load("images/pacman.png");
	img2.load("images/mspacman.png");
	vector<ofImage> rightAnimframes;
	vector<ofImage> rightAnimframes2;
    ofImage temp;
    ofImage temp2;
	for(int i=0; i<3; i++){
        temp.cropFrom(img1, i*16, 0, 16, 16);
        rightAnimframes.push_back(temp);
		temp2.cropFrom(img2, i*16, 0, 16, 16);
        rightAnimframes2.push_back(temp2);
    }
	anim = new Animation(10,rightAnimframes);
	anim2 = new Animation(10,rightAnimframes2);

}
void ChoosePlayerState::tick() {
	pacmanButton->tick();
	anim->tick();
	missPacmanButton->tick();
	anim2->tick();
	if(pacmanButton->wasPressed()){
		status = true;
		setNextState("over");
		setFinished(true);
	}

	else if(missPacmanButton->wasPressed()){
		status = false;
		setNextState("over");
		setFinished(true);
	}
}
void ChoosePlayerState::render() {
	string title = "Choose Player";
	ofDrawBitmapString(title, ofGetWidth()/2-4*title.size(), ofGetHeight()/2-300, 50);
	ofSetBackgroundColor(0, 0, 0);
	ofSetColor(256, 256, 256);
	anim->getCurrentFrame().draw(ofGetWidth()/2-60, ofGetHeight()/2-100, 100, 100);
	anim2->getCurrentFrame().draw(ofGetWidth()/2+60, ofGetHeight()/2-100, 100, 100);
	pacmanButton->render();
	missPacmanButton->render();
}

void ChoosePlayerState::keyPressed(int key){
	
}

void ChoosePlayerState::mousePressed(int x, int y, int button){
	pacmanButton->mousePressed(x, y);
	missPacmanButton->mousePressed(x, y);
}

void ChoosePlayerState::reset(){
	setFinished(false);
	setNextState("");
	pacmanButton->reset();
	missPacmanButton->reset();
}

ChoosePlayerState::~ChoosePlayerState(){
	delete pacmanButton;
	delete missPacmanButton;
	delete anim;
	delete anim2;
}
