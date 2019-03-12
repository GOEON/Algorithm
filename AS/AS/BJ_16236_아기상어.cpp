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

// ũ�Ⱑ �۰� ���� ���� ���� ���ʿ� �ִ� ���̰� top�� �ֵ��� 
priority_queue<Feed> pq_feed; // ����ť 
queue<Shark> q_shark; // ���ť (�̵��� �� �ִ� ��, ũ�� ���� ������ڸ� ����)

int cr, cc, csize, c_eat; // current 
int dr[] = {-1, 0, 0, 1};
int dc[] = {0, -1, 1, 0};

bool operator<(Feed a, Feed b)
{
	if (a.d != b.d) {
		return a.d > b.d; // ��������
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
	// ��� �̵� �˻�� 
	while(true){
		while (!q_shark.empty()) {
			Shark s = q_shark.front();
			q_shark.pop();

			// ���� �˻� 
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
						if (a[nr][nc] == 0) { // �� �� 
							backup.push(ns);
						}
						else { // ����� 
							if (a[nr][nc] < csize) { // ���� 
								Feed f;
								f.r = nr;
								f.c = nc;
								f.size = a[nr][nc];
								f.d = s.d + 1;
								pq_feed.push(f);
							}
							else if (a[nr][nc] == csize) { // �̵� ���� 
								backup.push(ns);
							}
							// else �� ������ 
						}
					}
				}
			}
		}
		if (pq_feed.size() > 0) { // �̵� �� ����
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
		else { // �̵� Ž�� 
			if (backup.size() > 0) {
				q_shark = backup;
				queue<Shark>().swap(backup);
			}
			else { // ��
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

	// ù° �ٿ� �Ʊ� �� ���� ���� ������ ��û���� �ʰ� 
	// ����⸦ ��Ƹ��� �� �ִ� �ð��� ����Ѵ�.
	printf("%d\n", ans);
	return 0;
}