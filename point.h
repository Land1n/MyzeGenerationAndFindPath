#pragma once

enum class Move {Up,Right,Down,Left};

class point
{    
public: 
    int x;
    int y;
    point(int x = 0 , int y = 0) :  x(x) , y(y){}

    point checkDoMove(Move m,int step_size = 1){
        point new_p = {x,y};
        new_p.doMove(m,step_size);
        return new_p;
    }
    void doMove(Move m,int step_size = 1){
        switch (m)
        {
            case Move::Down: 
                y += step_size;
                break;
            case Move::Right:
                x += step_size;
                break;
            case Move::Up:
                y -= step_size;
                break;
            case Move::Left:
                x -= step_size;
                break;
        };
    }

    bool operator == (const point &p) {
        return ( x == p.x &&  y == p.y) == true;
    }

    bool operator != (const point &p) {
        return ( x != p.x || y != p.y) == true;
    }
};
std::ostream& operator << (std::ostream &os, point &p)
{
    return os << " ( " << p.x << ", " << p.y << " ) ";
};
