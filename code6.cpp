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


    int n; cin>>n;
    vector<int> v(n);

    for(int i=0; i<n; ++i)
        cin>>v[i];

    vector<int> segtree(4*n,1e18),lazy(4*n,0);

    function<int(int,int,int)> makeseg = [&](int s,int e,int po)
    {

        if(s==e)
            return segtree[po] = v[s];
        return segtree[po] = min(makeseg(s,(s+e)/2,2*po+1),makeseg((s+e)/2+1,e,2*po+2));
    };

    makeseg(0,n-1,0);

    function<void(int,int,int,int,int,int)> changelazy = [&](int s,int e,int ps,int pe,int val,int po)
    {
        if(e<s)
            return ;

        if(lazy[po]!=0)
        {
            segtree[po] += lazy[po];
            if(s!=e)
            {
                lazy[2*po + 1] += lazy[po];
                lazy[2*po + 2] += lazy[po];
            }

            lazy[po] = 0;
        }


        if(e<ps || s>pe){
            return ;
        }

        if(ps<=s && e<=pe)  
        {
            segtree[po] += val;
            if(s!=e)
            {
                lazy[2*po+1] += val;
                lazy[2*po+2] += val;
            }

            return ;
        }

        int mid = (s+e)/2;

        changelazy(s,mid,ps,pe,val,2*po+1);
        changelazy(mid+1,e,ps,pe,val,2*po+2);
        segtree[po] = min(segtree[2*po+1],segtree[2*po+2]);

    };



    function<int(int,int,int,int,int)> getmin = [&](int s,int e,int ps,int pe,int po=0)
    {   
        if(lazy[po]!=0)
        {
            segtree[po] += lazy[po];
            if(s!=e)
            {
                lazy[2*po + 1] += lazy[po];
                lazy[2*po + 2] += lazy[po];
            }

            lazy[po] = 0;
        }


        if(ps<=s && e<=pe){
            return segtree[po];
        }
        if(e<ps || s>pe)
            return (int)(1e18);

        int mid = (s+e)/2;

        return min(getmin(s,mid,ps,pe,2*po+1),getmin(mid+1,e,ps,pe,2*po+2));

    };

    int q; cin>>q;
    while(q--)
    {
        vector<int> tem(3);
        cin>>tem[0]>>tem[1];

        if(cin.peek()!=' ')
        {
            if(tem[0]<=tem[1])
            {
                cout<<getmin(0,n-1,tem[0],tem[1],0);
            }
            else
            {
                cout<<min(getmin(0,n-1,tem[0],n-1,0),getmin(0,n-1,0,tem[1],0));
            }
            cout<<endl;
        }
        else 
        {
            cin>>tem[2];
            if(tem[0]<=tem[1]){
                changelazy(0,n-1,tem[0],tem[1],tem[2],0);
            }
            else{
                changelazy(0,n-1,tem[0],n-1,tem[2],0);
                changelazy(0,n-1,0,tem[1],tem[2],0);
            }
        }

    }

    return 0;
}