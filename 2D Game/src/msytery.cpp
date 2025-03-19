#include "msytery.hpp"

Mystery::Mystery()
{
    image = LoadTexture("pic/mystery.png");
    alive=false;

}

Mystery::~Mystery()
{
    UnloadTexture(image);
}

void Mystery::Draw()
{
    if(alive){
        DrawTexture(image,position.x,position.y,WHITE);
    }
}

void Mystery::Spawn()
{
    position.y = 120 ;
    int side = GetRandomValue(0,1);

    if(side == 0){
        position.x = 0 ;
        speed = 3 ;
    }else{
        position.x=GetScreenWidth() - image.width;
        speed=-3;
    }
    alive = true ; 
}

Rectangle Mystery::getRect()
{   
    if(alive){
        return {position.x,position.y,float(image.width),float(image.height)};
    }else{
        return {position.x,position.y,0,0};
    }
}

void Mystery::Update()
{   
    if(alive){
        position.x+=speed;
        if(position.x > GetScreenWidth() -  image.width || position.x < 0){
            alive = false ;
        }
    }
}
