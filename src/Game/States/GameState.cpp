#include "GameState.h"
#include "Entity.h"
#include "PauseState.h"

GameState::GameState() {
	music.load("music/pacman_chomp.wav");
	mapImage.load("images/map1.png");
	map = MapBuilder().createMap(mapImage);
}
void GameState::tick() {
	if(!music.isPlaying()){
			music.play();
	}
	map->tick();
	if(map->getPlayer()->getHealth() == 0){
		setFinished(true);
		setNextState("over");
		map->getPlayer()->setHealth(3);
		finalScore = map->getPlayer()->getScore();
		map->getPlayer()->setScore(0);
	}
	if(map->getPlayer()->getDotsConsumed()+1==map->getDotCount()){
		setFinished(true);
		setNextState("win");
		map->getPlayer()->setHealth(3);
		finalScore = map->getPlayer()->getScore();
		map->getPlayer()->setScore(0);
	}
}
void GameState::render() {
	map->render();
	ofDrawBitmapString(to_string(map->getPlayer()->getDotsConsumed()) + "/" + to_string(map->getDotCount()-1), ofGetWidth()/2, ofGetHeight()/2-300, 50);
}

void GameState::keyPressed(int key){
	map->keyPressed(key);
	switch(key)
	{
		case 'p':
			setFinished(true);
			setNextState("Pause");
			break;
		case 'y':
			setFinished(true);
			setNextState("win");
			map->getPlayer()->setHealth(3);
			finalScore = map->getPlayer()->getScore();
			map->getPlayer()->setScore(0);
			break;
	}
}

void GameState::mousePressed(int x, int y, int button){
	map->mousePressed(x, y, button);
}

void GameState::keyReleased(int key){
	map->keyReleased(key);
}

void GameState::reset(){
	setFinished(false);
	setNextState("");
}

int GameState::getFinalScore(){
	return finalScore;
}

GameState::~GameState(){
	delete map;
}