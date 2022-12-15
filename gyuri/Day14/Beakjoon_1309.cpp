#include <iostream>
#define endl '\n'
using namespace std;

int N; // 우리 크기
int dp[1000000][3];
int answer;

void Calc() {
    // 첫 번째 칸 1로 초기화
    for (int i = 0; i < 3; i++) {
        dp[1][i] = 1;
    }

    for (int i = 2; i <= N; i++) {
        dp[i][0] = dp[i - 1][1] + dp[i - 1][2] % 9901;
        dp[i][1] = dp[i][0] % 9901;
        dp[i][2] = dp[i - 1][0] + dp[i - 1][1] + dp[i - 1][2] % 9901;
    }

    for (int i = 0; i < 3; i++) {
        answer += dp[N][i];
    }
}

void Output() {
    cout << answer % 9901 << endl;
}

void Input() {
    cin >> N;
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    Input();
    Calc();
    Output();
    

    return 0;
}