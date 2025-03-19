#pragma once
#include <raylib.h>
#include <vector>
#include "block.hpp"
using namespace std;

class Obstacle{
    private:
    public:
        Vector2 position;
        vector<Block> blocks;
        static vector<vector<int>> grid;
        Obstacle(Vector2 position);
        void Draw();
};