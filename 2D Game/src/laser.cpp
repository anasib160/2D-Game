#include "laser.hpp"
Laser::Laser(Vector2 position, int speed)
{
    this -> position = position;
    this -> speed = speed;
    active = true;
}
void Laser::Draw(){
    if(active){
        DrawRectangle(position.x, position.y, 5,15, RED); 
    }
}
Rectangle Laser::GetREct()
{
    return {position.x,position.y,5,15};
}
void Laser::Update()
{
    position.y += speed ;
    if(active){
        if(position.y<0){
            active = false ;
        }
    }
}