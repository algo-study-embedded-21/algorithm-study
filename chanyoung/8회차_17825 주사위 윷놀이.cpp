#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<string>
#include<cmath>

// 1:47 ���� �Ϻ�����
// 2:10 ���ƾ���
// 2:59 ���� ����
// 3:40 ����.....

using namespace std;

struct dir { int red; int blue; };

int dice[10];
dir unit[4]; // unit[i].red = i��° ���� ��ġ  unit[i].blue = i��° ���� �Ķ�ȭ��ǥ�� ��� Ÿ�� �Դ���
dir map[41]; // map[i].red = �Ķ�ȭ��ǥ�� ź�����°�� ������ ����ĭ map[i].blue = �Ķ�ȭ��ǥ�� ź���� �ִ°�� ������ ���� ĭ
int score;
int maxscore = -1;
vector<int> path[4];
vector<int> pathmap[4];

int check(int now, int bluecnt) // �̵��� ��ġ�� �̹� ������ ���� �ִ��� Ȯ��
{
	if (now > 40)
	{
		return 1;
	}
	for (int i = 0; i < 4; i++)
	{
		if (unit[i].red == now && (now == 40 || unit[i].blue == bluecnt)) //40�� �ϳ���
		{
			return 0;
		}
	}
	return 1;
}

void play(int level)
{
	if (level == 10)
	{
		maxscore = max(score, maxscore);
		if (score == maxscore)
		{
			int t = 1;
		}
		return;
	}
	for (int i = 0; i < 4; i++)
	{
		int now = unit[i].red;
		if (now > 40) // �̹� ������ ���� �������� �ʴ´�
		{
			continue;
		}
		int temp = now;
		int crossblue = unit[i].blue;
		if (now == 10 || now == 20 ) // �Ķ��� ĭ(10�Ǵ�20) ���� ����ϴ°��
		{
			for (int j = 0; j < dice[level]; j++)
			{
				now = map[now].blue;
			}
			if (check(now, 1)) // �ٸ����� ������ �̵�
			{
				unit[i].red = now;
				unit[i].blue = 1; // �Ķ��� ȭ��ǥ�� �ϳ� Ÿ�� �Դ�
			}
			else continue;
		}
		else if (now == 30 && crossblue == 0) /////////// �Ķ��� 30�� ĭ���� ����ϴ°��
		{
			now = 28; // ������ ��ĭ �ű�� ����
			for (int j = 0; j < dice[level] -1; j++)
			{
				now = map[now].blue;
			}
			if (check(now, 1)) // �ٸ����� ������ �̵�
			{
				unit[i].red = now;
				unit[i].blue = 1; // �Ķ��� ȭ��ǥ�� �ϳ� Ÿ�� �Դ�
			}
			else continue;
		}
		else if (crossblue == 0) // �Ķ��� ȭ��ǥ�� ź���� ���°��
		{
			for (int j = 0; j < dice[level]; j++)
			{
				now = map[now].red;
				if (now > 40) break; // �����ϸ� Ż��
			}
			if (check(now, 0)) unit[i].red = now; // �ٸ����� ������ �̵�
			else continue;
		}
		else // �Ķ��� ȭ��ǥ�� ź���� �ִ°��
		{
			for (int j = 0; j < dice[level]; j++)
			{
				if (now == 30) now = 35;
				else now = map[now].blue;
				if (now > 40) break; // �����ϸ� Ż��
			}
			if (check(now, 1)) unit[i].red = now; // �ٸ����� ������ �̵�
			else continue;
		}
		if (now <= 40) score += unit[i].red;
		path[i].push_back(now);
		pathmap[i].push_back(dice[level]);
		play(level + 1);
		pathmap[i].pop_back();
		path[i].pop_back();
		if (now <= 40) score -= unit[i].red;
		unit[i].red = temp; // ��ġ ����
		unit[i].blue = crossblue; // ������ �Ķ��� ĭ���� ����Ѱ��
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	for (int i = 0; i < 10; i++)
	{
		cin >> dice[i];
	}
	// �� ����
	for (int i = 0; i < 41; i++)
	{
		map[i].red = i + 2;
		map[i].blue = i + 2;
	}
	for (int i = 25; i < 40; i += 5) map[i].blue = i + 5;
	for (int i = 10; i < 19; i += 3) map[i].blue = i + 3;
	for (int i = 28; i >= 26; i--) map[i].blue = i - 1;
	map[19].blue = 25;
	map[24].blue = 25;

	play(0);
	cout << maxscore;

	return 0;
}