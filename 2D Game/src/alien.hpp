#pragma once
#include <raylib.h>

class Alien{
    public:
        Alien(int type,Vector2 position);
        void Draw();
        void Update(int direction);
        int GetType();
        static void UnloadAliens();
        static Texture2D image[3];
        Rectangle getRect();
        Texture2D img;
        int type;
        Vector2 position;

    private:
};