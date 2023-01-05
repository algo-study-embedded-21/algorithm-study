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

    for ( int i = 1; i <= N; i++ ) { // 카드팩 종류
        for ( int j = i; j <= N; j++ ) { // 목표 카드 개수
            // 목표 카드 개수에 나누어 떨어질 때
            // 몫 * 현재까지 저장된 최대 금액, 목표 카드 개수에 저장된 최대 금액, 목표 카드 개수만큼 카드를 가지고 있는 카드팩
            if ( j % i == 0 ) dp[j] = max(max(dp[i] * (j / i), dp[j]), cards[j]); 
            // 목표 카드 개수가 나눋어 떨어지지 않을 때
            // 현재까지 저장된 최대 금액 + 나머지 카드팩의 최대 금액, 목표 카드 개수만큼 카드를 가지고 있는 카드팩
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
