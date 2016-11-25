#include<bits/stdc++.h>
using namespace std;
#define f first
#define s second
typedef pair<char,int>par;
int ar[]={0x000001B2,0x000001C9,0x000001FA,0x000001D3,0x000001C1,0x000001D1,0x0000018E,0x0000017D,0x000001CB,0x000001D1,0x000001D2,0x0000021A,0x0000021E,0x00000222,0x000001D3,0x000001C1,0x000001C5,0x000001CF,0x000001C0,0x0000020B,0x000001C9,0x000001C0,0x000001BA,0x000001C7,0x000001C4,0x00000209,0x00000218,0x000001CF,0x000001CC,0x000001D3,0x000001D2,0x000001C5,0x000001D3,0x000001E3,0x00000174};
int main(){
    /*string s[4];
    while(true){
        for(int i=0;i<4;i++)
            cin>>s[i];
        cout<<",0x";
        for(int i=0;i<4;i++)
            cout<<s[3-i];
        }*/
    int cnt=0x195;
    cout<<"FLAG{";
    queue<char>q;
    q.push('F');
    q.push('L');
    q.push('A');
    q.push('G');
    q.push('{');
    for(int x:ar){
        cnt-=q.front();
        q.pop();
        q.push(x-cnt);
        putchar(x-cnt);
        cnt=x;
        }
	return 0;
    }
