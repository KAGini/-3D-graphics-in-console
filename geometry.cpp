#include "geometry.h"

Vector::Vector(Point B, Point A) {
    x = B.x - A.x;
    y = B.y - A.y;
}

void Vector::Rotate(double angle) {
    angle = PI * angle / 180;
    long double t = x;
    x = x * cos(angle) - y * sin(angle);
    y = t * sin(angle) + y * cos(angle);
}

Vector Vector::GetRotated(double angle) {
    Vector v({x, y});
    v.Rotate(angle);
    return v;
}

long double GetDotProduct(Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
}

long double GetCrossProduct(Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

long double GetAngle(Vector a, Vector b) {
    return 180 * atan2(GetCrossProduct(a, b), GetDotProduct(a, b)) / PI;
}

bool Line::IsBelong(Point A) const {
    long double t = A.x * a + A.y * b + c;
    return -eps < t && t < eps;
}

Line GetLine(Point A, Point B) {
    long double a = B.y - A.y;
    long double b = A.x - B.x;
    long double c = A.x * (A.y - B.y) + A.y * (B.x - A.x);
    return {a, b, c};
}

Point GetLinesIntersection(Line ln1, Line ln2) {
    const long double d1 = ln2.c * ln1.b - ln1.c * ln2.b;
    const long double d2 = ln1.c * ln2.a - ln2.c * ln1.a;
    const long double d = ln1.a * ln2.b - ln2.a * ln1.b;
    if (d == 0) {
        if (d1 == d2 && d1 == 0) {
            return {-INF, -INF};
        }
        return {INF, INF};
    }
    return {d1 / d, d2 / d};
}

long double GetDistance(Point A, Point B) {
    const long double x = A.x - B.x;
    const long double y = A.y - B.y;
    return sqrt(x * x + y * y);
}

bool Segment::IsBelong(Point C) const {
    if (!GetLine(A, B).IsBelong(C)) {
        return false;
    }
    if (std::min(A.x, B.x) <= C.x && C.x <= std::max(A.x, B.x)) {
        if (std::min(A.y, B.y) <= C.y && C.y <= std::max(A.y, B.y)) {
            return true;
        }
    }
    return false;
}

Ray::Ray(Point A, Vector v) {
    x0 = A.x;
    y0 = A.y;
    px = v.x;
    py = v.y;
}

bool Ray::IsBelong(Point A) const {
    if (px == 0) {
        return (A.x == x0 && (A.y - y0) / py > 0);
    }
    if (py == 0) {
        return (A.y == y0 && (A.x - x0) / px > 0);
    }
    long double t1 = (A.y - y0) / py;
    long double t2 = (A.x - x0) / px;
    return -eps < t1 - t2 && t1 - t2 < eps && t1 > -eps && t2 > -eps;
}

Point GetIntersection(Ray A, Segment AB) {
    Line a = GetLine({A.x0, A.y0}, {A.x0 + A.px, A.y0 + A.py});
    Line b = GetLine(AB.A, AB.B);
    Point I = GetLinesIntersection(a, b);
    if (I.x == -INF) {
        long double d1 = INF, d2 = INF;
        if (A.IsBelong(AB.A)) {
            d1 = GetDistance(AB.A, {A.x0, A.y0});
        }
        if (A.IsBelong(AB.B)) {
            d2 = GetDistance(AB.B, {A.x0, A.y0});
        }

        if (d1 == INF && d2 == INF) {
            return {INF, INF};
        }

        if (d1 > d2) {
            return AB.B;
        } 
        return AB.A;
    }
    if (I.x == INF) {
        return {INF, INF};
    }
    if (A.IsBelong(I) && AB.IsBelong(I)) {
        return I;
    }
    return {INF, INF};
}

long double GetClosestIntersectionDistance(std::vector<Polygon> &p, Ray r) {
    long double d = INF;
    for (auto pol : p) {
        for (int i = 0; i < pol.n; ++i) {
            Point I = GetIntersection(r, {pol.points[i], pol.points[(i + 1) % pol.n]});
            if (I.x != INF) {
                long double k = GetDistance(I, {r.x0, r.y0});
                d = std::min(d, k);
            }
        }
    }
    return d;
}
