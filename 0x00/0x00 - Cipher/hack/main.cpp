#include<bits/stdc++.h>
#include"Jtol.h"
#include"md5.h"
#define f first
#define s second
using namespace Jtol;
using namespace std;
void HtmlExample();
void NetExample();
void SNetExample();
void ColExample();
void CheatExample();
void Control();
void ControlServer();
void WOT();
void SAI();
void KalisinBMA();
int WinExample(HINSTANCE hInstance);

int sqrt16(int x,int n=0){
    if(n)return sqrt(sqrt16(x,n-1))*16;
    return sqrt(x)*16;
    }

int avg(int x,int y=255,int v1=1,double v2=1){
    return (x*v1+y*v2)/(v1+v2);
    }
void ArtClass(){
    auto v=Dir("D:\\Downloads\\artclass2");
    /*random_shuffle(v.begin(),v.end());
    random_shuffle(v.begin(),v.end());
    for(string &x:v)*/
    string x="D:\\Downloads\\FB.bmp";
        if(x[x.length()-1]=='p'){
            string fil;
            cout<<x<<endl<<"  ";
            BMP pic=ReadBMP(x);
            int w=pic.size(),h=pic[0].size();
            fil+=IntToStr(w-1)+" "+IntToStr(h-1)+"\n";
            for(int i=1;i<w;i++){
                for(int j=1;j<h;j++){
                    if(j!=1)fil+=" ";
                    fil+=IntToStr(pic[i][j].R)+" "+IntToStr(pic[i][j].G)+" "+IntToStr(pic[i][j].B);
                    }
                fil+="\n";
                }
            x[x.length()-3]='i';
            x[x.length()-2]='n';
            x[x.length()-1]=0;
            StrToFile(fil,x.c_str());
            }
    }
string wget(string host,int port=80,string place="/"){
    //printf("%s %d\n",host.c_str(),port);
    Net net=NetCreat(host.c_str(),port);
    if(!net)return "";
    string str;
    str+="GET "+place+" HTTP/1.1\n";
    str+="Accept: text/html, application/xhtml+xml, */*\n";
    str+="Accept-Language: zh-Hant-TW,zh-Hant\n";
    str+="User-Agent: Jtol/1.0 (Windows NT 6.3; WOW64;)\n";
    str+="Accept-Encoding: identity\n";
    str+="Host: m.agar.io\n";
    str+="Connection: Keep-Alive\n\n";
    NetSend(net,&str[0]);
    //Sleep(3000);
    Time tim=GetTime();
    string get;
    while(GetTime()-tim<500){
        const char *buf=NetGet(net);
        if(strlen(buf)){
            get+=buf;
            tim=GetTime();
            }
        }
    return get;
    }

void Agar(){
    //putst(wget("m.agar.io"));
    }
bool exi=0;
int de=0,de2;
Time t;

void CK(int key,int t=50){
    keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
    Sleep(t);
    keybd_event(key, 0, 0, 0);
    }
double v=0.60;
double spdt=0;
int spdnt;
std::mutex mtx;
deque<double>dq;
int L=310,R=570,H=615;
bool splock=0;
void OUSOwO2(int px,char key){
    while(1){
        //Background_Update_Screen_Lock.read_lock();
        for(int i=R;i>=L;i--){
            if(GetColFast(px,i).L()>100&&GetColFast(px,i+1).L()<=10){
                if(i<350&&!splock){
                    int j;
                    Time pt=GetTime();
                    while(1){
                        for(j=R;j>=L;j--)
                            if(GetColFast(px,j).L()>100)
                                break;
                        if((j-i)>50&&i!=j)break;
                        Delay(1);
                        }
                    Time tt=GetTime();
                    double sp=1.0*(j-i)/(tt-pt);
                    if(pt!=tt&&sp>0.1&&sp<1.5){
                        mtx.lock();
                        dq.push_back(sp);
                        if(dq.size()>5)dq.pop_front();
                        double tot=0,ma=-9999,mi=9999;
                        for(auto tmp:dq)
                            tot+=tmp,ma=max(tmp,ma


                            ),mi=min(tmp,mi);
                        int sz=dq.size();
                        mtx.unlock();
                        if(sz>=3)sz-=2,tot-=ma+mi;
                        v=(v+(tot/sz))/2;
                        //v=(v+sp)/2;
                        }
                    i=j;
                    }
                break;
                }
            }
        //Background_Update_Screen_Lock.unlock();
        Delay(1);
        if(exi)return;
        }
    }
void OUSOwO(int px,char key){
    ThreadCreate(OUSOwO2,px,key);
    map<Time,int>qu;
    while(1){
        t=GetTime();
        int fis=1;
        Background_Update_Screen_Lock.read_lock();
        for(int i=L;i<=R;i++){
            if(GetColFast(px,i).L()>100&&GetColFast(px,i+1).L()<=100){
                bool ok=1;
                auto it=qu.upper_bound(t+(H-i)/v);
                if(it!=qu.begin()){
                    auto it2=it--;
                    int tmp=it->f;
                    if((t+(H-i)/v)-tmp<max(30/v,100.0))ok=0;
                    it++;
                    }
                if(it!=qu.end()){
                    int tmp=it->f;
                    if(tmp-(t+(H-i)/v)<max(30/v,100.0))ok=0;
                    }
                if(ok)
                    qu.insert(make_pair(t+(H-i)/v,1));
                }
            }
        Background_Update_Screen_Lock.unlock();
        t=GetTime();
        while(!qu.empty()&&qu.begin()->f<=t+10){
            qu.erase(qu.begin());
            ThreadCreate(CK,key,20);
            }
        Delay(1);
        if(exi)return;
        }
    }
void OSU(){
    Move(600,600);
    //scanf("%d%d",&de,&de2);
    //ThreadCreate(Beep,800,1000);
    bool go=0;
    queue<pair<Time,char>>qu;
    Thread S=NULL,D=NULL,F=NULL,E=NULL,J=NULL,K=NULL,L=NULL;
    while(1){
        if(Key('H')){
            Pos p=GetPos();
            Color coll=GetColFast(p);
            printf("%d %d %d %d %d\n",p.f,p.s,coll.R,coll.G,coll.B);
            }
        if(go){
            if(Key('Q'))
                H--;
            if(Key('W'))
                H++;
            if(Key('V')){
                splock=!splock;
                }
            }
        if(Key('G')){
            go=!go;
            if(go){
                exi=0;
                spdt=0;

                S=ThreadCreate(OUSOwO,540,'S');
                D=ThreadCreate(OUSOwO,594,'D');
                F=ThreadCreate(OUSOwO,648,'F');
                E=ThreadCreate(OUSOwO,702,' ');
                J=ThreadCreate(OUSOwO,756,'J');
                K=ThreadCreate(OUSOwO,811,'K');
                J=ThreadCreate(OUSOwO,867,'L');

                puts("On");
/*
                K=ThreadCreate(OUSOwO,784,'K');
                J=ThreadCreate(OUSOwO,729,'J');
                F=ThreadCreate(OUSOwO,675,'F');
                D=ThreadCreate(OUSOwO,617,'D');
*/
                }
            else{
                puts("Off"),exi=1;
                if(S)Wait(S);S=NULL;
                if(D)Wait(D);D=NULL;
                if(F)Wait(F);F=NULL;
                if(E)Wait(E);E=NULL;
                if(J)Wait(J);J=NULL;
                if(K)Wait(K);K=NULL;
                if(L)Wait(L);L=NULL;
                }
            }
        if(Key('E')){
            exi=1;
            if(S)Wait(S);S=NULL;
            if(D)Wait(D);D=NULL;
            if(F)Wait(F);F=NULL;
            if(E)Wait(E);E=NULL;
            if(J)Wait(J);J=NULL;
            if(K)Wait(K);K=NULL;
            if(L)Wait(L);L=NULL;
            /*
            if(K)Wait(K);
            if(J)Wait(J);
            if(F)Wait(F);
            if(D)Wait(D);
            */
            break;
            }
        Sleep(1);
        }
    }
