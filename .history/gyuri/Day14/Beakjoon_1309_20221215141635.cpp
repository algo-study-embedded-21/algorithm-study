#include <iostream>
using namespace std;

int N; // 우리 크기
int dp[1000000][3];

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    dp[1][0] = 1;
    dp[1][1] = 1;
    dp[1][2] = 1;

    for(int i = 2; i <= N; i++){
        dp[i][0] = dp[i-1][1] + dp[i-1][2];
        dp[i][1] = dp[i][0]; 
        dp[i][2] = dp[i-1][0] + dp[i-1][1] + dp[i-1][2];
    }

    int answer = 0;

    for(int i = 0; i < 3; i++){
        answer += dp[N][i];
    }

    cout << answer%9901 << endl;

    return 0;
}