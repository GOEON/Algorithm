// 190312
// https://www.acmicpc.net/problem/16236

#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;

int ans;
int n;
int a[20][20];
bool visit[20][20];

typedef struct _shark {
	int r;
	int c;
	int d;
}Shark;

typedef struct _feed {
	int r;
	int c;
	int d;
	int size;
}Feed;

Shark shark;

// 크기가 작고 가장 위에 가장 왼쪽에 있는 먹이가 top에 있도록 
priority_queue<Feed> pq_feed; // 먹이큐 
queue<Shark> q_shark; // 상어큐 (이동할 수 있는 곳, 크기 같은 물고기자리 포함)

int cr, cc, csize, c_eat; // current 
int dr[] = {-1, 0, 0, 1};
int dc[] = {0, -1, 1, 0};

bool operator<(Feed a, Feed b)
{
	if (a.d != b.d) {
		return a.d > b.d; // 오름차순
	}
	else {
		if (a.r != b.r) {
			return a.r > b.r; 
		}
		else {
			return a.c > b.c;
		}
	}
}

void babyShark()
{
	queue<Shark> backup;
	// 상어 이동 검사용 
	while(true){
		while (!q_shark.empty()) {
			Shark s = q_shark.front();
			q_shark.pop();

			// 방향 검사 
			for (int k = 0; k < 4; k++) {
				int nr = s.r + dr[k];
				int nc = s.c + dc[k];

				if (0 <= nr && nr < n && 0 <= nc && nc < n) {
					if (visit[nr][nc] == false) {
						visit[nr][nc] = true;
						Shark ns;
						ns.r = nr;
						ns.c = nc;
						ns.d = s.d + 1;
						if (a[nr][nc] == 0) { // 빈 곳 
							backup.push(ns);
						}
						else { // 물고기 
							if (a[nr][nc] < csize) { // 먹이 
								Feed f;
								f.r = nr;
								f.c = nc;
								f.size = a[nr][nc];
								f.d = s.d + 1;
								pq_feed.push(f);
							}
							else if (a[nr][nc] == csize) { // 이동 가능 
								backup.push(ns);
							}
							// else 못 지나감 
						}
					}
				}
			}
		}
		if (pq_feed.size() > 0) { // 이동 후 섭취
			Shark cs;
			cs.r = cr = pq_feed.top().r;
			cs.c = cc = pq_feed.top().c;
			cs.d = 0;
			c_eat += 1;
			ans += pq_feed.top().d;
			if (c_eat == csize) {
				csize += 1;
				c_eat = 0;
			}
			queue<Shark>().swap(q_shark);
			queue<Shark>().swap(backup);
			priority_queue<Feed>().swap(pq_feed);
			q_shark.push(cs);

			a[cr][cc] = 0;
			memset(visit, false, sizeof(visit));
			visit[cr][cc] = true;
		}
		else { // 이동 탐색 
			if (backup.size() > 0) {
				q_shark = backup;
				queue<Shark>().swap(backup);
			}
			else { // 끝
				break;
			}
		}
	}
}

int main()
{
	ans = 0;
	c_eat = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &a[i][j]);
			if (a[i][j] == 9) {
				a[i][j] = 0;
				shark.r = cr = i;
				shark.c = cc = j;
				shark.d = 0;
				csize = 2;
				visit[i][j] = true;
				q_shark.push(shark);
			}
		}
	}

	babyShark();

	// 첫째 줄에 아기 상어가 엄마 상어에게 도움을 요청하지 않고 
	// 물고기를 잡아먹을 수 있는 시간을 출력한다.
	printf("%d\n", ans);
	return 0;
}