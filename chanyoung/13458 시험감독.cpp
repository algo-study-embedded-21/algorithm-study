#include<iostream>
#include<queue>
#include<vector>
#include<string>
#include<cstring>

using namespace std;

int main()
{

	vector<int> test;
	int n;
	cin >> n; // 시험장 개수
	long long cnt = 0; // 감독관수
	for (int i = 0; i < n; i++) //강의장 수만큼 반복
	{
		int a;
		cin >> a;
		test.push_back(a);  // 응시자 수를 벡터에 넣음
		cnt++; // 강의장마다 총감독관 1명 필수
	}
	int b, c;
	cin >> b >> c; // 감독관 역량 입력
	for (int i = 0; i < n; i++)
	{
		if (test[i] - b > 0)
		{
			int ex = test[i] - b; // 강의장 응시자 수에서 총감독관 1명분의 응시자수를 뺌
			if ((ex % c) == 0)  // 부 감독관 역량으로 나머지 응시자수가 나누어 떨어질 경우
			{
				cnt = cnt + ex / c;
			}
			else  // 나누어 떨어지지 않을경우
			{
				cnt = cnt + ex / c + 1;  // 남는 응시자수 때문에 +1
			}
		}
	}
	cout << cnt;
	return 0;
}