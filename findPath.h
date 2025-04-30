#pragma once

#include "utils.h"

std::vector<int> checkOnWallNextStep(point position_now){
    std::vector<int> bad_move;
    for (int i = 0; i != 4; i++){
        Move m = static_cast<Move>(i);
        if (getFieldOnPosition(position_now.checkDoMove(m)))
            bad_move.push_back(i);
    }
    return bad_move;
}

bool checkIsFullPath(std::vector<point> path){
    for (size_t i = 0;i!=path.size()-1;i++){
        if ((abs(path[i].x - path[i+1].x) + abs(path[i].y - path[i+1].y)) > 1) return false;
    }
    return true;
}

std::vector<point> findRandomPath(point &start = START_POSITION,point &end = END_POSITION,std::vector<point> bad_path = {}){
    std::vector<point> path;
    std::vector<point> crossroads;
    point position_now = start;
    int bad_last_crossroad = 0;
    while (position_now != end)
    {   
        std::vector<int> bad_move = checkOnWallNextStep(position_now);
        std::cout << position_now;
	if (counterRoadOnPosition(position_now) > 2 && checkPointInArr(position_now,crossroads) == 0) 
                crossroads.push_back(position_now);
                
            for(point bpos: bad_path)
                for (int i = 0; i!=4;i++){
                    Move m = static_cast<Move>(i);
                    if (position_now.checkDoMove(m) == bpos)
                        bad_move.push_back(i);
                }
        for (int i = 0; i != 4; i++){
            Move m = static_cast<Move>(i);
            if (checkPointInArr(position_now.checkDoMove(m),path)) 
                bad_move.push_back(i);
        }
        int seed = getRandomInt(0,3,bad_move);

        if (seed == -1){
	    bad_last_crossroad += 1;
            position_now = crossroads.back();
            while (path.back() != crossroads.back())
                path.pop_back();
            
	    if (bad_last_crossroad > 10) {
	    	crossroads.pop_back();
	
           
		while (path.back() != crossroads.back())
                	path.pop_back();
		position_now = crossroads.back();
	    }
            bad_move.clear();
            continue;
        }
        else if (seed != -1) {
            path.push_back(position_now);
            Move m = static_cast<Move>(seed);
            position_now.doMove(m);
        }

        if (DEBUG){
            std::system("cls");
            printField(path,bad_path);
        }
    }
    if (path.size() > 0)
        path.push_back(position_now);

    return path;
}
std::vector<point> cleanPath(std::vector<point> path){
    std::vector<point> temp_path;
    std::vector<point> clean_path;
    std::vector<int> temp_position;
    for (size_t i = 0;i != path.size();i++){
        if (!count(temp_path.begin(), temp_path.end(), path[i])){
            temp_path.push_back(path[i]);
        } else {
            temp_position.push_back(i);
        }
    }
    temp_path.clear();
    std::reverse(temp_position.begin(),temp_position.end());
    for (int pos : temp_position){
        auto begin = path.cbegin();
        path.erase(begin+pos-1,begin+pos);
    }
    for (size_t i = 0;i != path.size();i++)
        if (!count(clean_path.begin(), clean_path.end(), path[i]))
            clean_path.push_back(path[i]);

    return clean_path;
}


std::vector<point> findBadPath() {
    std::vector<point> bad_point;
    std::vector<point> crossroad;
   // std::vector<point> temp_bad_path;
    for (int x = 1; x != FIELD_SIZE-1; x++){
        for (int y = 1; y != FIELD_SIZE-1; y++){
            point position_now = {x,y};
            if (counterWallOnPosition(position_now) == 3 && getFieldOnPosition(position_now) == 0)
                bad_point.push_back(position_now);
            if (counterRoadOnPosition(position_now) > 2 && getFieldOnPosition(position_now) == 0)
                crossroad.push_back(position_now);
	}
  
    }
    for (point pos: bad_point){
	std::vector<point> temp_bad_path = findRandomPath(pos);
	point near_cr = crossroad[0];
	int c = 0;
	for (point cr: crossroad)
		if ((abs(pos.x - cr.x) + abs(pos.y - cr.y)) < (abs(pos.x - near_cr.x) + abs(pos.y - near_cr.y))) near_cr = cr;
//	std::cout << pos << near_cr;
		 while (pos != near_cr && counterRoadOnPosition(pos) !=  3)
    		{
			std::vector<int> bad_way = checkOnWallNextStep(pos);
			//for (int i = 0;i != 4; i++){
			//	Move m = static_cast<Move>(i);
			//	if (checkPointInArr(pos.checkDoMove(m),temp_bad_path))bad_way.push_back(i);
			//};
			int way = getRandomInt(0,3,bad_way);
			if (c == 100) break;
			if (way == -1) {
			//	while (temp_bad_path.size() != 1){
			//		temp_bad_path.pop_back();
			//	}	
			c += 1;
			continue;
			//w	pos = temp_bad_path.back(); 
			}
			else{
				Move m = static_cast<Move>(way);
                        	temp_bad_path.push_back(pos);
                        	pos.doMove(m);
			}
		};
		 bad_point.insert(bad_point.end(),temp_bad_path.begin(),temp_bad_path.end());
    }
    return bad_point;
}

