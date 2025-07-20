#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
using ll = long long;
#define mod 1000000007

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //freopen("1.txt","r",stdin);
    //freopen("13.txt","w",stdout);
    vector<pair<long long,long long>>s;
    long long z,x;
    cin>>z>>x;
    //cout<<z<<" "<<x<<endl;
    vector<long long>v;
    for(long long i=0;i<z;i++){
        long long t;
        cin>>t;
        v.push_back(t);
    }
    vector<pair<long long,pair<long long,long long>>>p;
    long long resposta[200005];
    for(long long i=0;i<x;i++){
        long long a,b;
        cin>>a>>b;
        p.push_back(make_pair(a-1,make_pair(b-1,i)));
    }
    long long BLOCK_SIZE = 468;
    sort(p.begin(), p.end(), [BLOCK_SIZE](auto &left, auto &right) {
        long long blockL = left.first / BLOCK_SIZE;
        long long blockR = right.first / BLOCK_SIZE;

        if (blockL != blockR)
            return blockL < blockR;

        return (blockL & 1) ? (left.second.first > right.second.first) : (left.second.first < right.second.first);
    });
    ll sq=448;
    ll bloco[sq+5];
    for(int i=0;i<=sq;i++){
        ll mi=INT_MAX;
        for(int j=sq*i;j<sq*(i+1) and j<z;j++){
            mi=min(v[j],mi);
        }
        bloco[i]=mi;
    }
    ll vm=-1;
    for(int i=0;i<x;i++){
        ll in=p[i].first;
        ll f=p[i].second.first;
        ll atual=0;
        ll mi=INT_MAX;
        while((atual)*sq<in){
            //cout<<"?";
            atual++;
        }
        while(atual*sq>=in and in<=f){
            //cout<<"#";
            mi=min(mi,v[in]);
            in++;
        }
        while((atual+1)*sq<=f and atual*sq<=in){
            //cout<<"!°";
            mi=min(bloco[atual],mi);
            
            atual++;in=atual*sq;
        }
        for(int j=in;j<=f;j++){
            //cout<<"**";
            mi=min(mi,v[j]);
        }
        vm=mi;
        //cout<<i<<endl;
        resposta[p[i].second.second]=mi;
    }
    for(int i=0;i<x;i++){
        cout<<resposta[i]<<endl;
    }
}
