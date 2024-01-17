#ifndef CONSOLE3D_IO_H
#define CONSOLE3D_IO_H

#include "iostream"
#include "fstream"
#include "ncurses.h"
#include "geometry.h"

char GetChar();

void MoveCaret(int up, int down, int left, int right);

void Print(std::vector<std::vector<int>> &screen);

void GetPolygons(std::vector<Polygon> &p, std::string FileName);

#endif //CONSOLE3D_IO_H
