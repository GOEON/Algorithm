// 190328
// https://www.acmicpc.net/problem/16939

#include <iostream>
using namespace std;

int cube[25];
bool ok;

int order[6][8] = { {1,3,5,7,9,11,24,22},
					{2,4,6,8,10,12,23,21},
					{13,14,5,6,17,18,21,22},
					{15,16,7,8,19,20,23,24},
					{3,4,17,19,10,9,16,14}, 
					{1,2,18,20,12,11,15,13}};
bool check()
{
	int cnt = 1;
	int t;
	for (int i = 0; i < 6; i++) {
		for (int j = 2; j <= 4; j++) {
			if (cube[i * 4 + 1] != cube[i * 4 + j]) 
				return false;
		}
	}
	ok = true;
	return true;
}

void play()
{
	for (int k = 0; k < 6; k++) { // 여섯번 돌려서 비교 
		int tmp[8];
		for (int i = 0; i < 8; i++) {
			tmp[i] = cube[order[k][i]];
		}
		for (int i = 0; i < 8; i++) { 
			cube[order[k][(i + 2) % 8]] = tmp[i];
		}
		if (check()) return;
		for (int i = 0; i < 8; i++) { // 제자리
			cube[order[k][i]] = tmp[i];
		}
	}
}

int main()
{
	//freopen("sample_input.txt", "r", stdin);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	for (int i = 1; i <= 24; i++) cin >> cube[i];

	play();

	if (ok) cout << 1 << endl;
	else cout << 0 << endl;
	return 0;
}