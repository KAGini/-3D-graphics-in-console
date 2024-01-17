#ifndef CONSOLE3D_GEOMETRY_H
#define CONSOLE3D_GEOMETRY_H

#include "vector"
#include "cmath"

const long double PI = acos(-1);
constexpr long double eps = 1e-5;
constexpr long double INF = 1e9;


struct Point {
    long double x, y;
};

struct Polygon {
    int n;
    std::vector<Point> points;
};

struct Vector {
    Vector(Point B, Point A = {0, 0});

    long double x, y;

    void Rotate(double angle);

    Vector GetRotated(double angle);
};

long double GetDotProduct(Vector a, Vector b);

long double GetCrossProduct(Vector a, Vector b);

long double GetAngle(Vector a, Vector b);

struct Line {
    long double a, b, c;

    bool IsBelong(Point A) const;
};

Line GetLine(Point A, Point B);

Point GetLinesIntersection(Line ln1, Line ln2);

long double GetDistance(Point A, Point B);

struct Segment {
    Point A, B;

    bool IsBelong(Point C) const;
};

struct Ray {
    Ray(Point A, Vector v);
    long double x0, y0;
    long double px, py;

    bool IsBelong(Point A) const;
};

Point GetIntersection(Ray A, Segment AB);

long double GetClosestIntersectionDistance(std::vector<Polygon> &p, Ray r);

#endif //CONSOLE3D_GEOMETRY_H
