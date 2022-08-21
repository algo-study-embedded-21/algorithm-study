#include<iostream>
#include<queue>
#include<vector>
#include<string>
#include<cstring>
#include<algorithm>

using namespace std;

struct gps
{
	int y;
	int x;
	int space;
};

bool cmp(gps l, gps r)  // 빈공간 큰순 > 행번호 작은순 > 열번호 작은순
{
	if (l.space > r.space)
	{
		return true;
	}
	if (l.space < r.space)
	{
		return false;
	}
	if (l.y < r.y)
	{
		return true;
	}
	if (l.y > r.y)
	{
		return false;
	}
	if (l.x < r.x)
	{
		return true;
	}
	if (l.x > r.x)
	{
		return false;
	}
	return false;
}

int n;
int map[20][20]; // 좌석표
vector<int> love[401]; // 각 학생이 좋아하는 학생 저장
vector<gps> chair[401]; // 주변에 좋아하는 학생이 제일 많은 위치'들' 저장
vector<int> line; // 좌석을 고를 학생 순서 저장

void school(int st)
{
	int maxlike = -1;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (map[i][j] != 0)
			{
				continue; // 이미 누군가 앉아있는좌석 통과
			}
			int yc[4] = { -1,0,0,1 };
			int xc[4] = { 0,-1,1,0 };
			int like = 0; // 주변의 선호하는 학생 수
			int spacecnt = 0; // 주변의 빈공간 수
			for (int k = 0; k < 4; k++)
			{
				int yy = i + yc[k];
				int xx = j + xc[k];
				if (yy<0 || yy>n - 1 || xx<0 || xx>n - 1)
				{
					continue;
				}
				for (int a = 0; a < 4; a++)
				{
					if (map[yy][xx] == love[st][a]) // 인근에 선호하는 학생이 있는경우
					{
						like++;
					}
				}
				if (map[yy][xx] == 0) // 인근에 빈자리가 있는경우
				{
					spacecnt++;
				}
			}
			if (maxlike == like) // 좋아하는 학생수가 최대치와 같을때
			{
				chair[st].push_back({ i,j,spacecnt }); // 후보 위치 추가
			}
			if (maxlike < like) // 최대치를 갱신했을때
			{
				maxlike = like;
				vector<gps> newchair; 
				chair[st] = newchair; // 그전까지의 후보들을 지우고
				chair[st].push_back({ i,j,spacecnt }); // 후보 위치로 등록
			}
		}
	}
	sort(chair[st].begin(), chair[st].end(), cmp); // 조건에 맞게 정렬하여
	map[chair[st][0].y][chair[st][0].x] =  st; // 가장 적합한 후보 위치에 착석
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n;
	int student = n * n;
	for (int i = 1; i <= student; i++) 
	{
		int st, a, b, c, d;
		cin >> st >> a >> b >> c >> d;
		line.push_back(st);  // 순서 저장
		// 관계저장
		love[st].push_back(a);  
		love[st].push_back(b);
		love[st].push_back(c);
		love[st].push_back(d);
	}
	for (int i = 0; i < student; i++)
	{
		school(line[i]); // 모든 학생 착석
	}
	int ans = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int st = map[i][j];
			int yc[4] = { -1,0,0,1 };
			int xc[4] = { 0,-1,1,0 };
			int like = 0;
			for (int k = 0; k < 4; k++)
			{
				int yy = i + yc[k];
				int xx = j + xc[k];
				if (yy<0 || yy>n - 1 || xx<0 || xx>n - 1)
				{
					continue;
				}
				for (int a = 0; a < 4; a++)
				{
					if (map[yy][xx] == love[st][a])
					{
						
						like++;
					}
				}
			}
			if (like > 0) // 착석한 자리 주변에 선호하는 학생이 있는경우
			{
				int score = 1;
				for (int a = 1; a < like; a++)
				{
					score = score * 10; // 1일때 1점 2일때 10점 3일때 100점 4일때 1000점
				}
				ans += score;
			}
		}
	}
	cout << ans;
	return 0;
}