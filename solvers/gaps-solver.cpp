/*
 Solver for the "Gaps" puzzle in Something Is Off
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
typedef pair<int, pii> piii;
typedef vector<int> vi;
typedef vector<pii> vii;
const int INF = 0x3f3f3f3f;
const ll INFL = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;
const int MAX = 2e5 + 5;

const pii dir[] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, -1}, {-1, 1}, {-1, -1}, {1, 1} };
bool grid[10][10];
int dp[10][10][10];

inline int cntRow(int x) {
    int ans = 0;
    for (int i = 1; i <= 8; i++) {
        ans += grid[x][i];
    }
    return ans;
}

inline int cntCol(int x) {
    int ans = 0;
    for (int i = 1; i <= 8; i++) {
        ans += grid[i][x];
    }
    return ans;
}

inline bool valid(int i, int j) {
    if (i < 1 || i > 8 || j < 1 || j > 8) {
        return 0;
    }
    for (pii p : dir) {
        if (grid[i + p.f][j + p.s]) {
            return 0;
        }
    }
    return grid[i][j] != 1 && cntRow(i) < 2 && cntCol(j) < 2;
}

inline void place(int i, int j) {
    grid[i][j] = 1;
}

inline void del(int i, int j) {
    grid[i][j] = 0;
}

bool solve(int row) {
    
    if (row > 8) {
        for (int i = 1; i <= 8; i++) {
            if (cntRow(i) != 2 || cntCol(i) != 2) {
                return 0;
            }
        }
        int pos1 = 0, pos2 = 0;
        for (int i = 1; i <= 8; i++) {
            if (grid[i][2] && pos1 == 0) {
                pos1 = i;
            } else {
                pos2 = i;
            }
        }
        if (pos2 != pos1 + 2) {
            return 0;
        }
        for (int i = 1; i <= 8; i++) {
            for (int j = 1; j <= 8; j++) {
                printf("%d ", grid[i][j]);
            }
            printf("\n");
        }
        printf("\n");
        return 1;
    }
    
    if (row == 3) {
        for (int i = 1; i + 2 <= 8; i++) {
            if (valid(row, i) && valid(row, i + 2)) {
                place(row, i), place(row, i + 2);
                if (solve(row + 1)) {
                    return 1;
                }
                del(row, i), del(row, i + 2);
            }
        }
    } else {
        for (int i = 1; i <= 8; i++) {
            for (int j = i + 2; j <= 8; j++) {
                if (valid(row, i) && valid(row, j)) {
                    place(row, i), place(row, j);
                    if (solve(row + 1)) {
                        return 1;
                    }
                    del(row, i), del(row, j);
                }
            }
        }
    }
    return 0;
}

int main() {
    
    solve(1);
    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}
