#include<iostream>
#include<queue>
#include<vector>
#include<string>
#include<cstring>
#include<algorithm>
#include<unordered_map>

using namespace std;

int wheel[5][8];  // wheel[�����ǹ�ȣ][����ǹ�ȣ] = ��
int k;
int turnox[5]; // ��Ϲ����� ���Ҵ��� ����

void turn(int wheelnum, int direction)
{
	turnox[wheelnum] = 1; // ���� �ش� ��ȣ�� ��� ������ �������̴�
	int opo;
	if (direction == 1) // �ݴ���� ����
	{
		opo = -1;
	}
	else
	{
		opo = 1;
	}
	if (wheelnum < 4 && turnox[wheelnum + 1] == 0 && wheel[wheelnum][2] != wheel[wheelnum + 1][6])
	{ // �޹�ȣ ��Ϲ����� ������ �ִ� ��� �̸鼭 �޹�ȣ�� ���� ���� �������
		turn(wheelnum + 1, opo);
	}
	if (wheelnum > 1 && turnox[wheelnum - 1] == 0 && wheel[wheelnum - 1][2] != wheel[wheelnum][6])
	{ // �չ�ȣ ��Ϲ����� ������ �ִ� ��� �̸鼭 �չ�ȣ�� ���� ���� �������
		turn(wheelnum - 1, opo);
	}
	if (direction == 1) // �ð�������� ����
	{
		int temp = wheel[wheelnum][7];
		for (int i = 7; i >=1; i--)
		{
			wheel[wheelnum][i] = wheel[wheelnum][i-1];
		}
		wheel[wheelnum][0] = temp;
	}
	else // �ݽð�������� ����
	{
		int temp = wheel[wheelnum][0];
		for (int i = 0; i < 7; i++)
		{
			wheel[wheelnum][i] = wheel[wheelnum][i+1];
		}
		wheel[wheelnum][7] = temp;
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();
	
	for (int i = 1; i < 5; i++)
	{
		string line;
		cin >> line;
		for (int j = 0; j < 8; j++)
		{
			wheel[i][j] = line[j] - '0';
		}
	}
	cin >> k;
	for (int i = 0; i < k; i++)
	{
		int wheelnum, direction;
		cin >> wheelnum >> direction;
		turn(wheelnum, direction);
		for (int j = 1; j < 5; j++) // ��Ϲ��� ���Ҵ��� ���� �ʱ�ȭ
		{
			turnox[j] = 0;
		}
	}
	int score = 1; // ��Ϲ��� ��ȣ�� 1�϶� 1��
	int totalscore = 0;
	for (int i = 1; i < 6; i++)
	{
		if (wheel[i][0] == 1) // 12���� �ؼ���  s�϶��� ���� �߰�
		{
			totalscore += score;
		}
		score = score * 2; // ��Ϲ����� ���� = 2^(��Ϲ�����ȣ-1)
	}
	cout << totalscore;
	return 0;
}