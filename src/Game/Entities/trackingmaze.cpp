#include "Entity.h"
#include "trackingmaze.h"
#include <string>

using namespace std;

trackingmaze::trackingmaze(std::vector<std::vector<int>> maze,Player* played)
{
    this->played = played;
    this->maze = maze;
}

string trackingmaze::findCheese(int row, int col)
{
        if (row < 0 || row > 5) {
            return "";
        }
        if (col < 0 || col > 5) {
            return "";
        }
        if (maze[row][col] == 3) {  // Found cheese
            return "[" + to_string(row) + "," + to_string(col) + "]";
        }
        if (maze[row][col] == 0) {  // Hit on wall
            return "";
        }
        if (maze[row][col] == 2) {  // Been there
            return "";
        }
        maze[row][col] = 2;  // Mark new place

        string path = findCheese(row-1, col);

        if (!path.empty()) {  // Try up
            return "[" + to_string(row) + "," + to_string(col) + "]" + path;
        }
        path = findCheese(row, col+1);
        if (!path.empty()) {  // Try right
            return "[" + to_string(row) + "," + to_string(col) + "]" + path;
        }  
        path = findCheese(row+1, col);
        if (!path.empty()) {  // Try down
            return "[" + to_string(row) + "," + to_string(col) + "]" + path;
        }  
        path = findCheese(row, col-1);
        if (!path.empty()) {  // Try left
            return "[" + to_string(row) + "," + to_string(col) + "]" + path;
        } 
        return "";
}

void trackingmaze::tick()
{
    
}

void trackingmaze::activate()
{
    string route = this->findCheese(played->getX(),played->getY());
    ofDrawBitmapString("test:"  + route, ofGetWidth()/2-200, 100);
    //for(Grid* test : em->grids)
    //{
    //}
}