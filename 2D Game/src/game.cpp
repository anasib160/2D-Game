#include "game.hpp"
#include <iostream>
using namespace std;

Game::Game(){
    obstacles=CreateObstacle();
    aliens=CreateAlien();
    aliensdire=1;
    lastspawn = 0.0;
    spawnInter = GetRandomValue(10,20);
    life = 3;
    run = true ;
    score = 0;
    HS = 0;
    won = false;
}

Game::~Game()
{
    Alien::UnloadAliens();
}
void Game::Draw(){
    spaceship.Draw();
    Mystery.Draw();

    for(auto& laser: spaceship.lasers){
        laser.Draw();
    }
    for(auto& obstacle: obstacles){
        obstacle.Draw();
    }
    for(auto& aliens: aliens){
        aliens.Draw();
    }
    for(auto& laser: alienLasers){
        laser.Draw();
    }
}
void Game::Update()
{
    if(run && !won){
        double currentTime = GetTime();
        if(currentTime - lastspawn > spawnInter) {
            Mystery.Spawn();
            lastspawn = GetTime();
            spawnInter = GetRandomValue(10, 20);
        }

        
        for(auto& laser: spaceship.lasers){
            laser.Update();
        }
        MoveAliens();

        ALiensshoot();

        for(auto& laser: alienLasers){
            laser.Update();
        }

        Mystery.Update();
        
        Life();
        highscore();

        DeleteInactiveLasers();
        CHeckForHit();
    }

}
void Game::HandleInput()
{
    if(run && !won){
        if(IsKeyDown(KEY_LEFT)){
            spaceship.MoveLeft();
        }else if(IsKeyDown(KEY_RIGHT)){
            spaceship.MoveRight();
        }else if(IsKeyDown(KEY_SPACE)){
            spaceship.FireLaser();
        }
    }else{
        if(IsKeyDown(KEY_ENTER)){
            obstacles=CreateObstacle();
            aliens=CreateAlien();
            aliensdire=1;
            lastspawn = 0.0;
            spawnInter = GetRandomValue(10,20);
            life = 3;
            score = 0;
            spaceship.reset();
            won = false;
            run = true ;
        }
    }
}

vector<Obstacle> Game::CreateObstacle(){
    int obw = Obstacle::grid[0].size() * 3 ;
    float gap = (GetScreenWidth() - (obw * 4))/5;

    for(int i = 0 ; i<4; i++){ 
        float ofx = (i + 1) * gap + i * obw;
        obstacles.push_back( Obstacle({ ofx , float(GetScreenHeight()-200) }) );
    }
    return obstacles  ;
}

vector<Alien> Game::CreateAlien()
{
    vector<Alien> aliens;
    for(int row = 0 ; row < 5 ; row++ ){
        for(int col = 0 ; col < 11 ; col++ ){
            float x = 75 + col * 55;
            float y = 150 + row * 55;
            if(row<2){
                aliens.push_back(Alien(1, {x,y}));
            }else if(row<4){
                aliens.push_back(Alien(2, {x,y}));
            }else{
                aliens.push_back(Alien(3, {x,y}));
            }
        }
    }
    return aliens;
}

void Game::DeleteInactiveLasers()
{
    for(auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();){
        if(!it -> active){
            it = spaceship.lasers.erase(it);
        }else{
            ++it;
        }
    }
    for(auto it = alienLasers.begin(); it != alienLasers.end();){
        if(!it -> active){
            it = alienLasers.erase(it);
        }else{
            ++it;
        }
    }
}

void Game::MoveAliens()
{
    for(auto& alien: aliens) {
        if(alien.position.x + alien.image[alien.type - 1].width > GetScreenWidth()) {
            aliensdire = -1;
            MoveDownAliens(4);
        }
        if(alien.position.x < 5) {
            aliensdire = 1;
            MoveDownAliens(4);
        }

        alien.Update(aliensdire);
    }
}

void Game::MoveDownAliens(int distance)
{
    for(auto& alien:aliens){
        alien.position.y+=distance;
    }
}

