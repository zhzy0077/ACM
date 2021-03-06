#include <iostream>
#include <cstdio>
#include <algorithm>
#include <hash_map>
using namespace std;
using namespace __gnu_cxx;

#define N 10005
#define M 50005

template <class T>
inline bool getInt(T &x) {
	char c; T sign = 1;
	if ((c = getchar()) == EOF) { return false; }
	while ((c < '0' || c > '9') && c != '-') { c = getchar(); };
	if (c == '-') { sign = -1; c = getchar(); }
	x = c - '0';
	while ((c = getchar()) >= '0' && c <= '9') { x = x * 10 + c - '0'; }
	x *= sign;
	return true;
}

struct Node {
	int a, b;
	bool m;
} edge[N << 1], que[M];
int n, m, q, fa[N], pw[N], ans[M], ansn;
hash_map<int, bool> mp;

void init() {
	mp.clear();
	for (int i = 0; i < n; i++) { fa[i] = i; }
	ansn = 0;
}

int findfa(int n) {
	return n == fa[n] ? n : fa[n] = findfa(fa[n]);
}

void unite(int a, int b) {
	a = findfa(a); b = findfa(b);
	if (a != b) {
		if (pw[a] > pw[b] || (pw[a] == pw[b] && a < b)) { fa[b] = a; }
		else { fa[a] = b; }
	}
}

int main() {
	char c[8];
	bool first = true;
	while (getInt(n)) {
		if (!first) { printf("\n"); }
		first = false;
		init();
		for (int i = 0; i < n; i++) { getInt(pw[i]); }
		getInt(m);
		for (int i = 0; i < m; i++) {
			getInt(edge[i].a); getInt(edge[i].b);
			if (edge[i].a > edge[i].b) { swap(edge[i].a , edge[i].b); }
		}
		getInt(q);
		for (int i = 0; i < q; i++) {
			scanf("%s", c);
			if (c[0] == 'd') {
				getInt(que[i].a); getInt(que[i].b);
				if (que[i].a > que[i].b) { swap(que[i].a , que[i].b); }
				que[i].m = true; mp[que[i].a * N + que[i].b] = true;
			} else {
				getInt(que[i].a);
				que[i].m = false;
			}
		}
		for (int i = 0; i < m; i++) {
			if (!mp[edge[i].a * N + edge[i].b]) {
				unite(edge[i].a, edge[i].b);
			}
		}
		for (int i = q - 1; i >= 0; i--) {
			if (que[i].m) {
				unite(que[i].a, que[i].b);
			} else {
				int t = findfa(que[i].a);
				if (pw[t] <= pw[que[i].a]) { ans[ansn++] = -1; }
				else { ans[ansn++] = t; }
			}
		}
		for (int i = ansn - 1; i >= 0; i--) {
			printf("%d\n", ans[i]);
		}
	}
}
