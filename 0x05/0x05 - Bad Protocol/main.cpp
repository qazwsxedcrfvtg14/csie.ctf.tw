#define _USE_MATH_DEFINES
#include<bits/stdc++.h>//Jtol.h v1.7.2.3
#include"Jtol.h"
using namespace Jtol;
using namespace std;
/*int main(int argc,char** argv){
    return 0;
    }*/
void Fun0(){
    string key;
    key+=char(0xb0);
    key+=char(0x00);
    key+=char(0x00);
    key+=char(0x00);
    key+=char(0x00);
    key+=char(0x00);
    key+=char(0x00);
    key+=char(0x01);
    key+=char(0xf8);
    string Nc="000000000000000000000000000";
    for(int k=0;;k++){
        Net net=NetCreat("csie.ctf.tw",10129,0);
        string ret;
        while(true){
            ret=NetGet(net);
            cout<<ret;
            if(ret.find(":")!=string::npos)break;
            }
        NetSend(net,"admin||"+Nc+"\n");
        cout<<"admin||"+Nc+"\n";
        ret=NetGet(net);
        if(ret.find("You should send your random str")==string::npos)
            cout<<NetGet(net);
        else
            ret=ret.substr(0,ret.find("You should send your random str"));
        auto ve=split(ret,"||");
        for(string &x:ve)
            cout<<x<<endl;
        string run;
        for(int i=0;i<6;i++){
            run+="0x";
            for(int j=0;j<8;j++)
                run+=(ve[1][i*8+j]);
            run+=(' ');
            }
        puts("");
        Net net2=NetCreat("csie.ctf.tw",10129,0);
        while(true){
            ret=NetGet(net2);
            cout<<ret;
            if(ret.find(":")!=string::npos)break;
            }
        NetSend(net2,"admin||"+ve[0]+"\n");
        cout<<"admin||"+ve[0]+"\n";
        ret=NetGet(net2);
        auto ve2=split(ret,"||");
        for(string &x:ve2)
            cout<<x<<endl;
        string cmd=R"(bash -c "python ./hw5.py )"+run+IntToStr(k)+R"( > res.txt")";
        puts(cmd.c_str());
        system(cmd.c_str());
        ret=FileToStr("res.txt");
        NetSend(net,Nc+key+"||"+ve2[2]+"||"+ret);
        cout<<Nc+"?????????||"+ve2[2]+"||"+ret;
        while(true){
            ret=NetGet(net);
            if(ret=="")break;
            cout<<ret;
            }
        NetClose(net);
        NetClose(net2);
        if(Nc=="")break;
        Nc=Nc.substr(1);
        }
    }
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
    int argc=__argc; char** argv=__argv;
#pragma GCC diagnostic pop
    Setup();
    Fun0();
    return 0;
    }
