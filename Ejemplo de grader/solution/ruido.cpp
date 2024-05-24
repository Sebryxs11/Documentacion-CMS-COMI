#include<bits/stdc++.h>
#include "ruido.h"

using namespace std;

#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL)
#define lli long long int
#define vi vector<int>
#define vlli vector<long long int>
#define pii pair<int, int>
#define rep(i, a, b) for(int i = (a); i <= (b); i++)
#define repa(i, a, b) for(int i = (a); i >= (b); i--)
#define repv(x, v) for(auto x : v)
#define debug(x) cout << #x << " = " << x << endl
#define debugsl(x) cout << #x << " = " << x << ", "
#define debugarr(x, a, b) cout << #x << " = ["; rep(i, a, b) cout << x[i] << ", "; cout << "]\n"
#define pb push_back
#define all(a) a.begin(), a.end()
#define nl "\n"

#define INF 2000000000
#define MOD 1000000007
#define MAX 1000000000


vector<int> filtrador_de_ruido_cosmico(string P, vector <int> A){
    vector <int> B;
    string P2;
    P2.push_back(P[0]);
    rep(i, 1, P.size() - 1) {
        if (P[i] == P[i - 1]) P2.push_back('{');
        P2.push_back(P[i]);
    }
    swap(P, P2);
    lli largo = A.size() / P.size();
    lli cnt = 0;
    lli l = 0;
    for(auto v: A){
        if ((v % 27) == P[l] - 'a') B.pb(v);
        ++cnt;
        if (cnt >= largo){
            ++l;
            cnt = 0;
        }
    }
    return B;
}

string mensaje_para_jp(vector <int> C) {
    string P = "";
    lli ult = -1;

    for(auto v: C){
        lli m = v % 27;
        if (m != ult && m != 26) P += (char) (m + 'a');
        ult = m;
    }
    return P;
}
