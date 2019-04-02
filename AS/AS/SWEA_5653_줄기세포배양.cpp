// 190402
// https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRJ8EKe48DFAUo&categoryId=AWXRJ8EKe48DFAUo&categoryType=CODE

#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

int ans, T;
int dr[] = { -1,1,0,0 };
int dc[] = { 0,0,-1,1 };

int n, m, k;
bool a[800][800]; // 차지하면 true 

int timer;

typedef struct _cell {
	int r;
	int c;
	int x;
	int p; // 번식
	int t; // 죽는 시간 
}Cell;

bool operator<(Cell c1, Cell c2)
{
	return c1.x < c2.x;
}

priority_queue<Cell> pq;

void play()
{
	timer = 0;
	priority_queue<Cell> pq2;
	while (timer <= k) {
		while (!pq.empty()) {
			Cell tCell = pq.top();
			pq.pop();

			// 번식 
			if (tCell.p == timer) {
				Cell pCell;
				for (int h = 0; h < 4; h++) {
					int nr = tCell.r + dr[h];
					int nc = tCell.c + dc[h];

					if (a[nr][nc]) continue;
					a[nr][nc] = true;
					pCell.r = nr; pCell.c = nc;
					pCell.x = tCell.x;
					pCell.p = timer + tCell.x + 1;
					pCell.t = timer + tCell.x + tCell.x;
					pq2.push(pCell);
				}
			}
			if (tCell.t != timer) pq2.push(tCell);
		}
		timer += 1;
		pq = pq2;
		priority_queue<Cell>().swap(pq2);
	}
	ans = pq.size();
}

int main()
{
	//freopen("sample_input.txt", "r", stdin);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		memset(a, false, sizeof(a));
		ans = 0;
		priority_queue<Cell>().swap(pq);
		cin >> n >> m >> k;
		
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				int life;
				cin >> life;
				if (life == 0) continue;
				a[i + 400][j + 400] = true;
				Cell cell;
				cell.r = i + 400; cell.c = j + 400; cell.x = life;
				cell.p = life + 1; cell.t = life + life;
				pq.push(cell);
			}
		}

		play();

		cout << "#" << tc << " " << ans << '\n';
	}
	return 0;
}