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

int mp[1005][1005];
int od[1005];
int id[1005];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    // freopen("in.txt","r",stdin);
    // freopen("out.txt","w",stdout);

    memset(mp,0,sizeof(mp));
    memset(id,0,sizeof(id));
    memset(od,0,sizeof(od));

    int n,m;
    cin>>n>>m;
    int in,out,wei;
    while(m--){
        cin>>in>>out>>wei;
        od[in]++;
        id[out]++;
        mp[in][out]=wei;
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(j)
                cout<<' ';
            cout<<mp[i+1][j+1];
        }
        cout<<'\n';
    }
    for(int i=0;i<n;i++)
        cout<<id[i+1]<<' '<<od[i+1]<<'\n';

    return 0;
}