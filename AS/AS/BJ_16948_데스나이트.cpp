// 190317
// https://www.acmicpc.net/problem/16948

#include <cstdio>
#include <queue>
#include <map>
using namespace std;

bool ok;
int n, ans, r1, c1, r2, c2;
int dr[] = {-2, -2, 0, 0, 2, 2};
int dc[] = { -1, 1, -2, 2, -1, 1};


void chess()
{
	map<pair<int, int>, int> m;
	queue<pair<int, int>> q;
	q.push({ r1, c1 });
	m.insert({{ r1, c1 }, 1});
	while (!q.empty()) {
		for (int i = q.size(); i--;) {
			auto t = q.front();
			q.pop();

			if (t.first == r2 && t.second == c2) {
				ok = true;
				return;
			}

			for (int k = 0; k < 6; k++) {
				int nr = t.first + dr[k];
				int nc = t.second + dc[k];

				if (0 <= nr && nr < n && 0 <= nc && nc < n) {
					if (m.count({ nr,nc }) == 0) {
						m.insert({ { nr, nc }, 1 });
						q.push({nr, nc});
					}
				}
			}
		}
		ans += 1;
	}
}

int main()
{
	scanf("%d", &n);
	scanf("%d %d %d %d", &r1, &c1, &r2, &c2);

	chess();

	if (ok) printf("%d\n", ans);
	else printf("-1\n");
	return 0;
}