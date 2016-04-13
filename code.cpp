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
pair<point,II> E[N];
vector<point> F[N];
int optF[N],NE[N][10],NY[N][10],MN[N][10],MX[N][10],CNT[N];
double Lamda[N][10],A[N],B[N],T[N][10],STD = 0.2,ans[N][10];
const double PI = acos(-1);
double get(point p,vector<point>& A)
{
	double mn = 1e18;
	for(int i=0;i<SZ(A);i++)
		mn = min(mn,hypot(p.x-A[i].x,p.y-A[i].y));
	return mn;
}
pair<double,double> linearRegression(const std::vector<double>& x, const std::vector<double>& y) {
	const auto n    = x.size();
	const auto s_x  = accumulate(x.begin(), x.end(), 0.0);
	const auto s_y  = accumulate(y.begin(), y.end(), 0.0);
	const auto s_xx = inner_product(x.begin(), x.end(), x.begin(), 0.0);
	const auto s_xy = inner_product(x.begin(), x.end(), y.begin(), 0.0);
	const auto b    = (n * s_xy - s_x * s_y) / (n * s_xx - s_x * s_x);
	const auto a    = (s_y - b * s_x)/n;
	return {a,b};
}
double FF(double x)
{
	double sum = x, value = x;
	for(int i=0;i<100;i++)
	{
		value = (value*x*x/(2*i+1));
		sum += value;
	}
	double ret = 0.5 + (sum / sqrt(2*PI)) * exp(-(x*x)/2);
	return ret;
}
double f(double x, double t)
{
	double ret = exp( - x*x / 2.0);
	ret = ret / (t * sqrt(2*PI) * STD) ;
	return ret;
}
double H(double t,int i,int j)
{
	double x = (log(t) - T[i][j])/STD;
	return f(x,t)/(1 - FF(x));
}
int getCurrentYear()
{
	time_t timenow;
	time(&timenow);
	struct tm *current = localtime(&timenow);
	return current->tm_year+1900;
}
int main(int argc,char* argv[])
{
	//read earthquake data
	freopen(argv[1],"r",stdin);
	int n;si(n);
	//trace(n);
	for(int i=1;i<=n;i++)
	{
		//x y magnitude year
		double x;
		scanf("%lf %lf %lf %d",&E[i].F.x,&E[i].F.y,&x,&E[i].S.S);
		E[i].S.F = floor(x);
	}
	//read fault data
	freopen(argv[2],"r",stdin);
	int m;si(m);
	//trace(n,m);
	for(int i=1;i<=m;i++)
	{
		int x;si(x);
		while(x--)
		{
			point p;
			scanf("%lf %lf",&p.x,&p.y);
			F[i].PB(p);
		}
	}
	//done :)
	for(int i=1;i<=n;i++)
	{
		double mn = 1e18;
		int idx = 0;
		for(int j=1;j<=m;j++)
		{
			double d = get(E[i].F,F[j]);
			if(d < mn)
			{
				mn = d;
				idx = j;
			}
		}
		optF[i]=idx;
	}
	//generate the tables NY and NE
	for(int i=1;i<=m;i++)
		for(int j=0;j<10;j++)
			MN[i][j]=int(1e9),MX[i][j]=-int(1e9);
	for(int i=1;i<=n;i++)
	{
		NE[optF[i]][E[i].S.F]++;
		MN[optF[i]][E[i].S.F] = min(MN[optF[i]][E[i].S.F],E[i].S.S);
		MX[optF[i]][E[i].S.F] = max(MX[optF[i]][E[i].S.F],E[i].S.S);
	}
	for(int i=1;i<=n;i++)
		NY[optF[i]][E[i].S.F] = MX[optF[i]][E[i].S.F] - MN[optF[i]][E[i].S.F] + 1;
	//generate Lambda
	for(int i=1;i<=m;i++)
		for(int j=0;j<10;j++)
			if(NY[i][j] && NE[i][j])
				Lamda[i][j]=(NE[i][j]*1.0)/NY[i][j];
	//do linear regression
	vector<double> x,y;
	for(int j=1;j<=m;j++)
	{
		for(int i=1;i<10;i++)
			if(NY[j][i] && NE[j][i])
			{
				x.PB(i+0.5);y.PB(log(Lamda[j][i]));
				CNT[j]++;
			}
		if(!x.empty() && CNT[j] > 1)
		{
			pair<double,double> temp = linearRegression(x,y);
			A[j]=temp.F;B[j]=temp.S;
		}
		x.clear();y.clear();
	}
	//Re-calculate lamda
	for(int i=1;i<=m;i++)
		for(int j=1;j<10;j++)
			if(NY[i][j] && NE[i][j] && CNT[i]>1)
				Lamda[i][j] = exp(A[i] + B[i]*(j+0.5));
	//calculate T table
	for(int i=1;i<=m;i++)
		for(int j=1;j<10;j++)
			if(NY[i][j] && NE[i][j])
				T[i][j] = 1 / Lamda[i][j];
	//get the answer i.e. number of earthquakes predicted per magnitude per fault 
	int ft = atoi(argv[3]);
	for(int i=1;i<=m;i++)
		for(int j=1;j<10;j++)
			if(NY[i][j] && NE[i][j])
			{
				int st = getCurrentYear() - MX[i][j];
				for(int k = 0; k <= ft; k++)
				{
					int t = st + k;
					ans[i][j] += H(t,i,j);
				}
			}
	for(int i=1;i<=m;i++)
		for(int j=1;j<10;j++)
			ans[i][j]=floor(ans[i][j]);
	//done :)
	//print the output
	for(int j=1;j<10;j++)
	{
		int add = 0;
		for(int i=1;i<=m;i++)
			add += ans[i][j];
		printf("%d %d\n",j,add);
	}
	return 0;
}
