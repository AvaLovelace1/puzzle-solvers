/*
 Solver for the word search puzzle in Race for the Galaxy
 (https://2019.galacticpuzzlehunt.com/puzzle/race-for-the-galaxy)
 In this puzzle, you are given a word search encoded using a substitution cipher
 and a list of English words. You must decode the word search to find the words.
 */

#include <bits/stdc++.h>

using namespace std;

#define f first
#define s second
#define pb push_back
#define FILL(a, b) memset(a, b, sizeof(a))

typedef long long int ll;
typedef pair<int, int> pii;
typedef pair<pii, string> piii;
typedef vector<int> vi;
typedef vector<pii> vii;
const int INF = 0x3f3f3f3f;
const ll INFL = 0x3f3f3f3f3f3f3f3fLL;
const int MOD = 1e9 + 7;
const int MAX = 2e5 + 5;

const pii dirs[] = { {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1} };
const string dirToStr[] = { "N", "NE", "E", "SE", "S", "SW", "W", "NW" };
int R = 12, C = 12;
int N;
string words[MAX];
char grid[20][20];
// has this square been used?
int used[20][20];
// Cipher to English, English to cipher
stack<char> cipher[2][26];
char cipherTmp[2][26];

inline bool comp(string a, string b) {
    if (a.length() == b.length()) {
        return a < b;
    }
    return a.length() > b.length();
}

// try to find the word at r, c, dir
inline bool place(int r, int c, int dir, string word) {
    int r0 = r, c0 = c;
    string gridWord = "";
    for (int i = 0; i < word.length(); i++) {
        if (r < 1 || c < 1 || r > R || c > C) {
            return 0;
        }
        gridWord += grid[r][c];
        r += dirs[dir].f, c += dirs[dir].s;
    }
    FILL(cipherTmp, 0);
    for (int i = 0; i < 26; i++) {
        for (int t = 0; t < 2; t++) {
            if (!cipher[t][i].empty()) {
                cipherTmp[t][i] = cipher[t][i].top();
            }
        }
    }
    for (int i = 0; i < gridWord.length(); i++) {
        if (cipherTmp[0][gridWord[i] - 'A'] == 0 && cipherTmp[1][word[i] - 'A'] == 0) {
            // if this letter has not yet been decoded, put it in the code
            cipherTmp[0][gridWord[i] - 'A'] = word[i];
            cipherTmp[1][word[i] - 'A'] = gridWord[i];
        } else if (cipherTmp[0][gridWord[i] - 'A'] != word[i] || cipherTmp[1][word[i] - 'A'] != gridWord[i]) {
            // else if the current code does not agree with the word, return
            return 0;
        }
    }
    // update cipher
    for (int i = 0; i < gridWord.length(); i++) {
        cipher[0][gridWord[i] - 'A'].push(word[i]);
        cipher[1][word[i] - 'A'].push(gridWord[i]);
    }
    for (int i = 0; i < word.length(); i++) {
        used[r0][c0]++;
        r0 += dirs[dir].f, c0 += dirs[dir].s;
    }
    return 1;
}

inline void unplace(int r, int c, int dir, string word) {
    int r0 = r, c0 = c;
    string gridWord = "";
    for (int i = 0; i < word.length(); i++) {
        gridWord += grid[r][c];
        r += dirs[dir].f, c += dirs[dir].s;
    }
    for (int i = 0; i < gridWord.length(); i++) {
        cipher[0][gridWord[i] - 'A'].pop();
        cipher[1][word[i] - 'A'].pop();
    }
    for (int i = 0; i < word.length(); i++) {
        used[r0][c0]--;
        r0 += dirs[dir].f, c0 += dirs[dir].s;
    }
}

void solve(int n) {
    
    if (n > N) {
        cout << "Cipher to English:\n";
        // print cipher
        for (int i = 0; i < 26; i++) {
            cout << (char) (i + 'A');
        }
        cout << "\n";
        
        for (int i = 0; i < 26; i++) {
            if (cipher[0][i].empty()) {
                cout << '?';
            } else {
                cout << cipher[0][i].top();
            }
        }
        cout << "\n\n";
        
        // print positions of words
        for (int i = 1; i <= N; i++) {
            bool found = 0;
            for (int r = 1; r <= R && !found; r++) {
                for (int c = 1; c <= C && !found; c++) {
                    for (int dir = 0; dir < 8 && !found; dir++) {
                        if (place(r, c, dir, words[i])) {
                            found = 1;
                            cout << words[i] << ' ' << r << ' ' << c << ' ' << dirToStr[dir] << '\n';
                        }
                    }
                }
            }
        }
        cout << "\n";
        
        for (int r = 1; r <= R; r++) {
            for (int c = 1; c <= C; c++) {
                if (!used[r][c]) {
                    cout << (cipher[0][grid[r][c] - 'A'].empty() ? '?' : cipher[0][grid[r][c] - 'A'].top());
                }
            }
        }
        cout << "\n\n";
        
        return;
    }
    
    for (int r = 1; r <= R; r++) {
        for (int c = 1; c <= C; c++) {
            for (int dir = 0; dir < 8; dir++) {
                if (place(r, c, dir, words[n])) {
                    solve(n + 1);
                    unplace(r, c, dir, words[n]);
                }
            }
        }
    }
    
}

int main() {
    
    // case and spacing does not matter
    // input grid
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            cin >> grid[i][j];
            grid[i][j] = toupper(grid[i][j]);
        }
    }

    // input # of words, then words
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> words[i];
        transform(words[i].begin(), words[i].end(), words[i].begin(), ::toupper);
    }
    sort(words + 1, words + N + 1, comp);
    
    solve(1);
    
    return 0;
}
