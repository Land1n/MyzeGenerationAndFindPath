#pragma once

#include "point.h"

const bool DEBUG = false;

const int FIELD_SIZE = 31;

int FIELD[FIELD_SIZE][FIELD_SIZE];

point START_POSITION = {1,1};
point END_POSITION = {FIELD_SIZE-2,FIELD_SIZE-2};
