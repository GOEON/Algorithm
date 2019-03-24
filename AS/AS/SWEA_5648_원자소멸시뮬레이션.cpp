// 190324
// https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRFInKex8DFAUo&categoryId=AWXRFInKex8DFAUo&categoryType=CODE

#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

int T, ans, n;
int a[4001][4001];
int dx[] = { 0,0,-1,1 };
int dy[] = { -1,1,0,0 };

typedef struct node {
	int x; int y;
	int d; int k;
}Node;

vector<Node> v;

void move()
{
	vector<Node> tv;
	while (!v.empty()) {
		vector<Node>().swap(tv);
		int size = v.size();
		// 이동
		for (int i = 0; i < size; i++) {
			Node temp = v[i];
			a[temp.y][temp.x] = 0;
			temp.x += dx[temp.d], temp.y += dy[temp.d];
			if (0 > temp.x || temp.x > 4000 || 0 > temp.y || temp.y > 4000) {
				v[i].k = 0;
				continue;
			}
			v[i].x = temp.x;
			v[i].y = temp.y;
			a[temp.y][temp.x] += temp.k;
		}
		// 충돌 검사
		for (int i = 0; i < size; i++) {
			Node temp = v[i];
			if (temp.k == 0) continue;
			if (a[temp.y][temp.x] != temp.k) { // 충돌 발생
				ans += a[temp.y][temp.x];
				a[temp.y][temp.x] = 0;
				continue;
			}
			tv.push_back(temp);
		}
		swap(v, tv);
	}
}

int main()
{
	//freopen("sample_input.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		ans = 0;
		memset(a, 0, sizeof(a));
		scanf("%d", &n);
		vector<Node>().swap(v);
		for (int i = 0; i < n; i++) {
			Node nd;
			scanf("%d %d %d %d", &nd.x, &nd.y, &nd.d, &nd.k);
			nd.x += 1000; nd.y *= (-1); nd.y += 1000;
			nd.x *= 2, nd.y *= 2;
			a[nd.y][nd.x] = nd.k;
			v.push_back(nd);
		}
		move();
		printf("#%d %d\n", tc, ans);
	}

	return 0;
}