void Game::ALiensshoot()
{
    int random = GetRandomValue(0,aliens.size()-1);
    Alien& alien= aliens[random];
    if(GetTime()-current > 0.35){
        alienLasers.push_back(Laser({alien.position.x + alien.image[alien.type -1].width/2, 
                                    alien.position.y + alien.image[alien.type - 1].height}, 6));
        current = GetTime();
    }
}

void Game::CHeckForHit()
{
    //spaceship hit aliens
    for(auto& laser : spaceship.lasers){
        auto it = aliens.begin();
        while(it != aliens.end()){
            if(CheckCollisionRecs(it->getRect(),laser.GetREct())){
                it = aliens.erase(it);
                laser.active = false;
                if(it->type == 1){
                    score += 100;
                }else if(it->type == 2){
                    score += 200;
                }else if(it->type == 3){
                    score += 300;
                }
                if(aliens.empty()){
                    won = true;
                }
            }else{
                it++;
            }
        }
    }
    //aliens hit SPACSHIP
    for(auto& laser: alienLasers){
        auto it = alienLasers.begin();
        while(it != alienLasers.end()){
            if(CheckCollisionRecs(it->GetREct(),spaceship.getRect())){
                it = alienLasers.erase(it);
                laser.active = false;
                life--;
                if(life == 0){
                    GameOver();
                }
            }else{
                it++;
            }
        }
    }
        //aliens hit SPACSHIP
        for(auto& laser: alienLasers){
            auto it = alienLasers.begin();
            while(it != alienLasers.end()){
                if(CheckCollisionRecs(it->GetREct(),spaceship.getRect())){
                    it = alienLasers.erase(it);
                    laser.active = false;
                    cout<<"the spaceship have been hit"<<endl;
                }else{
                    it++;
                }
            }
        }
        //SPACSHIP hit mysterycpacdship
        for(auto& laser : spaceship.lasers){
            auto it = spaceship.lasers.begin();
            while(it != spaceship.lasers.end()){
                if(CheckCollisionRecs(it->GetREct(),Mystery.getRect())){
                    it = spaceship.lasers.erase(it);
                    laser.active = false;
                    Mystery.alive = false;
                    score+=500;
                }else{
                    it++;
                }
            }
        }
        //SPACSHIP hit obstacles
        for(auto& laser : spaceship.lasers){
            for(auto& obstacle: obstacles){
                auto it = obstacle.blocks.begin();
                while(it != obstacle.blocks.end()){
                    if(CheckCollisionRecs(it->getRect(),laser.GetREct())){
                        it = obstacle.blocks.erase(it);
                        laser.active = false;
                    }else{
                        it++;
                    }
                }
            }
        }

        //alien hits obstacles
        for(auto& laser: alienLasers){
            for(auto& obstacle: obstacles){
                auto it = obstacle.blocks.begin();
                while(it != obstacle.blocks.end()){
                    if(CheckCollisionRecs(it->getRect(),laser.GetREct())){
                        it = obstacle.blocks.erase(it);
                        laser.active = false;
                    }else{
                        it++;
                    }
                }
            }
        }
        //alien Collision with obstacle
        for(auto& aliens: aliens){
            for(auto& obstacle: obstacles){
                auto it = obstacle.blocks.begin();
                while(it != obstacle.blocks.end()){
                    if(CheckCollisionRecs(it->getRect(),aliens.getRect())){
                        it = obstacle.blocks.erase(it);
                    }else{
                        it++;
                    }
                }
            }
        }
        for(auto& aliens: aliens){
            if(CheckCollisionRecs(aliens.getRect(),spaceship.getRect())){
                cout << "GAME OVER" << endl ;
            }
        }
}

void Game::GameOver(){
    run = false;
}

void Game::Life()
{
    for(int i = 0 ; i<life ; i++){
        DrawTexture(spaceship.image,  40 + (i*50),750,WHITE);
    }

}

void Game::highscore()
{
    if(HS<score){
        HS=score;
    }
}