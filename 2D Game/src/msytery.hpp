#pragma once 
#include <raylib.h>

class Mystery{
    public:
        Mystery();
        ~Mystery();
        void Update();
        void Draw();
        void Spawn();
        Rectangle getRect();
        bool alive;
    private:
        Vector2 position;
        Texture2D image;
        int speed;
};