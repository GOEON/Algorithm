// 190226
// https://www.acmicpc.net/problem/9095

#include <cstdio>
using namespace std;

int t, n;

int main()
{
	scanf("%d", &t);

	while (t--) {
		int ans = 0;
		int sum = 0;
		scanf("%d", &n);
		for (int n1 = 1; n1 <= 3; n1++) {
			if (n1 == n) ans += 1;
			for (int n2 = 1; n2 <= 3; n2++) {
				if (n1 + n2 == n) ans += 1;
				for (int n3 = 1; n3 <= 3; n3++) {
					if (n1 + n2 + n3 == n) ans += 1;
					for (int n4 = 1; n4 <= 3; n4++) {
						if (n1 + n2 + n3 + n4 == n) ans += 1;
						for (int n5 = 1; n5 <= 3; n5++) {
							if (n1 + n2 + n3 + n4 + n5 == n) ans += 1;
							for (int n6 = 1; n6 <= 3; n6++) {
								if (n1 + n2 + n3 + n4 + n5 + n6 == n) ans += 1;
								for (int n7 = 1; n7 <= 3; n7++) {
									if (n1 + n2 + n3 + n4 + n5 + n6 + n7 == n) ans += 1;
									for (int n8 = 1; n8 <= 3; n8++) {
										if (n1 + n2 + n3 + n4 + n5 + n6 + n7 + n8 == n) ans += 1;
										for (int n9 = 1; n9 <= 3; n9++) {
											if (n1 + n2 + n3 + n4 + n5 + n6 + n7 + n8 + n9 == n) ans += 1;
											for (int n10 = 1; n10 <= 3; n10++) {
												if (n1 + n2 + n3 + n4 + n5 + n6 + n7 + n8 + n9 + n10 == n) ans += 1;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}

		printf("%d\n", ans);
	}


	return 0;
}