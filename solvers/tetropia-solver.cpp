/*
 Solver for the "Tetropia" puzzle in Something Is Off
 (https://2019.galacticpuzzlehunt.com/puzzle/something-is-off)
 */

#include <bits/stdc++.h>

using namespace std;

#define f first
#define s second
#define pb push_back
#define FILL(a, b) memset(a, b, sizeof(a))

typedef long long int ll;
typedef pair<int, int> pii;
typedef pair<pii, int> piii;
typedef vector<int> vi;
typedef vector<pii> vii;
const int INF = 0x3f3f3f3f;
const ll INFL = 0x3f3f3f3f3f3f3f3fLL;
const int MOD = 1e9 + 7;
const int MAX = 2e5 + 5;

// L, S, I, O, T
const vii tetro[] = {
    { {0, 0}, {1, 0}, {2, 0}, {2, 1} },
    { {0, 0}, {1, 0}, {1, 1}, {2, 1} },
    { {0, 0}, {0, 1}, {0, 2}, {0, 3} },
    { {0, 0}, {0, 1}, {1, 1}, {1, 0} },
    { {0, 0}, {0, 1}, {0, 2}, {1, 1} }
};
const int rots[] = {4, 2, 2, 1, 4}; // # of valid rotations
const int refs[] = {2, 2, 1, 1, 1}; // # of valid reflections

int N = 4;
char grid[10][10];
pii cells[50];
vi cDirs[50];

inline int closest(int r, int c, int dir) {
    int k = 1;
    if (dir == 0) {
        while (r - k >= 1 && grid[r - k][c] != '#') {
            k++;
        }
        if (r - k < 1) {
            k = INF;
        }
    } else if (dir == 1) {
        while (c + k <= 7 && grid[r][c + k] != '#') {
            k++;
        }
        if (c + k > 7) {
            k = INF;
        }
    } else if (dir == 2) {
        while (r + k <= 7 && grid[r + k][c] != '#') {
            k++;
        }
        if (r + k > 7) {
            k = INF;
        }
    } else {
        while (c - k >= 1 && grid[r][c - k] != '#') {
            k++;
        }
        if (c - k < 1) {
            k = INF;
        }
    }
    return k;
}

inline bool valid(int n) {
    pii vals[4] = {};
    for (int i = 0; i < 4; i++) {
        vals[i] = {closest(cells[n].f, cells[n].s, i), i};
    }
    sort(vals, vals + 4);
    for (int i = 0; i < cDirs[n].size(); i++) {
        if (vals[i].s != cDirs[n][i] || (i > 0 && vals[i].f != vals[i - 1].f)) {
            return 0;
        }
    }
    if (cDirs[n].size() != 4 && vals[cDirs[n].size()].f <= vals[0].f) {
        return 0;
    }
    return 1;
}

inline void normalize(vii &t) {
    pii minElem = {0, 0};
    for (auto &p : t) {
        minElem.f = min(minElem.f, p.f);
        minElem.s = min(minElem.s, p.s);
    }
    for (auto &p : t) {
        p.f -= minElem.f, p.s -= minElem.s;
    }
}

inline void rotTetro(vii &t) {
    for (auto &p : t) {
        swap(p.f, p.s);
        p.s = -p.s;
    }
    normalize(t);
}

inline void refTetro(vii &t) {
    for (auto &p : t) {
        swap(p.f, p.s);
    }
    normalize(t);
}

inline bool place(vii &t, int r, int c) {
    // check that tetromino can be placed
    for (auto p : t) {
        if (r + p.f > 7 || c + p.s > 7) {
            return 0;
        }
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i == 0 && j == 0) {
                    if (grid[r + p.f + i][c + p.s + j] != ' ') {
                        return 0;
                    }
                } else if (grid[r + p.f + i][c + p.s + j] == '#') {
                    return 0;
                }
            }
        }
    }
    for (auto p : t) {
        grid[r + p.f][c + p.s] = '#';
    }
    return 1;
}

inline void unplace(vii &t, int r, int c) {
    for (auto p : t) {
        grid[r + p.f][c + p.s] = ' ';
    }
}

void solve(int n) {
    if (n >= 5) {
        for (int i = 0; i < N; i++) {
            if (!valid(i)) {
                return;
            }
        }
        for (int i = 1; i <= 7; i++) {
            for (int j = 1; j <= 7; j++) {
                printf("%c", grid[i][j]);
            }
            printf("\n");
        }
        printf("\n");
        return;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 4; j++) {
            if (find(cDirs[i].begin(), cDirs[i].end(), j) == cDirs[i].end()
                && closest(cells[i].f, cells[i].s, j) == 1) {
                return;
            }
        }
    }
    vii t = tetro[n];
    for (int ref = 0; ref < refs[n]; ref++) {
        for (int rot = 0; rot < rots[n]; rot++) {
            for (int i = 1; i <= 7; i++) {
                for (int j = 1; j <= 7; j++) {
                    if (place(t, i, j)) {
                        solve(n + 1);
                        unplace(t, i, j);
                    }
                }
            }
            rotTetro(t);
        }
        refTetro(t);
    }
}

int main() {
    
    FILL(grid, ' ');
    
    cells[0] = {1, 3};
    cells[1] = {2, 5};
    cells[2] = {5, 1};
    cells[3] = {5, 7};
    cDirs[0].pb(2);
    cDirs[0].pb(3);
    cDirs[1].pb(2);
    cDirs[1].pb(3);
    cDirs[2].pb(0);
    cDirs[3].pb(0);
    cDirs[3].pb(2);
    
    for (int i = 0; i < N; i++) {
        grid[cells[i].f][cells[i].s] = '~';
        sort(cDirs[i].begin(), cDirs[i].end());
    }
    
    solve(0);
    
    return 0;
}
