#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

bool real_ok, ok;
int ans, T, total;
int n, m;

int dr[] = { -1,1,0,0 };
int dc[] = { 0,0,-1,1 };
int a[50][50];
bool v[50][50];

struct Node {
	int r;
	int c;
};

int nIdx, timer, cnt;
int virus[10];
Node node[10];

queue<Node> q;

void cleaning()
{
	timer = 0;
	while (timer <= n * n) {
		int size = q.size();
		if (cnt == total) {
			real_ok = true;
			ok = true;
			break;
		}
		while (size--) {
			Node tempNode = q.front();
			q.pop();

			for (int k = 0; k < 4; k++) {
				int nr = tempNode.r + dr[k];
				int nc = tempNode.c + dc[k];

				if (nr < 0 || nc < 0 || nr >= n || nc >= n) continue;
				if (v[nr][nc] == true || a[nr][nc] == 1) continue;
				v[nr][nc] = true;
				if (a[nr][nc] == 2) {
					q.push({ nr,nc });
				}
				else if (a[nr][nc] == 0) {
					cnt += 1;
					q.push({ nr,nc });
				}
			}
		}
		timer += 1;
	}
}

void play()
{
	memset(virus, 0, sizeof(virus));
	for (int i = 0; i < m; i++) {
		virus[i] = 1;
	}

	do {
		ok = false;
		queue<Node> q2;
		swap(q, q2);

		memset(v, false, sizeof(v));
		cnt = 0;
		for (int i = 0; i < nIdx; i++) {
			if (virus[i] == 1) {
				q.push(node[i]);
				v[node[i].r][node[i].c] = true;
				cnt += 1;
			}
		}

		cleaning();
		if (ok && ans > timer) ans = timer;
	} while (prev_permutation(virus, virus + nIdx));
}

int main()
{
	freopen("sample_input.txt", "r", stdin);
	cin >> n >> m;
	total = 0; ans = 2500;
	real_ok = false; nIdx = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> a[i][j];
			if (a[i][j] == 0) {
				total += 1;
			}
			else if (a[i][j] == 2) {
				node[nIdx++] = { i,j };
				a[i][j] = 0;
				total += 1;
			}
		}
	}

	play();

	if (real_ok) cout << ans << endl;
	else cout << -1 << endl;
	return 0;
}