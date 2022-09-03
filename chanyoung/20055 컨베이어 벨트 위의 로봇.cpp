#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
#include<unordered_map>

using namespace std;

struct gps
{
	int num;
	int sit;
};

bool down(gps l, gps r) // �����÷��������ϼ��� ����ĭ�� ��ġ�Ѵ�
{
	if (l.sit < r.sit)
	{
		return true;
	}
	if (l.sit > r.sit)
	{
		return false;
	}
	return false;
}

int n, k;
int cnt = 1; // Ƚ������
gps line[200]; // num�� �κ� ���� ���� sit�� ĭ�� ������
vector<gps> robott; // num�� �κ���ȣ (Ŭ���� �������� �κ�) sit�� �κ��� �ִ� ĭ�� ��ȣ

void turn() // �����̾Ʈ ������
{
	int end = 2 * n - 1;
	gps temp = line[end];
	for (int i = end; i >0; i--)
	{
		line[i].sit = line[i-1].sit;
		line[i].num = line[i-1].num;
	}
	line[0].sit = temp.sit;
	line[0].num = temp.num;

}
void robotturn() // �κ���ġ�� �����̾Ʈ�� ���� ���� ����
{
	for (int i = robott.size()-1; i >=0; i--)
	{
		robott[i].sit++;
		if (robott[i].sit == n - 1) // ������ ��ġ�� �����ϸ� �κ� ������
		{
			line[n - 1].num = 0;
			robott.pop_back();
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> k;
	for (int i = 0; i < 2 * n; i++)
	{
		cin >> line[i].sit;
		line[i].num = 0;
	}
	int age = 200;
	while (1)
	{
		turn(); // �����̾� ��Ʈ ����
		sort(robott.begin(), robott.end(), down); // �κ��� �ø��� ��ġ���� ���������� ����
		robotturn();
		for (int i = robott.size() - 1; i >= 0; i--) // ���� �� �κ�(���� ���� �ø� �κ�) ���� ����
		{
			int robotsit = robott[i].sit;
			if (line[robotsit + 1].sit > 0 && line[robotsit + 1].num == 0) // ����ĭ�� �κ��� ���� �������� �����ִٸ�
			{
				robott[i].sit++; // �κ��� �ű��
				line[robotsit].num = 0; // �κ��� �ִ�ĭ�� ����
				line[robotsit + 1].num = 1; // �κ��� �ű�ĭ�� ä���
				line[robotsit + 1].sit--; // �ű�ĭ�� �������� ���ҽ�Ų��
			}
			if (robott[i].sit == n - 1) // �ű� �κ��� ������ ĭ�� �����ϸ� �κ� ����
			{
				line[n - 1].num = 0;
				robott.pop_back();
			}
		}
		if (line[0].sit != 0 && line[0].num == 0) // �ø��� ĭ�� �κ��� ���� �������� ���Ҵٸ� �κ� �ø���
		{
			robott.push_back({ age, 0 });
			line[0].num = 1; // ĭ ä���
			line[0].sit--; // ������ ����
			age--;
		}
		int brokesit = 0; // �������� 0�� ĭ�� ����
		for (int i = 0; i < 2 * n; i++)
		{
			if (line[i].sit == 0)
			{
				brokesit++;
			}
		}
		if (brokesit >= k)
		{
			break;
		}
		cnt++; // Ƚ�� �ø���
	}
	cout << cnt;

	return 0;
}