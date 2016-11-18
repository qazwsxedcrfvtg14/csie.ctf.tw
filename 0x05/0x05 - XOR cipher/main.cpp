#define _USE_MATH_DEFINES
#include<bits/stdc++.h>//Jtol.cpp v1.7.3.1
#include"Jtol.h"
using namespace Jtol;
using namespace std;
/*int main(int argc,char** argv){
    return 0;
    }*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wunused-variable"
    int argc=__argc; char** argv=__argv;
    #pragma GCC diagnostic pop
    Setup();
    Net net=nc("csie.ctf.tw",10131,0);
    auto &str=nc(net);
    string s;
    while(!nc_is_closed(net)){
        NetSend(net,"\n");
        Sleep(15);
        }
    nc_close(net);
    StrToFile(str.str(),"out.txt");
    stringstream st;
    st<<FileToStr("out.txt");
    vector<string>ve;
    string ss;
    while(getline(st,ss)){
        if(ss[0]=='P')continue;
        else ve.push_back(ss);
        }
    int sz=ve.size();
    vector<int> key;
    auto chk=[](char c){
        if(c>='0'&&c<='9')return 1;
        if(c>='a'&&c<='z')return 1;
        if(c>='a'&&c<='Z')return 1;
        if(c==' '||c=='!'||c=='?'||c=='.'||c=='\n'||c==',')return 1;
        return 0;
        };
    for(int k=0;k<64*2;k+=2){
        int mp[256]={0};
        for(int i=0;i<sz-1;i++){
            int c=hex(ve[i][k])*16+hex(ve[i][k+1]);
            mp[c]++;
            }
        int ma=0,p=0;
        for(int i=0;i<256;i++){
            int score=0;
            for(int j=0;j<256;j++)
                score+=chk(j^i)*mp[j];
            if(score>ma)
                ma=score,p=i;
            }
        key.push_back(p);
        }
    string res;
    for(int i=0;i<sz;i++){
        int len=ve[i].length();
        for(int k=0;k<len;k+=2){
            int c=hex(ve[i][k])*16+hex(ve[i][k+1]);
            res+=c^key[k/2];
            }
        }
    StrToFile(res,"res.txt");
    //HideConsole();
    //Wait(ThreadCreate(WinExample,hInstance));
    //system("pause");
    return 0;
    }
