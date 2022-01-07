#include<bits/stdc++.h>
#include <stdio.h>
#include "string.h"
using namespace std;
#define int long long 
#define endl '\n' 
#define pb push_back
#define all(x) x.begin(),x.end() 
#define con(s1,s2) strstr(s1.c_str(),s2.c_str())
#define foreach(x,y) for(auto &x:y)
#define allr(x) x.rbegin(),x.rend()
#define sum(a) accumulate(a.begin(), a.end(), (int)0)
#define ff first
#define ss second
#define vi vector<int> 
#define pi pair<int,int>
int M = 998244353;

int32_t main()
{
 
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout<<setprecision(5)<<fixed;

    int t; cin>>t;
    int nu = 0;
    while(t--)
    {
        nu++;
        int n; cin>>n;
        vector<int> v[n];

        for(int i=0; i<n; ++i)
        {
            int m; cin>>m;
            for(int j=0,c; j<m; ++j)
            {
                cin>>c;
                c--;
                v[i].pb(c);
            }
        }

        vector<int> euler,dep,noix(n);

        function<void(int,int)> dfs = [&](int s,int dp)
        {
            noix[s] = euler.size();
            euler.pb(s);
            dep.pb(dp);
            foreach(x,v[s])
            {
                dfs(x,dp+1);
                euler.pb(s);
                dep.pb(dp);
            }
        };

        dfs(0,1);

        vector<vector<int>> table(euler.size(),vector<int> ((int)log2(euler.size())+1));

        for(int i=0; i<euler.size(); ++i){
            table[i][0] = i;
        }

        for(int i=1; i<=(int)log2(euler.size()); ++i)
        {
            for(int j=0; j+(1<<i)<euler.size(); ++j)
            {
                if(dep[table[j+(1<<(i-1))][i-1]]<dep[table[j][i-1]])
                    table[j][i] = table[j+(1<<i-1)][i-1];
                else
                    table[j][i] = table[j][i-1];
            }
        }
        // print(table);

        cout<<"Case "<<nu<<':'<<endl;

        int q; cin>>q;
        while(q--)
        {
            int r,l; cin>>r>>l;
            r--; l--;
            int mi = min(noix[r],noix[l]);
            int mx = max(noix[r],noix[l]);

            // cout<<mi<<" "<<mx<<" ";
            int xx = log2(mx-mi+1);
            if(dep[table[mi][xx]]<dep[table[mx-(1<<xx)+1][xx]])
                cout<<euler[table[mi][xx]]+1<<endl;
            else
                cout<<euler[table[mx-(1<<xx)+1][xx]]+1<<endl;
            // cout<<euler[min(table[mi][xx],table[mx-(1<<xx)+1][xx])]+1<<endl;


        }

    

    }
 
    return 0;
}