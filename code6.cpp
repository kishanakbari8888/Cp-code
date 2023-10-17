#include<bits/stdc++.h>
#include <stdio.h>
#include "string.h"
using namespace std;
// #define int long long 
// #define ll long long 
#define endl '\n' 
#define pb push_back
#define all(x) x.begin(),x.end() 
#define con(s1,s2) strstr(s1.c_str(),s2.c_str())
#define foreach(x,y) for(auto &x:y)
#define allr(x) x.rbegin(),x.rend()
#define sum(a) accumulate(a.begin(), a.end(), (int)0)
#define ff first
#define ss second
#define pi pair<int,int>
int M = 998244353;



int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);  
    cout<<setprecision(10)<<fixed;

    int com = 1;
    int test; cin>>test;
    while(test--)
    {
        int n; cin>>n;
        vector<int> v(n);
     
        for(int i=0; i<n; ++i)
            cin>>v[i];
     
        vector<pair<int,int>> segtree(4*n,{INT_MAX,INT_MIN});
        vector<pair<int,int>> sign(4*n,{INT_MAX,INT_MIN});

        vector<int> lazy(4*n,0);
     
        function<pi(int,int,int)> makeseg = [&](int s,int e,int po)
        {
     
            if(s==e)
                return segtree[po] = {s,s};

            pi p = makeseg(s,(s+e)/2,2*po+1);
            pi pp = makeseg((s+e)/2+1,e,2*po+2);
            pi ans;
            if(v[p.ff]<v[pp.ff])
                ans.ff = p.ff;
            else
                ans.ff = pp.ff;

            if(v[p.ss]<v[pp.ss])
                ans.ss = pp.ss;
            else
                ans.ss = p.ss;

            return segtree[po] = ans;
        };
     
        makeseg(0,n-1,0);
     
        function<void(int,int,int,int,int,int)> changelazy = [&](int s,int e,int ps,int pe,int val,int po)
        {
            if(e<s)
                return ;
     
            if(lazy[po]!=0)
            {
                segtree[po] = {-segtree[po].ss,-segtree[po].ff};
                sign[po] = {!sign[po].ss,!sign[po].ff};
                if(s!=e)
                {
                    lazy[2*po + 1] ^= lazy[po];
                    lazy[2*po + 2] ^= lazy[po];
                }
     
                lazy[po] = 0;
            }
     
     
            if(e<ps || s>pe){
                return ;
            }
     
            if(ps<=s && e<=pe)  
            {
                segtree[po] = {segtree[po].ss,segtree[po].ff};
                sign[po] = {!sign[po].ss,!sign[po].ff};
                if(s!=e)
                {
                    lazy[2*po+1] ^= val;
                    lazy[2*po+2] ^= val;
                }
     
                return ;
            }
     
            int mid = (s+e)/2;
     
            changelazy(s,mid,ps,pe,val,2*po+1);
            changelazy(mid+1,e,ps,pe,val,2*po+2);
            pi p = segtree[2*po+1];
            pi pp = segtree[2*po+2];


            // if(sign[2*po+1].ff==1)
            //     p.ff = -p.ff;
            // if(sign[2*po+1].ss)
            //     p.ss = -p.ss;

            // if(sign[2*po+2].ff==1)
            //     pp.ff = -p.ff;
            // if(sign[2*po+2].ss)
            //     pp.ss = -p.ss;
            
            pi ans;
            if(v[p.ff] - sign[2*po+1].ff*v[p.ff] <v[pp.ff] - sign[2*po+2].ff*v[pp.ff])
                ans.ff = p.ff;
            else
                ans.ff = pp.ff;

            if(v[p.ss] - sign[2*po+1].ss*v[p.ss]<v[pp.ss]- sign[2*po+2].ss*v[pp.ss])
                ans.ss = pp.ss;
            else
                ans.ss = p.ss;

            segtree[po] = ans;
     
        };
     
     
     
        function<pi(int,int,int,int,int)> getmin = [&](int s,int e,int ps,int pe,int po=0)
        {   
            if(lazy[po]!=0)
            {
                segtree[po] = {segtree[po].ss,segtree[po].ff};
                sign[po] = {!sign[po].ss,!sign[po].ff};
                if(s!=e)
                {
                    lazy[2*po + 1] ^= lazy[po];
                    lazy[2*po + 2]^= lazy[po];
                }
     
                lazy[po] = 0;
            }
     
     
            if(ps<=s && e<=pe){
                return segtree[po];
            }
            if(e<ps || s>pe)
                return (pi){-1,-1};
     
            int mid = (s+e)/2;
     
            pi p = getmin(s,mid,ps,pe,2*po+1);
            pi pp = getmin(mid+1,e,ps,pe,2*po+2);

            if(p.ff==-1)
                return pp;
            if(pp.ff==-1)
                return p;


            pi ans;
            if(v[p.ff] - sign[2*po+1].ff*v[p.ff] <v[pp.ff] - sign[2*po+2].ff*v[pp.ff])
                ans.ff = p.ff;
            else
                ans.ff = pp.ff;

            if(v[p.ss] - sign[2*po+1].ss*v[p.ss]<v[pp.ss]- sign[2*po+2].ss*v[pp.ss])
                ans.ss = pp.ss;
            else
                ans.ss = p.ss;

            return ans;

        };


        if(tem[0]<=tem[1])
            {
                cout<<getmin(0,n-1,tem[0],tem[1],0);
            }
            else
            {
                cout<<min(getmin(0,n-1,tem[0],n-1,0),getmin(0,n-1,0,tem[1],0));
            }
            cout<<endl;



        int fans = 0;
        int q; cin>>q;
        while(q--)
        {
            int a,b; cin>>a>>b;
            changelazy(0,n-1,a,b,1,0);
            pi p = getmin(0,n-1,a,b,0);

            


        }
     




    }
    


    return 0;
}       