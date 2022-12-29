#include<iostream>
using namespace std;

long long dp[41]; //연속되는 일반석의 갯수가 i개일 때 가능한 경우의 수

int main() {
    int n, m;
    cin >> n >> m;
    dp[1] = 1;
    dp[2] = 2;
    for (int i = 3; i <= 40; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    int idx = 1;
    int ans = 1;
    for (int i = 0; i < m; i++) {
        int vip;
        cin >> vip;
        ans *= dp[vip - idx]; //vip의 위치에 따라 연속되는 일반석의 개수가 끊어지기 떄문에
        idx = vip + 1;
    }
    ans *= dp[n + 1 - idx];
    cout << ans;
}
