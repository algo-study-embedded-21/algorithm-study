#include<iostream>
#include<string>
#include<cstring>
#include<queue>
#include<vector>
#include<algorithm>

using namespace std;

int n;
vector<int> num; // 수를 담을 벡터
vector<int> process; // 연산자를 담을 벡터
int usepro[10]; // 연산자 중복 사용 방지
int maxresult = -2134567890;
int minresult = 2134567890;
int cost;

void dfs(int index)
{
	if (index == n) // 마지막 까지 수행
	{
		if (cost > maxresult)
		{ // 최댓값
			maxresult = cost;
		}
		if (cost < minresult)
		{ // 최솟값
			minresult = cost;
		}
		return;
	}
	int next = num[index];
	for (int j = 0; j < n - 1; j++)
	{
		if (usepro[j] == 1)
		{
			continue;
		}
		if (process[j] == 0) // 덧셈 연산자
		{
			cost = cost + next;
			usepro[j] = 1;
			dfs(index + 1);
			usepro[j] = 0;
			cost = cost - next;
		}
		else if (process[j] == 1) // 뺄셈 연산자
		{
			cost = cost - next;
			usepro[j] = 1;
			dfs(index + 1);
			usepro[j] = 0;
			cost = cost + next;
		}
		else if (process[j] == 2) // 곱셈 연산자
		{
			cost = cost * next;
			usepro[j] = 1;
			dfs(index + 1);
			usepro[j] = 0;
			cost = cost / next;
		}
		else // 나눗셈 연산자
		{
			int ex;
			ex = cost % next; // 나머지 담아두기
			cost = cost / next;
			usepro[j] = 1;
			dfs(index + 1);
			usepro[j] = 0;
			cost = cost * next+ ex; // 복구시 나머지 더하기
		}

	}
}

int main()
{
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int a;
		cin >> a;
		num.push_back(a);
	}
	for (int i = 0; i < 4; i++)
	{
		int a;
		cin >> a;
		for (int j = 0; j < a; j++)
		{// 입력 수만큼 연산자 벡터에 반복 담기
			process.push_back(i);
		}
	}
	cost = num[0];// 최초 수로 초기값 세팅
	dfs(1);// 다음 수 index = 1
	cout << maxresult << "\n" << minresult;
	return 0;
}
