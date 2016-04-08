//Tanuj Khattar
#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int>   II;
typedef vector< II >      VII;
typedef vector<int>     VI;
typedef vector< VI > 	VVI;
typedef long long int 	LL;

#define PB push_back
#define MP make_pair
#define F first
#define S second
#define SZ(a) (int)(a.size())
#define ALL(a) a.begin(),a.end()
#define SET(a,b) memset(a,b,sizeof(a))

#define si(n) scanf("%d",&n)
#define dout(n) printf("%d\n",n)
#define sll(n) scanf("%lld",&n)
#define lldout(n) printf("%lld\n",n)
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)

#define TRACE

#ifdef TRACE
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1){
	cerr << name << " : " << arg1 << std::endl;
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args){
	const char* comma = strchr(names + 1, ',');cerr.write(names, comma - names) << " : " << arg1<<" | ";__f(comma+1, args...);
}
#else
#define trace(...)
#endif

//FILE *fin = freopen("in","r",stdin);
//FILE *fout = freopen("out","w",stdout);
const int N = int(1e5)+10;
struct point{
	double x,y;
};
point E[N];
vector<point> F[N];
int ans[N]; 
double get(point p,vector<point>& A)
{
	double mn = 1e18;
	for(int i=0;i<SZ(A);i++)
		mn = min(mn,hypot(p.x-A[i].x,p.y-A[i].y));
	return mn;
}
int main(int argc,char* argv[])
{
	//read earthquake data
	freopen(argv[1],"r",stdin);
	int n;si(n);
	//trace(n);
	for(int i=1;i<=n;i++)
		scanf("%lf %lf",&E[i].x,&E[i].y);
	//read fault data
	freopen(argv[2],"r",stdin);
	int m;si(m);
	int cnt=0;
	//trace(n,m);
	for(int i=1;i<=m;i++)
	{
		int x;si(x);cnt+=x;
		while(x--)
		{
			point p;
			scanf("%lf %lf",&p.x,&p.y);
			F[i].PB(p);
		}
	}
	//trace(cnt);
	//done :)
	for(int i=1;i<=n;i++)
	{
		double mn = 1e18;
		int idx = 0;
		for(int j=1;j<=m;j++)
		{
			double d = get(E[i],F[j]);
			if(d < mn)
			{
				mn = d;
				idx = j;
			}
		}
		ans[i]=idx;
	}
	//print the output
	for(int i=1;i<=n;i++)
		dout(ans[i]);
	return 0;
}
