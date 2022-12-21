#include <iostream>
#include <string>
#define endl '\n'
using namespace std;

string str_1 = "0";
string str_2 = "0";
string 
int N, M;
int dp[1001][1001];

void Output(){
    cout << dp[N-1][M-1];
}

void FillDp(){
    
    for ( int i = 0; i < N; i++ ) {
        for ( int j = 0; j < M; j++ ) {
            if ( i == 0 || j == 0 ) dp[i+1][j+1] == 0;
            else if ( str_1[i] == str_2[j] ) dp[i][j] = dp[i-1][j-1] + 1;
            else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }

    for ( int i = 0; i < N; i++ ) {
        for ( int j = 0; j < M; j++ ) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }

}

void Input(){
    int A, B;
    cin >> A >> B;

    str_1 += A;
    str_2 += B;
    N = str_1.length();
    M = str_2.length();
}

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    Input();
    FillDp();
    Output();

    return 0;
}