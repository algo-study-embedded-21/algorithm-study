#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
#include<unordered_map>
#include<cmath>

// 1�ð� ������ , ���� �Ϻ� ����
// 1�ð� 40�� ���� ��ü ����
// 1�ð� 58�� �Ϸ�

using namespace std;

struct gps
{
	int y;
	int x;
};

int n;
int map[10][10];
int score;

int yy[4] = { 0,0,0,1 };
int xx[4] = { 0,0,1,0 };

void put(int t, gps st) //������
{
	gps stt; // ��翡 ���� �߰� ���
	stt.y = st.y + yy[t];
	stt.x = st.x + xx[t];
	gps blue = st;
	gps bluee = stt;
	while (map[blue.y][blue.x] == 0 && map[bluee.y][bluee.x] == 0) // �����ϳ��� �ɸ��� ������ ���涧����
	{
		if (blue.x + 1 > 9 || bluee.x + 1 > 9) // ���� �ٱ��̸� ��ž
		{
			blue.x += 1;
			bluee.x += 1;
			break;
		}
		blue.x += 1;
		bluee.x += 1;
	}
	map[blue.y][blue.x-1] = 1;
	map[bluee.y][bluee.x-1] = 1;
	gps green = st;
	gps greenn = stt;
	while (map[green.y][green.x] == 0 && map[greenn.y][greenn.x] == 0)
	{
		if (green.y + 1 > 9 || greenn.y + 1 > 9)
		{
			green.y += 1;
			greenn.y += 1;
			break;
		}
		green.y += 1;
		greenn.y += 1;
	}
	map[green.y-1][green.x] = 1;
	map[greenn.y-1][greenn.x] = 1;
}

void light() // ���ѻ� ����
{
	int lightblue = 0; // ���� �ִ� ���Ķ� ���� ����
	int lightgreen = 0; // ���� �ִ� ���ʷ� ���� ����
	for (int j = 4; j < 6; j++) // ���Ķ� ����
	{
		for (int i = 0; i < 4; i++)
		{
			if (map[i][j] == 1)
			{
				lightblue++;
				break;
			}
		}
	}
	for (int i = 4; i < 6; i++) // ���ʷ� ����
	{
		for (int j = 0; j < 4; j++)
		{
			if (map[i][j] == 1)
			{
				lightgreen++;
				break;
			}
		}
	}
	for (int j = 9; j > 3; j--) // ���Ķ� ������ŭ �ű��
	{
		for (int i = 0; i < 4; i++)
		{
			map[i][j] = map[i][j - lightblue];
		}
	}
	for (int i = 9; i > 3; i--) // ���ʷ� �����ŭ �ű��
	{
		for (int j = 0; j < 4; j++)
		{
			map[i][j] = map[i - lightgreen][j];
		}
	}
}

void bomb() // �Ͷ߸���
{
	int gcol[4] = { 0 };
	int braw[4] = { 0 };
	for (int i = 6; i < 10; i++) // �ʷϻ� ����
	{
		for (int j = 0; j < 4; j++)
		{
			if (map[i][j] == 1)
			{
				gcol[i - 6] += 1;
			}
		}
	}
	for (int i = 0; i < 4; i++) // �Ķ��� ����
	{
		for (int j = 6; j < 10; j++)
		{
			if (map[i][j] == 1)
			{
				braw[j - 6] += 1;
			}
		}
	}
	for (int i = 0; i < 4; i++)
	{
		if (gcol[i] == 4) // �ʷϻ� �Ͷ߸���
		{
			for (int j = i + 6; j > 3; j--)
			{
				for (int k = 0; k < 4; k++)
				{
					map[j][k] = map[j - 1][k];
				}
			}
			score += 1;
		}
		if (braw[i] == 4) // �Ķ��� �Ͷ߸���
		{
			for (int j = i + 6; j > 3; j--)
			{
				for (int k = 0; k < 4; k++)
				{
					map[k][j] = map[k][j-1];
				}
			}
			score += 1;
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int t, y, x;
		cin >> t >> y >> x;
		put(t, { y,x });
		bomb(); // �Ͷ߸��Ⱑ ����ĭ ���� ���� ����
		light();
	}
	int block = 0;
	for (int i = 0; i < 4; i++) // �Ķ�ĭ ���� ����
	{
		for (int j = 6; j < 10; j++)
		{
			block += map[i][j];
		}
	}
	for (int i = 6; i < 10; i++) // �ʷ�ĭ ���� ����
	{
		for (int j = 0; j < 4; j++)
		{
			block += map[i][j];
		}
	}
	cout << score << "\n" << block;

	return 0;
}