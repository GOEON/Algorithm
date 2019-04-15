#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

bool ok;
int a[101][101];
int r, c, k, ans;
int W, H;
int timer;

struct Node {
	int number;
	int cnt;
};

Node node[101];
bool used[101];

bool comp(Node n1, Node n2)
{
	if (n1.cnt != n2.cnt) return n1.cnt > n2.cnt;
	else if (n1.cnt == n2.cnt) return n1.number > n2.number;
}

int countAndModifyR(int i)
{
	int howmany = 0;
	int maxW = 0;
	for (int j = 1; j <= W; j++) {
		if (a[i][j] > 0) {
			if (used[a[i][j]] == false) {
				used[a[i][j]] = true;
				howmany += 1;
			}
			if (maxW < a[i][j]) maxW = a[i][j];
			node[a[i][j]].cnt += 1;
			node[a[i][j]].number = a[i][j];
			a[i][j] = 0;
		}
		
	}
	sort(node, node + maxW + 1, comp);
	int ret = 1;
	for (int j = howmany - 1; j >= 0; j--) {
		a[i][ret++] = node[j].number;
		a[i][ret++] = node[j].cnt;
	}
	return ret;
}

void moveR()
{
	int temp_ans = 0;
	for (int i = 1; i <= H; i++) {
		memset(node, 0, sizeof(node));
		memset(used, 0, sizeof(used));
		int temp = countAndModifyR(i);
		if (temp_ans < temp) temp_ans = temp;
	}
	if (W < temp_ans) W = temp_ans;
}

int countAndModifyC(int j)
{
	int howmany = 0;
	int maxH = 0;
	for (int i = 1; i <= H; i++) {
		if (a[i][j] > 0) {
			if (used[a[i][j]] == false) {
				used[a[i][j]] = true;
				howmany += 1;
			}
			if (maxH < a[i][j]) maxH = a[i][j];
			node[a[i][j]].cnt += 1;
			node[a[i][j]].number = a[i][j];
			a[i][j] = 0;
		}

	}
	sort(node, node + maxH + 1, comp);
	int ret = 1;
	for (int i = howmany - 1; i >= 0; i--) {
		a[ret++][j] = node[i].number;
		a[ret++][j] = node[i].cnt;
	}
	return ret;
}

void moveC()
{
	int temp_ans = 0;
	for (int j = 0; j < W; j++) {
		memset(node, 0, sizeof(node));
		memset(used, 0, sizeof(used));
		int temp = countAndModifyC(j);
		if (temp_ans < temp) temp_ans = temp;
	}
	if (H < temp_ans) H = temp_ans;
}

void play()
{
	timer = 0;
	while (timer != 101) {
		if (a[r][c] == k) {
			ok = true;
			ans = timer;
			break;
		}
		if (H >= W) moveR();
		else moveC();
		
		timer += 1;
	}
}

int main()
{
	//freopen("sample_input.txt", "r", stdin);
	cin >> r >> c >> k;
	W = 3; H = 3;
	for (int i = 1; i <= H; i++)
		for (int j = 1; j <= W; j++)
			cin >> a[i][j];

	play();

	if (ok) cout << ans << endl;
	else cout << -1 << endl;

	return 0;
}