#define _USE_MATH_DEFINES
#include<bits/stdc++.h>
#include"Jtol.h"//Jtol.h v1.7.3.2
using namespace Jtol;
using namespace std;
int WinExample(HINSTANCE hInstance);
/*int main(int argc,char** argv){
    return 0;
    }*/
int key[16]={16,15,7,17,16,1,4,16,8,9,20,11,8,8,13,14};
void run(int k){
    string x1,x2,r1,r2,k1,k2;
    Time t;
    for(int j=1;j<=20;j++){
        printf("~~%d %d~~\n",k,j);
        Net net1=nc("csie.ctf.tw",10132,0);
        auto &str1=nc(net1);
        Net net2=nc("csie.ctf.tw",10132,0);
        auto &str2=nc(net2);
        stringstream stt;
        for(int i=0;i<16;i++){
            string s1,s2;
            t=GetTime();
            while(true)
                if(str1>>s1&&s1.length()>30)break;
                else if(nc_is_closed(net1))goto begin;
                else if(GetTime()-t>5000)goto begin;
            while(true)
                if(str2>>s2&&s2.length()>30)break;
                else if(nc_is_closed(net2))goto begin;
                else if(GetTime()-t>5000)goto begin;
            if(i==k){
                string snd=trim(exec(R"(python a.py )"+ToStr(j)));
                NetSend(net1,snd+"\n");
                NetSend(net2,snd+"\n");
                x1=s1;
                x2=s2;
                }
            else{
                NetSend(net1,s2+"\n");
                NetSend(net2,s1+"\n");
                }
            }
        t=GetTime();
        while(true)
            if(str1>>k1&&k1.length()>30)break;
            else if(nc_is_closed(net1))goto begin;
            else if(GetTime()-t>5000)goto begin;
        while(true)
            if(str2>>k2&&k2.length()>30)break;
            else if(nc_is_closed(net2))goto begin;
            else if(GetTime()-t>5000)goto begin;
        r1=trim(exec(R"(python b.py )"+k1+" "+x1));
        r2=trim(exec(R"(python b.py )"+k2+" "+x2));
        if(r1==r2){
            key[k]=j;
            printf("key%d %d\n",k,j);
            nc_close(net1);
            nc_close(net2);
            break;
            }
        goto end;
        begin:;
        j--;
        end:;
        nc_close(net1);
        nc_close(net2);
        }
    }
void run2(){
    Net net=nc("csie.ctf.tw",10132,0);
    auto &str=nc(net);
    stringstream stt;
    vector<string>ve;
    for(int i=0;i<16;i++){
        string s;
        while(true)
            if(str>>s&&s.length()>30)break;
        string snd=trim(exec(R"(python a.py )"+ToStr(key[i])));
        NetSend(net,snd+"\n");
        ve.push_back(s);
        }
    string k;
    while(true)
        if(str>>k&&k.length()>30)break;
    for(int i=0;i<16;i++)
        k=trim(exec(R"(python b.py )"+k+" "+ve[i]));
    nc_close(net);
    puts(exec("python -c \"y=hex("+k+")[2:];print(''.join([chr(int(''.join(c), 16)) for c in zip(y[0::2],y[1::2])]))\"").c_str());
    }
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wunused-variable"
    int argc=__argc; char** argv=__argv;
    #pragma GCC diagnostic pop
    Setup();

    for(int k=0;k<16;k++)
        run(k);

    for(int k=0;k<16;k++)
        printf("%d ",key[k]);
    puts("");
    run2();
    //HideConsole();
    //Wait(ThreadCreate(WinExample,hInstance));
    //system("pause");
    return 0;
    }
