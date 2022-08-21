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
int pluspower[11][11]; // ���� �� ĭ�� �߰��� ���
int map[11][11]; // �� ĭ�� ���� ��� ����
int alive[11][11]; // �� ĭ�� ���� ���� ����
vector<int> tree[11][11]; // �� ĭ�� �ִ� ���� ����
vector<fall> newtree; // �������� ���� �ɾ��� ���� ������ ����

void seed(gps st)
{
	//�� (��� �Ա�)
	sort(tree[st.y][st.x].begin(), tree[st.y][st.x].end()); // ��������� ����� ���̱� ���� ����
	int num = 0;
	while (num < tree[st.y][st.x].size() && map[st.y][st.x] >= tree[st.y][st.x][num])
	{ // ��� ������ ����� �԰ų� ���� ����� �����Ҷ����� �ݺ� ����
		map[st.y][st.x] -= tree[st.y][st.x][num]; //���� ��и�ŭ �ʿ��� ����
		tree[st.y][st.x][num] += 1; // ������ ���� +1
		num++; // ���� ������
	}
	//���� (���� ����)
	int len = tree[st.y][st.x].size(); // ���� �� ������ ��
	for (int i = len - 1; i >= num; i--)
	{ // �ǵ� �������� ����� ���� ���� �������� => ���� ����
		map[st.y][st.x] = map[st.y][st.x] + (tree[st.y][st.x][i] / 2); 
		tree[st.y][st.x].pop_back();
	}
	len = tree[st.y][st.x].size(); // ���� ���� ��
	if (len == 0)
	{ // ���� ������ ���ٸ� ������ �ǹ̰� �����Ƿ� �������� ���θ� ǥ���� ����
		alive[st.y][st.x] = 0;
		return;
	}
	//���� �غ�
	int cnt = 0; 
	for (int i = 0; i < len; i++)
	{
		if (tree[st.y][st.x][i] % 5 == 0)
		{  // ���̰� 5�� ����� ���� ��
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
			newtree.push_back({ newseed.y,newseed.x,cnt }); // ���ο� ������ �Ѹ����� ��ġ�� ���ο� ������ �� ����
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
			map[i][j] = 5; // ������ ��� ���� ����� 5
		}
	}
	for (int i = 0; i < m; i++)
	{
		int x, y, z;
		cin >> x >> y >> z;
		alive[x][y] = 1;
		tree[x][y].push_back(z); // �ʱ� ������ġ�� ���� ����
	}
	for (int i = 0; i < k; i++)
	{
		while (newtree.size() > 0)
		{
			newtree.pop_back(); // ���ο� ������ ��� �ɾ����� �ʱ�ȭ
		}
		for (int r = 1; r <= n; r++)
		{
			for (int c = 1; c <= n; c++)
			{
				if (alive[r][c] == 1)
				{
					seed({ r,c }); // ��,���� ���� + �����غ�
				}
				map[r][c] += pluspower[r][c]; // �ܿ￡ ��� �߰� (������ ������ ���� �ʾ� �����ص� �������)
			}
		}
		for (int j = 0; j < newtree.size(); j++) // ���� ���� ����
		{
			alive[newtree[j].y][newtree[j].x] = 1; // ���ο� ������ �ɾ����� �ڸ� ǥ��
			for (int f = 0; f < newtree[j].num; f++)
			{
				tree[newtree[j].y][newtree[j].x].push_back(1); // ���ο� ���� �ɱ�
			}
		}
	}
	int cnt = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)\
		{
			cnt += tree[i][j].size(); // ��� ������ �� ������
		}
	}
	cout << cnt;
	return 0;
}