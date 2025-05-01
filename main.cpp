#include <iostream>
#include <chrono>
#include "generationField.h"
#include "findPath.h"


int main(){ 
    GenerationField();
    int counter_bad_maze = 0;
    std::cout << "start generation maze"<< std::endl;
    while (findPathMultithreading(END_POSITION,START_POSITION).size() == 0) {
    	counter_bad_maze+=1;
        std::cout << "bad generation maze: " << counter_bad_maze << std::endl;
	clearField();
	GenerationField();
	std::cout << "new generation maze:" << std::endl;
	printField();
	}
    std::cout << "create Maze";
    std::vector path = findPath();
    printField(path);
    return 0;
}

