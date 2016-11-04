#define _USE_MATH_DEFINES
#include<bits/stdc++.h>
#include"Jtol.h" //Jtol.h v1.7.2.2
using namespace Jtol;
using namespace std;
/*int main(int argc,char** argv){
    return 0;
    }*/
Net net;
void Fun0(){
    string s="ofJnFC5PuNItJNBhtGWdB3Bwinou6KYSMzsyGmPNaf1W8YLCiX+j13tSzjCoIUg2CtdHdDTcv0EZ/pi7R6rYk2/o8FOUvv6KFLrqDTe9QZU=";
    //cin>>s;
    StrToFile(DecodeBase64(s),"qq.txt");
    }
void Fun1(){
    net=NetCreat("csie.ctf.tw",10128,0);
    string ret;
    while(true){
        ret=NetGet(net);
        cout<<ret;
        if(ret.find("?")!=string::npos)break;
        }
    string fil=FileToStr("qq.txt");
    string tmp;
    for(int i=0;i<16;i++)
        tmp+='\0';
    string fin;
    for(int z=0;z<5;z++){
        string ans;
        string s=tmp+fil.substr(16*z,16);
        for(int k=0;k<16;k++){
            for(unsigned char i=0;i<=0xFF;i++){
                printf("~~%d~~\n",i);
                string ss=s;
                for(int j=0;j<k;j++){
                    ss[15-j]=((unsigned char)ans[k-j-1])^(1+k);
                    }
                ss[15-k]=i^(1+k);
                ss=EncodeBase64(ss)+"\n";
                cout<<ss;
                re:;
                NetSend(net,ss);
                string r=NetGet(net);
                if(trim(r)!="true"&&trim(r)!="false"){
                    puts("restart");
                    NetClose(net);
                    net=NetCreat("csie.ctf.tw",10128,0);
                    while(true){
                        ret=NetGet(net);
                        cout<<ret;
                        if(ret.find("?")!=string::npos)break;
                        }
                    goto re;
                    }
                else if(trim(r)=="true"){
                    ans=char(i)+ans;
                    cout<<r;
                    break;
                    }
                else
                    cout<<r;
                if(i==0xFF){
                    puts("Fuck");
                    exit(0);
                    break;
                    }
                }
            }
        fin+=ans;
        }
    StrToFile(fin,"final.txt");
    }
void Fun2(){
    string a=FileToStr("qq.txt");
    string b=FileToStr("final.txt");
    a="8whXbWqehnACf6tZ"+a;
    for(int i=0;i<16*5;i++)
        a[i]^=b[i];
    StrToFile(a,"result.txt");
    }
void Fun3(){
    cout<<FileToStr("result.txt")<<endl;
    }
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
    int argc=__argc; char** argv=__argv;
#pragma GCC diagnostic pop
    Setup();
    Fun0();
    Fun1();
    Fun2();
    Fun3();
    return 0;
    }
