// 190405
// https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5V4A46AdIDFAWu&categoryId=AV5V4A46AdIDFAWu&categoryType=CODE

#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

int T, ans;
int n, m, c;
int a[10][10];

struct Node {
	int r; 
	int c1; // ���� ������
	int c2; // ���� ���� 
	int profit;
};

vector<Node> v1;

void go(int i, int j, int k)
{
	Node node;
	node.r = i, node.c1 = j, node.c2 = k;
	node.profit = 0;

	vector<int> v3(m);
	int idx = 0;
	for (int x = j; x <= k; x++) {
		v3[idx++] = a[i][x];
	}

	int profit;
	int honey_sum;
	for (int x = 1; x <= m; x++) { // x�� ���� ��� �� ����
		vector<int> v4(m);
		for (int y = 0; y < x; y++) {
			v4[y] = 1;
		}

		do {
			profit = 0;
			honey_sum = 0;
			for (int z = 0; z < v4.size(); z++) {
				if (v4[z] == 1) {
					honey_sum += v3[z];
					if (honey_sum > c) {
						profit = 0;
						break;
					}
					profit += v3[z] * v3[z];
				}
			}
			if (node.profit < profit) node.profit = profit;
		} while (prev_permutation(v4.begin(), v4.end()));
	}
	v1.push_back(node);
}

void cal_profit()
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			// i, j�� ������
			if (j + m - 1 >= n) break;
			go(i, j, j + m - 1);
		}
	}
}

void real_profit()
{
	vector<int> v2(v1.size());
	v2[0] = 1; v2[1] = 1;
	Node node[2];
	int idx, temp;
	do {
		idx = 0; temp = 0;
		for (int i = 0; i < v2.size(); i++) {
			if (v2[i] == 1) node[idx++] = v1[i];

			if (node[0].r != node[1].r) {
				temp = node[0].profit + node[1].profit;
			}
			else if (node[0].c2 < node[1].c1) {
				temp = node[0].profit + node[1].profit;
			}
			if (ans < temp) ans = temp;
		}
	} while (prev_permutation(v2.begin(), v2.end()));
}

int main()
{
	freopen("sample_input.txt", "r", stdin);
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		ans = 0;
		vector<Node>().swap(v1);
		cin >> n >> m >> c;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cin >> a[i][j];
			}
		}

		cal_profit(); // ó������ �� ���鼭 profit ��� (v1 �ϼ�)
		real_profit();

		cout << "#" << tc << " " << ans << '\n';
	}
	return 0;
}