std::string& trim(std::string &s)
{
    if (s.empty())
        return s;
    s.erase(0,s.find_first_not_of(" "));
    s.erase(s.find_last_not_of(" ") + 1);
    return s;
}
string make_line(string s){
    string ss;
    for(auto &x:s)
        if(x=='\\')ss+="\\\\";
        else if(x=='\"')ss+="\\\"";
        else ss+=x;
    return ss;
    }
string make_linux_path(string s){
    s=FileFullName(s);
    string ss="/";
    int len=s.length();
    for(int i=0;i<len;i++)
        if(s[i]=='\\')ss+='/';
        else ss+=s[i];
    return "\""+ss+"\"";
    }
string FileArg(string s){
    trim(s);
    //cout<<s<<endl;
    if(s=="<")return s;
    if(s==">")return s;
    if(s=="2>")return s;
    if(s=="1>")return s;
    //if(s.find(".")!=string::npos)
        //return make_linux_path(s);
    if(FileExists(s.c_str()))
        return make_linux_path(s);
    return s;
    }
string FG(string s){
    if(s=="<")return s;
    if(s==">")return s;
    if(s=="2>")return s;
    if(s=="1>")return s;
    if(FileExists(s.c_str()))
        return make_linux_path(s);
    string ss,tmp;
    int len=s.length();
    bool ins=0,inb=0;
    for(int i=0;i<len;i++){
        if((inb||ins)&&s[i]=='\\')tmp+=s[i],tmp+=s[i+1],i++;
        else if((!inb&&!ins)&&s[i]==' '){
            if(tmp!="")
                ss+=FileArg(tmp);
            ss+=" ";
            tmp="";
            }
        else if(s[i]=='"'&&!ins)inb^=inb;
        else if(s[i]=='\''&&!inb)ins^=ins;
        else tmp+=s[i];
        }
    if(ins|inb){puts("phase error");exit(0);}
    if(tmp!="")
        ss+=FileArg(tmp);
    return ss;
    }

struct MatchPathSeparator
{
    bool operator()( char ch ) const
    {
        return ch == '\\' || ch == '/';
    }
};
std::string basename( std::string const& pathname ){
    return std::string(
        std::find_if( pathname.rbegin(), pathname.rend(),
                      MatchPathSeparator() ).base(),
        pathname.end() );
}

static const std::string base64_chars =
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";
std::string base64_encode(unsigned char const* , unsigned int len);
std::string base64_decode(std::string const& s);

static inline bool is_base64(unsigned char c) {
  return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len) {
  std::string ret;
  int i = 0;
  int j = 0;
  unsigned char char_array_3[3];
  unsigned char char_array_4[4];

  while (in_len--) {
    char_array_3[i++] = *(bytes_to_encode++);
    if (i == 3) {
      char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
      char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
      char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
      char_array_4[3] = char_array_3[2] & 0x3f;

      for(i = 0; (i <4) ; i++)
        ret += base64_chars[char_array_4[i]];
      i = 0;
    }
  }

  if (i)
  {
    for(j = i; j < 3; j++)
      char_array_3[j] = '\0';

    char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
    char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
    char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
    char_array_4[3] = char_array_3[2] & 0x3f;

    for (j = 0; (j < i + 1); j++)
      ret += base64_chars[char_array_4[j]];

    while((i++ < 3))
      ret += '=';

  }

  return ret;

}

