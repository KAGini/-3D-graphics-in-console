#include "io.h"

char GetChar() {
    initscr();
    cbreak();
    noecho();
    char a = tolower(getch());
    endwin();
    return a;
}

void MoveCaret(int up = 0, int down = 0, int left = 0, int right = 0) {
    printf("\x1b[%dA", up);
    printf("\x1b[%dC", down);
    printf("\x1b[%dD", left);
    printf("\x1b[%dB", right);
}

void Print(std::vector<std::vector<int>> &screen) {
    MoveCaret(screen.size() + 1, 0, screen[0].size() + 1);
    for (int i = 0; i < screen.size(); ++i) {
        for (int j = 0; j < screen[0].size(); ++j) {
            if (screen[i][j] == 1) {
                std::printf("#");
            } else {
                std::printf(" ");
            }
        }
        std::printf("\t%d\n", i);
    }
}

void GetPolygons(std::vector<Polygon> &p, std::string FileName) {
    std::ifstream fin(FileName);
    int q;
    fin >> q;
    p.resize(q);

    for (int i = 0; i < q; ++i) {
        int n;
        fin >> n;
        long double x, y;
        std::vector<Point> points(n);
        for (int j = 0; j < n; ++j) {
            fin >> x >> y;
            points[j] = {x, y};
        }
        p[i] = {n, points};
    }

    fin.close();
}