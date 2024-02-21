#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    int k;
    string ch;
    string prev="0";
    bool square;
    for (int i=0;i<n;i++){
        square=false;
        cin>>k;
        
        for (int j=0;j<k;j++){
            cin>>ch;
            if (count(ch.begin(),ch.end(),'1')!=0 && count(ch.begin(),ch.end(),'1')==count(prev.begin(),prev.end(),'1')){
                square=true;
            }
            prev=ch;
        }
        if (square){
            cout<<"SQUARE"<<endl;
        }
        else{
            cout<<"TRIANGLE"<<endl;
        }
    }
    return 0;
}