// 190311
// https://www.acmicpc.net/problem/1525

#include <cstdio>
#include <queue>
#include <cmath>
#include <map>
using namespace std;

int a[9];
int idx;
map<int, int> m;

int swap_idx(int num, int zero, int newZero)
{
	int ret = 0;

	int num9[9];
	for (int i = 0; i < 9; i++) {
		num9[i] = (num / (int)pow(10, 8 - i)) % 10;
	}
	int temp = num9[zero];
	num9[zero] = num9[newZero];
	num9[newZero] = temp;

	for (int i = 0; i < 9; i++) {
		ret += num9[i] * (int)pow(10, 8 - i);
	}
	
	return ret;
}

bool minMove()
{
	int ret;
	queue<pair<int,int>> q; // 숫자, 0위치 
	int sNum = 0;
	for (int i = 8; i >= 0; i--) {
		sNum += a[i] * (int)pow(10, 8 - i);
	}
	m[sNum] = 0;
	q.push(make_pair(sNum, idx));
	while (!q.empty()) {
		int num = q.front().first;
		int zero = q.front().second;
		q.pop();
		// 위
		if (zero - 3 >= 0) {
			int x = swap_idx(num, zero, zero - 3);
			if (m.count(x) == 0) {
				m[x] = m[num] + 1;
				q.push(make_pair(x, zero - 3));
			}
		}
		// 아래
		if (zero + 3 < 9) {
			int x = swap_idx(num, zero, zero + 3);
			if (m.count(x) == 0) {
				m[x] = m[num] + 1;
				q.push(make_pair(x, zero + 3));
			}
		}
		// 좌
		if (zero != 0 && zero != 3 && zero != 6) {
			int x = swap_idx(num, zero, zero - 1);
			if (m.count(x) == 0) {
				m[x] = m[num] + 1;
				q.push(make_pair(x, zero - 1));
			}
		}
		// 우
		if (zero != 2 && zero != 5 && zero != 8) {
			int x = swap_idx(num, zero, zero + 1);
			if (m.count(x) == 0) {
				m[x] = m[num] + 1;
				q.push(make_pair(x, zero + 1));
			}
		}
		if (m.count(123456789) > 0) return true;
	}
	return false;
}

int main()
{
	for (int i = 0; i < 9; i++) {
		scanf("%d", &a[i]);
		if (a[i] == 0) {
			a[i] = 9;
			idx = i;
		}
	}

	if (minMove()) {
		printf("%d\n", m[123456789]);
	}
	else {
		printf("-1\n");
	}

	
	return 0;
}