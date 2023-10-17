#include<bits/stdc++.h>
#include <stdio.h>
#include "string.h"
using namespace std;
#define int long long 
#define ll long long 
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
vector<int> hash1 = {146527, 19260817, 91815541};

vector<int> z_function(string s) {
    int n = (int) s.length();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min (r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}


int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);  
    cout<<setprecision(10)<<fixed;


    int n; cin>>n;
    string s; cin>>s;
    map<int,int> m,mm;
    vector<string> v(n);
    map<int,int> h1[3];


    int val[3] = {0,0,0};
    int po[3] = {1,1,1};
    for(int j=-1 + (int)s.size(); j>=0; --j)
    {
        for(int l=0; l<3; ++l)
        {
            val[l] = val[l] + (po[l]*(s[j]))%M;
            val[l]%=M;
            h1[l][val[l]] = j;
            po[l] =po[l]*hash1[l];
            po[l]%=M;
        }
    }




    for (int i = 0; i < n; ++i)
    {
        cin>>v[i];
        vector<int> pre = z_function(s+'#'+v[i]);
        int m1 = pre.size();
        for(int j=0; j<m1; ++j)
        {
            if(j+pre[j]==m1)
                m[pre[j]]++;
        }

        int val[3] = {00};
        int po[3] = {1,1,1};
        for(int j=0; j<v.size(); ++j)
        {
            map<int,int> tt;
            for(int l=0; l<3; ++l)
            {
                val[l] = val[l] + (po[l]*(v[i][j]))%M;
                val[l]%=M;
                if(h1[l].count(val[l]))
                {
                    tt[h1[l][val[l]]]++;
                }
                po[l] =po[l]*hash1[l];
                po[l]%=M;
            }

            if(tt.size()<=2 && tt.size())
            {
                mm[j+1]++;
            }
        }
        cout<<endl;
    }

    print(mm);


    int si = s.size();
    int ans = m[si]*n + mm[si]*n;


    for (int i = 1; i+1<s.size(); ++i)
    {
        ans+=m[i]*mm[si-i];
    }   

    cout<<ans<<endl;











    return 0;
}       


