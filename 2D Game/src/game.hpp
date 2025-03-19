#pragma once
#include "spaceship.hpp"
#include "obstacle.hpp"
#include "alien.hpp"
#include "msytery.hpp"

using namespace std;

class Game{
    public:
        Game();
        ~Game();
        void Draw();
        void Update();
        void HandleInput();
        bool run;
        int score;
        int HS;
        bool won;
    private:
        vector<Obstacle> CreateObstacle();
        vector<Alien> CreateAlien();
        void DeleteInactiveLasers();
        void MoveAliens();
        void MoveDownAliens(int distance);
        void ALiensshoot();
        void CHeckForHit();
        void GameOver();
        void Life();
        void highscore();
        Spaceship spaceship;
        vector<Obstacle> obstacles;
        vector<Alien> aliens;
        int aliensdire;
        vector<Laser> alienLasers;
        float current=0;
        Mystery Mystery;
        float lastspawn;
        float spawnInter;
        int life;
};