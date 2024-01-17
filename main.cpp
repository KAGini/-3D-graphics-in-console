#include "io.h"
#include "geometry.h"


using namespace std;

const double D = 1;
const int ScreenWidth = 150;
const int ScreenHeight = 60;
const double ViewAngle = 140;
const string FileName = "polygons.txt";

class Camera {
public:
    Point position;
    Vector view;

    void Move(bool type) {
        Vector f = view.GetRotated(-ViewAngle);
        long double dx = (f.x + view.x) / 2;
        long double dy = (f.y + view.y) / 2;
        if (type) {
            position.x += dx;
            position.y += dy;
        } else {
            position.x -= dx;
            position.y -= dy;
        }
    }
};

void Update(vector<vector<int>> &screen, vector<Polygon> &polygons, Camera c) {
    screen.assign(ScreenHeight, vector<int> (ScreenWidth));
    Vector v = c.view;
    for (int i = 0; i < ScreenWidth; ++i) {
        long double p = GetClosestIntersectionDistance(polygons, Ray(c.position, v));
        v.Rotate(-ViewAngle / ScreenWidth);
        if (p == INF) {
            continue;
        }
        if (p < D + eps) {
            for (int j = 0; j < ScreenHeight; ++j) {
                screen[j][i] = 1;
            }
            continue;
        }
        for (int j = int(ScreenHeight * (1 - D / p) / 2 + 0.5); j < int(ScreenHeight * (1 + D / p) / 2 + 0.5); ++j) {
            screen[j][i] = 1;
        }
    }
}

int main() {
    vector<Polygon> polygons;
    vector<vector<int>> screen(ScreenHeight, vector<int> (ScreenWidth));
    GetPolygons(polygons, FileName);
    cout << "\n\n";

    Camera pl{{0, 0}, Vector({0, 0.5})};
    Update(screen, polygons, pl);
    Print(screen);

    bool NeedToUpdate;

    while (true) {

        char t = GetChar();

        NeedToUpdate = true;

        if (t == 'l') {
            printf("\n");
            break;
        } else if (t == 'a') {
            pl.view.Rotate(ViewAngle / ScreenWidth * 10);
        } else if (t == 'd') {
            pl.view.Rotate(-ViewAngle / ScreenWidth * 10);
        } else if (t == 'w') {
            pl.Move(true);
        } else if (t == 's') {
            pl.Move(false);
        } else NeedToUpdate = false;

        if (NeedToUpdate) {
            Update(screen, polygons, pl);
            Print(screen);
            printf("x:%F\ty:%F\tangle:%F\n", double(pl.position.x), double(pl.position.y), double(GetAngle(Vector({1, 0}), pl.view)));
        }
    }
}