#pragma once

#include "utils.h"

void baseGenerationField(std::vector<point> Maze = {}){
    for (int x = 0; x != FIELD_SIZE; x++) {
        for (int y = 0; y != FIELD_SIZE; y++){
            point now_position = {x,y};
            if (Maze.size()){
                bool flag = false;
                for (point pos :Maze){
                    if (now_position == pos)
                        flag = true;
                }
                if (flag)
                    FIELD[y][x] = 0;
                else{
                    FIELD[y][x] = 1;
                }
            }
            if (x == 0 || x == FIELD_SIZE-1 || y == 0 || y == FIELD_SIZE-1)
                FIELD[y][x] = 1;
            if (now_position == START_POSITION || now_position == END_POSITION)
                FIELD[y][x] = 0;
        }
    }
}

bool cheakMaze(point now_position){
    for(int y = 0;y != FIELD_SIZE;y++)
        for(int x = 0;x != FIELD_SIZE;x++){
            point p = {x,y};
            if(!((x % 2 != 0  && y % 2 != 0) && (x < FIELD_SIZE-1 && y < FIELD_SIZE-1) && counterWallOnPosition(p)))
                return false;

        }
    return true;
}
void RandomGenerationField(){
    std::vector<point> Maze;
    for( int y = 0; y < FIELD_SIZE;y+=2){
        for( int x = 0; x != FIELD_SIZE;x++){
            FIELD[y][x] = 1;
        }
        int nrandom = getRandomInt(1,round(FIELD_SIZE/2));
        for( int n = 0; n != nrandom;n++){
            int xrandom = getRandomInt(1,FIELD_SIZE-1);
            FIELD[y][xrandom] = 0;
        }
    }

    for( int x = 0; x != FIELD_SIZE;x++){
        FIELD[START_POSITION.y][x] = 0;
        FIELD[END_POSITION.y][x] = 0;

    }   
    baseGenerationField(Maze);
}

bool cheakNearCocedi(point& p, std::vector<point> &vp){
	for (int i = 0;i!=4;i++){
		Move m = static_cast<Move>(i);
		for(point pinv: vp)
			if (checkPointInArr(p.checkDoMove(m,2),vp)) return true;
	};
	return false;
}


void GenerationField(){
	
	std::vector<point> cocedi;
	for(int y = 0;y != FIELD_SIZE;y++)
        	for(int x = 0;x != FIELD_SIZE;x++){
			if(x % 2 != 0  && y % 2 != 0)
			{
				FIELD[y][x] = 0 ;
				cocedi.push_back(point(x,y));
			}
            		else
                		FIELD[y][x] = 1;
	}
	point p = cocedi.back();
	std::vector<point> path;
	int c = 0;
	
		while(cheakNearCocedi(p,cocedi) || cocedi.size() > 0)
		{
			for(size_t i = 0;i!=cocedi.size();i++)
				if (p == cocedi[i]){
					cocedi.erase(cocedi.begin()+i);
					break;
				}
			std::vector<int> bad_int;
			std::vector<int> good_int;
		        for (int i = 0;i!=4;i++){
                		Move m = static_cast<Move>(i);
                		for(point pinv: cocedi)
					if (p.checkDoMove(m,2) == pinv)
				good_int.push_back(i);			
			}
			for(int i = 0;i!=4;i++)
			{
				if(count(good_int.begin(), good_int.end(), i) == 0)bad_int.push_back(i);
			}
			int seed = getRandomInt(0,3,bad_int);
			Move m = static_cast<Move>(seed);
			if (seed != -1){
				path.push_back(p);
				p.doMove(m);
				FIELD[p.y][p.x] = 0;
				p.doMove(m);
			}else{
				for(int i = path.size();i!=0;i--)
                        		if(cheakNearCocedi(path[i],cocedi))
                        		{
                                		p = path[i];
                                		break;
                        		}	
			}
		};
 		
baseGenerationField();

};
