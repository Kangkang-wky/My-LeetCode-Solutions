#include "../include/help.h"

const int maxx = 5*1e5+5;
int arr[maxx], tree[maxx];
int ans[maxx], cnt;
int n, m;

int lowbit(int x)
{
	return x&(-x);
}

void add(int l,int r,int k)
{
	for(int i=l;i<=n;i+=lowbit(i))
	tree[i]+=k;
	for(int i=r+1;i<=n;i+=lowbit(i))
	tree[i]-=k;
}

int ask(int x)
{
	int tmp=0;
	for(int i=x;i>=1;i=i-lowbit(i))
	tmp+=tree[i];
	return arr[x]+tmp;
}

int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	cin>>arr[i];
	
	int t,x,y,k;
	for(int i=1;i<=m;i++)
	{
		cin>>t;
		if(t==1)
		{
			cin>>x>>y>>k;
			add(x,y,k);
		}
		else
		{
			cin>>x;
			ans[++cnt]=ask(x);
		}
	}
	
	for(int i=1;i<=cnt;i++)
	cout<<ans[i]<<endl;
	
	return 0;
}