std::string base64_decode(std::string const& encoded_string) {
  int in_len = encoded_string.size();
  int i = 0;
  int j = 0;
  int in_ = 0;
  unsigned char char_array_4[4], char_array_3[3];
  std::string ret;

  while (in_len-- && ( encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
    char_array_4[i++] = encoded_string[in_]; in_++;
    if (i ==4) {
      for (i = 0; i <4; i++)
        char_array_4[i] = base64_chars.find(char_array_4[i]);

      char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
      char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
      char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

      for (i = 0; (i < 3); i++)
        ret += char_array_3[i];
      i = 0;
    }
  }

  if (i) {
    for (j = i; j <4; j++)
      char_array_4[j] = 0;

    for (j = 0; j <4; j++)
      char_array_4[j] = base64_chars.find(char_array_4[j]);

    char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
    char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
    char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

    for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
  }

  return ret;
}
string text;
string fnd(string s){
    for(int i=0;i<text.length();i++){
        bool ok=true;
        for(int j=0;j<s.length();j++){
            if(s[j]!='_'&&s[j]!=text[i+j]){
                if(!(s[j]=='^'&&((text[i+j]>='a'&&text[i+j]<='z')||(text[i+j]>='A'&&text[i+j]<='Z')))){
                    ok=false;
                    break;
                    }
                }
            }
        if(ok)return text.substr(i,s.length());
        }
    return s;
    }
string stage0(string s){
    string ss;
    int x,len=s.length();
    for(int i=0;i+1<len;i+=2)
        sscanf(s.substr(i,2).c_str(),"%2x",&x),ss+=x;
    return ss;
    }
vector<int> stagex(string s){
    vector<int> ss;
    int x,len=s.length();
    for(int i=0;i+1<len;i+=2)
        sscanf(s.substr(i,2).c_str(),"%2x",&x),ss.push_back(x);
    return ss;
    }
string stage2(string s){
    map<char,char>mp;
    mp['a']='z';
    mp['b']='y';
    mp['c']='x';
    mp['d']='w';
    mp['e']='v';
    mp['f']='u';
    mp['g']='t';
    mp['h']='s';
    mp['i']='r';
    mp['j']='q';
    mp['k']='p';
    mp['l']='o';
    mp['m']='n';
    mp['n']='m';
    mp['o']='l';
    mp['p']='k';
    mp['q']='j';
    mp['r']='i';
    mp['s']='h';
    mp['t']='g';
    mp['u']='f';
    mp['v']='e';
    mp['w']='d';
    mp['x']='c';
    mp['y']='b';
    mp['z']='a';
    string ss;
    for(int i=0;i<s.length();i++)
        if(s[i]>='A'&&s[i]<='Z')
            ss+=mp[s[i]-'A'+'a']-'a'+'A';
        else if(s[i]>='a'&&s[i]<='z')
            ss+=mp[s[i]];
        else
            ss+=s[i];
    return ss;
    }
string stage3(string s,string m0,string c0){
    //cout<<endl<<m0<<endl<<c0<<endl;
    int d=0;
    map<char,char>mp;
    for(int i=0;i<c0.length();i++)
        if((c0[i]>='A'&&c0[i]<='Z')||(c0[i]>='a'&&c0[i]<='z')){
            d=m0[i]-c0[i];
            break;
            }
    if(d<0)d+=26;
    string ss;
    for(int i=0;i<s.length();i++)
        if(s[i]>='A'&&s[i]<='Z')
            ss+=(s[i]-'A'+d)%26+'A';
        else if(s[i]>='a'&&s[i]<='z')
            ss+=(s[i]-'a'+d)%26+'a';
        else
            ss+=s[i];
    return ss;
    }
string stage4(string s,string m0,string c0){
    //cout<<endl<<m0<<endl<<c0<<endl;
    string ss;
    for(int i=0;i<s.length();i++)
        if(s[i]>='A'&&s[i]<='Z')
            ss+="^";
        else if(s[i]>='a'&&s[i]<='z')
            ss+="^";
        else
            ss+=s[i];
    return fnd(ss);
    /*
    deque<int>ve;
    for(int i=0;i<c0.length();i++)
        if((c0[i]>='A'&&c0[i]<='Z')||(c0[i]>='a'&&c0[i]<='z'))
            ve.push_back((m0[i]-c0[i]+26)%26);
    puts("");
    string ss;
    for(int i=0;i<s.length();i++)
        if(s[i]>='A'&&s[i]<='Z')
            ss+=(s[i]-'A'+ve.front())%26+'A',ve.pop_front();
        else if(s[i]>='a'&&s[i]<='z')
            ss+=(s[i]-'a'+ve.front())%26+'a',ve.pop_front();
        else
            ss+=s[i];
    return ss;*/
    }

string stage5(string s_in,string m0,string c0s,string m1,string c1s,string m2,string c2s){
    vector<int>c0=stagex(c0s);
    vector<int>c1=stagex(c1s);
    vector<int>c2=stagex(c2s);
    vector<int>s=stagex(s_in);
    string ss;
    for(int i=0;i<s.size();i++)
        if(s[i]==c0[i])
            ss+=m0[i];
        else if(s[i]==c1[i])
            ss+=m1[i];
        else if(s[i]==c2[i])
            ss+=m2[i];
        else
            ss+='_';
    return fnd(ss);
    }
string fnd2(vector<int> v,int n){
    for(int i=0;i<text.length();i++){
        bool ok=true;
        vector<int>cnt(256);
        for(int j=0;j<n;j++){
            if((++cnt[text[i+j]])>v[text[i+j]]){
                ok=false;
                break;
                }
            }
        if(ok)return text.substr(i,n);
        }
    return "~~~~~~";
    }

string stage6(string s){
    vector<int>v(256);
    for(int i=0;i<s.length();i++)
        v[s[i]]++;
    return fnd2(v,s.length());
    }
void pras(string s,string mat,string &res){
    if(s.find(mat)!=-1){
        s=s.substr(s.find(mat)+mat.length());
        res=s.substr(0,s.find("\n"));
        }
    }
bool getS_run=true;
string getS_res;
void getS(string md){
    string ss;
    map<string,int>mp;
    while(getS_run){
        ss="";
        int k=rand()%5+15;
        for(int i=0;i<k;i++)
            ss+=rand()%26+'a';
        string res=md5(ss).substr(0,md.length());
        //cout<<md<<"   "<<res<<"   "<<ss<<endl;
        if(res==md){
            getS_run=false;
            getS_res=ss;
            }
        }
    }
int main(int argc,char** argv){
    srand(time(0));
    text=FileToStr("text.txt");
    //cout<<text;
    //return 0;
    Net net=NetCreat("csie.ctf.tw",10124,1);
    NetSend(net,"\0");
    int cnt=0;
    string m0,c0,m1,c1,m2,c2,c3,md;
    while(true){
        string s=NetGet(net);
        cout<<s;
        pras(s,"m0 = ",m0);
        pras(s,"m1 = ",m1);
        pras(s,"m2 = ",m2);
        pras(s,"c0 = ",c0);
        pras(s,"c1 = ",c1);
        pras(s,"c2 = ",c2);
        pras(s,"c3 = ",c3);
        pras(s,"MD5(m) = ",md);
        int posR=s.find("Round"),posC=s.find("c1 = ");
        if(posR==-1&&posC==-1&&s.find("c3 = ")==-1)continue;
        if(posR!=-1){
            s=s.substr(posR);
            s=s.substr(s.find(":")+2);
            }
        else if(posC!=-1){
            s=s.substr(posC+5);
            s=s.substr(0,s.find("\n"));
            }
        s=trim(s);
        if(cnt<3){
            string ss=stage0(s);
            ss+="\n";
            cout<<ss;
            NetSend(net,ss);
            }
        else if(cnt<6){
            string ss=base64_decode(s);
            ss+="\n";
            cout<<ss;
            NetSend(net,ss);
            }
        else if(cnt<7){
            string ss=stage2(s);
            ss+="\n";
            cout<<ss;
            NetSend(net,ss);
            }
        else if(cnt<8){
            string ss=stage3(s,m0,c0);
            ss+="\n";
            cout<<ss;
            NetSend(net,ss);
            }
        else if(cnt<9){
            string ss=stage4(s,m0,c0);
            ss+="\n";
            cout<<ss;
            NetSend(net,ss);
            }
        else if(cnt<10){
            string ss=stage5(c3,m0,c0,m1,c1,m2,c2);
            ss+="\n";
            cout<<ss;
            NetSend(net,ss);
            }
        else if(cnt<11){
            string ss=stage6(c1);
            ss+="\n";
            cout<<ss;
            NetSend(net,ss);
            }
        else if(cnt<15){
            Thread t[16];
            getS_run=true;
            for(int i=0;i<16;i++)
                t[i]=ThreadCreate(getS,md);
            for(int i=0;i<16;i++)
                Wait(t[i]);
            string ss=getS_res;
            ss+="\n";
            cout<<ss;
            NetSend(net,ss);
            }
        else{
            string ss;
            getline(cin,ss);
            ss+="\n";
            NetSend(net,ss);
            }
        cnt++;
        }
    return 0;
    }
/*
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
    int argc=__argc; char** argv=__argv;
    Setup();
    //Wait(ThreadCreate(WinExample,hInstance));
    //CheatExample();
    WOT();
    //SAI();
    }
int WinExample(HINSTANCE hInstance){
    WinCreat(hInstance,
        [](HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)->LRESULT{
            HDC hDC;
            PAINTSTRUCT ps;
            switch(msg){
                case WM_PAINT:
                    hDC = BeginPaint(hWnd, &ps);
                    EndPaint(hWnd, &ps);
                    return 0;
                case WM_DESTROY:
                    PostQuitMessage(0);
                    return 0;
                }
            return DefWindowProc(hWnd, msg, wParam, lParam);
            }
        );
    MSG msg;
	while(GetMessage(&msg,NULL,0,0)){
	    TranslateMessage(&msg);
		DispatchMessage(&msg);
        }
	return (int)msg.wParam;
    }
*/
string Content(string s){
    return "Content-Length: "+IntToStr(s.length())+"\r\n\r\n"+s;
    }
string JsonGetObj(string &s,string fnd){
    size_t x=s.find(fnd);
    if(x==string::npos)return "";
    int a=0,b=0,len=s.length();
    for(int i=x;i<len;i++)
        if(s[i]==':')a=i;
        else if(s[i]==','||s[i]=='}'){b=i;break;}
    string ret;
    if(s[a+1]=='"')
        ret=s.substr(a+2,b-a-1-2);
    else
        ret=s.substr(a+1,b-a-1);
    return ret;
    }
string JsonGetCardID(string &s,string fnd){
    size_t x=s.find(fnd);
    if(x==string::npos)return "";
    string ss=s.substr(x-25,s.length()-x+25);
    string ret=JsonGetObj(ss,"uniqid");
    s=s.substr(x+1,s.length()-x-1);
    return ret;
    }
string key_main;
string UserID;
string uuid;
void relogin();
pair<string,string> kalisin(string path,string snd="",int dcnt=0){
    Net net=NetCreat("app.kairisei-ma.jp",80);
    while(!net){
        net=NetCreat("app.kairisei-ma.jp",80);
        }
    string str;
    str+="POST "+path+" HTTP/1.1\r\n";
    str+="User-Agent: Jtol/1.0 (Linux; U; Android 4.2.2; Droid4X-WIN Build/JDQ39E)\r\n";
    str+="Host: app.kairisei-ma.jp\r\n";
    str+="Connection: Keep-Alive\r\n";
    str+="Content-Type: application/x-www-form-urlencoded\r\n";
    str+=Content(key_main+snd);
    NetSend(net,str.c_str());
    Time tim=GetTime();
    string get;
    while(GetTime()-tim<300||get==""){
        const char *buf=NetGet(net);
        if(GetTime()-tim>2000)break;
        if(strlen(buf)){
            get+=buf;
            //printf("~$~");
            //for(int i=0;buf[i];i++)
                //printf("%c %d\n",buf[i],buf[i]);
            //printf("%s",buf);
            tim=GetTime();
            }
        }
    Node http=HttpDecode(get);
    if(http.Type["Transfer-Encoding"]=="chunked"){
        crope cont=http.Type["HTML"].c_str();
        http.Type["HTML"]="";
        while(cont.size()){
            string code;
            int i=0;
            for(;cont[i];i++){
                if(cont[i]=='\n'){
                    i++;
                    break;
                    }
                }
            int num;
            sscanf(cont.substr(0,i).c_str(),"%x",&num);
            //printf("~~~\n",cont.substr(0,i).c_str());
            http.Type["HTML"]+=cont.substr(i,num).c_str();
            cont.erase(0,i+num+2);
            }
        }
    //printf("Key: %s\n",key_main.c_str());
    if(http.Type["HTML"].length()<=1){
        cout<<"Key Error!"<<endl;
        if(dcnt>=5)
            relogin();
        return kalisin(path,snd,dcnt+1);
        }
    string nk=http.Type["HTML"].substr(0,30);
    if(nk!=key_main&&nk[0]!='{'){
        key_main=nk;
        }
    int len=http.Type["HTML"].length(),a=-1,b=len;
    int cnt=0;
    for(int i=30;i<len;i++){
        if(http.Type["HTML"][i]=='}'){
            cnt--;
            if(!cnt)a=i;
            }
        else if(http.Type["HTML"][i]=='{'){
            if(!cnt&&~a){
                b=i;
                break;
                }
            cnt++;
            }
        }
    if(b!=len)
        return make_pair(http.Type["HTML"].substr(30,a-30+1),http.Type["HTML"].substr(b,len-b));
    else
        return make_pair(http.Type["HTML"].substr(30,a-30+1),"");
    }
string hash_token;
string device_os;
string clver;
string token;
string market;
void login(){
    printf("uuid:");
    getline(cin,uuid);
    if(uuid!=""){
        printf("hash_token:");
        getline(cin,hash_token);
        printf("token[\"\"]:");
        getline(cin,token);
        printf("os[1]:");
        getline(cin,device_os);
        if(device_os=="")device_os="1";
        printf("client version[3]:");
        getline(cin,clver);
        if(clver=="")clver="3";
        printf("market[2]:");
        getline(cin,market);
        if(market=="")market="2";
        //puts(("{\"uuid\":\""+uuid+"\",\"hash_token\":\""+hash_token+"\",\"clver\":\"3\",\"os\":"+device_os+",\"carrier\":1,\"market\":2,\"lang\":0,\"device\":\"MIT Droid4X-WIN\",\"token\":\""+token+"\"}").c_str());
        system(("curl -s -d \"{\\\"uuid\\\":\\\""+uuid+"\\\",\\\"hash_token\\\":\\\""+hash_token+"\\\",\\\"clver\\\":\\\""+clver+"\\\",\\\"os\\\":"+device_os+",\\\"carrier\\\":1,\\\"market\\\":"+market+",\\\"lang\\\":0,\\\"device\\\":\\\"MIT Droid4X-WIN\\\",\\\"token\\\":\\\""+token+"\\\"}\" -A \"Dalvik/1.6.0 (Linux; U; Android 4.2.2; Droid4X-WIN\" https://app.login.kairisei-ma.jp/Auth/login.php > Auth").c_str());
        string auth=FileToStr("Auth");
        key_main=JsonGetObj(auth,"sess_key");
        puts(("Key: "+key_main).c_str());
        }
    else{
        printf("Key:");
        cin>>key_main;
        }
    if(key_main.length()==29)key_main+='=';
    kalisin("/Game/Connect");
    string home=kalisin("/Game/HomeShow").s;
    UserID=JsonGetObj(home,"user");
    puts(("UserID: "+UserID).c_str());
    }
void relogin(){
    if(uuid!=""){
        system(("curl -s -d \"{\\\"uuid\\\":\\\""+uuid+"\\\",\\\"hash_token\\\":\\\""+hash_token+"\\\",\\\"clver\\\":\\\"2\\\",\\\"os\\\":"+device_os+",\\\"carrier\\\":1,\\\"market\\\":2,\\\"lang\\\":0,\\\"device\\\":\\\"MIT Droid4X-WIN\\\",\\\"token\\\":\\\""+token+"\\\"}\" -A \"Dalvik/1.6.0 (Linux; U; Android 4.2.2; Droid4X-WIN\" https://app.login.kairisei-ma.jp/Auth/login.php > Auth").c_str());
        string auth=FileToStr("Auth");
        key_main=JsonGetObj(auth,"sess_key");
        puts(("Key: "+key_main).c_str());
        if(key_main.length()==29)key_main+='=';
        kalisin("/Game/Connect");
        string home=kalisin("/Game/HomeShow").s;
        UserID=JsonGetObj(home,"user");
        puts(("UserID: "+UserID).c_str());
        }
    else{
        puts("Connect User Error!");
        exit(0);
        }
    }
pair<string,string> NetObjGet(Net net,int cl=0){
    static queue<char> Obj_Queue;
    if(cl)while(Obj_Queue.size())Obj_Queue.pop();
    static int now=0;
    static string head,body;
    const char *buf=NetGet(net);
    for(;*buf;buf++)
        Obj_Queue.push(*buf);
    while(!Obj_Queue.empty()){
        char x=Obj_Queue.front();
        Obj_Queue.pop();
        if(x=='}'){
            string h=head,b=body;
            head="";body="";now=0;
            return make_pair(h,b);
            }
        else if(x=='{')now=1;
        else if(x=='\r'||x==' ')continue;
        else if(now&&(x!='\n'||body!=""))body+=x;
        else if(!now&&x!='\n')head+=x;
        }
    return make_pair("","");
    }
vector<string> StringCut(string s){
    vector<string> ve;
    ve.push_back("");
    int len=s.length();
    for(int i=0;i<len;i++){
        if(s[i]==','||s[i]=='\n')ve.push_back("");
        else ve.back()+=s[i];
        }
    return ve;
    }
void SellCard(string crd_nam="20000001",int num=-1){
    string crd=kalisin("/Game/CardShow").s;
    Sleep(2000);
    string ss=JsonGetCardID(crd,"\"cardid\":"+crd_nam);
    vector<string>chacha;
    int ccc=0;
    while(ss!=""){
        chacha.push_back(ss);
        ccc++;
        if(ccc==num)break;
        ss=JsonGetCardID(crd,"\"cardid\":"+crd_nam);
        }
    int chnt=0;
    string chs;
    for(auto z:chacha){
        if(chnt)chs+=',';
        chs+=z;
        chnt++;
        if(chnt==10){
            chnt=0;
            puts(("{\"uniqids\":["+chs+"]}").c_str());
            kalisin("/Game/CardSell","{\"uniqids\":["+chs+"]}");
            Sleep(3000);
            chs="";
            }
        }
    if(chnt){
        chnt=0;
        puts(("{\"uniqids\":["+chs+"]}").c_str());
        kalisin("/Game/CardSell","{\"uniqids\":["+chs+"]}");
        Sleep(3000);
        chs="";
        }
    }
void OnlineBattleOther(){
    string deck_arthur_type,deck_arthur_type_idx,bossid,pass;
    printf("deck_arthur_type:");
    cin>>deck_arthur_type;
    printf("deck_arthur_type_idx:");
    cin>>deck_arthur_type_idx;
    printf("bossid:");
    cin>>bossid;
    getline(cin,pass);
    printf("pass[\"\"]:");
    getline(cin,pass);
    printf("AutoSellBlueQieQie[1]:");
    int AutoChaCha=1;
    string ACC;
    getline(cin,ACC);
    if(ACC!="")AutoChaCha=StrToInt(ACC);
    if(AutoChaCha)
        SellCard();
    int notfnd=0;
    while(1){
        string teamlist=kalisin("/Game/TeamBattleMultiRoomSearch","{\"deck_arthur_type\":"+deck_arthur_type+",\"deck_arthur_type_idx\":"+deck_arthur_type_idx+",\"bossid\":"+(pass==""?bossid:(string)"0")+",\"pass\":\""+pass+"\"}").s;
        string RoomID=JsonGetObj(teamlist,"roomid");
        if(RoomID==""){
            if(notfnd>=10&&(notfnd>=30||pass=="")){
                relogin();
                notfnd=0;
                }
            notfnd++;
            puts("Not Found");
            Sleep(1000);
            continue;
            }
        else{
            notfnd=0;
            }
        printf("RoomID:%s\n",RoomID.c_str());
        string team=kalisin("/Game/TeamBattleMultiRoomEnter","{\"roomid\":"+RoomID+",\"deck_arthur_type\":"+deck_arthur_type+",\"deck_arthur_type_idx\":"+deck_arthur_type_idx+"}").s;
        if(team=="{}"||team==""){
            puts("Too Slow(Or Bag Is Full)");
            Sleep(1000);
            continue;
            }
        else{
            string host=JsonGetObj(team,"host"),port_s=JsonGetObj(team,"port"),auth_token=JsonGetObj(team,"auth_token"),signature=JsonGetObj(team,"signature");
            printf("host:%s port:%s\n%s\n",host.c_str(),port_s.c_str(),auth_token.c_str());
            int port=StrToInt(port_s);
            Net net=NetCreat(host.c_str(),port);
            if(!net){
                puts("Net Error!");
                continue;
                }
            NetObjGet(net,1);
            NetSend(net,("RoomEnterRequest{\n"+UserID+","+RoomID+","+deck_arthur_type+","+pass+","+auth_token+","+signature+"\n}\n").c_str());
            Time ti=GetTime(),gist=ti,lt=ti,sever_gt=ti,ltc=0;//,uat,ept;
            int Win=0;
            string target="5";
            int okgo=0;
            int rnd=1,tur=0,auto_go=1;
            while(1){
                Time gt=GetTime();
                if(gt-ti>15000){
                    ti=GetTime();
                    NetSend(net,"Ping{\n}\n");
                    }
                if(gt-gist>35000&&!okgo){
                    puts("Wait Too Long!");
                    break;
                    }
                if(gt-sever_gt>60000&&!okgo){
                    puts("Wait Too Long!");
                    break;
                    }
                pair<string,string> Obj=NetObjGet(net);
                if(Obj.f!=""&&Obj.f.find("Pong")==string::npos)
                    puts(Obj.f.c_str()),lt=gt,sever_gt=gt;
                if(Obj.f.find("Pong")==string::npos)
                    lt=gt;
                if(GetTime()-lt>30000){
                    puts("No Respond!");
                    break;
                    }
                if(Obj.f.find("RoomEnterRequestResult")!=string::npos){
                    if(Obj.s.find("OK")==string::npos){
                        puts("No OK");
                        break;
                        }
                    Sleep(1000);
                    puts("RoomLoadingFinish");
                    NetSend(net,"RoomLoadingFinish{\n}\n");
                    }
                else if(Obj.f.find("RoomDelete")!=string::npos){
                    puts("Break");
                    break;
                    }
                else if(Obj.f.find("RoomMember")!=string::npos){
                    gist=gt;
                    printf("%s",Obj.s.c_str());
                    }
                else if(Obj.f.find("RoomCountdownFinish")!=string::npos){
                    okgo=1;
                    Sleep(3000);
                    puts("LoadingFinish");
                    NetSend(net,"LoadingFinish{\n}\n");
                    Sleep(1000);
                    }
                else if(Obj.f.find("ApiGameStart")!=string::npos){
                    puts("GameStartFinish");
                    Sleep(500);
                    NetSend(net,"GameStartFinish{\n}\n");
                    }
                else if(Obj.f.find("ApiTurnPhase")!=string::npos){
                    tur++;
                    printf("R:%d T:%d C:%d\n",rnd,tur,min(tur+2,10));
                    puts("TurnPhaseFinish");
                    Sleep(500);
                    NetSend(net,"TurnPhaseFinish{\n}\n");
                    }
                else if(Obj.f.find("GameNextStart")!=string::npos){
                    puts("GameNextFinish");
                    target="5";
                    Sleep(500);
                    rnd++;
                    tur=0;
                    NetSend(net,"GameNextFinish{\n}\n");
                    }
                else if(Obj.f.find("MemberChat")!=string::npos){
                    gist=GetTime();
                    if(rand()&1&&ti-ltc>2000){
                        vector<string> ve=StringCut(Obj.s);
                        Sleep(1000);
                        puts(("Say "+ve[0]+"!").c_str());
                        NetSend(net,"Chat{\n"+ve[0]+"\n}\n");
                        ltc=ti;
                        }
                    }
                else if(Obj.f.find("ApiUserAttack")!=string::npos){
                    //uat=GetTime();
                    Sleep(5000);
                    puts("UserAttackFinish");
                    NetSend(net,"UserAttackFinish{\n}\n");
                    }
                else if(Obj.f.find("ApiEnemyPhase")!=string::npos){
                    //ept=GetTime();
                    vector<string> ve=StringCut(Obj.s);
                    int sz=ve.size(),ok70=0,oao=0;
                    for(int i=0;i<sz;i++)
                        if(ve[i]=="60")i+=7;
                        else if(ve[i]=="62")i+=8;
                        else if(ve[i]=="72")i+=2;
                        else if(ve[i]=="71")i+=3;
                        else if(ve[i]=="3")i+=3;
                        else if(ve[i]=="50")i+=5;
                        else if(ve[i]=="70")ok70=1;
                        else if(ve[i]=="6"){
                            if(StrToInt(ve[i+1])<=8&&StrToInt(ve[i+1])>=5)
                                target=max(target,ve[i+1]);
                            if(StrToInt(ve[i+1])>8||StrToInt(ve[i+1])<=0)
                                oao=1;
                            if(ok70)
                                printf("%s HP:%s/%s\n",ve[i+1].c_str(),ve[i+2].c_str(),ve[i+3].c_str());
                            i+=8;
                            }
                    if(oao)puts(Obj.s.c_str());
                    Sleep(3000);
                    puts("EnemyPhaseFinish");
                    NetSend(net,"EnemyPhaseFinish{\n}\n");
                    }
                else if(Obj.f.find("ApiUserPhase")!=string::npos){
                    vector<string> ve=StringCut(Obj.s);
                    int sz=ve.size();
                    string ar[5]={"0","0","0","0","0"},arr[5]={"0","0","0","0","0"};
                    int cnt=0,mp=99,ps=0;
                    string gd="0";
                    for(int i=0;i<sz;i++){
                        if(ve[i]=="20")i+=3;
                        else if(ve[i]=="21")i+=3;
                        else if(ve[i]=="24")i+=6;
                        else if(ve[i]=="25")i+=8;
                        else if(ve[i]=="27"){
                            if(ve[i+1]==deck_arthur_type){
                                printf("(%d,%d)",StrToInt(ve[i+2]),StrToInt(ve[i+3]));
                                int cost=StrToInt(ve[i+3]);
                                if((cost<=3||(tur>1&&cost<=4)||(tur>2&&cost<=5&&deck_arthur_type!="4"))&&StrToInt(ve[i+2])<mp){
                                    ps=cnt;
                                    gd=ve[i+2];
                                    mp=StrToInt(ve[i+2]);
                                    }
                                cnt++;
                                }
                            i+=3;
                            }
                        }
                    if(target!="0"){
                        ar[ps]=gd,arr[ps]=target;
                        }
                    puts("");
                    if(auto_go){
                        string ss;
                        for(int i=0;i<5;i++){
                            if(i)ss+=",";
                            ss+=ar[i]+","+arr[i];
                            }
                        puts(("Target:"+target).c_str());
                        Sleep(rand()%4000+3000);
                        puts(("CardPlay{"+ss+"}").c_str());
                        target="0";
                        NetSend(net,"CardPlay{\n"+ss+"\n}\n");
                        }
                    else{
                        while(1){
                            break;
                            }
                        string ss;
                        for(int i=0;i<5;i++){
                            if(i)ss+=",";
                            ss+=ar[i]+","+arr[i];
                            }
                        puts(("CardPlay{"+ss+"}").c_str());
                        NetSend(net,"CardPlay{\n"+ss+"\n}\n");
                        }
                    }
                else if(Obj.f.find("MemberOver")!=string::npos);
                else if(Obj.f.find("GameEnd")!=string::npos){
                    if(Obj.s.find("1")!=string::npos)
                        Win=1;
                    break;
                    }
                else if(Obj.f.find("ApiCardPlayR")!=string::npos);
                else if(Obj.f.find("RoomCountdownStart")!=string::npos)
                    okgo=1;
                else if(Obj.f.find("Pong")!=string::npos);
                else if(Obj.f.find("ApiContinuePhaseStart")!=string::npos){
                    Sleep(1000);
                    NetSend(net,"ContinuePhaseFinish{\n}\n");
                    }
                else if(Obj.f.find("ApiContinue")!=string::npos){
                    Sleep(1000);
                    NetSend(net,"ContinueFinish{\n}\n");
                    }
                else if(Obj.f.find("ApiGameOver")!=string::npos){
                    Sleep(1000);
                    NetSend(net,"GameOverPhaseFinish{\n}\n");
                    }
                else if(Obj.f!=""){
                    puts(Obj.s.c_str());
                    }
                Sleep(1);
                }
            NetClose(net);
            if(Win){
                puts("Win");
                kalisin("/Game/TeamBattleResult","{\"roomid\":"+RoomID+"}");
                Sleep(2000);
                if(AutoChaCha)
                    SellCard();
                }
            kalisin("/Game/HomeShow");
            Sleep(1000);
            }
        }
    }
void OnlineBattleSelf(){
    string deck_arthur_type,deck_arthur_type_idx,bossid,pass,room_type,is_need_deck_rank,deck_rank;
    printf("deck_arthur_type:");
    cin>>deck_arthur_type;
    printf("deck_arthur_type_idx:");
    cin>>deck_arthur_type_idx;
    printf("bossid:");
    cin>>bossid;
    getline(cin,pass);
    printf("pass[\"\"]:");
    getline(cin,pass);
    printf("room_type(only friend?)[0]:");
    getline(cin,room_type);if(room_type=="")room_type="0";
    printf("is_need_deck_rank[0]:");
    getline(cin,is_need_deck_rank);
    if(is_need_deck_rank=="")is_need_deck_rank="0",deck_rank="0";
    if(is_need_deck_rank=="1"){
        printf("deck_rank(1=F+~13=SS)[12]:");
        getline(cin,deck_rank);
        if(deck_rank=="")deck_rank="12";
        }
    else
        deck_rank=="0";
    string mf;
    int min_fame=90;
    printf("min fame[90]:");
    getline(cin,mf);if(mf!="")min_fame=StrToInt(mf);
    printf("AutoSellBlueQieQie[1]:");
    int AutoChaCha=1;
    string ACC;
    getline(cin,ACC);
    if(ACC!="")AutoChaCha=StrToInt(ACC);
    if(AutoChaCha)SellCard();
    while(1){
        string team=kalisin("/Game/TeamBattleMultiRoomCreate","{\"bossid\":"+bossid+",\"deck_arthur_type\":"+deck_arthur_type+",\"deck_arthur_type_idx\":"+deck_arthur_type_idx+",\"room_type\":"+room_type+",\"pass\":\""+pass+"\",\"is_need_deck_rank\":"+is_need_deck_rank+",\"deck_rank\":"+deck_rank+"}").s;
        //puts(("{\"bossid\":"+bossid+",\"deck_arthur_type\":"+deck_arthur_type+",\"deck_arthur_type_idx\":"+deck_arthur_type_idx+",\"room_type\":"+room_type+",\"pass\":\""+pass+"\",\"is_need_deck_rank\":"+is_need_deck_rank+",\"deck_rank\":"+deck_rank+"}").c_str());
        //puts(team.c_str());
        if(team=="{}"||team==""){
            puts("Error(Maybe no pt)!");
            Sleep(1000);
            continue;
            }
        else{
            string RoomID;
            string host=JsonGetObj(team,"host"),port_s=JsonGetObj(team,"port"),auth_token=JsonGetObj(team,"auth_token"),signature=JsonGetObj(team,"signature");
            printf("host:%s port:%s\n%s\n",host.c_str(),port_s.c_str(),auth_token.c_str());
            int port=StrToInt(port_s);
            Net net=NetCreat(host.c_str(),port);
            if(!net){
                puts("Net Error!");
                continue;
                }
            NetObjGet(net,1);
            NetSend(net,("RoomCreateRequest{\n"+UserID+","+bossid+","+room_type+","+pass+","+is_need_deck_rank+","+deck_rank+","+auth_token+","+signature+"\n}\n").c_str());
            //puts(("RoomCreateRequest{\n"+UserID+","+bossid+","+room_type+","+pass+","+is_need_deck_rank+","+deck_rank+","+auth_token+","+signature+"\n}\n").c_str());
            Time ti=GetTime(),lt=ti,sever_gt=ti,uat=0,ready=-1;//,lct=ti,gist=ti,ept;
            int Win=0;
            string target="5";
            int okgo=0;
            int rnd=1,tur=0,auto_go=1,gone=0,went=0;
            int member=0;
            while(1){
                Time gt=GetTime();
                if(gt-ti>15000){
                    ti=GetTime();
                    NetSend(net,"Ping{\n}\n");
                    }
                if(gt-sever_gt>60000&&!okgo){
                    puts("Wait Too Long!");
                    break;
                    }
                pair<string,string> Obj=NetObjGet(net);
                if(Obj.f!=""&&Obj.f.find("Pong")==string::npos)
                    puts(Obj.f.c_str()),lt=gt,sever_gt=gt;
                if(Obj.f.find("Pong")==string::npos)
                    lt=gt;
                if(GetTime()-lt>30000){
                    puts("No Respond!");
                    break;
                    }
                if(member==15&&~ready&&gt-ready>12000&&!gone){
                    puts("Go!");
                    NetSend(net,"RoomCountdownStartRequest{\n}\n");
                    gone=1;
                    }
                else if(member==15&&~ready&&gt-ready>10000&&!gone&&!went){
                    puts("RoomLoadingFinish");
                    NetSend(net,"RoomLoadingFinish{\n}\n");
                    went=1;
                    }
                else if(member==15&&!~ready){
                    ready=gt;
                    puts("Ready...");
                    }
                else if(member!=15)
                    ready=-1;
                if(Obj.f.find("RoomCreateRequestResult")!=string::npos){
                    if(Obj.s.find("OK")==string::npos){
                        puts("No OK");
                        break;
                        }
                    vector<string> ve=StringCut(Obj.s);
                    RoomID=ve[2];
                    puts(("RoomID:"+RoomID).c_str());
                    Sleep(1000);
                    puts("RoomLoadingFinish");
                    NetSend(net,"RoomLoadingFinish{\n}\n");
                    }
                else if(Obj.f.find("RoomDelete")!=string::npos){
                    puts("Break");
                    break;
                    }
                else if(Obj.f.find("RoomMember")!=string::npos){
                    //gist=gt;
                    printf("%s",Obj.s.c_str());
                    vector<string> ve=StringCut(Obj.s);
                    if(StrToInt(ve[1])<0)
                        member&=(15^(1<<(StrToInt(ve[0])-1)));
                    else{
                        member|=(1<<(StrToInt(ve[0])-1));
                        if(StrToInt(ve[12])<min_fame)
                            break;
                        }
                    }
                else if(Obj.f.find("RoomCountdownFinish")!=string::npos){
                    okgo=1;
                    Sleep(3000);
                    puts("LoadingFinish");
                    NetSend(net,"LoadingFinish{\n}\n");
                    Sleep(1000);
                    }
                else if(Obj.f.find("ApiGameStart")!=string::npos){
                    puts("GameStartFinish");
                    Sleep(500);
                    NetSend(net,"GameStartFinish{\n}\n");
                    }
                else if(Obj.f.find("ApiTurnPhase")!=string::npos){
                    tur++;
                    printf("R:%d T:%d C:%d\n",rnd,tur,min(tur+2,10));
                    puts("TurnPhaseFinish");
                    Sleep(500);
                    NetSend(net,"TurnPhaseFinish{\n}\n");
                    }
                else if(Obj.f.find("GameNextStart")!=string::npos){
                    puts("GameNextFinish");
                    target="5";
                    Sleep(500);
                    rnd++;
                    tur=0;
                    NetSend(net,"GameNextFinish{\n}\n");
                    }
                else if(Obj.f.find("MemberChat")!=string::npos){
                    //gist=GetTime();
                    }
                else if(Obj.f.find("ApiUserAttack")!=string::npos){
                    uat=gt;
                    Sleep(5000);
                    puts("UserAttackFinish");
                    NetSend(net,"UserAttackFinish{\n}\n");
                    }
                else if(Obj.f.find("ApiEnemyPhase")!=string::npos){
                    //printf("%lld\n",gt-uat);
                    //ept=gt;
                    vector<string> ve=StringCut(Obj.s);
                    int sz=ve.size(),ok70=0,oao=0;
                    for(int i=0;i<sz;i++)
                        if(ve[i]=="60")i+=7;
                        else if(ve[i]=="62")i+=8;
                        else if(ve[i]=="72")i+=2;
                        else if(ve[i]=="71")i+=3;
                        else if(ve[i]=="3")i+=3;
                        else if(ve[i]=="50")i+=5;
                        else if(ve[i]=="70")ok70=1;
                        else if(ve[i]=="6"){
                            if(StrToInt(ve[i+1])<=8&&StrToInt(ve[i+1])>=5)
                                target=max(target,ve[i+1]);
                            if(StrToInt(ve[i+1])>8||StrToInt(ve[i+1])<=0)
                                oao=1;
                            if(ok70)
                                printf("%s HP:%s/%s\n",ve[i+1].c_str(),ve[i+2].c_str(),ve[i+3].c_str());
                            i+=8;
                            }
                    if(oao)puts(Obj.s.c_str());
                    Sleep(3000);
                    puts("EnemyPhaseFinish");
                    NetSend(net,"EnemyPhaseFinish{\n}\n");
                    }
                else if(Obj.f.find("ApiUserPhase")!=string::npos){

                    printf("%lld\n",gt-uat);
                    vector<string> ve=StringCut(Obj.s);
                    int sz=ve.size();
                    string ar[5]={"0","0","0","0","0"},arr[5]={"0","0","0","0","0"};
                    int cnt=0,mp=99,ps=0;
                    string gd="0";
                    for(int i=0;i<sz;i++){
                        if(ve[i]=="20")i+=3;
                        else if(ve[i]=="21")i+=3;
                        else if(ve[i]=="24")i+=6;
                        else if(ve[i]=="25")i+=8;
                        else if(ve[i]=="27"){
                            if(ve[i+1]==deck_arthur_type){
                                printf("(%d,%d)",StrToInt(ve[i+2]),StrToInt(ve[i+3]));
                                int cost=StrToInt(ve[i+3]);
                                if((cost<=3||(tur>1&&cost<=4)||(tur>2&&cost<=5&&deck_arthur_type!="4"))&&StrToInt(ve[i+2])<mp){
                                    ps=cnt;
                                    gd=ve[i+2];
                                    mp=StrToInt(ve[i+2]);
                                    }
                                cnt++;
                                }
                            i+=3;
                            }
                        }
                    if(target!="0"){
                        ar[ps]=gd,arr[ps]=target;
                        }
                    puts("");
                    if(auto_go){
                        string ss;
                        for(int i=0;i<5;i++){
                            if(i)ss+=",";
                            ss+=ar[i]+","+arr[i];
                            }
                        puts(("Target:"+target).c_str());
                        Sleep(rand()%4000+3000);
                        puts(("CardPlay{"+ss+"}").c_str());
                        target="0";
                        NetSend(net,"CardPlay{\n"+ss+"\n}\n");
                        }
                    else{
                        while(1){
                            break;
                            }
                        string ss;
                        for(int i=0;i<5;i++){
                            if(i)ss+=",";
                            ss+=ar[i]+","+arr[i];
                            }
                        puts(("CardPlay{"+ss+"}").c_str());
                        NetSend(net,"CardPlay{\n"+ss+"\n}\n");
                        }
                    }
                else if(Obj.f.find("MemberOver")!=string::npos);
                else if(Obj.f.find("GameEnd")!=string::npos){
                    if(Obj.s.find("1")!=string::npos)
                        Win=1;
                    break;
                    }
                else if(Obj.f.find("ApiCardPlayR")!=string::npos);
                else if(Obj.f.find("RoomCountdownStart")!=string::npos)
                    okgo=1;
                else if(Obj.f.find("Pong")!=string::npos);
                else if(Obj.f.find("ApiContinuePhaseStart")!=string::npos){
                    Sleep(1000);
                    NetSend(net,"ContinuePhaseFinish{\n}\n");
                    }
                else if(Obj.f.find("ApiContinue")!=string::npos){
                    Sleep(1000);
                    NetSend(net,"ContinueFinish{\n}\n");
                    }
                else if(Obj.f.find("ApiGameOver")!=string::npos){
                    Sleep(1000);
                    NetSend(net,"GameOverPhaseFinish{\n}\n");
                    }
                else if(Obj.f!=""){
                    puts(Obj.s.c_str());
                    }
                Sleep(1);
                }
            NetClose(net);
            if(Win){
                puts("Win");
                kalisin("/Game/TeamBattleResult","{\"roomid\":"+RoomID+"}");
                puts("Reward Get!");
                Sleep(2000);
                if(AutoChaCha)
                    SellCard();
                }
            kalisin("/Game/HomeShow");
            Sleep(1000);
            }
        }
    }
void Walk(){
    kalisin("/Game/ExploreStart","{\"arthur_type\":1,\"deck_idx\":0}");
    printf("Start Walking");
    for(int i=0;i<7;i++){
        putchar('.');
        Sleep(1000);
        }
    puts("\nFinish Walking!");
    kalisin("/Game/ExploreEnd");
    }
void UseItem(string obj="1000"){
    kalisin("/Game/ItemUse","{\"itemid\":"+obj+"}");
    }
int KalisinBMA(int argc, char** argv){
    //CheatExample();
    //1CjV6JDu713ghCDI7yXlD8CNlOqfg=
    login();
    Sleep(2000);
    while(1){
        puts("Chose Service:");
        puts("1 Online Battle Other PT");
        puts("2 Online Battle Self PT");
        puts("3 Walk");
        puts("4 Sell Card");
        puts("5 Use Item //testing");
        int inp;
        scanf("%d",&inp);
        if(inp==1)
            OnlineBattleOther();
        else if(inp==2)
            OnlineBattleSelf();
        else if(inp==3)
            Walk();
        else if(inp==4){
            puts("Sell Card ID[20000001]:");
            string cid;
            getline(cin,cid);
            getline(cin,cid);
            if(cid=="")cid="20000001";
            puts("Sell Card Num[-1]:");
            int cnum=-1;
            string scnum;
            getline(cin,scnum);
            if(scnum!="")cnum=StrToInt(scnum);
            SellCard(cid,cnum);
            }
        else if(inp==5){
            puts("Item ID(1000=half water)[NULL]:");
            string cid;
            cin>>cid;
            if(cid=="")continue;
            UseItem(cid);
            }
        kalisin("/Game/HomeShow");
        Sleep(2000);
        }
    return 0;
    }
void WOT2(){
    printf("WOT2 start");
    while(1){
        Pos now=GetPos();
        //Color col=GetCol(now.f,now.s);
        //printf("%3d %3d %3d ",col.R,col.G,col.B);
        int ok=0;
        for(int i=0;i<30;i++){
            Color col=GetCol(now.f+i,now.s);
            if(col.R>200&&col.G<100&&col.B<100){
                ok=1;
                break;
                }
            }
        if(ok){
            ok=0;
            for(int i=0;i<30;i++){
                Color col=GetCol(now.f-i,now.s);
                if(col.R>200&&col.G<100&&col.B<100){
                    ok=1;
                    break;
                    }
                }
            if(ok){
                printf("Shut!\n");
                Click();
                }
            }
        //puts("Over");
        Sleep(20);
        }
    }
void WOT(){
    //Thread td(WOT2);
    int go=0,ld=0,rd=0,onx=0;
    while(1){
        if(go){
            if(ChkKey('U')&&!ld)
                Press(),ld=1;
            else if(ld&&!ChkKey('U'))
                Release(),ld=0;
            if(ChkKey('O')&&!rd)
                Press(1),rd=1;
            else if(rd&&!ChkKey('O'))
                Release(1),rd=0;
            int tim=12;
            if(Key('H'))
                onx^=1;
            if(onx)
                tim=1;
            if(ChkKey('V'))
                tim=40;
            if(ChkKey('I'))
                mouse_event(MOUSEEVENTF_MOVE,0,-1*tim, 0, 0);
            if(ChkKey('L'))
                mouse_event(MOUSEEVENTF_MOVE,1*tim,0, 0, 0);
            if(ChkKey('K'))
                mouse_event(MOUSEEVENTF_MOVE,0,1*tim, 0, 0);
            if(ChkKey('J'))
                mouse_event(MOUSEEVENTF_MOVE,-1*tim,0, 0, 0);
            }
        if(Key('G')){
            go=!go;
            if(go)puts("On");
            else puts("Off");
            }
        Sleep(20);
        }
    //td.join();
    }
void SAI(){
    int go=0,ld=0,rd=0,onx=0;//,cnt=0;
    while(1){
        if(go){
            if(ChkKey('U')&&!ld)
                Press(),ld=1;
            else if(ld&&!ChkKey('U'))
                Release(),ld=0;
            if(ChkKey('O')&&!rd)
                Press(1),rd=1;
            else if(rd&&!ChkKey('O'))
                Release(1),rd=0;
            int tim=12;
            if(Key('H'))
                onx^=1;
            if(onx)
                tim=1;
            if(ChkKey('V'))
                tim=40;
            if(ChkKey('I'))
                mouse_event(MOUSEEVENTF_MOVE,0,-1*tim, 0, 0);
            if(ChkKey('L'))
                mouse_event(MOUSEEVENTF_MOVE,1*tim,0, 0, 0);
            if(ChkKey('K'))
                mouse_event(MOUSEEVENTF_MOVE,0,1*tim, 0, 0);
            if(ChkKey('J'))
                mouse_event(MOUSEEVENTF_MOVE,-1*tim,0, 0, 0);
            }
        if(Key('G')){
            go=!go;
            if(go)puts("On");
            else puts("Off");
            }
        Sleep(20);
        }
    }
void Control(){
    char s[100];
    printf("ip://");
    scanf("%s",s);
    Net net=NetCreat(s,23);
    while(1){
        string str;
        sprintf(s,"5491 %d %d ",GetPos().f,GetPos().s);
        str=s;
        for(int i=0;i<256;i++){
            if(ChkKey(i)){
                sprintf(s,"%d ",i);
                str+=s;
                }
            if(Key(i)){
                sprintf(s,"%d ",-i);
                str+=s;
                }
            }
        NetSend(net,str.c_str());
        Sleep(20);
        }
    }

void ControlServer(){
    HideConsole();
    set<Net> *snet=SNetCreat(23);
    if(snet==NULL)return;
    puts("SNet Started!");
    while(1){
        set<Net> snet_c=*snet;
        for(auto sock:snet_c){
            const char *buf=NetGet(sock);
            if(strlen(buf)){
                stringstream str;
                str<<buf;
                //puts(buf);
                int tmp;
                str>>tmp;
                //printf("%d\n",tmp);
                //Time t;
                while(tmp==5491){
                    int x,y;
                    str>>x>>y;
                    Move(x,y);
                    //printf("M %d %d\n",x,y);
                    tmp=-1;
                    while(str>>tmp){
                        if(tmp==5491){
                            break;
                            }
                        if(tmp>=0){
                            if(tmp==1)
                                Press();
                            else if(tmp==2)
                                Press(1);
                            else
                                PressKey(tmp);
                            //printf("P %d\n",tmp);
                            }
                        else{
                            if(tmp==-1)
                                Release();
                            else if(tmp==-2)
                                Release(1);
                            else
                                ReleaseKey(-tmp);
                            //printf("R %d\n",-tmp);
                            }
                        tmp=-1;
                        }
                    }
                //sscanf(buf,"~%d %d\n",&x,&y);
                //Move(x,y);
                }
            }
        Sleep(20);
        }
    }
void HtmlExample(){
    string html = "<html><body>hey<link href=\"http://www.apple.com\" /><a href=\"yahoo.com.tw\">haha</a></body></html>";
    HtmlToNode(html)->Print();
    }
void NetExample(){
    Net net=NetCreat("web.ck.tp.edu.tw",80);
    string str;
    str+="GET /ann/ HTTP/1.1\n";
    str+="Accept: text/html, application/xhtml+xml, */*\n";
    str+="Accept-Language: zh-Hant-TW,zh-Hant\n";
    str+="User-Agent: Jtol/1.0 (Windows NT 6.3; WOW64;)\n";
    str+="Accept-Encoding: identity\n";
    str+="Host: ck10227.twbbs.org\n";
    str+="Connection: Keep-Alive\n\n";
    NetSend(net,&str[0]);
    //Sleep(3000);
    Time tim=GetTime();
    string get;
    while(GetTime()-tim<500){
        const char *buf=NetGet(net);
        if(strlen(buf)){
            get+=buf;
            //printf("~$~");
            //for(int i=0;buf[i];i++)
                //printf("%c %d\n",buf[i],buf[i]);
            //printf("%s",buf);
            tim=GetTime();
            }
        }
    Node http=HttpDecode(get);
    if(http.Type["Transfer-Encoding"]=="chunked"){
        crope cont=http.Type["HTML"].c_str();
        http.Type["HTML"]="";
        while(cont.size()){
            string code;
            int i=0;
            for(;cont[i];i++){
                if(cont[i]=='\n'){
                    i++;
                    break;
                    }
                }
            int num;
            sscanf(cont.substr(0,i).c_str(),"%x",&num);
            //printf("~~~\n",cont.substr(0,i).c_str());
            http.Type["HTML"]+=cont.substr(i,num).c_str();
            cont.erase(0,i+num+2);
            }
        }
    //http.Print();
    HtmlToNode(http.Type["HTML"].c_str())->Print();
    //HtmlToNode(get)->Print();
    }
void SNetExample(){
    set<Net> *snet=SNetCreat(80);
    if(snet==NULL)return;
    puts("SNet Started!");
    while(1){
        set<Net> snet_c=*snet;
        for(auto sock:snet_c){
            const char *buf=NetGet(sock);
            if(strlen(buf)){
                //printf("%s",buf);
                string s=FileToStr("a.html");
                string str;
                str+="HTTP/1.1 200 OK\n";
                str+="Content-Length: "+IntToStr(s.length())+"\n";
                str+="Content-Type: text/html\n";
                str+="Server: Jtol/1.0 (Win) (Windows8.1/WindowsNT)\n";
                str+="Last-Modified: "+UTCTime()+"\n";
                str+="Accept-Ranges: bytes\n";
                str+="Date: "+UTCTime()+"\n";
                str+="\n";
                str+=s;
                //cout<<str;
                NetSend(sock,&str[0]);
                NetClose(sock);
                snet->erase(sock);
                }
            }
        if(Key('E'))break;
        Sleep(20);
        }
    }

void ColExample(){
    int go=0;
    while(1){
        if(go){
            if(Key(0x01)){
                par pos=GetPos();
                Color col=GetCol(pos);
                printf("%d %d %d (%d %d)\n",col.R,col.G,col.B,pos.f,pos.s);
                }
            if(Key('C'))
                Clear();
            if(Key('M'))
                Move(0,0,1000);
            if(ChkKey('P'))
                PressKey(0x01);
            else if(!ChkKey(0x01))
                ReleaseKey(0x01);
            }
        if(Key('G')){
            go=!go;
            if(go)puts("On");
            else puts("Off");
            }
        if(Key('E'))break;
        Sleep(20);
        }
    }

void CheatExample(){
    Setup();
    int go=0;
    while(1){
        if(go){
            //Pos p=GetPos();
            //Color coll=GetCol(p);
            //printf("%d %d %d %d %d\n",p.f,p.s,coll.R,coll.G,coll.B);
            Color col=GetCol(Pos(1885,557));
            if(col.R==255&&col.G==255&&col.B==255){
                ClickKey('X');
                puts("Click!");
                }
            }
        if(Key('G')){
            go=!go;
            if(go)puts("On");
            else puts("Off");
            }
        if(Key('E'))break;
        Sleep(20);
        }
    }
