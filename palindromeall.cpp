#include <bits/stdc++.h>

using namespace std;

unsigned long long int a[60][60];
string s;

unsigned long long int p(int l,int r){
    if(l>r){
        return 0;
    }
    unsigned long long int i=l;
    unsigned long long int j=r;
    unsigned long long int &ans=a[l][r];
    if(ans!=-1){
        return ans;
    }
    ans=0;
    if(s[l]==s[r])
    return ans=1+p(l+1,r)+p(l,r-1);
    return ans=p(l+1,r)+p(l,r-1)-p(l+1,r-1);
}

int main(){
    unsigned long long int z;
    cin>>z;
    for(int i=0;i<z;i++){
        memset(a,-1,sizeof a);
        cin>>s;
        cout<<p(0,s.size()-1)<<endl;
    }
}
