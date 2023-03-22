#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<queue>

using namespace std;

struct gps { int y, x; };
struct turning { int r, c, s; };

int n, m, k;
vector<vector<int>> A; // 배열 ( 복사 쉽게 하기위해 )
vector<turning> co; //회전 커맨드 저장
int visit[6];
int result=50000; // 답 최대 500

void turn(turning now) // 배열 돌리기
{
	int r = now.r, c = now.c, s = now.s;
	while (s > 0) // 가장 바깥 라인부터 점점 안쪽 라인까지
	{
		gps st = { r - s,c - s };
		int tmp = A[st.y][st.x];
		while (st.y < r + s) // 왼쪽 열 돌리기
		{
			A[st.y][st.x] = A[st.y + 1][st.x];
			st.y += 1;
		}
		while (st.x < c + s) // 아래 행 돌리기
		{
			A[st.y][st.x] = A[st.y][st.x + 1];
			st.x += 1;
		}
		while (st.y > r - s) // 오른쪽 열 돌리기
		{
			A[st.y][st.x] = A[st.y - 1][st.x];
			st.y -= 1;
		}
		while (st.x > c - s + 1) // 윗 행 돌리기
		{
			A[st.y][st.x] = A[st.y][st.x - 1];
			st.x -= 1;
		}
		A[st.y][st.x] = tmp; // 마무리
		s -= 1;
	}
}

int cal() // A 배열의 최솟값 계산
{
	int ans = 50000; // 최대 500
	for (int i = 0; i < n; i++)
	{
		int cnt = 0;
		for (int j = 0; j < m; j++)
		{
			cnt += A[i][j];
		}
		ans = min(ans, cnt);
	}
	return ans;
}

void dfs(int level)
{
	if (level == k)
	{
		result = min(result, cal());
		return;
	}
	for (int i = 0; i < k; i++)
	{
		if (visit[i])continue;
		visit[i] = 1;
		vector<vector<int>> tmp = A; // 이전 배열 복사
		turning now = co[i];
		turn(now);
		dfs(level + 1);
		A = tmp;
		visit[i] = 0;
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> m >> k;
	for (int i = 0; i < n; i++)
	{
		vector<int> v;
		for (int j = 0; j < m; j++)
		{
			int a;
			cin >> a;
			v.push_back(a);
		}
		A.push_back(v);
	}
	for (int i = 0; i < k; i++)
	{
		int r, c, s;
		cin >> r >> c >> s;
		co.push_back({ r - 1,c - 1,s }); // 0,0 기준으로 변경해서 적용
	}
	dfs(0);
	cout << result;

	return 0;
}
