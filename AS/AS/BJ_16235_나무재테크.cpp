// 190312
// https://www.acmicpc.net/problem/16235

#include <cstdio>
#include <queue>
#include <algorithm>
#include <vector>
#include <cstdlib>
using namespace std;

typedef struct _tree {
	int r;
	int c;
	int age;
}Tree;

int n, m, k;
int ground[11][11]; // 땅
int a[11][11]; // 양분 
int x, y, z;
int ans;
int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};


priority_queue<Tree> q1; // 봄 
queue<Tree> q2; // 여름, 양분 되는 죽은 나무들
queue<Tree> q3; // 가을, 번식 하는 나무들 

bool operator<(Tree t1, Tree t2)
{
	return t1.age > t2.age;
}


// 봄에는 나무가 자신의 나이만큼 양분을 먹고, 나이가 1 증가한다.
// 각각의 나무는 나무가 있는 1×1 크기의 칸에 있는 양분만 먹을 수 있다
// 하나의 칸에 여러 개의 나무가 있다면, 나이가 어린 나무부터 양분을 먹는다
// 만약, 땅에 양분이 부족해 자신의 나이만큼 양분을 먹을 수 없는 
// 나무는 양분을 먹지 못하고 즉시 죽는다.
void spring()
{
	priority_queue<Tree> backup;
	while (!q1.empty())
	{
		Tree t = q1.top();
		q1.pop();
		if (ground[t.r][t.c] - t.age >= 0) {
			ground[t.r][t.c] -= t.age;
			t.age += 1;

			if (t.age % 5 == 0) {
				q3.push(t);
			}
			backup.push(t);
		}
		else {
			q2.push(t);
		}
	}
	q1 = backup;
}

// 여름에는 봄에 죽은 나무가 양분으로 변하게 된다.
// 각각의 죽은 나무마다 나이를 2로 나눈 값이 
// 나무가 있던 칸에 양분으로 추가된다. 소수점 아래는 버린다.
void summer()
{
	while (!q2.empty()) {
		Tree victim = q2.front();
		q2.pop();
		ground[victim.r][victim.c] += victim.age / 2;
	}
}

// 가을에는 나무가 번식한다. 
// 번식하는 나무는 나이가 5의 배수이어야 하며, 
// 인접한 8개의 칸에 나이가 1인 나무가 생긴다. 
void fall()
{
	while(!q3.empty()) {
		Tree parent = q3.front();
		q3.pop();

		for (int h = 0; h < 8; h++) {
			Tree baby;
			baby.r = parent.r + dr[h];
			baby.c = parent.c + dc[h];
			baby.age = 1;
			if (1 <= baby.r && baby.r <= n && 1 <= baby.c && baby.c <= n) {
				q1.push(baby);
			}
		}
	}
}

// 겨울에는 S2D2가 땅을 돌아다니면서 땅에 양분을 추가한다. 
// 각 칸에 추가되는 양분의 양은 A[r][c]이고, 입력으로 주어진다.
void winter()
{
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			ground[i][j] += a[i][j];
}

void investment()
{
	while (k--) {
		// 봄
		spring();
		// 여름
		summer();
		// 가울
		fall();
		// 겨울
		winter();
	}
}

// K년이 지난 후 상도의 땅에 살아있는 
// 나무의 개수를 구하는 프로그램을 작성하시오.
int main()
{
	ans = 0;
	scanf("%d %d %d", &n, &m, &k);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%d", &a[i][j]);
			ground[i][j] = 5;
		}
	}

	Tree temp;
	for (int i = 1; i <= m; i++) {
		scanf("%d %d %d", &x, &y, &z); // z는 나무의 나이 
		temp.r = x;
		temp.c = y;
		temp.age = z;
		
		q1.push(temp);
	}

	investment();
	ans = q1.size();

	printf("%d\n", ans);

	return 0;
}