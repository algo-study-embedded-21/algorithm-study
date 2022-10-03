#include<iostream>
#include<queue>
#include<vector>
#include<string>
#include<cstring>
#include<algorithm>

using namespace std;

struct gps {
	int y;
	int x;
};
struct fall {
	int y;
	int x;
	int num;
};

int n, m, k;
int pluspower[11][11]; // 매해 각 칸에 추가될 양분
int map[11][11]; // 각 칸의 현재 양분 상태
int alive[11][11]; // 각 칸에 나무 존재 여부
vector<int> tree[11][11]; // 각 칸에 있는 나무 저장
vector<fall> newtree; // 번식으로 새로 심어질 나무 데이터 저장

void seed(gps st)
{
	//봄 (양분 먹기)
	sort(tree[st.y][st.x].begin(), tree[st.y][st.x].end()); // 어린나무부터 양분을 먹이기 위해 정렬
	int num = 0;
	while (num < tree[st.y][st.x].size() && map[st.y][st.x] >= tree[st.y][st.x][num])
	{ // 모든 나무가 양분을 먹거나 맵의 양분이 부족할때까지 반복 실행
		map[st.y][st.x] -= tree[st.y][st.x][num]; //먹은 양분만큼 맵에서 차감
		tree[st.y][st.x][num] += 1; // 나무의 나이 +1
		num++; // 다음 나무로
	}
	//여름 (죽은 나무)
	int len = tree[st.y][st.x].size(); // 현재 총 나무의 수
	for (int i = len - 1; i >= num; i--)
	{ // 맨뒤 나무부터 양분을 먹지 못한 나무까지 => 죽은 나무
		map[st.y][st.x] = map[st.y][st.x] + (tree[st.y][st.x][i] / 2); 
		tree[st.y][st.x].pop_back();
	}
	len = tree[st.y][st.x].size(); // 남은 나무 수
	if (len == 0)
	{ // 남은 나무가 없다면 가을이 의미가 없으므로 나무존재 여부를 표시후 리턴
		alive[st.y][st.x] = 0;
		return;
	}
	//가을 준비
	int cnt = 0; 
	for (int i = 0; i < len; i++)
	{
		if (tree[st.y][st.x][i] % 5 == 0)
		{  // 나이가 5의 배수인 나무 수
			cnt++;
		}
	}
	if (cnt > 0)
	{
		int yy[8] = { -1,-1,-1,0,0,1,1,1 };
		int xx[8] = { -1,0,1,-1,1,-1,0,1 };
		for (int j = 0; j < 8; j++)
		{
			gps newseed;
			newseed.y = st.y + yy[j];
			newseed.x = st.x + xx[j];
			if (newseed.y<1 || newseed.y>n || newseed.x<1 || newseed.x>n)
			{
				continue;
			}
			newtree.push_back({ newseed.y,newseed.x,cnt }); // 새로운 나무가 뿌리내릴 위치와 새로운 나무의 수 저장
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			cin >> pluspower[i][j];
			map[i][j] = 5; // 최초의 모든 맵의 양분은 5
		}
	}
	for (int i = 0; i < m; i++)
	{
		int x, y, z;
		cin >> x >> y >> z;
		alive[x][y] = 1;
		tree[x][y].push_back(z); // 초기 나무위치와 나이 저장
	}
	for (int i = 0; i < k; i++)
	{
		while (newtree.size() > 0)
		{
			newtree.pop_back(); // 새로운 나무를 모두 심었으니 초기화
		}
		for (int r = 1; r <= n; r++)
		{
			for (int c = 1; c <= n; c++)
			{
				if (alive[r][c] == 1)
				{
					seed({ r,c }); // 봄,여름 실행 + 가을준비
				}
				map[r][c] += pluspower[r][c]; // 겨울에 양분 추가 (가을에 영향을 주지 않아 먼저해도 상관없음)
			}
		}
		for (int j = 0; j < newtree.size(); j++) // 가을 번식 실행
		{
			alive[newtree[j].y][newtree[j].x] = 1; // 새로운 나무가 심어지는 자리 표시
			for (int f = 0; f < newtree[j].num; f++)
			{
				tree[newtree[j].y][newtree[j].x].push_back(1); // 새로운 나무 심기
			}
		}
	}
	int cnt = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)\
		{
			cnt += tree[i][j].size(); // 모든 나무의 수 누적합
		}
	}
	cout << cnt;
	return 0;
}
