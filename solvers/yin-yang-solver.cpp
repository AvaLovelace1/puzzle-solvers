/*
 Solver for the "Yin-Yang" puzzle in Something Is Off
 (https://2019.galacticpuzzlehunt.com/puzzle/something-is-off)
 Input format:
 R C
 N
 c11c12c13...
 c21c22c23...
 ...
 where
 R = number of rows
 C = number of columns
 cij = 'X' if the cell at row i and col j is black, 'O' if it is white, ' ' otherwise
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

const pii dirs[] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

int R = 10, C = 10;
char grid[15][15];
set<pii> vis;
pii firstW = {0, 0}, firstB = {0, 0};
int nWhites, nBlacks;

inline void printGrid() {
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            printf("%c", grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

inline bool isDone(int r, int c, int r0, int c0) {
    return r == r0 ? c < c0 : r < r0;
}

inline bool square(int r, int c) {
    char col = tolower(grid[r][c]);
    return tolower(grid[r + 1][c]) == col && tolower(grid[r][c + 1]) == col && tolower(grid[r + 1][c + 1]) == col;
}

inline bool place(int r, int c, char col) {
    if (tolower(grid[r - 1][c - 1]) == col && tolower(grid[r - 1][c]) == col && tolower(grid[r][c - 1]) == col) {
        return 0;
    }
    col == 'x' ? nBlacks++ : nWhites++;
    grid[r][c] = col;
    return 1;
}

inline void unplace(int r, int c) {
    if (tolower(grid[r][c]) == 'x') {
        nBlacks--;
    } else {
        nWhites--;
    }
    grid[r][c] = ' ';
}

int dfs(int r, int c, char col) {
    int ans = tolower(grid[r][c]) == col;
    for (auto p : dirs) {
        int r1 = r + p.f, c1 = c + p.s;
        if (r1 >= 1 && r1 <= R && c1 >= 1 && c1 <= C &&
            vis.find({r1, c1}) == vis.end() && (grid[r1][c1] == ' ' || tolower(grid[r1][c1]) == col)) {
            vis.insert({r1, c1});
            ans += dfs(r1, c1, col);
        }
    }
    return ans;
}

void solve(int r, int c) {
    
    //printGrid();
    
    if (c > C) {
        c = 1;
        r++;
    }
    
    // check connectivity
    vis.insert(firstB);
    if (dfs(firstB.f, firstB.s, 'x') != nBlacks) {
        vis.clear();
        return;
    }
    vis.clear();
    vis.insert(firstW);
    if (dfs(firstW.f, firstW.s, 'o') != nWhites) {
        vis.clear();
        return;
    }
    vis.clear();

    if (r > R) {
        printGrid();
        return;
    }
    
    if (grid[r][c] == 'X' || grid[r][c] == 'O') {
        if (!square(r - 1, c - 1)) {
            solve(r, c + 1);
        }
    } else {
        if (place(r, c, 'x')) {
            solve(r, c + 1);
            unplace(r, c);
        }
        if (place(r, c, 'o')) {
            solve(r, c + 1);
            unplace(r, c);
        }
    }
}

int main() {
    
    scanf("%d%d", &R, &C);
    FILL(grid, ' ');
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            scanf("%c", &grid[i][j]);
            nWhites += grid[i][j] == 'O';
            nBlacks += grid[i][j] == 'X';
            if (grid[i][j] == 'O' && firstW.f == 0) {
                firstW = {i, j};
            } else if (grid[i][j] == 'X' && firstB.f == 0) {
                firstB = {i, j};
            }
        }
        scanf("%*c");
    }
    
    solve(1, 1);
    
    return 0;
}
