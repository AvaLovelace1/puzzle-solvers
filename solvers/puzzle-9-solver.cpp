/*
 Solver for the 9th puzzle in Race for the Galaxy
 (https://2019.galacticpuzzlehunt.com/puzzle/race-for-the-galaxy)
 This puzzle is a series of blocks of 5 logical statements each
 and you must determine which statements are true.
 */

#pragma GCC optimize ("Ofast")

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
const ll INFL = 0x3f3f3f3f3f3f3f3fLL;
const int MOD = 1e9 + 7;
const int MAX = 1e5 + 5;

int N = 5;
int T;
piii arr[25];
string S = "";
string inputs[] = {"", "corr", "incorr", "corr2", "neither", "notboth", "exactly", "either", "pigs", "sky"};

inline int findInput(string str) {
    return (int) (find(inputs, inputs + 10, str) - inputs);
}

inline bool truth(int i, int m) {
    return m & (1 << i);
}

inline bool check(int m) {
    for (int i = 0; i < N; i++) {
        bool t = !truth(i, m);
        switch (arr[i].f) {
            case 1:
                if (t ^ !truth(arr[i].s.f, m)) {
                    return 0;
                }
                break;
            case 2:
                if (t ^ truth(arr[i].s.f, m)) {
                    return 0;
                }
                break;
            case 3:
                if (t ^ !(truth(arr[i].s.f, m) && truth(arr[i].s.s, m))) {
                    return 0;
                }
                break;
            case 4:
                if (t ^ !(!truth(arr[i].s.f, m) && !truth(arr[i].s.s, m))) {
                    return 0;
                }
                break;
            case 5:
                if (t ^ (truth(arr[i].s.f, m) && truth(arr[i].s.s, m))) {
                    return 0;
                }
                break;
            case 6:
                if (t ^ ((truth(arr[i].s.f, m) && truth(arr[i].s.s, m)) || (!truth(arr[i].s.f, m) && !truth(arr[i].s.s, m)))) {
                    return 0;
                }
                break;
            case 7:
                if (t ^ (!truth(arr[i].s.f, m) && !truth(arr[i].s.s, m))) {
                    return 0;
                }
                break;
            case 8:
                if (t ^ 1) {
                    return 0;
                }
                break;
            case 9:
                if (t ^ 0) {
                    return 0;
                }
                break;
        }
    }
    return 1;
}

int main() {
    
    cout << "For each case, enter the 5 statements in the form a x y (if x and y are applicable)\n";
    cout << "a is a string, x and y are characters (non-case-sensitive)\n";
    cout << "a = corr: x is correct\n";
    cout << "a = incorr: x is incorrect\n";
    cout << "a = corr2: x and y are correct\n";
    cout << "a = neither: neither x nor y are correct\n";
    cout << "a = notboth: x and y are not both correct\n";
    cout << "a = exactly: exactly one of x and y is correct\n";
    cout << "a = either: either x or y are correct (possibly both)\n";
    cout << "a = pigs: Pigs can fly\n";
    cout << "a = sky: The sky is blue\n\n";
    cout << "Enter the number of cases: ";
    cin >> T;
    
    while (T--) {
        printf("Enter case: ");
        string str;
        int a;
        char x, y;
        for (int i = 0; i < N; i++) {
            cin >> str;
            transform(str.begin(), str.end(), str.begin(), ::tolower);
            a = findInput(str);
            if (a >= 1 && a <= 2) {
                cin >> x;
                arr[i] = {a, {toupper(x) - 'A', 0}};
            } else if (a >= 2 && a <= 7) {
                cin >> x >> y;
                arr[i] = {a, {toupper(x) - 'A', toupper(y) - 'A'}};
            } else {
                arr[i] = {a, {0, 0}};
            }
        }
        
        for (int m = 0; m < (1 << N); m++) {
            if (check(m)) {
                cout << "Correct: ";
                int ans = 0;
                for (int i = 0; i < N; i++) {
                    if (truth(i, m)) {
                        cout << (char) ('A' + i);
                    }
                    ans <<= 1;
                    ans += truth(i, m);
                }
                S += ans + 'A' - 1;
                cout << "\n";
            }
        }
    }
    cout << "Answer: " << S << "\n";
    
    return 0;
}
