#include <iostream>
#define MIN -213456789

using namespace std;

int N, S, M;
int answer = MIN;
int volumes[51];
int dp[51][1001];

// dp[A][B] = V

void Input() {

    cin >> N >> S >> M;

    for (int i = 1; i <= N; i++) {
        cin >> volumes[i];
    }
}

void FillDp() {
    dp[0][S] = 1;
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j <= M; j++) {
            if (dp[i - 1][j] > 0) {
                if (j + volumes[i] <= M) {
                    dp[i][j + volumes[i]] = 1;
                }
                if (j - volumes[i] >= 0) {
                    dp[i][j - volumes[i]] = 1;
                }
            }
        }
    }
}

void Output() {
    for (int i = 0; i <= M; i++) {
        if (dp[N][i] == 0)
            continue;
        answer = max(answer, i);
    }
    answer = (answer > MIN) ? answer : -1;
    cout << answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    Input();
    FillDp();
    Output();
}