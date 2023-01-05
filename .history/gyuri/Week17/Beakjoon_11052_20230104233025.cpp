#include <iostream>
#include <vector>
#define endl '\n'
using namespace std;

int N;
int cards[1002];
int dp[10002]; // index: 카드팩 카드 개수, value: index만큼 카드를 구매하기 위한 최대 금액

void Input() {

    cin >> N;

    for ( int i = 1; i <= N; i++ ) {
        cin >> cards[i];
    }

}

void FillDp() {

    dp[0] = 0;
    for ( int i = 1; i <= N; i++ ) { // 카드팩 종류
        for ( int j = i; j <= N; j++ ) { // 목표 카드 개수
            if ( j % i == 0 ) dp[j] = max(cards[j], max(dp[i] * (j / i), dp[j]));
            else dp[j] = max(dp[j - i] + dp[i], cards[j]);
        }
    }
}

void Output() {

    cout << dp[N];

}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    Input();
    FillDp();
    Output();

    return 0;
}