std::vector<point> findRandomMemoryPath(point &start = START_POSITION, point &end = END_POSITION)
{
	std::vector<point> bad_path;

	std::vector<point> path;
	point position_now = start;
	point last_near_crossroad = start;
	
	int bad_memory = 0;
	int real_not_can = 0;	
	while (position_now != end)
	{

		std::vector<int> bad_move = checkOnWallNextStep(position_now);
           	for(point bpos: bad_path)
                	for (int i = 0; i!=4;i++){
                    		Move m = static_cast<Move>(i);
				if(start == bpos){
					
					path.clear();
					printField(path,bad_path);
					return path;
				};
				if (position_now.checkDoMove(m) == bpos || checkPointInArr(position_now.checkDoMove(m),path))
                        		bad_move.push_back(i);
                
			}
		if (counterRoadOnPosition(position_now) > 2 && (abs(position_now.x - end.x) + abs(position_now.y - end.y)) <(abs(last_near_crossroad.x - end.x) + abs(last_near_crossroad.y - end.y))) last_near_crossroad = position_now;
        	int seed = getRandomInt(0,3,bad_move);	
		if (seed == -1)
		{
			
			if (counterWallOnPosition(position_now) == 3&& position_now!=start)bad_path.push_back(position_now);
			for(point bpos: bad_path)
			 for (int i = 0; i!=4;i++){
                                Move m = static_cast<Move>(i);
				if (position_now.checkDoMove(m) == bpos && counterRoadOnPosition(position_now) < 3)
					bad_path.push_back(position_now);
			}
			if (counterRoadOnPosition(position_now) == 3) {
				int c = 0;
				for(point bpos: bad_path)
			       	for (int i = 0; i!=4;i++){
					Move m = static_cast<Move>(i);
                                		if (position_now.checkDoMove(m) == bpos)c+=1;
					}
				if (c == 2)
					bad_path.push_back(position_now);
			}
			position_now = start;
                        path.clear();
			//			while (path.back() != last_near_crossroad)
//			{
//				path.pop_back();
//				bad_path.push_back(path.back());
//			}
//			position_now = last_near_crossroad;
//			bad_memory+=1;
//			real_not_can+=1;
//			
//			if (bad_memory == FIELD_SIZE*10){
//				bad_memory = 0;
//				bad_path.clear();
//				
//				last_near_crossroad = start;
//			}
//			if (real_not_can == FIELD_SIZE*FIELD_SIZE*10){
//				//std::vector<point> not_can;
//				return path;
//			}
		}
        	else if (seed != -1) {
            		path.push_back(position_now);
            		Move m = static_cast<Move>(seed);
            		position_now.doMove(m);
        	}
	      if (DEBUG){
        	    //std::system("cls");
        	    printField(path,bad_path);
        	}
	}
    	if (path.size() > 0)
       		path.push_back(position_now);

    	return path;
}
std::vector<point> minRandomMemoryPath(int niterations = 1000000,point &start = START_POSITION,point &end = END_POSITION){
    std::vector<point> min_path = findRandomMemoryPath(start,end);

        for(int i = 0; i != niterations; i++){
                std::vector<point> random_path = findRandomMemoryPath(start,end);
                if (min_path.size() > random_path.size() && random_path.size() != 0 )min_path = random_path;
        }

    return min_path;
}
std::vector<point> findPath(int niterations = 10000, point &start = START_POSITION, point &end = END_POSITION){

    std::vector<point> min_path = minRandomMemoryPath(1,start,end);
    std::vector<point> clean_path = cleanPath(min_path);
    
    return clean_path;
}

