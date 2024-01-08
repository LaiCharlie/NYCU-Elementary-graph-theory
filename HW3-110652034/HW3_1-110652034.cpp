#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <cstring>
#include <map>
#include <sstream>
using namespace std;

#define F first
#define S second

typedef long long ll;
typedef pair<int,int> pii;

struct edge{
    int u;
    int v;
    ll  w;
};

int n, m;
ll  c[100005];
int p[100005];
vector<edge> road;

int findp(int x){
    if(x == p[x])
        return x;
    return (p[x] = findp(p[x]));
}

void join(int x, int y){
    if(findp(x) == findp(y))
        return;
    else
        p[findp(x)] = findp(y);
}

bool cmp(edge a, edge b){
    return a.w < b.w;
}

void solve(){
    sort(road.begin(), road.end(), cmp);
    int edge_num = 0;
    ll  ans = 0;

    for(int i=0; i<road.size(); i++){
        // cout << road[i].u << " , " << findp(road[i].u) << " | " << road[i].v << " , " << findp(road[i].v) << '\n';
        if(findp(road[i].u) == findp(road[i].v))
            continue;

        // cout << road[i].u << ' ' << road[i].v << " | " << ans << '\n';
        join(road[i].u, road[i].v);
        ans += road[i].w;
        edge_num++;
        // cout << road[i].u << ' ' << road[i].v << " | " << ans << '\n';
        if(edge_num == n-1)
            break;
    }

    cout << ans << '\n';
    return;
}

void init(){
    memset(c, 0, sizeof(c));
    road.clear();

    for(int i=0;i<n+3;i++)
        p[i] = i;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    // freopen("in.txt","r",stdin);
    // freopen("out.txt","w",stdout);

    int t;
    cin >> t;
    while(t--){
        cin >> n >> m;
        init();
        c[0] = 10000000000;
        int mni = 0;
        for(int i=0; i<n; i++){
            cin >> c[i+1];
            if(c[i+1] < c[mni])
                mni = i+1;
        }

        for(int i=0; i<m; i++){
            struct edge temp;
            cin >> temp.u >> temp.v >> temp.w;
            if(temp.w < (c[temp.u] + c[temp.v]))
                road.push_back(temp);
        }

        for(int i=0; i<n; i++){
            if((i+1) != mni){
                struct edge temp;
                temp.u = mni;
                temp.v = i+1;
                temp.w = c[mni] + c[i+1];
                road.push_back(temp);
            }
        }

        solve();
    }

    return 0;
}

// 3
// 6 1
// 1 2 1 2 2 2
// 3 5 1
// 6 1
// 2 1 1 2 1 2
// 2 4 1
// 6 0
// 2 2 2 1 2 2