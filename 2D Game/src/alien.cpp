#include "alien.hpp"

Texture2D Alien::image[3]={};


Alien::Alien(int type, Vector2 position)
{
    this->type = type;
    this-> position = position;

    if( image[type-1].id == 0){
        switch (type){
            case 1 :
                image[0] = LoadTexture("pic/alien_1.png");
                break;
            case 2 :
                image[1]= LoadTexture("pic/alien_2.png");
                break;
            case 3 :
                image[2] = LoadTexture("pic/alien_3.png");
                break;
            default:
                image[0] = LoadTexture("pic/alien_3.png");
        }
    }

}

void Alien::Draw()
{
    DrawTextureV(image[type-1],position,WHITE);
}

void Alien::Update(int direction)
{
    position.x+=direction;
}

int Alien::GetType()
{
    return type;
}

void Alien::UnloadAliens()
{
    for(int i=0 ; i<3 ; i++ ){
        UnloadTexture(image[i]);
    }
}

Rectangle Alien::getRect()
{
    return {position.x,position.y,float(image[type-1].width),float(image[type-1].height)};
}
