#include <raylib.h>
#include "game.hpp"
#include <iostream>
#include <string>
using namespace std;

string FormatWithLeadingZeros(int number, int width) {
    string numberText = to_string(number);
    int leadingZeros = width - numberText.length();
    return numberText = string(leadingZeros, '0') + numberText;
}

int main() 
{
    Color white = {235,235,235,255};
    Font font = LoadFontEx("font/monogram.ttf", 64, 0, 0);;
    int offset = 50 ;
    int windowWidth = 750 ;
    int windowHeight = 700 ;

    InitWindow(windowWidth + offset , windowHeight + offset*2  , "C++ Spaces Invaders");
    SetTargetFPS(60);

    Game game;
    while(WindowShouldClose() == false){

       game.HandleInput();
       game.Update();

       BeginDrawing();
       ClearBackground(white);

       DrawTextEx(font,"HIGHSCORE",{600,30},30,2,GRAY);
       string highscore = FormatWithLeadingZeros(game.HS,6);
       DrawTextEx(font,highscore.c_str(),{600,60},34,2,GRAY);

       DrawTextEx(font,"SCORE",{50,30},34,2,GRAY);
       string score = FormatWithLeadingZeros(game.score,6);
       DrawTextEx(font,score.c_str(),{50,60},34,2,GRAY);

       DrawRectangleRoundedLinesEx({10,10,780,780},0.18f, 20,3 ,GRAY);

       DrawLineEx({25,730},{775,730,},2,GRAY);

       if(game.run && !game.won){
            DrawTextEx(font,"LEVEL 01",{570,740},34,2,GRAY);
       }else if(game.won){
            DrawTextEx(font,"YOU WON !",{570,740},34,2,GRAY);
        }else{
            DrawTextEx(font,"GAME OVER",{570,740},34,2,GRAY);
        }

       game.Draw();

       EndDrawing(); 
    }
    CloseWindow();
}