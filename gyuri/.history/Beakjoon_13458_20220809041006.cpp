#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 1000001
using namespace std;

int N; // 시험장 개수
int B, C; // 총 감독관이 감시할 수 있는 응시자 수, 부감독관이 감시할 수 있는 응시자 수

int arr[MAX]; // index: 응시자 수, value: 응시자 수 카운팅
long long result;

int main() {
    cin >> N;
    
    for(int i=0; i<N; i++){
        int A; // 응시자의 수
        cin >> A;
        arr[i] = A;
    }
    cin >> B >> C;

    for(int i=0; i<N; i++){
        int sub = 0; // 부 감독관 수
        int temp = arr[i]-B; // 응시자수 - 총 감독관이 감시할 수 있는 응시자 수
        if (temp > 0) {
            if (temp%C > 0) sub++; // 나머지가 있을 떄 부 감독관 수를 1명 더 늘려줘야 됨
            sub += temp/C;
        }

        result += (1+sub); // (총 감독관 수 + 부 감독관 수) * 
    }
    cout << result;

    return 0;
}