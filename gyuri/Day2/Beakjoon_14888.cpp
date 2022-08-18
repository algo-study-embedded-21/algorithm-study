// 구현 아이디어
//모든 식을 다 구해서 최댓값과 최솟값을 구해야 하므로
//dfs 완전탐색을 이용해서 문제를 풀어야할 것 같다.

#include <iostream>
#include <vector>
#define endl "\n"
using namespace std;

int N; // 수의 개수
int _number[102]; // 수 담은 배열

int operatorCount[4]; // 각 연산자 별 개수
char _operator[15]; // 모든 연산자 담은 배열
char operPath[15]; // 연산자 조합
int used[15] = { 0, }; // 사용했나 안했나

int maxResult = -2134567890;
int minResult = 2134567890;


int calculator() {
	int calcResult = _number[0];
	for (int i = 1; i < N; i++) {
		if (operPath[i-1] == '+') {
			calcResult += _number[i];
		}
		if (operPath[i-1] == '-') {
			calcResult -= _number[i];
		}
		if (operPath[i-1] == '*') {
			calcResult *= _number[i];
		}
		if (operPath[i-1] == '/') {
			if (calcResult < 0) { // 음수일 경우 양수로 바꿔준다.
				calcResult = -calcResult;
				calcResult /= _number[i];
				calcResult = -calcResult;
			}
			else {
				calcResult /= _number[i];
			}
		}
	}
	return calcResult;
}

void dfs(int operIdx) {

	// 기저 조건
	if (operIdx == N-1) {
		int result = calculator();
		if (result > maxResult) {
			maxResult = result;
		}
		if (result < minResult) {
			minResult = result;
		}
	}

	// 재귀 구성
	for (int next = 0; next < N-1; next++) {
		// 가지치기
		if (used[next] == 1) continue;

		used[next] = 1; // 사용 기록 (중복되면 안되기 때문에)
		operPath[operIdx] = _operator[next]; // path 기록
		dfs(operIdx + 1);	
		used[next] = 0; // 사용 기록 해제
	}
}

int main() {

	cin >> N;
	
	for (int i = 0; i < N; i++) {
		cin >> _number[i];
	}

	for (int i = 0; i < 4; i++) {
		cin >> operatorCount[i];
	}

	int idx = 0;
	for (int i = 0; i < 4; i++) {
		if (operatorCount[i] == 0) continue;
		for (int j = 0; j < operatorCount[i]; j++) {
			if (i == 0) _operator[idx] = '+';
			if (i == 1) _operator[idx] = '-';
			if (i == 2) _operator[idx] = '*';
			if (i == 3) _operator[idx] = '/';
			idx++;
		}
	}

	dfs(0);

	cout << maxResult << endl;
	cout << minResult;
}