#include <iostream>
#define endl '\n'
using namespace std;

int n, k;
int coins[101];
int dp[101]; // index: 만들고자 하는 가격, value: 해당 가격을 만들 수 있는 모든 경우의 수


void Input() {

    cin >> n >> k;

    for(int i = 0; i < n; i++) {
        cin >> coins[i];
    }

}

void FillDp() {

    dp[0] = 1; // 동전 자기 자신

    for ( int i = 0; i < n; i++ ) {
        for ( int j = coins[i]; j <= k; j++ ) {
            dp[j] = 
        }
    }
}

void Output() {}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    return 0;
}
