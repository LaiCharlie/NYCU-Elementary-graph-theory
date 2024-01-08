#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <cstring>
#include <map>
#include <sstream>
#include <set>
#include <queue>
using namespace std;

#define F first
#define S second

typedef long long ll;
typedef pair<int,int> pii;

vector<int> t[1000005];
vector<int> joi;
int d[1000005];
int last[1000005];
int joint[1000005];

int farnode = 0;
int fardis  = 0;

void dfs(int now){
    queue<int> q;
    q.push(now);
    while(!q.empty()){
        int idx = q.front();
        q.pop();
        for(int i : t[idx]){
            if(d[i] == 0){
                d[i] = d[idx] + 1;
                last[i] = idx;
                q.push(i);
                if(d[i] > fardis){
                    fardis  = d[i];
                    farnode = i;
                }
            }
        }
    }
}

set<int> pth;
vector<int> p;
void path(int s, int e){
    if(s == e){
        pth.insert(s);
        if(joint[s]==3)
            p.push_back(s);
        // cout << s << '\n';
        return;
    }
    // cout << e << " <- ";
    pth.insert(e);
    if(joint[e]==3)
        p.push_back(e);
    path(s,last[e]);
}

set<int> ddep[1000005];
void depth(int node){
    vector<int> walk;
    for(int i:t[node])
        if(!pth.count(i))
            walk.push_back(i);

    for(int possible : walk){
        int lst = node, now = possible, ret = 1;
        while(t[now].size() > 1){
            ret++;
            for(int i=0;i<2;i++){
                if(t[now][i] != lst){
                    int tmp = now;
                    now = t[now][i];
                    lst = tmp;
                    break;
                }
            }
        }
        ddep[node].insert(ret);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    // freopen("in.txt","r",stdin);
    // freopen("out.txt","w",stdout);

    memset(d,0,sizeof(d));
    memset(last,0,sizeof(last));
    memset(joint,0,sizeof(joint));
    int n;
    cin >> n;
    for(int k=1;k<n;k++){
        int i,j;
        cin >> i >> j;
        t[i].push_back(j);
        t[j].push_back(i);
        joint[i]++;
        joint[j]++;
        if(joint[i]==3) joi.push_back(i);
        if(joint[j]==3) joi.push_back(j);
    }
    int m;
    cin >> m;
    vector<int> key;
    for(int k=0;k<m;k++){
        int i;
        cin >> i;
        key.push_back(i);
    }
    int start = 0;
    dfs(start);

    memset(d,0,sizeof(d));
    start  = farnode;
    fardis = 0;
    dfs(start);

    fardis = 0;
    int farjoi;
    for(auto i:joi){
        if(d[i] > fardis){
            farjoi = i;
            fardis = d[i];
        }
    }

    memset(d,0,sizeof(d));
    start  = farjoi;
    fardis = 0;
    dfs(start);

    fardis = 0;
    for(auto i:joi){
        if(d[i] > fardis){
            farjoi = i;
            fardis = d[i];
        }
    }

    pth.clear();
    p.clear();
    path(start, farjoi);

    for(int i : p){
        depth(i);
        // cout << i << " possible depth = ";
        // for(auto j : ddep[i])
        //     cout << j << ' ';
        // cout << '\n';
    }

    bool ans1 = true;
    for(int i=0;i<m;i++){
        if(!ddep[p[i]].count(key[i]))
            ans1 = false;
    }
    bool ans2 = true;
    for(int i=0;i<m;i++){
        if(!ddep[p[m-i-1]].count(key[i]))
            ans2 = false;
    }
    
    if(ans1 || ans2)
        cout << "YES\n";
    else
        cout << "NO\n";

    return 0;
}

// 14
// 4 13
// 2 5
// 5 8
// 1 11
// 11 7
// 9 2
// 1 13
// 12 0
// 8 1
// 10 6
// 9 6
// 3 9
// 7 12
// 2
// 2 2

// 18
// 1 2
// 2 3
// 3 10
// 10 11
// 3 4
// 4 12
// 12 13
// 13 14
// 4 5
// 5 15
// 5 6
// 6 7
// 7 16
// 16 17
// 7 8
// 8 0
// 8 9
// 5
// 2 3 1 2 1