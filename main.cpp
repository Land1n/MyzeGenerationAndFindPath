#include <iostream>
#include <chrono>
#include <ctime>
#include <fstream>
#include "generationField.h"
#include "findPath.h"
//#include "constant.h"

int main(){ 
    GenerationField();
    while (findPath(1,END_POSITION,START_POSITION).size() == 0) {
    	clearField();
	GenerationField();
    }
    std::cout << "create Maze";
    std::vector path = findPath();
    printField(path);
    return 0;
}

