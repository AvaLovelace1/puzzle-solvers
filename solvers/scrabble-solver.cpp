/*
 Solver for the "Scrabble" puzzle in Something Is Off
 (https://2019.galacticpuzzlehunt.com/puzzle/something-is-off)
 Not actually a solver for the Scrabble game.
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

string strs[] = {"", "aadb", "abac", "acbc", "dccc", "adbcb", "bdaca",
    "cabcd", "ccbad", "ababca", "cbbaca", "ccbabc", "cdabaa"};

inline bool comp(string a, string b) {
    if (a.length() == b.length()) {
        return a < b;
    }
    return a.length() > b.length();
}

int N = 12;
stack<char> grid[10][10];

inline bool place(int n, int r, int c, bool dir) {
    if (dir == 0) {
        if (r < 1 || r > 6 || c < 0 || c + strs[n].length() - 1 > 7) {
            return 0;
        }
        for (int i = 0; i < strs[n].length(); i++) {
            if (!grid[r][c + i].empty() && grid[r][c + i].top() != strs[n][i]) {
                return 0;
            }
        }
        for (int i = 0; i < strs[n].length(); i++) {
            grid[r][c + i].push(strs[n][i]);
        }
        return 1;
    } else {
        if (c < 1 || c > 6 || r < 0 || r + strs[n].length() - 1 > 7) {
            return 0;
        }
        for (int i = 0; i < strs[n].length(); i++) {
            if (!grid[r + i][c].empty() && grid[r + i][c].top() != strs[n][i]) {
                return 0;
            }
        }
        for (int i = 0; i < strs[n].length(); i++) {
            grid[r + i][c].push(strs[n][i]);
        }
        return 1;
    }
}

inline void del(int n, int r, int c, bool dir) {
    if (dir == 0) {
        for (int i = 0; i < strs[n].length(); i++) {
            grid[r][c + i].pop();
        }
    } else {
        for (int i = 0; i < strs[n].length(); i++) {
            grid[r + i][c].pop();
        }
    }
}

void solve(int n) {
    if (n > N) {
        for (int i = 1; i <= 6; i++) {
            for (int j = 1; j <= 6; j++) {
                if (!grid[i][j].empty()) {
                    printf("%c", grid[i][j].top());
                } else {
                    printf(" ");
                }
            }
            printf("\n");
        }
        printf("\n");
        return;
    }
    for (int i = 0; i <= 7; i++) {
        for (int j = 0; j <= 7; j++) {
            if (place(n, i, j, 0)) {
                solve(n + 1);
                del(n, i, j, 0);
            }
            if (place(n, i, j, 1)) {
                solve(n + 1);
                del(n, i, j, 1);
            }
        }
    }
}

int main() {
    
    sort(strs + 1, strs + N + 1, comp);
    for (int i = 1; i <= N; i++) {
        strs[i] = ' ' + strs[i] + ' ';
    }
    solve(1);
    
    return 0;
}
