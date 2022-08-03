#include <bits/stdc++.h>

using namespace std;


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int z;
    //freopen("12.txt","w",stdout);
    //freopen("1.txt","r",stdin);
    while(cin>>z){
        vector<int>A;
        vector<int>p;
        for(int i=0;i<z;i++){
            int x;
            cin>>x;
            A.push_back(x);
        }
        vector<int>LDS(A.size(),0);
        vector<int>LIS(A.size(),0);
        int k=0,lis_end=0;
        vector<int>L(A.size(),0),L_id(A.size(),0);
        p.assign(A.size(),-1);
        int pos;
        for(int j=A.size()-1;j>=0;j--){
            pos=lower_bound(L.begin(),L.begin()+k,A[j])-L.begin();
            L[pos]=A[j];
            L_id[pos]=j;
            p[j]=pos?L_id[pos-1]:-1;
            if(pos==k){
                k=pos+1;
                lis_end=j;
            }
            LDS[j]=pos+1;
        }
        k=0,lis_end=0;
        L.assign(A.size(),0),L_id.assign(A.size(),0);
        p.assign(A.size(),-1);
        pos;
        for(int j=0;j<A.size();j++){
            pos=lower_bound(L.begin(),L.begin()+k,A[j])-L.begin();
            L[pos]=A[j];
            L_id[pos]=j;
            p[j]=pos?L_id[pos-1]:-1;
            if(pos==k){
                k=pos+1;
                lis_end=j;
            }
            LIS[j]=pos+1;
        }
        int m=0;
        for(int i=0;i<A.size();i++){
            m=max(m,min(LIS[i],LDS[i])*2-1);
        }
        cout<<m<<endl;
    }
}
