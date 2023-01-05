#include <iostream>
#include <vector>
#define endl '\n'
using namespace std;

int N;
vector<int> regionsCnt;
vector<int> graph;

void Input() {

    cin >> N;

    for ( int i = 0; i < N; i++ ) {
        int cnt;
        cin >> cnt;
        regionsCnt.push_back(cnt);
    }

    for ( int i = 0; i < regionsCnt.size(); i++ ) {
        int connectCnt;
        cin >> connectCnt;

        for ( int j = 0; j < connectCnt; j++ ) {
            
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
