#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <cstring>
#include <map>
#include <queue>
#include <sstream>
using namespace std;

#define F first
#define S second

typedef long long ll;
typedef pair<int,int> pii;

struct e{
    int  nei;
    ll   wei;
    bool operator<(e &cmp){
        return cmp.wei > wei;
    }
};

ll mxw = 1000000000000;

vector<e> edge[200005];
ll disfo[200005];
ll disfn[200005];
ll disff[200005];
int ptho[200005];

void dfso(int node){
    priority_queue<pair<ll,ll>, vector<pair<ll,ll> >, greater<pair<ll,ll> > > q;
    q.push(make_pair(0,node));

    while(!q.empty()){
        auto pp = q.top();
        q.pop();
        
        if(disfo[pp.second] != pp.first)
            continue;

        for(auto i: edge[pp.second]){
            if((disfo[i.nei] > (disfo[pp.second] + i.wei)) && i.nei != node){
                disfo[i.nei] = disfo[pp.second] + i.wei;
                q.push(make_pair(disfo[i.nei], i.nei));
            }
        }
    }
}

void dfsn(int node){
    priority_queue<pair<ll,ll>, vector<pair<ll,ll> >, greater<pair<ll,ll> > > q;
    q.push(make_pair(0,node));

    while(!q.empty()){
        auto pp = q.top();
        q.pop();
        
        if(disfn[pp.second] != pp.first)
            continue;

        for(auto i: edge[pp.second]){
            if((disfn[i.nei] > (disfn[pp.second] + i.wei)) && i.nei != node){
                disfn[i.nei] = disfn[pp.second] + i.wei;
                q.push(make_pair(disfn[i.nei], i.nei));
            }
        }
    }
}

void dfsz(int node){
    priority_queue<pair<ll,ll>, vector<pair<ll,ll> >, greater<pair<ll,ll> > > q;
    q.push(make_pair(0,node));

    while(!q.empty()){
        auto pp = q.top();
        q.pop();
        
        if(disff[pp.second] != pp.first)
            continue;

        for(auto i: edge[pp.second]){
            if((disff[i.nei] > (disff[pp.second] + i.wei)) && i.nei != node){
                disff[i.nei] = disff[pp.second] + i.wei;
                q.push(make_pair(disff[i.nei], i.nei));
            }
        }
    }
}

void solve(){
    int n, m, k;
    cin >> n >> m >> k;
    for(int i=0;i<n+3;i++){
        disfo[i] = mxw;
        disfn[i] = mxw;
        disff[i] = mxw;
        edge[i].clear();
    }
    memset(ptho, 0, sizeof(ptho));

    for(int i=0; i<m; i++){
        int u, v;
        ll  w;
        cin >> u >> v >> w;
        struct e temp;
        temp.nei = u;
        temp.wei = w;
        edge[v].push_back(temp);
    }

    disfn[n] = 0;
    disfo[1] = 0;
    disff[0] = 0;
    dfso(1);

    if(k==1){
        for(int i=1; i<=n; i++){
            if(disfo[i] != mxw)
                cout << disfo[i] <<  ' ';
            else
                cout << "-1 ";
        }
    }

    else if(k==2){
        dfsn(n);
        for(int i=1; i<=n; i++){
            struct e temp;
            temp.nei = i;
            temp.wei = disfo[i] + disfn[i];
            if(temp.wei < mxw)
                edge[0].push_back(temp);
        }
        dfsz(0);
        for(int i=1; i<=n; i++){
            if(disff[i] < mxw)
                cout << disff[i] << ' ';
            else
                cout << "-1 ";
        }
    }

    cout << '\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    // freopen("in.txt","r",stdin);
    // freopen("out.txt","w",stdout);

    int test1, test2;
    cin >> test1 >> test2;
    while(test1--)
        solve();

    return 0;
}

// k = 1 -> A win
// k = 2 -> D win
// if A win : ANS = dis(i -> 1) = (reverse map)dis(1 -> i)
// if D win : ANS = dis(i -> 1) + dis(i -> n) = (reverse map)dis(1 -> i) + dis(n -> i)

// 2 2
// 4 5 1
// 2 3 1
// 3 1 2
// 3 4 3
// 2 4 3
// 2 1 4
// 4 5 2
// 2 3 1
// 3 1 2
// 3 4 3
// 2 4 3
// 2 1 4

// reverse map
// 3 2 1
// 1 3 2
// 4 3 3
// 4 2 3
// 1 2 4

// ANS = 0 3 2 -1
// ANS = -1 6 5 -1



// 2 4
// 4 6 1
// 1 2 2
// 2 1 2
// 2 3 4
// 3 2 4
// 4 2 3
// 2 4 3
// 4 6 2
// 1 2 2
// 2 1 2
// 2 3 4
// 3 2 4
// 4 2 3
// 2 4 3

// reverse map
// 2 1 2
// 1 2 2
// 3 2 4
// 2 3 4
// 2 4 3
// 4 2 3

// ANS = 0 2 6 5
// ANS = 5 5 9 5


// ----------------------
// score 80%

// void dfso(int node){
//     queue<int> q;
//     q.push(node);

//     while(!q.empty()){
//         int pp = q.front();
//         q.pop();

//         for(auto i: edge[pp]){
//             if((disfo[i.nei] > (disfo[pp] + i.wei)) && i.nei != node){
//                 disfo[i.nei] = disfo[pp] + i.wei;
//                 q.push(i.nei);
//             }
//         }
//     }
// }

// void dfsn(int node){
//     queue<int> q;
//     q.push(node);

//     while(!q.empty()){
//         int pp = q.front();
//         q.pop();

//         for(auto i: edge[pp]){
//             if((disfn[i.nei] > (disfn[pp] + i.wei)) && i.nei != node){
//                 disfn[i.nei] = disfn[pp] + i.wei;
//                 q.push(i.nei);
//             }
//         }
//     }
// }

// void dfsz(int node){
//     queue<int> q;
//     q.push(node);

//     while(!q.empty()){
//         int pp = q.front();
//         q.pop();

//         for(auto i: edge[pp]){
//             if((disff[i.nei] > (disff[pp] + i.wei)) && i.nei != node){
//                 disff[i.nei] = disff[pp] + i.wei;
//                 q.push(i.nei);
//             }
//         }
//     }
// }

// ----------------------