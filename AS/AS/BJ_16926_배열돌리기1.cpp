// 190327
// https://www.acmicpc.net/problem/16926

#include <iostream>
#include <queue>
using namespace std;

int n, m, r;
bool c[301][301];
int a[301][301];

int di[] = { 0,1,0,-1 }; // ����, �� �� �� ��
int dj[] = { 1,0,-1,0 };

queue<int> q;

void getOrder(pair<int,int> s)
{
	int i = s.first;
	int j = s.second;
	
	int stti = i;
	int dsti = n - i + 1;
	int sttj = j;
	int dstj = m - j + 1;
	int d = 0;

	while (1) {
		q.push(a[i][j]);
		i += di[d];
		j += dj[d];
		if (i > dsti) i = dsti, d = 2, j = dstj - 1;
		else if (j > dstj) j = dstj, d = 1, i = stti + 1;
		else if (i < stti) i = stti, d = 0, j = sttj + 1;
		else if (j < sttj) j = sttj, d = 3, i = dsti - 1;
		if (i == stti && j == sttj) break;
	}
}

void revolution(pair<int, int> s)
{
	int d = 1; // �Ʒ����� ����
	int cnt = 0;
	int i = s.first;
	int j = s.second;

	int stti = i;
	int dsti = n - i + 1;
	int sttj = j;
	int dstj = m - j + 1;

	while(1) { // find start
		
		// ��ǥ �̵�
		i += di[d];
		j += dj[d];
		if (i > dsti) i = dsti, d = 0, j = sttj + 1;
		else if (j > dstj) j = dstj, d = 3, i = dsti - 1; 
		else if (i < stti) i = stti, d = 2, j = dstj - 1;
		else if (j < sttj) j = sttj, d = 1, i = stti + 1;
		// �˻�
		cnt += 1;
		if (cnt == r) break;
	}

	if (d == 0) d = 2;
	else if (d == 1) d = 3;
	else if (d == 2) d = 0;
	else if (d == 3) d = 1;

	while (!q.empty()) { // ����

		int temp = q.front();
		q.pop();

		a[i][j] = temp;
		c[i][j] = true;

		i += di[d];
		j += dj[d];
		if (i > dsti) i = dsti, d = 2, j = dstj - 1;
		else if (j > dstj) j = dstj, d = 1, i = stti + 1;
		else if (i < stti) i = stti, d = 0, j = sttj + 1;
		else if (j < sttj) j = sttj, d = 3, i = dsti - 1;
	}
}

void counter_clock_wise()
{
	pair<int, int> s;
	int i = 1;
	while(1) {
		s = { i,i }; // ������
		if (c[i][i]) break;
		getOrder(s); // �ű� ��ǥ�� ť�� ����
		revolution(s);
		i += 1;
	}
}

int main()
{
	//freopen("sample_input.txt", "r", stdin);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m >> r;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> a[i][j];
		}
	}

	counter_clock_wise();

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cout << a[i][j] << " ";
		}
		cout << endl;
	}


	return 0;
}