#include "spaceship.hpp"


Spaceship::Spaceship()
{
    image = LoadTexture("pic/spaceship.png");
    position.x= (GetScreenWidth()-image.width)/2;
    position.y=(GetScreenHeight()-image.height)-100;
    lastFireTime=0;
}

Spaceship::~Spaceship(){
    UnloadTexture(image);
}

void Spaceship::Draw(){
    DrawTextureV(image, position, WHITE);
}

void Spaceship::MoveLeft(){
    position.x-=7;
    if(position.x < 40){
        position.x = 40;
    }
}
void Spaceship::MoveRight(){
    position.x+=7;
    if(position.x > GetScreenWidth()-image.width-50){
        position.x = GetScreenWidth()-image.width-50;
    }
}

void Spaceship::FireLaser()
{
    if(GetTime() - lastFireTime >=0.3){
        lasers.push_back(Laser( {position.x + image.width/2 ,position.y} , -7));
        lastFireTime = GetTime();
    }
}

Rectangle Spaceship::getRect()
{
    return {position.x,position.y,float(image.width),float(image.height)};
}

void Spaceship::reset()
{
    position.x= (GetScreenWidth()-image.width)/2;
    position.y=(GetScreenHeight()-image.height)-100;
}

