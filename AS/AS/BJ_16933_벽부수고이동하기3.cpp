// 190325
// https://www.acmicpc.net/problem/16933

#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

bool ok;
int n, m, k, ans;
int a[1001][1001];
int b[1001][1001]; // 각 지점까지 벽 부순 횟수 저장 

struct XY {
	bool af; // afternoon
	int x;
	int y;
	int cnt; // num of breaking wall 
	int day; // answer
};

void findWay()
{
	bool renight;
	queue<XY> q;
	q.push({ true, 1, 1, 0, 1 });
	b[1][1] = 0;
	
	while (!q.empty()) {
		XY xy = q.front();
		q.pop();
		
		if (xy.y == n && xy.x == m) { // 정답에 도달 
			ok = true;
			ans = xy.day;
			return;
		}
		
		renight = false;

		for (int d = 0; d < 4; d++) {
			int nx = xy.x + dx[d];
			int ny = xy.y + dy[d];

			if (nx < 1 || ny < 1 || nx > m || ny > n) continue;

			if (a[ny][nx] == 0) { // 빈
				if (b[ny][nx] == -1) { // 방문한 적 없다면 
					b[ny][nx] = xy.cnt;
					q.push({ xy.af ? false : true, nx, ny, xy.cnt, xy.day + 1 });
				}
				else if (b[ny][nx] > xy.cnt) { // 방문한 적 있다면 k 값으로
					b[ny][nx] = xy.cnt;
					q.push({ xy.af ? false : true, nx, ny, xy.cnt, xy.day + 1 });
				}
			}
			else { // 벽
				if (xy.cnt < k) { // 부술 수 있음 
					if (xy.af == true) { // 낮
						if (b[ny][nx] == -1) { // 첫 방문
							b[ny][nx] = xy.cnt + 1;
							q.push({ false, nx, ny, xy.cnt + 1, xy.day + 1 });
						}
						else if (xy.cnt + 1 < b[ny][nx]) {
							b[ny][nx] = xy.cnt + 1;
							q.push({ false, nx, ny, xy.cnt + 1, xy.day + 1 });
						}
					}
					else { // 밤
						if (renight == false) {
							q.push({ true, xy.x, xy.y, xy.cnt, xy.day + 1 });
							renight = true;
						}
						else if (xy.cnt < b[ny][nx]) {
							q.push({ true, xy.x, xy.y, xy.cnt, xy.day + 1 });
						}
					}
				}
			}
		}
	}
}

int main()
{
	//freopen("sample_input.txt", "r", stdin);

	ans = 1;
	ok = false;
	memset(b, -1, sizeof(b));
	scanf("%d %d %d", &n, &m, &k);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%1d", &a[i][j]);
		}
	}

	findWay();

	if (ok) printf("%d\n", ans);
	else printf("-1\n");

	return 0;
}