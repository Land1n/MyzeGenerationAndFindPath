#pragma once

#include "utils.h"

#include <thread>
#include <mutex>

std::mutex path_mutex;
std::mutex bad_path_mutex;
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

bool isBadCrossroad(point &crossroad,std::vector<point>& bad_path,short way = 1){
	short nRoads = counterRoadOnPosition(crossroad);
	short bad_way = 0;
	for (int i = 0; i!=4;i++){
        	Move m = static_cast<Move>(i);
		for(point bpos: bad_path)
			if (crossroad.checkDoMove(m) == bpos)bad_way += 1;
	}
	if (bad_way == nRoads-way) return true;
	return false;
}

void addBadPoint(point &p,std::vector<point>& path,std::vector<point>& bad_path,point &start = START_POSITION)
{
	if (p != start){
		short bad_way = counterWallOnPosition(p);
		for(point bpos: bad_path)
                        for (int i = 0; i!=4;i++){
                                Move m = static_cast<Move>(i);
                                if(p.checkDoMove(m) == bpos)bad_way += 1;
			}
		if (bad_way == 3)
		{
			bad_path.push_back(p);
		}
	} else if(p ==start && isBadCrossroad(p,bad_path,0)){
		bad_path.push_back(p);
	}
}
 
std::vector<point> findRandomMemoryPath(std::vector<point>& bad_path,bool &finding,point &start = START_POSITION, point &end = END_POSITION,bool view_try_counter = false)
{
	std::vector<point> path;
	point position_now = start;
	while (position_now != end)
	{
		if (finding == false){
			path.clear();
			return path;
		}
                if (view_try_counter  && bad_path.size()%50 == 0){
                        std::cout << "bad path size: " << bad_path.size() << std::endl;
                        printField(path,bad_path);
                }

		std::vector<int> bad_move = checkOnWallNextStep(position_now);
//		bad_path_mutex.lock();
		for(point bpos: bad_path)
                	for (int i = 0; i!=4;i++){
                    		Move m = static_cast<Move>(i);
				if(start == bpos){
					finding = false;
//					bad_path_mutex.unlock();
					path.clear();
					printField(path,bad_path);
					return path;
				};
				if (position_now.checkDoMove(m) == bpos || checkPointInArr(position_now.checkDoMove(m),path))
                        		bad_move.push_back(i);
		}
//		bad_path_mutex.unlock();

		short seed = getRandomInt(0,3,bad_move); 
		if (seed == -1)
		{
			addBadPoint(position_now,path,bad_path,start);
			position_now = start;
                        path.clear();
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
//		bad_path_mutex.unlock();
	}
    	if (path.size() > 0)
       		path.push_back(position_now);
//	bad_path_mutex.unlock();
    	return path;
}

 

std::vector<point> findPathMultithreading(std::vector<point> &bad_path,bool&finding,point &start = START_POSITION, point &end = END_POSITION){
	std::vector<point> path;
	auto f1 = [&path,&bad_path,&start,&end,&finding]() {
//    		path_mutex.lock();
		path = findRandomMemoryPath(bad_path,finding,start,end,true); 
//		path_mutex.unlock();
	};
  // 	auto f2 = [&path,&bad_path,&start,&end,&finding]() {
//		path_mutex.lock();
    //            findRandomMemoryPath(bad_path,finding,start,end);
//		path_mutex.unlock();
       // };
        auto f3 = [&path,&bad_path,&start,&end,&finding]() {
//              path_mutex.lock();
		path = findRandomMemoryPath(bad_path,finding,end,start);
//              path_mutex.unlock();
        };
	std::thread t1(f1);
//	std::thread t2(f2);
	std::thread t2(f3);
    	t1.join();
    	t2.join();
	return path;
};
