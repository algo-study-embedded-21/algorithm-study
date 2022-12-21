#include <iostream>
#include <string>
#define endl '\n'
using namespace std;

string str_1, str_2;
int dp[1001][1001];

void FillDp(){
    
    for ( int i = 0; i < str_1.length(); i++ ) {
        for ( int j = 0; j < str_2.length(); j++ ) {
            if ( i == 0 || j == 0 ) dp[i][j] = 0;
            else if ( str_1[i] == str_2[j] ) dp[i][j] = dp[i-1][j-1] + 1;
            else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }

    for ( int i = 0; i < str_1.length(); i++ ) {
        for ( int j = 0; j < str_2.length(); j++ ) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }

}

void Input(){
    cin >> str_1 >> str_2;
}

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    Input();
    FillDp();

    return 0;
}