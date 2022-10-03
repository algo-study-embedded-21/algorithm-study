#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
#include<unordered_map>
#include<cmath>

// 1:25 예제 다 맞춤
// 1:52 질문검색
// 2:58 완료

using namespace std;

struct two
{
	int circle;
	int num;
};

int n, m, t;
int circle[51][50];

void turn(int num,int di,int k) //원판 회전
{
	int temp;
	if (di == 1) // 반시계방향
	{
		for (int i = 0; i < k; i++)
		{
			temp = circle[num][0];
			for (int j = 0; j < m - 1; j++)
			{
				circle[num][j] = circle[num][j + 1];
			}
			circle[num][m-1] = temp;
		}
	}
	else // 시계방향
	{
		for (int i = 0; i < k; i++)
		{
			temp = circle[num][m-1];
			for (int j = m-1; j >0;j--)
			{
				circle[num][j] = circle[num][j - 1];
			}
			circle[num][0] = temp;
		}
	}
}

void find() // 같은수 찾아 지우기
{
	int flag = 0; // 같은수가 있었는지 여부
	vector<two> v; // 지울 숫자의 위치
	long long avg = 0; // 전체 평균값
	int cnt = 0; // 숫자가 남아있는 갯수
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			flag = 0;
			int now = circle[i][j];
			if (now != -1001) // 지워진 수 제외
			{
				if (now == circle[i][(j + 1) % m]) // 바로 옆수와 같은경우
				{
					flag = 1;
					v.push_back({ i,(j + 1) % m });
				}
				if (i!=n && now == circle[i + 1][j]) // 다음 원판의 같은 자리와 같은경우(마지막판은 조사 X)
				{
					flag = 1;
					v.push_back({ i + 1,j });
				}
				if (flag == 1)
				{
					v.push_back({ i,j });
				}
				avg += now;
				cnt++;
			}
		}
	}
	if (v.size() != 0) // 지워야할 수가 있는경우
	{
		for (int i = 0; i < v.size(); i++)
		{
			circle[v[i].circle][v[i].num] = -1001; // -1로도 가능했다 ***** 0은 불가능하다 ******
		}
	}
	else if(cnt !=0 )
	{
		int last = avg % cnt; // 평균값의 소숫점자리 존재여부
		avg = avg / cnt; // 평균값
		for (int i = 1; i <= n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if (circle[i][j] > avg) // 평균보다 큰수
				{
					circle[i][j] -= 1;
				}
				else if (circle[i][j] < avg && circle[i][j] != -1001) // 지워진 수가 아니면서 평균보다 작은수
				{
					circle[i][j] += 1;
				}
				else // 평균값 목과 같다면
				{
					if (last > 0 && circle[i][j] != -1001)
					{ // 지워진 수가 아니면서 평균값과 목이 같지만 평균값에 양수인 소숫점이 있는경우 평균보다 작다고 판단
						circle[i][j] += 1;
					}
					else if (last < 0 && circle[i][j] != -1001)
					{ // 음수인 소숫점이 있는경우 평균보다 크다고 판단  >>> 결과적으로 없어도 가능했다
						circle[i][j] -= 1;
					}
				}
			}
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();
	
	cin >> n >> m >> t;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			int a;
			cin >> a;
			circle[i][j] = a;
		}
	}
	for (int i = 0; i < t; i++) // 돌릴 원판 정보 받음과 동시에 실행
	{
		int x, d, k;
		cin >> x >> d >> k;
		int xx = x;
		while (xx <= n) // 원판 내부중
		{
			turn(xx, d, k); // 돌리기
			xx += x; //배수 원판 >>>>>>>>  **** xx += xx 로 작성한것이 최종 틀린부분 ****
		}
		find();
	}
	int ans = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (circle[i][j] != -1001)
			{
				ans += circle[i][j];
			}
		}
	}
	cout << ans;

	return 0;
}
