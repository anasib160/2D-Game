#pragma once 
#include <raylib.h>
#include "laser.hpp"
#include <vector>
#include <iostream>
using namespace std ; 


class Spaceship{
    private:
        double lastFireTime;
        Vector2 position;
    public:
        Spaceship();
        ~Spaceship();
        void Draw();
        void MoveLeft();
        void MoveRight();
        void FireLaser();
        vector<Laser> lasers;
        Rectangle getRect();
        void reset();
        Texture2D image;

};