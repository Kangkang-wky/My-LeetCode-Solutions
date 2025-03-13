#include "../include/help.h"

const int maxx = 5*1e5+5;
int a[maxx], tree[maxx];
int n, m, cnt; int ans[maxx];

int lowbit(int x) {
	return x&(-x);
}

void build() {
	for(int i = 1; i <= n; i++) {
		int lb = lowbit(i);
		for(int j = 1; j < lb; j <<= 1) {
            tree[i] += tree[i - j];
        }
	}
}

void add(int x,int k) {
	for(int i = x; i <= n; i += lowbit(i)) {
        tree[i] += k;
    }
}

int ask(int l,int r)
{
	int sum1 = 0,sum2 = 0;
	for (int i = r;i >= 1; i -= lowbit(i)) {
        sum1 += tree[i];
    }
	for (int i = l - 1; i >= 1; i -= lowbit(i)) {
        sum2 += tree[i];
    } 
	return sum1 - sum2;
}

int main()
{
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
        cin>>tree[i];
    }
	
	// 建立树状数组
	build();
	
	int t, x, y;
	for (int i = 1; i <= m; i++) {
		cin >> t >> x >> y;
		if (t == 1) {
            add(x,y);
        }
		else {
            ans[++cnt] = ask(x,y);
        }
	}
	
	for(int i = 1; i <= cnt; i++) {
        cout << ans[i] << endl;
    }

	return 0;
}
