#include <iostream>
#include <chrono>
#include "generationField.h"
#include "findPath.h"
#include <thread>

int main(){ 
    GenerationField();
    int counter_bad_maze = 0;
    std::vector<point> bad_path;
    std::cout << "start generation maze"<< std::endl;
    bool finding = true;
    while (findPathMultithreading(bad_path,finding,END_POSITION,START_POSITION).size() == 0) {
    	bad_path.clear();
	finding = true;
	counter_bad_maze+=1;
        std::cout << "bad generation maze: " << counter_bad_maze << std::endl;
	clearField();
	GenerationField();
	std::cout << "new generation maze:" << std::endl;
	printField();
	}

    std::thread t2([&]()
    {
      while (true) 
     	{
		std::string w = "";
		std::cin >> w;
		if (w == "p"){
			std::vector<point> path;
			std::cout << "size bad path" << bad_path.size()<<std::endl;
			printField(path,bad_path);
		} 
		if (w == "c"){
			break;
		}
	} 
    });
    
    t2.join();
    std::cout << "create Maze";
    std::vector path = findRandomMemoryPath(bad_path,finding,END_POSITION,START_POSITION);
    printField(path);
    return 0;
}

