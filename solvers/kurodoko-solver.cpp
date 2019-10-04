/*
 Solver for the "Kurodoko" puzzle in Something Is Off
 (https://2019.galacticpuzzlehunt.com/puzzle/something-is-off)
 Input format:
 R C
 N
 r1 c1 k1
 r2 c2 k2
 ...
 where
 R = number of rows
 C = number of columns
 N = number of cells containing numbers
 ri, ci = row and column of cell i (where cell i is a number-containing cell)
 ki = number in cell i
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

int N;
int R = 9, C = 9;
piii arr[MAX];
char grid[15][15];
set<pii> vis;
int nWhites;

inline int visible(int r, int c, int dir, int R, int C) {
    int k = 1;
    if (dir == 0) {
        while (r - k >= 1 && grid[r - k][c] != '#') {
            k++;
        }
    } else if (dir == 1) {
        while (c + k <= C && grid[r][c + k] != '#') {
            k++;
        }
    } else if (dir == 2) {
        while (r + k <= R && grid[r + k][c] != '#') {
            k++;
        }
    } else {
        while (c - k >= 1 && grid[r][c - k] != '#') {
            k++;
        }
    }
    return k - 1;
}

inline int visible(int r, int c, int R, int C) {
    int ans = 1;
    for (int i = 0; i < 4; i++) {
        ans += visible(r, c, i, R, C);
    }
    return ans;
}

int dfs(int r, int c) {
    int ans = 1;
    for (auto p : dirs) {
        int r1 = r + p.f, c1 = c + p.s;
        if (r1 >= 1 && r1 <= R && c1 >= 1 && c1 <= C
            && vis.find({r1, c1}) == vis.end() && grid[r1][c1] != '#') {
            vis.insert({r1, c1});
            ans += dfs(r1, c1);
        }
    }
    return ans;
}

inline bool place(int r, int c) {
    if (grid[r][c] != ' ') {
        return 0;
    }
    for (auto p : dirs) {
        if (grid[r + p.f][c + p.s] == '#') {
            return 0;
        }
    }
    grid[r][c] = '#';
    nWhites--;
    return 1;
}

inline void unplace(int r, int c) {
    grid[r][c] = ' ';
    nWhites++;
}

inline void printGrid() {
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            printf("%c", grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void solve(int r, int c, int rw, int cw) {

    //printGrid();
    
    if (c > C) {
        c = 1, r++;
    }
    
    // check that whites are contiguous
    vis.insert({rw, cw});
    int reach = dfs(rw, cw);
    vis.clear();
    if (reach != nWhites) {
        return;
    }
    
    if (r > R) {
        // check the numbered cells
        for (int i = 1; i <= N; i++) {
            if (visible(arr[i].f.f, arr[i].f.s, R, C) != arr[i].s) {
                return;
            }
        }
        printGrid();
        return;
    }
    
    // check numbered cells
    for (int i = 1; i <= N; i++) {
        if (visible(arr[i].f.f, arr[i].f.s, R, C) < arr[i].s) {
            return;
        }
        if (arr[i].f.f < r && visible(arr[i].f.f, arr[i].f.s, r - 1, C) > arr[i].s) {
            return;
        }
    }
    
    // place black square here
    if (place(r, c)) {
        int rw1 = rw, cw1 = cw;
        if (rw1 == r && cw1 == c) {
            cw1++;
            if (cw1 > C) {
                cw1 = 1, rw1++;
            }
        }
        solve(r, c + 1, rw1, cw1);
        unplace(r, c);
    }
    solve(r, c + 1, rw, cw);
}

int main() {
    
    FILL(grid, ' ');

    scanf("%d%d%d", &R, &C, &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d%d%d", &arr[i].f.f, &arr[i].f.s, &arr[i].s);
        grid[arr[i].f.f][arr[i].f.s] = '~';
    }
    
    nWhites = R * C;
    solve(1, 1, 1, 1);
    
    return 0;
}
