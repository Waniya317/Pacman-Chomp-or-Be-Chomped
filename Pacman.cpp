#include "Pacman.h"
#include <iostream>
#include <cmath>
#include<SFML/Audio.hpp>
#include"SoundManager.h"
using namespace sf;
using namespace std;

Pacman::Pacman() {
    row = 1;
    col = 1;
    tileSize = 16.0f;
    mouthOpen = false;
    mouthTimer = 0.0f;
    direction = 0; 
    shape.setPointCount(20);
   
    float radius = tileSize * 0.6f;
	float centerX = col * tileSize + tileSize / 2.0f;
	float centerY = row * tileSize + tileSize / 2.0f;
    for (int i = 0; i < 18; i++) 
    { 
        float angle = i * 2 * 3.14159f / 18 + 0.785f; 
        shape.setPoint(i, Vector2f(centerX + radius * cos(angle), centerY + radius * sin(angle)));
    }
    shape.setPoint(18, Vector2f(centerX, centerY)); 
    shape.setPoint(19, Vector2f(centerX + radius * cos(0.785f), centerY + radius * sin(0.785f)));
    shape.setFillColor(Color::Yellow);
}

Pacman::Pacman(int startRow, int startCol, float tileSize)
    : row(startRow), col(startCol), tileSize(tileSize), mouthOpen(false), mouthTimer(0.0f), direction(0) {
    shape.setPointCount(20);
    float radius = tileSize * 0.6f;
	float centerX = col * tileSize + tileSize / 2.0f;
	float centerY = row * tileSize + tileSize / 2.0f;
    for (int i = 0; i < 18; i++) {
        float angle = i * 2 * 3.14159f / 18 + 0.785f;
        shape.setPoint(i, Vector2f(centerX + radius * cos(angle), centerY + radius * sin(angle)));
    }
    shape.setPoint(18, Vector2f(centerX, centerY));
    shape.setPoint(19, Vector2f(centerX + radius * cos(0.785f), centerY + radius * sin(0.785f)));
    shape.setFillColor(Color::Yellow);
   
}

bool Pacman::handleInput(Keyboard::Key key, Game& game, Score& score,SoundManager &soundManager, FrontEnd& frontend) {
    int newRow = row;
    int newCol = col;
    int newDirection = direction;

    if (key == Keyboard::Up) {
        newRow--;
        newDirection = 3;
        
    }
    else if (key == Keyboard::Down) {
        newRow++;
        newDirection = 1;
        
    }
    else if (key == Keyboard::Left) {
        newCol--;
        newDirection = 2;
        
    }
    else if (key == Keyboard::Right) {
        newCol++;
        newDirection = 0;
       
    }
    else {
        return false;
    }

    // Check wall collision
    if (newRow >= 0 && newRow < game.rowsloaded && newCol >= 0 && newCol < 86 &&
        game.gamelayout[newRow][newCol] != '#') {
        row = newRow;
        col = newCol;
        direction = newDirection;
        // Update shape position and mouth
		float centerX = col * tileSize + tileSize / 2.0f;
		float centerY = row * tileSize + tileSize / 2.0f;
		float radius = tileSize * 0.6f;
        float mouthAngle = (mouthOpen ? 0.785f : 0.262f); 
        float startAngle = (direction * 1.5708f) + mouthAngle / 2; 
        for (int i = 0; i < 18; i++) {
            float angle = i * (2 * 3.14159f - mouthAngle) / 18 + startAngle;
            shape.setPoint(i, Vector2f(centerX + radius * cos(angle), centerY + radius * sin(angle)));
        }
        shape.setPoint(18, Vector2f(centerX, centerY));
        shape.setPoint(19, Vector2f(centerX + radius * cos(startAngle), centerY + radius * sin(startAngle)));
       
    }
    

    // eat food 
    if (game.gamelayout[row][col] == '.') {
        score.add(10); 
        game.gamelayout[row][col] = ' '; 
       
        soundManager.playChomp();
        
    }
    else if (game.gamelayout[row][col] == 'o') {
        score.add(50);
        game.gamelayout[row][col] = ' ';
       
        soundManager.playPellet();
        frontend.stopArenaMusic();
        return true;
    }
    return false;

}

void Pacman::update(float deltaTime) {
    mouthTimer += deltaTime;
    if (mouthTimer > 0.2f) { 
        mouthOpen = !mouthOpen;
        mouthTimer = 0.0f;
		float centerX = col * tileSize + tileSize / 2.0f;
		float centerY = row * tileSize + tileSize / 2.0f;
		float radius = tileSize * 0.6f;
        float mouthAngle = (mouthOpen ? 0.785f : 0.262f);
        float startAngle = (direction * 1.5708f) + mouthAngle / 2;
        for (int i = 0; i < 18; i++) {
            float angle = i * (2 * 3.14159f - mouthAngle) / 18 + startAngle;
            shape.setPoint(i, Vector2f(centerX + radius * cos(angle), centerY + radius * sin(angle)));
        }
        shape.setPoint(18, Vector2f(centerX, centerY));
        shape.setPoint(19, Vector2f(centerX + radius * cos(startAngle), centerY + radius * sin(startAngle)));
    }
}

void Pacman::draw(RenderWindow& window) const {
    window.draw(shape);
}

int Pacman::getRow() const { return row; }
int Pacman::getCol() const { return col; }