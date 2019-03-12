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
int ground[11][11]; // ��
int a[11][11]; // ��� 
int x, y, z;
int ans;
int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};


priority_queue<Tree> q1; // �� 
queue<Tree> q2; // ����, ��� �Ǵ� ���� ������
queue<Tree> q3; // ����, ���� �ϴ� ������ 

bool operator<(Tree t1, Tree t2)
{
	return t1.age > t2.age;
}


// ������ ������ �ڽ��� ���̸�ŭ ����� �԰�, ���̰� 1 �����Ѵ�.
// ������ ������ ������ �ִ� 1��1 ũ���� ĭ�� �ִ� ��и� ���� �� �ִ�
// �ϳ��� ĭ�� ���� ���� ������ �ִٸ�, ���̰� � �������� ����� �Դ´�
// ����, ���� ����� ������ �ڽ��� ���̸�ŭ ����� ���� �� ���� 
// ������ ����� ���� ���ϰ� ��� �״´�.
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

// �������� ���� ���� ������ ������� ���ϰ� �ȴ�.
// ������ ���� �������� ���̸� 2�� ���� ���� 
// ������ �ִ� ĭ�� ������� �߰��ȴ�. �Ҽ��� �Ʒ��� ������.
void summer()
{
	while (!q2.empty()) {
		Tree victim = q2.front();
		q2.pop();
		ground[victim.r][victim.c] += victim.age / 2;
	}
}

// �������� ������ �����Ѵ�. 
// �����ϴ� ������ ���̰� 5�� ����̾�� �ϸ�, 
// ������ 8���� ĭ�� ���̰� 1�� ������ �����. 
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

// �ܿ￡�� S2D2�� ���� ���ƴٴϸ鼭 ���� ����� �߰��Ѵ�. 
// �� ĭ�� �߰��Ǵ� ����� ���� A[r][c]�̰�, �Է����� �־�����.
void winter()
{
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			ground[i][j] += a[i][j];
}

void investment()
{
	while (k--) {
		// ��
		spring();
		// ����
		summer();
		// ����
		fall();
		// �ܿ�
		winter();
	}
}

// K���� ���� �� ���� ���� ����ִ� 
// ������ ������ ���ϴ� ���α׷��� �ۼ��Ͻÿ�.
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
		scanf("%d %d %d", &x, &y, &z); // z�� ������ ���� 
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