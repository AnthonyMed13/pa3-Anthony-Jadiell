#include "Grid.h"
Grid::Grid(){
   this->xPos = ofGetWidth()/2;
    this->yPos = ofGetHeight()/2;
    this->width = 64;
    this->height = 20; 
}
Grid::Grid(int xPos, int yPos, int width, int height, string GridText) {
    this->xPos = xPos;
    this->yPos = yPos;
    this->width = width;
    this->height = height;
    this->GridText = GridText;
}

void Grid::reset(){
}
void Grid::tick(){

}

void Grid::mousePressed(int x, int y){

}

void Grid::render(){
    ofSetColor(255, 0, 0);
    ofDrawBitmapString(GridText, xPos+4, yPos+10);
}
