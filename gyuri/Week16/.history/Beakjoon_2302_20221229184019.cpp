#include <iostream>
#define endl '\n'
using namespace std;

int N, M;
int seats[41];
int dp[41];
int answer = 1;

// 재귀
//int Fibo(int n) {
//
//    if (n <= 2) return n;
//
//    else {
//        if (dp[n] > 0) return dp[n];
//        else return Fibo(n - 1) + Fibo(n - 2);
//    }
//
//}

int Fibo(int n) {

    if (n == 1) return 1;
    else if (n == 2) return 2;
    else {
        return dp[n - 1] + dp[n - 2];
    }
}

void FillDp() {

    for (int i = 1; i <= N; i++) {
        if (seats[i] != 0) { // VIP가 아닌 경우
            if (seats[i - 1] == 0) dp[i] = 1; // 앞의 요소가 VIP인 경우 현재 자리는 1
            else dp[i] = Fibo(i);
        }
        else { // VIP인 경우
            dp[i] = 1;
            answer *= dp[i - 1];
        }
    }
    answer *= dp[N];
}

void Input() {

    cin >> N >> M;

    for (int i = 1; i <= N; i++) {
        seats[i] = i;
    }

    for (int i = 0; i < M; i++) {
        int idx;
        cin >> idx;
        seats[idx] = 0;
    }

    dp[0] = 1; // dp 0번째 인덱스 값 1

}

void Output() {

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