#pragma once

#include <random> 
#include <algorithm>
#include <vector>

#include "constant.h"

bool checkCanDoMove(point pos){
    return ((0<=pos.x && pos.x <=FIELD_SIZE) && (0<=pos.y && pos.y <=FIELD_SIZE)) == true;
}

bool checkPointInArr(point p,std::vector<point> &arr_p){
    return count(arr_p.begin(), arr_p.end(), p)>0;
}

int getRandomInt(int start,int end,std::vector<int> bad_int = {}){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(start, end);
    int random_int = dis(gen);
    int c = 0;
    while (count(bad_int.begin(), bad_int.end(), random_int) > 0)
    {
        random_int = dis(gen);
        c+=1;
        if(c == 10) return -1;
    }
    return random_int;
}

void printField(){
    std::cout << "\n";
    for (int x = 0; x != FIELD_SIZE; x++){
        for (int y = 0; y != FIELD_SIZE; y++) {
		if (FIELD[x][y] == 1)
    		std::cout << "▮";
		else std::cout<<" ";
        } 
        std::cout << "\n";
    }
    std::cout << "\n";

}

void printField(std::vector<point> &path,std::vector<point> bad_path = {}){
    std::cout << "\n" << "\n";
    for (int x = 0; x != FIELD_SIZE; x++){
        for (int y = 0; y != FIELD_SIZE; y++) {
		std::string str = " ";
	    if (FIELD[x][y] == 1)
                str =  "▮";
            for(point pos: path){
                if (pos.x == y && pos.y == x)
                	str = "▯";
            }
            for (point pos: bad_path){
                if (pos.x == y && pos.y == x)
                str = "╳";
            }
	    std::cout << str;
	}
        std::cout << "\n";
    }
    std::cout << "\n" << "\n";
    }


void printPath(std::vector<point> &path){
    std::cout << "[ ";
    for (auto pos:path){
        std::cout << "(" << pos.x << "," << pos.y << "),";
        }
    std::cout << " ]" << std::endl;
    std::cout << "path size: "<< path.size() << std::endl;
}
void clearField(){
	for (int x = 0; x != FIELD_SIZE; x++)
        	for (int y = 0; y != FIELD_SIZE; y++) 
			FIELD[x][y] == 0;
}


int getFieldOnPosition(point p){
    return FIELD[p.y][p.x];
}

int counterWallOnPosition(point position_now){
    int counter_wall_on_position = 0;
    for (int i = 0; i != 4; i++){
        Move m = static_cast<Move>(i);
        if (getFieldOnPosition(position_now.checkDoMove(m))) counter_wall_on_position +=1;
    }
    return counter_wall_on_position;
}

int counterRoadOnPosition(point position_now){
    int counter_wall_on_road = 0;
    for (int i = 0; i != 4; i++){
        Move m = static_cast<Move>(i);
        if (getFieldOnPosition(position_now.checkDoMove(m)) == 0) counter_wall_on_road +=1;
    }
    return counter_wall_on_road;
}
