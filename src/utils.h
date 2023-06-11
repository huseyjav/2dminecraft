#pragma once
#include <vector>
#include <iostream>
struct vector2{
    int x,y;
};

std::ostream& operator << (std::ostream& os, vector2& a );

//Bresenham's line algorithm
std::vector<vector2> bresenhamalgo(vector2 start, vector2 end);


