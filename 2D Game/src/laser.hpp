#pragma once
#include <raylib.h>

class Laser {
    public:
        Laser(Vector2 position,int speed);
        void Update();
        void Draw();
        bool active;
        Rectangle GetREct();
    private:
        int speed;
        Vector2 position;
};