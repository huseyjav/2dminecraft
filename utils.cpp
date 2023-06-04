#include "utils.h"

std::ostream& operator << (std::ostream& os, vector2& a ){
    os << a.x << " " << a.y;
    return os;
}

//Bresenham's line algorithm
std::vector<vector2> bresenhamalgo(vector2 start, vector2 end) {
    std::vector<vector2> toret;
    int dx = abs(end.x - start.x);
    int dy = abs(end.y - start.y);
    
    int sx = (start.x < end.x) ? 1 : -1;
    int sy = (start.y < end.y) ? 1 : -1;
    
    int err = dx - dy;
    int currentX = start.x;
    int currentY = start.y;
    
    while (true) {
        vector2 toadd{currentX,currentY};
        //std::cout << "(" << currentX << ", " << currentY << ")" << std::endl;
        toret.push_back(toadd);
        if (currentX == end.x && currentY == end.y) {
            break;
        }
        
        int err2 = 2 * err;
        
        if (err2 > -dy) {
            err -= dy;
            currentX += sx;
        }
        
        if (err2 < dx) {
            err += dx;
            currentY += sy;
        }
    }
    //std::cout <<"a" << std::endl;
    return toret;
}
