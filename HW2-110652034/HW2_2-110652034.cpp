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

vector<int> t[300005];
int d[300005];

int farnode = 0;
int fardis  = 0;

void dfs(int now){
    for(int i : t[now]){
        if(d[i] == 0){
            d[i] = d[now] + 1;
            if(d[i] > fardis){
                fardis  = d[i];
                farnode = i;
            }
            dfs(i);
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    // freopen("in.txt","r",stdin);
    // freopen("out.txt","w",stdout);

    int n;
    cin >> n;
    for(int k=1;k<n;k++){
        int i,j;
        cin >> i >> j;
        t[i].push_back(j);
        t[j].push_back(i);
    }
    memset(d,0,sizeof(d));
    dfs(1);
    memset(d,0,sizeof(d));
    dfs(farnode);

    cout << fardis << '\n';

    return 0;
}