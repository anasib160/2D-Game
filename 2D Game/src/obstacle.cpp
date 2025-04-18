#include "obstacle.hpp"

vector<vector<int>> Obstacle::grid  =  {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
};

Obstacle::Obstacle(Vector2 position)
{
    this->position = position;

    for(unsigned int row = 0; row < grid.size() ; row++){
        for(unsigned int col = 0; col < grid[0].size() ; col++){
            if(grid[row][col] == 1){
                float px=position.x + col* 3;
                float py=position.y +row * 3;
                Block block = Block({px,py});
                blocks.push_back(block);
            }
        }
    }
}

void Obstacle::Draw()
{
    for(auto& block: blocks){
        block.Draw();
    }
}
