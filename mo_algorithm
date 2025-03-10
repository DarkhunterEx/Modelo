#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
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
    vector<long long>xx=v;
    sort(xx.begin(),xx.end());
    vector<pair<long long,long long>>::iterator it;
    long long ind=0;
    for(long long i=0;i<xx.size();i++){
        if(s.size()==0){
            s.push_back(make_pair(xx[i],(long long)0));
        }
        else if(s[ind].first!=xx[i]){
            ind++;
            s.push_back(make_pair(xx[i],(long long)0));
        }
    }
    for(long long i=0;i<v.size();i++){
        it=lower_bound(s.begin(),s.end(),make_pair(v[i],(long long)0));
        v[i]=it-s.begin();
        //cout<<v[i]<<" "<<it->first<<" "<<v.size()<<endl;
    }
    vector<pair<long long,pair<long long,long long>>>p;
    long long resposta[200005];
    for(long long i=0;i<x;i++){
        long long a,b;
        cin>>a>>b;
        p.push_back(make_pair(a-1,make_pair(b-1,i)));
    }
    long long BLOCK_SIZE = sqrt(z);
    sort(p.begin(), p.end(), [BLOCK_SIZE](auto &left, auto &right) {
        long long blockL = left.first / BLOCK_SIZE;
        long long blockR = right.first / BLOCK_SIZE;

        if (blockL != blockR)
            return blockL < blockR;

        return (blockL & 1) ? (left.second.first > right.second.first) : (left.second.first < right.second.first);
    });
    long long cur_l=0;
    long long cur_r=-1;
    long long sum=0;
    long long vt=0;
    for(auto x:p){
        while(cur_l>x.first){
            cur_l--;
            s[v[cur_l]].second++;
            if(s[v[cur_l]].second==1){
                sum++;
            }
        }
        while(cur_r<x.second.first){
            cur_r++;//cout<<v[cur_r]<<endl;
            s[v[cur_r]].second++;
            if(s[v[cur_r]].second==1){
                sum++;
            }
        }
        while(cur_l<x.first){
            s[v[cur_l]].second--;
            if(s[v[cur_l]].second==0){
                sum--;
            }
            cur_l++;
        }
        while(cur_r>x.second.first){
            s[v[cur_r]].second--;
            if(s[v[cur_r]].second==0){
                sum--;
            }
            cur_r--;
        }
        //cout<<x.first<<" "<<x.second.first<<" "<<sum<<endl;
        resposta[x.second.second]=sum;
    }
    //cout<<endl;
    for(long long i=0;i<x;i++){
        cout<<resposta[i]<<endl;
    }
}
