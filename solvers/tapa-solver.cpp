/*
 Solver for the "Tapa" puzzle in Something Is Off
 (https://2019.galacticpuzzlehunt.com/puzzle/something-is-off)
 Input format:
 R C
 N
 r1 c1 n1 x11 x12 x13...
 r2 c2 n2 x21 x22 x23...
 ...
 where
 R = number of rows
 C = number of columns
 N = number of cells containing numbers
 ri, ci = row and column of cell i (where cell i is a number-containing cell)
 ni = number of numbers in cell i
 xi1, xi2, xi3... = numbers in cell i
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
const pii touch[] = { {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1} };

int N;
int R = 10, C = 10;
pii cells[MAX];
vi nums[MAX];
int numLoc[15][15];
char grid[15][15];
set<pii> vis;
int nBlacks;

inline void printGrid() {
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            printf("%c", grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


int dfs(int r, int c) {
    int ans = 1;
    for (auto p : dirs) {
        int r1 = r + p.f, c1 = c + p.s;
        if (r1 >= 1 && r1 <= R && c1 >= 1 && c1 <= C &&
            vis.find({r1, c1}) == vis.end() && grid[r1][c1] == '#') {
            vis.insert({r1, c1});
            ans += dfs(r1, c1);
        }
    }
    return ans;
}

inline bool place(int r, int c) {
    if (grid[r][c] != '#') {
        return 0;
    }
    grid[r][c] = ' ';
    nBlacks--;
    return 1;
}

inline void unplace(int r, int c) {
    grid[r][c] = '#';
    nBlacks++;
}

// check if currently filled squares conform to the specifications of cell n
inline bool checkNum(int n) {
    int r = cells[n].f, c = cells[n].s;
    vector<bool> line;
    vi blacks;
    for (int i = 0; i < 8; i++) {
        pii p = touch[i];
        line.pb(grid[r + p.f][c + p.s] == '#');
    }
    line.pb(0);
    int cnt = 0;
    for (int i = 1; i < line.size(); i++) {
        cnt += line[i - 1];
        if (!line[i] && line[i - 1]) {
            blacks.pb(cnt);
            cnt = 0;
        }
    }
    if (line[0] && line[line.size() - 2] && blacks.size() > 1) {
        blacks[0] += blacks[blacks.size() - 1];
        blacks.pop_back();
    }
    sort(blacks.begin(), blacks.end());
    if (blacks.size() != nums[n].size()) {
        return 0;
    }
    for (int i = 0; i < blacks.size(); i++) {
        if (blacks[i] != nums[n][i]) {
            return 0;
        }
    }
    return 1;
}

void solve(int r, int c) {
    
    //printGrid();
    
    if (c > C) {
        c = 1, r++;
    }
    
    int r0 = r - 1;
    int c0 = c - 1;
    if (c0 < 1) {
        c0 = C;
        r0--;
    }
    c0--;
    if (c0 < 1) {
        c0 = C;
        r0--;
    }
    
    if (r0 >= 1 && c0 >= 1) {
        // check no 2 by 2 square
        if (grid[r0][c0] == '#' && grid[r0][c0 + 1] == '#' && grid[r0 + 1][c0] == '#' && grid[r0 + 1][c0 + 1] == '#') {
            return;
        }
        // check validity of previous number (if there is one)
        if (numLoc[r0][c0] && !checkNum(numLoc[r0][c0])) {
            return;
        }
    }
    
    // check that blacks are contiguous
    int rb, cb;
    bool good = 0;
    for (int i = 1; i <= R && !good; i++) {
        for (int j = 1; j <= C && !good; j++) {
            if (grid[i][j] == '#') {
                rb = i, cb = j;
                good = 1;
            }
        }
    }
    vis.insert({rb, cb});
    int reach = dfs(rb, cb);
    vis.clear();
    if (reach != nBlacks) {
        return;
    }
    
    if (r > R) {
        // check the numbered cells
        for (int i = 1; i <= N; i++) {
            if (!checkNum(i)) {
                return;
            }
        }
        // check no 2 by 2
        for (int i = 1; i + 1 <= R; i++) {
            for (int j = 1; j + 1 <= C; j++) {
                if (grid[i][j] == '#' && grid[i + 1][j] == '#' && grid[i][j + 1] == '#' && grid[i + 1][j + 1] == '#') {
                    return;
                }
            }
        }
        printGrid();
        return;
    }
    
    // delete black square here
    if (place(r, c)) {
        solve(r, c + 1);
        unplace(r, c);
    }
    // leave it there
    solve(r, c + 1);
}

int main() {
    
    FILL(grid, ' ');
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            grid[i][j] = '#';
        }
    }
    
    scanf("%d", &N);
    int n, x;
    // Format: r c n x1 x2 x3...
    for (int i = 1; i <= N; i++) {
        scanf("%d%d", &cells[i].f, &cells[i].s);
        grid[cells[i].f][cells[i].s] = '~';
        scanf("%d", &n);
        while (n--) {
            scanf("%d", &x);
            nums[i].pb(x);
        }
        sort(nums[i].begin(), nums[i].end());
        numLoc[cells[i].f][cells[i].s] = i;
    }
    
    nBlacks = R * C - N;
    solve(1, 1);
    
    return 0;
}
