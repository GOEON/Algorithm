// 190314
// https://www.acmicpc.net/problem/2251

#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

int Bottle_capacity[3];

typedef struct _bottle {
	int a;
	int b;
	int c;
}Bottle;

bool check[201][201][201];
Bottle bottle;
vector<bool> v(201);
queue<Bottle> q;

void giveWater(int p1, int p2, int w[]) // p1 -> p2
{
	int tw[3]; // temp water 
	for (int i = 0; i < 3; i++) tw[i] = w[i];

	tw[p2] += tw[p1];
	tw[p1] = 0;
	if (tw[p2] > Bottle_capacity[p2]) {
		tw[p1] = tw[p2] - Bottle_capacity[p2];
		tw[p2] = Bottle_capacity[p2];
	}

	if (check[tw[0]][tw[1]][tw[2]] == false) {
		Bottle nb;// new bottle
		nb.a = tw[0];
		nb.b = tw[1];
		nb.c = tw[2];
		q.push(nb);
		check[tw[0]][tw[1]][tw[2]] = true;
		if (tw[0] == 0) v[tw[2]] = true;
	}
}

void water_distribution()
{
	while (!q.empty()) {
		int w[3];
		w[0] = q.front().a;
		w[1] = q.front().b;
		w[2] = q.front().c;
		q.pop();
		
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (i != j) {
					giveWater(i, j, w); // a -> b
				}
			}
		}
	}
}

int main()
{
	int A, B, C;
	scanf("%d %d %d", &A, &B, &C);
	Bottle_capacity[0] = A;
	Bottle_capacity[1] = B;
	Bottle_capacity[2] = C;
	bottle.a = 0;
	bottle.b = 0;
	bottle.c = C;
	check[0][0][C] = true;
	v[C] = true;
	q.push(bottle);
	
	water_distribution();

	for (int i = 0; i <= 200; i++) {
		if (v[i]) printf("%d ", i);
	}
	printf("\n");
	
	return 0;
}