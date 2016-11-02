//Jtol.h v1.5
#include<bits/stdc++.h>
#undef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#include<Winsock2.h>
#include<windows.h>
#include<gdiplus.h>
#include<mmsystem.h>
#include<process.h>
#include<chrono>
#include<ext/rope>
#include<GL/gl.h>
#include<GL/glu.h>
#undef UNICODE
#define UNICODE
#define f first
#define s second
//#pragma comment(linker, "/subsystem:console /entry:WinMainCRTStartup")
namespace Jtol{
    using namespace __gnu_cxx;
    //using namespace Gdiplus;
    using namespace std;
    typedef pair<int,int> par;
    typedef HANDLE Hand;
    typedef unsigned long long int Time;
    typedef par Pos;
    typedef SOCKET Net;
    typedef thread* Thread;
    int Keypool[512];
    HDC hdc_;
    int _ScreenX=1920,_ScreenY=1080;
    struct Color{
        int R,G,B;
        Color(){}
        Color(int r,int g,int b){R=r,G=g,B=b;}
        //L(){return (R+G+B)/3;}
        L(){return max(R,max(G,B));}
        };
    struct MoveFncStrcut{
        int x,y,t;
        };
    unsigned long long int GetTime(){
        LARGE_INTEGER m_nBeginTime,m_nFreq;
        QueryPerformanceFrequency(&m_nFreq);
        QueryPerformanceCounter(&m_nBeginTime);
        return m_nBeginTime.QuadPart*1000/m_nFreq.QuadPart;
        }
    void Delay(Time x,Time feq=1){
        Time start=GetTime();
        while(1){
            if(GetTime()-start>=x)return;
            //Sleep(1);
            std::this_thread::sleep_for(std::chrono::milliseconds(feq));
            }
        }
    Pos GetPos(){
        POINT pt;
        GetCursorPos(&pt);
        return Pos(pt.x,pt.y);
        }
    Color GetCol(int x,int y){
        COLORREF color = GetPixel(hdc_,x,y);
        return Color(GetRValue(color),GetGValue(color),GetBValue(color));
        }
    Color GetCol(Pos p){
        return GetCol(p.f,p.s);
        }
    void Click(int t=50){
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0 );
        if(t)Sleep(t);
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0 );
        }
    void Press(int r=0){
        if(r)
            mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0 );
        else
            mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0 );
        }
    void Release(int r=0){
        if(r)
            mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0 );
        else
            mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0 );
        }
    void Mov(int x,int y){
        //mouse_event(0, 0, 0, 0, 0 );
        //mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MOVE,x*65535/1920,y*65535/1080, 0, 0);
        //mouse_event(MOUSEEVENTF_MOVE,x,y, 0, 0);
        SetCursorPos(x,y);
        mouse_event(MOUSEEVENTF_MOVE,0,0, 0, 0);
        }
    void Move(int x,int y,int t=0){
        if(t){
            Time start=GetTime();
            for(int i=0,j;i<t;){
                j=i+min(30,t-i);
                while(1){
                    if((int)(GetTime()-start)>=j)break;
                    Sleep(30);
                    }
                par bas=GetPos();
                //Mov(x+(bas.f-x)*(t-j)/(t-i)-bas.f,y+(bas.s-y)*(t-j)/(t-i)-bas.s);
                Mov(x+(bas.f-x)*(t-j)/(t-i),y+(bas.s-y)*(t-j)/(t-i));
                i=j;
                }
            }
        else{
            //par bas=GetPos();
            //Mov(x-bas.f,y-bas.s);
            Mov(x,y);
            }
        }
    void MoveFnc(MoveFncStrcut* MFS){
        int x=MFS->x,y=MFS->y,t=MFS->t;
        Move(x,y,t);
        delete MFS;
        }
    void MoveEX(int x,int y,int t=0){
        MoveFncStrcut* MFS=new MoveFncStrcut();
        MFS->x=x;MFS->y=y;MFS->t=t;
        CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)MoveFnc,(void*)MFS,0,NULL);
        }
    void Clear(){system("cls");}
    /*Hand Thread(void Fnc()){
        Hand thd;
        DWORD tid;
        thd=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)Fnc,(void*)0,0,&tid);
        return thd;
        }*/
    bool ChkKey(int key){
        return GetAsyncKeyState(key) & 0x8000;
        }
    bool Key(int key){
        if(ChkKey(key)){
            Keypool[key]=1;
            return 0;
            }
        if(Keypool[key]){
            Keypool[key]=0;
            return 1;
            }
        return 0;
        }
    void WaitKey(int key){
        while(1)
            if(ChkKey(key))
                break;
        }
    void PressKey(int key){
        keybd_event(key, 0, 0, 0);
        }
    void ReleaseKey(int key){
        keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
        }
    void ClickKey(int key,int t=50){
        keybd_event(key, 0, 0, 0);
        Sleep(t);
        keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
        }
    int putst(string s){return puts(s.c_str());}
    SOCKET NetCreat(const char ip[],int port=23,int mode=1){//mode: 1->NoWait 0->Wait
        //printf("%s %d\n",ip,port);
        NetCreatStatr:;
        WSADATA wsaData;
        if(WSAStartup(MAKEWORD(2,1),&wsaData)){
            printf("Winsock initiate failed!!\n");
            WSACleanup();
            return 0;
            }
        //printf("Winsock start...\n");
        sockaddr_in server;
        server.sin_family = AF_INET;
        server.sin_port = htons(port);  //the port need listened
        server.sin_addr.s_addr = inet_addr(ip);
        if( server.sin_addr.s_addr == INADDR_NONE ){
            hostent *host = gethostbyname(ip);
            server.sin_addr.s_addr = *reinterpret_cast<unsigned long*>(host->h_addr_list[0]);
            if( server.sin_addr.s_addr == INADDR_NONE ){
                puts("DNS error");
                goto NetCreatStatr;
                return 0;
                }
            }
        SOCKET socket1 = socket(AF_INET,SOCK_STREAM,0);
        ioctlsocket(socket1,FIONBIO, (u_long FAR*) &mode);//NoWait
        int r=connect(socket1, (struct sockaddr *)&server, sizeof(server));
        if(r==SOCKET_ERROR){
            if(WSAGetLastError() == WSAEWOULDBLOCK){
                fd_set Write, Err;
                TIMEVAL Timeout;
                int TimeoutSec = 2;
                FD_ZERO(&Write);
                FD_ZERO(&Err);
                FD_SET(socket1, &Write);
                FD_SET(socket1, &Err);
                Timeout.tv_sec = TimeoutSec;
                Timeout.tv_usec = 0;
                r=select(0,NULL,&Write,&Err,&Timeout);
                if(r==0){
                    printf("Connect Timeout!\n");
                    //MessageBoxA(0, "Connect Timeout!", "DLL Message", MB_OK | MB_ICONINFORMATION);
                    return 0;
                    }
                else{
                    if(!FD_ISSET(socket1, &Write)&&FD_ISSET(socket1, &Err)){
                        printf("Select error!\n");
                        return 0;
                        }
                    }
                }
            else{
                printf("Failed to connect to server!\n");
                goto NetCreatStatr;
                WSACleanup();
                return 0;
                }
            }
        return socket1;
        //DWORD tid;
        //HANDLE thd=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)chk,(void*)0,0,&tid);
        }
    map<Net,string > NetBuf;
    void NetClose(Net sock){
        NetBuf.erase(sock);
        closesocket(sock);
        }
    const char* NetGet(Net sock){
        //if(strlen(NetBuf))memset(NetBuf,0,sizeof(NetBuf));
        NetBuf[sock].resize(100000);
        fill(NetBuf[sock].begin(),NetBuf[sock].end(),0);
        char *buf=&(NetBuf[sock][0]);
        if(recv(sock,buf,NetBuf[sock].size(),0)!=SOCKET_ERROR){
            return buf;
            }
        //return &(NetBuf[sock][0]);
        return NetBuf[sock].c_str();
        }
    void NetSend(Net sock,string s){
        send(sock,s.c_str(),s.length(),0);
        }
    vector<string> HostIP;
    void SetHostIP(){
        HostIP.clear();
        char host_name[256];
        if (gethostname(host_name, sizeof(host_name)) == SOCKET_ERROR) {
            printf("Error %d when getting local host name.\n", WSAGetLastError());
            exit(1);
            }
        //printf("Host name is: %s\n", host_name);
        struct hostent *phe = gethostbyname(host_name);
        if(phe==0){
            printf("Bad host lookup.");
            }
        for(int i=0;phe->h_addr_list[i]!=0;i++){
            struct in_addr addr;
            memcpy(&addr, phe->h_addr_list[i], sizeof(struct in_addr));
            //printf("Address %d : %s\n" , i, inet_ntoa(addr));
            //int l=strlen(inet_ntoa(addr));k
            HostIP.push_back(inet_ntoa(addr));
            }
        HostIP.push_back("127.0.0.1");
        }
    struct SNetCreatFncStruct{
        vector<Net> *server_sockfd;
        set<Net>*client_sockfd_list;
        };
    void SNetCreatFnc(SNetCreatFncStruct *SNCF){
        vector<sockaddr_in> client_address;
        client_address.push_back(sockaddr_in());
        //(SNCF->client_sockfd_list)->push_back(SOCKET());
        Net client_tmp;
        int client_len=sizeof(client_address.back());
        int sz=(SNCF->server_sockfd)->size();
        while(1){
            for(int i=0;i<sz;i++){
                client_tmp=accept((SNCF->server_sockfd)->at(i),(struct sockaddr *)&client_address.back(), &client_len);
                if((int)client_tmp != SOCKET_ERROR){
                    printf("[%s] Connect!\n",inet_ntoa(client_address.back().sin_addr));
                    //CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)Fnc,(void*)(SNCF->client_sockfd_list)->back(),0,NULL);
                    client_address.push_back(sockaddr_in());
                    (SNCF->client_sockfd_list)->insert(client_tmp);
                    }
                Sleep(50);
                }
			}
        }
    set<Net>* SNetCreat(int port=23,int mode=1){
        vector<Net> *server_sockfd;
        server_sockfd=new vector<Net>;
        sockaddr_in server_address[100];
        int server_len[100];
        // µù¥U Winsock DLL
        WSADATA wsadata;
        if(WSAStartup(0x101,(LPWSADATA)&wsadata) != 0) {
            printf("Winsock Error\n");
            return NULL;
            }
        SetHostIP();
        for(auto x:HostIP)
            puts(x.c_str());
        int Err=0,sz=HostIP.size();
        for(int i=0;i<sz;i++){
            int err=0;
            server_sockfd->push_back(socket(AF_INET, SOCK_STREAM, 0));
            if((int)server_sockfd->at(i) == SOCKET_ERROR) {
                printf("Socket %d Error\n",i);
                err=1;
                }
            server_address[i].sin_family = AF_INET;
            server_address[i].sin_addr.s_addr = inet_addr(&HostIP[i][0]);
            server_address[i].sin_port = htons(port);
            server_len[i] = sizeof(server_address);
            if(bind(server_sockfd->at(i), (struct sockaddr *)&server_address[i], server_len[i]) < 0) {
                printf("Bind %d Error\n",i);
                err=1;
                }
            if(listen(server_sockfd->at(i), 5) < 0) {
                printf("Listen %d Error\n",i);
                err=1;
                }
            if(err){
                Err++;
                }
            else{
                ioctlsocket(server_sockfd->at(i),FIONBIO, (u_long FAR*) &mode);
                }
            }
        if(Err==sz){
            printf("Error %d\n",sz);
            return NULL;
            }
        set<Net> *client_sockfd_list;
        client_sockfd_list = new set<Net>;
        SNetCreatFncStruct *SNCF;
        SNCF=new SNetCreatFncStruct;
        SNCF->client_sockfd_list=client_sockfd_list;
        SNCF->server_sockfd=server_sockfd;
        CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)SNetCreatFnc,(void*)SNCF,0,NULL);
        return client_sockfd_list;
        }
    string FileToStr(const char *fil){
        fstream fin;
        fin.open(fil,ios::in);
        string in,ss;
        while(getline(fin,in)){
            //cout<<in;
            ss+=in+"\n";
            }
        fin.close();
        return ss;
        }
    void StrToFile(string s,const char fil[]){
        fstream fout;
        fout.open(fil,ios::out);
        fout<<s;
        fout.close();
        }
    string UTCTime(){
        time_t rawtime;
        struct tm * timeinfo;
        char buffer [80];
        time (&rawtime);
        timeinfo = localtime (&rawtime);
        strftime (buffer,80,"%a, %d %b %y %H:%M:%S GMT",timeinfo);
        //strftime(outstr,sizeof(outstr),"%a, %d %b %y %H:%M:%S GMT",tmp);
        return buffer;
        }
    string IntToStr(int x){
        stringstream str;
        string s;
        str<<x;
        str>>s;
        return s;
        }
    int StrToInt(string x){
        stringstream str;
        int s;
        str<<x;
        str>>s;
        return s;
        }
    struct Node{
        string name;
        list<Node*> Klis;
        Node* Fath;
        multimap<string,list<Node*>::iterator> Kmap;
        //map<string,list<Node*>::iterator> Kmap;
        map<string,string>Type;
        Node(){Fath=NULL;}
        Node(string s,Node* f=NULL){name=s;Fath=f;}
        ~Node(){
            for(list<Node*>::iterator it=Klis.begin(),now,ed=Klis.end();it!=ed;){
                now=it++;
                delete *now;
                }
            }
        void AddType(string s,string ss){
            if(Type[s]!="")Type[s]+="::";
            Type[s]+=ss;
            }
        void AddNode(string s){
            Klis.push_back(new Node(s,this));
            //Kmap[s]=Klis.end();
            Kmap.insert(make_pair(s,--Klis.end()));
            }
        void Print(int l=0){
            //printf("%d\n",this);
            for(int i=0;i<l*2;i++)
                cout<<" ";
            cout<<"("<<name<<"):";
            for(auto it:Type){
                if(name!="style"||it.f!="innerHTML")
                    if(name!="script"||it.f!="innerHTML")
                        cout<<it.f<<"->\""<<it.s<<"\" ";
                }
            cout<<endl;
            //system("pause");
            for(auto it:Klis)
                it->Print(l+1);
            for(int i=0;i<l*2;i++)
                cout<<" ";
            cout<<"(/"<<name<<")"<<endl;
            }
        };
    Node* HtmlToNode(string s){
        string sigtag[]={"br","meta","link","img","input","!DOCTYPE","hr"};
        int sigtagtop=8;
        Node *now=new Node(),*root=now;
        int sz=s.length();
        bool intag=0,ontag=0,instr1=0,instr2=0,detag=0,typove=0,sbreak=0,onword=0,skip=0;
        string tnam,snam,bnam,onam,str,emp,scc;
        for(int i=0;i<sz;i++){
            if(i+3<sz&&s[i]=='<'&&s[i+1]=='!'&&s[i+2]=='-'&&s[i+3]=='-'){
                skip=1;
                }
            else if(skip){
                if(s[i-2]=='-'&&s[i-1]=='-'&&s[i]=='>')
                    skip=0;
                }
            else if(!intag){
                if(now->name=="script"){
                    if(s[i]=='<'&&s[i+1]=='/'&&s[i+2]=='s'&&s[i+3]=='c'&&s[i+4]=='r'&&s[i+5]=='i'&&s[i+6]=='p'&&s[i+7]=='t'){
                        now->AddType("innerHTML",scc);
                        now=now->Fath;
                        for(;i<sz;i++)
                            if(s[i]=='>'){i++;break;}
                        scc="";
                        }
                    else{
                        scc+=s[i];
                        }
                    }
                else if(s[i]=='<'){
                    if(onam!="")
                        now->AddType("innerHTML",onam);
                    //cout<<now->name<<"<"<<onam<<endl;
                    //puts("~~~");
                    onam="";
                    intag=1;
                    ontag=1;
                    onword=0;
                    emp="";
                    if(s[i+1]=='/')detag=1,i++;
                    }
                else if(s[i]==' '||s[i]=='\n'||s[i]=='\r'||s[i]==' '||(s[i]<32&&s[i]>=0))
                    emp+=s[i];
                else{
                    //printf("%d %c %d\n",onword,s[i],s[i]);
                    if(onword)
                        onam+=emp;
                    emp="";
                    onam+=s[i];
                    onword=1;
                    }
                }
            else if(ontag){
                //if(s[i]=='/')detag=1;
                if(s[i]==' '){
                    ontag=0;
                    if(!detag){
                        now->AddNode(tnam);
                        now=now->Klis.back();
                        }
                    else{
                        if(now->Fath!=NULL){
                            if(now->name==tnam){
                                now=now->Fath;
                                }
                            }
                        }
                    tnam="";
                    }
                else if(s[i]=='>'){
                    ontag=0;
                    intag=0;
                    if(!detag){
                        now->AddNode(tnam);
                        now=now->Klis.back();
                        }
                    else{
                        if(now->Fath!=NULL){
                            if(now->name==tnam){
                                now=now->Fath;
                                //cout<<now->name<<endl;
                                }
                            }
                        }
                    bool cksig=0;
                    for(int i=0;i<sigtagtop;i++)
                        if(now->name==sigtag[i])
                            cksig=1;
                    if(!detag)
                    if(s[i-1]=='/'||cksig)
                        if(now->Fath!=NULL)
                                now=now->Fath;
                    detag=0;
                    tnam="";
                    //puts("OVE");
                    }
                else
                    tnam+=s[i];
                }
            else if(instr1){
                if(s[i]=='"'){
                    instr1=0;
                    }
                else if(s[i]=='\\')
                    i++;
                else
                    bnam+=s[i];
                }
            else if(instr2){
                if(s[i]=='\'')
                    instr2=0;
                else if(s[i]=='\\')
                    i++;
                else
                    bnam+=s[i];
                }
            else if(typove){
                if(s[i]==' '||s[i]=='\n'||s[i]=='\r'||s[i]==' '||(s[i]<32&&s[i]>=0)){
                    if(snam!=""&&bnam!=""){
                        now->AddType(snam,bnam);
                        typove=0;snam="";bnam="";
                        }
                    }
                else if(s[i]=='/'){}
                else if(s[i]=='>'){
                    if(snam!=""&&bnam!=""){
                        now->AddType(snam,bnam);
                        typove=0;
                        snam="";bnam="";
                        }
                    ontag=0;
                    intag=0;
                    bool cksig=0;
                    for(int i=0;i<sigtagtop;i++)
                        if(now->name==sigtag[i])
                            cksig=1;
                    if(detag){
                        if(now->Fath!=NULL){
                            if(now->name==tnam){
                                now=now->Fath;
                                }
                            }
                        }
                    else if(s[i-1]=='/'||cksig)
                        if(now->Fath!=NULL)
                                now=now->Fath;
                    detag=0;
                    tnam="";
                    }
                else if(s[i]=='"'){
                    instr1=1;
                    }
                }
            else if(intag){
                if(s[i]==' '||s[i]=='\n'||s[i]=='\r'||s[i]==' '||(s[i]<32&&s[i]>=0)){
                    if(snam!="")
                        sbreak=1;
                    }
                else if(s[i]=='='){
                    sbreak=0;
                    typove=1;
                    }
                else if(s[i]=='/'){}
                else if(s[i]=='>'){
                    if(snam!=""){
                        now->AddType(snam,bnam);
                        typove=0;snam="";bnam="";
                        }
                    ontag=0;
                    intag=0;
                    bool cksig=0;
                    for(int i=0;i<sigtagtop;i++)
                        if(now->name==sigtag[i])
                            cksig=1;
                    if(detag){
                        if(now->Fath!=NULL){
                            if(now->name==tnam){
                                now=now->Fath;
                                }
                            }
                        }
                    else if(s[i-1]=='/'||cksig)
                        if(now->Fath!=NULL)
                                now=now->Fath;
                    detag=0;
                    tnam="";
                    }
                else{
                    if(sbreak)now->AddType(snam,""),snam="",sbreak=0;
                    snam+=s[i];
                    }
                }
            }
        return root;
        }
    Node HttpDecode(string s){
        Node nod;
        int sz=s.length();
        bool mo=0,html=0;
        string a,b;
        int i;
        for(i=1;i<sz;i++)
            if(s[i-1]=='\r'&&s[i]=='\n')
                break;
        for(;i<sz;i++){
            if(html){
                a+=s[i];
                }
            else if(i+3<sz&&s[i]=='\r'&&s[i+1]=='\n'&&s[i+2]=='\r'&&s[i+3]=='\n'){
                html=1;
                nod.AddType(a,b);
                a="";b="";
                i+=3;
                }
            else if(s[i]==':'&&!mo){
                mo=1;
                if(i+1<sz&&s[i+1]==' ')i++;
                }
            else if(i&&s[i-1]=='\r'&&s[i]=='\n'){
                nod.AddType(a,b);
                a="";b="";
                mo=0;
                }
            else if(s[i]!='\r'){
                if(mo)b+=s[i];
                else a+=s[i];
                }
            }
        nod.AddType("HTML",a);
        return nod;
        }
    template<typename T,typename... Args>
    Thread ThreadCreate(T will_run, Args... args){
        Thread td=new thread(will_run,args...);
        return td;
        }
    void Wait(Thread thr){
        thr->join();
        delete thr;
        }
    template<typename Signature>
    std::function<Signature> ToFunction(FARPROC f){
        return std::function<Signature>(reinterpret_cast<Signature*>(f));
        }
    void HideConsole(){
        HWND hWnd = GetConsoleWindow();
        ShowWindow( hWnd, SW_HIDE );
        }
    void Setup(){
        memset(Keypool,0,sizeof(Keypool));
        hdc_ = GetDC(GetDesktopWindow()) ;
        RECT rect;
        GetWindowRect(GetDesktopWindow(),&rect);
        _ScreenX=rect.right;
        _ScreenY=rect.bottom;
        srand(time(0));
        //memset(NetBuf,0,sizeof(NetBuf));
        }
    void Alert(const char *content="",const char *titile=""){
        MessageBox( 0, content, titile, MB_SETFOREGROUND );
        }
    typedef HINSTANCE DLL;
    DLL LoadDLL(string s){
        DLL hinstLib=LoadLibrary(TEXT(s.c_str()));
        if(!hinstLib)
            puts("ERROR: unable to load DLL");
        return hinstLib;
        }
    void FreeDLL(DLL hinstLib){
        FreeLibrary(hinstLib);
        }
    template <typename T>
    struct TypeParser {};

    template <typename Ret, typename... Args>
    struct TypeParser<Ret(Args...)> {
        static std::function<Ret(Args...)> createFunction(const FARPROC lpfnGetProcessID) {
            return std::function<Ret(Args...)>(reinterpret_cast<Ret (__stdcall *)(Args...)>(lpfnGetProcessID));
        }
    };
    template<typename Signature>
    function<Signature>GetDLLFunc(DLL hinstLib,string s){
        FARPROC func=GetProcAddress(hinstLib,s.c_str());
        if(!func){
            puts("ERROR: unable to find DLL function");
            FreeLibrary(hinstLib);
            return 0;
            }
        return TypeParser<Signature>::createFunction(func);
        }

    template<typename T>
    Hand WinCreat(HINSTANCE hInstance,T WndProc/*, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow=10*/){
        WNDCLASSEX wndclass = {sizeof(wndclass),
            CS_HREDRAW|CS_VREDRAW,                //style
            WndProc,
            0, 0, hInstance,
            LoadIcon(NULL, IDI_APPLICATION),      //hIcon
            LoadCursor(NULL,IDC_ARROW),           //hCursor
            (HBRUSH)(COLOR_WINDOW+1),             //hbrBackground
            NULL,                                 //hMenu
            "window",
            LoadIcon(NULL, IDI_APPLICATION)};     //hIconSm
        RegisterClassEx(&wndclass);
        HWND hWnd = CreateWindowEx(
            0,                              //dwExStyle
            "window", "window",             //Title
            WS_OVERLAPPEDWINDOW,            //dwStyle
            CW_USEDEFAULT, CW_USEDEFAULT,
            CW_USEDEFAULT, CW_USEDEFAULT,
            NULL, NULL, hInstance, NULL);
        ShowWindow(hWnd,10/* nCmdShow*/);
        UpdateWindow(hWnd);
        return hWnd;
        }

    //BMP
    int bmp_read(const char *filein_name,int *xsize,int *ysize,int *bsize,unsigned char **rarray,unsigned char **garray,unsigned char **barray);
    int bmp_read_data(FILE *filein,int xsize,int ysize,int bsize,unsigned char *rarray,unsigned char *garray,unsigned char *barray);
    int bmp_read_header(FILE *filein,int *xsize,int *ysize,int *bsize,int *psize);
    int bmp_read_palette(FILE *filein,int psize);
    int bmp_read_test(char *filein_name);
    int bmp_write(const char *fileout_name,int xsize,int ysize,int bsize,unsigned char *rarray,unsigned char *garray,unsigned char *barray);
    int bmp_write_data(FILE *fileout,int xsize,int ysize,int bsize,unsigned char *rarray,unsigned char *garray,unsigned char *barray);
    int bmp_write_header(FILE *fileout,int xsize,int ysize,int bsize);
    int bmp_write_palette(FILE *fileout);
    int bmp_write_test(char *fileout_name);
    int read_u_long_int(unsigned long int*u_long_int_val,FILE *filein);
    int read_u_short_int(unsigned short int *u_short_int_val,FILE *filein);
    int write_u_long_int(unsigned long int u_long_int_val,FILE *fileout);
    int write_u_short_int(unsigned short int u_short_int_val,FILE *fileout);
    int byte_swap=1;
    int bmp_read(const char *filein_name,int *xsize,int *ysize,int* bsize,unsigned char **rarray,unsigned char **garray,unsigned char **barray){
        FILE *filein;
        int numbytes;
        int psize;
        int result;
        filein=fopen(filein_name,"rb");
        if(!filein){
            printf("\n");
            printf("BMP_READ - Fatal error!\n");
            printf("  Could not open the input file.\n");
            return 1;
            }
        result=bmp_read_header(filein,xsize,ysize,bsize,&psize);
        if(result==1){
            printf("\n");
            printf("BMP_READ: Fatal error!\n");
            printf("  BMP_READ_HEADER failed.\n");
            return 1;
            }
        if((*bsize)!=8&&(*bsize)!=24){
            printf("\n");
            printf("BMP_READ: bit size=%d is not supported\n",*bsize);
            printf("  BMP_READ failed.\n");
            return 1;
            }
        if(*bsize==8)
            psize=256;
        result=bmp_read_palette(filein,psize);
        if(result==1){
            printf("\n");
            printf("BMP_READ: Fatal error!\n");
            printf("  BMP_READ_PALETTE failed.\n");
            return 1;
            }
        numbytes=(*xsize)*(*ysize)* sizeof(unsigned char);
        *rarray=(unsigned char *)malloc(numbytes);
        if(rarray==NULL){
            printf("\n");
            printf("BMP_READ: Fatal error!\n");
            printf("  Could not allocate data storage.\n");
            return 1;
            }
        if(*bsize==24){
            *garray=(unsigned char *)malloc(numbytes);
            if(garray==NULL){
                printf("\n");
                printf("BMP_READ: Fatal error!\n");
                printf("  Could not allocate data storage.\n");
                return 1;
                }
            *barray=(unsigned char *)malloc(numbytes);
            if(barray==NULL){
                printf("\n");
                printf("BMP_READ: Fatal error!\n");
                printf("  Could not allocate data storage.\n");
                return 1;
                }
            }
        result=bmp_read_data(filein,*xsize,*ysize,*bsize,*rarray,*garray,*barray);
        if(result==1){
            printf("\n");
            printf("BMP_READ: Fatal error!\n");
            printf("  BMP_READ_DATA failed.\n");
            return 1;
            }
        fclose(filein);
        return 0;
        }
    int bmp_read_data(FILE *filein,int xsize,int ysize,int bsize,unsigned char *rarray,unsigned char *garray,unsigned char *barray){
        int i,j;
        unsigned char *indexb;
        unsigned char *indexg;
        unsigned char *indexr;
        int temp;
        int numbyte;
        numbyte=0;
        for(j=ysize-1;j>0;j--){
            indexr=rarray+xsize*j*sizeof(unsigned char);
            indexg=garray+xsize*j*sizeof(unsigned char);
            indexb=barray+xsize*j*sizeof(unsigned char);
            for(i=0;i<xsize;i++){
                if(bsize==24){
                    temp=fgetc(filein);
                    if(temp==EOF){
                        printf("BMP_READ_DATA: Failed reading data byte %d.\n",numbyte);
                        return 1;
                        }
                    *indexb=(unsigned char)temp;
                    numbyte=numbyte+1;
                    indexb=indexb+1;
                    temp=fgetc(filein);
                    if(temp==EOF){
                        printf("BMP_READ_DATA: Failed reading data byte %d.\n",numbyte);
                        return 1;
                        }
                    *indexg=(unsigned char)temp;
                    numbyte=numbyte+1;
                    indexg=indexg+1;
                    temp=fgetc(filein);
                    if(temp==EOF){
                        printf("BMP_READ_DATA: Failed reading data byte %d.\n",numbyte);
                        return 1;
                        }
                    *indexr=(unsigned char)temp;
                    numbyte=numbyte+1;
                    indexr=indexr+1;
                    }
                else if(bsize==8){
                    temp=fgetc(filein);
                    if(temp==EOF){
                        printf("BMP_READ_DATA: Failed reading data byte %d.\n",numbyte);
                        return 1;
                        }
                    *indexr=(unsigned char)temp;
                    numbyte=numbyte+1;
                    indexr=indexr+1;
                    }
                }
            while(numbyte % 4){
                fgetc(filein);
                numbyte++;
                }
            }
        return 0;
        }
    int bmp_read_header(FILE *filein,int *xsize,int *ysize,int *bsize,int *psize){
        int c1,c2,retval;
        unsigned long int u_long_int_val;
        unsigned short int u_short_int_val;
        c1=fgetc(filein);
        if(c1==EOF)
            return 1;
        c2=fgetc(filein);
        if(c2==EOF)
            return 1;
        if(c1!='B'||c2!='M')
            return 1;
        retval=read_u_long_int(&u_long_int_val,filein);
        if(retval==1)
            return 1;
        retval=read_u_short_int(&u_short_int_val,filein);
        if(retval==1)
            return 1;
        retval=read_u_short_int(&u_short_int_val,filein);
        if(retval==1)
            return 1;
        retval=read_u_long_int(&u_long_int_val,filein);
        if(retval==1)
            return 1;
        retval=read_u_long_int(&u_long_int_val,filein);
        if(retval==1)
            return 1;
        retval=read_u_long_int(&u_long_int_val,filein);
        if(retval==1)
            return 1;
        *xsize=(int)u_long_int_val;
        retval=read_u_long_int(&u_long_int_val,filein);
        if(retval==1)
            return 1;
        *ysize=(int)u_long_int_val;
        retval=read_u_short_int(&u_short_int_val,filein);
        if(retval==1)
            return 1;
        retval=read_u_short_int(&u_short_int_val,filein);
        if(retval==1)
            return 1;
        *bsize=(int)u_short_int_val;
        retval=read_u_long_int(&u_long_int_val,filein);
        if(retval==1)
            return 1;
        retval=read_u_long_int(&u_long_int_val,filein);
        if(retval==1)
            return 1;
        retval=read_u_long_int(&u_long_int_val,filein);
        if(retval==1)
            return 1;
        retval=read_u_long_int(&u_long_int_val,filein);
        if(retval==1)
            return 1;
        retval=read_u_long_int(&u_long_int_val,filein);
        if(retval==1)
            return 1;
        *psize=(int)u_long_int_val;
        retval=read_u_long_int(&u_long_int_val,filein);
        if(retval==1)
            return 1;
        return 0;
        }
    int bmp_read_palette(FILE *filein,int psize){
        int c,i,j;
        for(i=0;i<psize;i++){
            for(j=0;j<4;j++){
                c=fgetc(filein);
                if(c==EOF){
                    return 1;
                    }
                }
            }
        return 0;
        }
    int bmp_write(const char *fileout_name,int xsize,int ysize,int bsize,unsigned char *rarray,unsigned char *garray,unsigned char *barray){
        FILE *fileout;
        int   result;
        fileout=fopen(fileout_name,"wb");
        if(fileout==NULL){
            printf("\n");
            printf("BMP_WRITE - Fatal error!\n");
            printf("  Could not open the output file.\n");
            return 1;
            }
        result=bmp_write_header(fileout,xsize,ysize,bsize);
        if(result==1){
            printf("\n");
            printf("BMP_WRITE: Fatal error!\n");
            printf("  BMP_WRITE_HEADER failed.\n");
            return 1;
            }
        if(bsize==8){
            result=bmp_write_palette(fileout);
            if(result==1){
                printf("\n");
                printf("BMP_WRITE: Fatal error!\n");
                printf("  BMP_WRITE_PALETTE failed.\n");
                return 1;
                }
            }
        result=bmp_write_data(fileout,xsize,ysize,bsize,rarray,garray,barray);
        if(result==1){
            printf("\n");
            printf("BMP_WRITE: Fatal error!\n");
            printf("  BMP_WRITE_DATA failed.\n");
            return 1;
            }
        fclose(fileout);
        return 0;
        }
    int bmp_write_data(FILE *fileout,int xsize,int ysize,int bsize,unsigned char *rarray,unsigned char *garray,unsigned char *barray){
        int i;
        unsigned char *indexb;
        unsigned char *indexg;
        unsigned char *indexr;
        int j;
        int numbyte;
        numbyte=0;
        for(j=ysize-1;j>=0;j--){
            indexr=rarray+xsize*j*sizeof(unsigned char);
            indexg=garray+xsize*j*sizeof(unsigned char);
            indexb=barray+xsize*j*sizeof(unsigned char);
            for(i=0;i<xsize;i++){
                if(bsize==24){
                    fputc(*indexb,fileout);
                    fputc(*indexg,fileout);
                    fputc(*indexr,fileout);
                    indexb=indexb+1;
                    indexg=indexg+1;
                    indexr=indexr+1;
                    numbyte+=3;
                    }
                else{
                    fputc(*indexr,fileout);
                    indexr=indexr+1;
                    numbyte++;
                    }
                }
            while(numbyte %4){
                fputc(0,fileout);
                numbyte++;
                }
            }
        return 0;
        }
    int bmp_write_palette(FILE *fileout){
        int i,j;
        unsigned char c;
        for(i=0;i<256;i++){
            c=(unsigned char)i;
            for(j=0;j<3;j++)
                fputc(c,fileout);
            fputc(0,fileout);
            }
        return 0;
        }
    int bmp_write_header(FILE *fileout,int xsize,int ysize,int bsize){
        int i;
        unsigned long int u_long_int_val;
        unsigned short int u_short_int_val;
        int xsize_aligned;
        fputc('B',fileout);
        fputc('M',fileout);
        if(bsize==8){
            xsize_aligned=xsize;
            while(xsize_aligned %4)
                xsize_aligned++;
            u_long_int_val=xsize_aligned*ysize+54+256*4;
            }
        else{
            xsize_aligned=xsize;
            while(xsize_aligned %4)
                xsize_aligned++;
            u_long_int_val=xsize_aligned*ysize+54;
            }
        write_u_long_int(u_long_int_val,fileout);
        u_short_int_val=0;
        write_u_short_int(u_short_int_val,fileout);
        u_short_int_val=0;
        write_u_short_int(u_short_int_val,fileout);
        if(bsize==8){
            u_long_int_val=1078;
            }
        else{
            u_long_int_val=54;
            }
        write_u_long_int(u_long_int_val,fileout);
        u_long_int_val=40;
        write_u_long_int(u_long_int_val,fileout);
        write_u_long_int(xsize,fileout);
        write_u_long_int(ysize,fileout);
        u_short_int_val=1;
        write_u_short_int(u_short_int_val,fileout);
        u_short_int_val=bsize;
        write_u_short_int(u_short_int_val,fileout);
        u_long_int_val=0;
        write_u_long_int(u_long_int_val,fileout);   //compression
        u_long_int_val=(bsize/8)*xsize*ysize;
        write_u_long_int(u_long_int_val,fileout);
        for(i=2;i<4;i++){
            u_long_int_val=0;
            write_u_long_int(u_long_int_val,fileout);
            }
        if(bsize==8)
            u_long_int_val=256;		//Number of palette colors
        else
            u_long_int_val=0;
        write_u_long_int(u_long_int_val,fileout);
        u_long_int_val=0;
        write_u_long_int(u_long_int_val,fileout);
        return 0;
        }
    int bmp_write_test(char *fileout_name){
        unsigned char *barray;
        unsigned char *garray;
        unsigned char *rarray;
        int i;
        unsigned char *indexb;
        unsigned char *indexg;
        unsigned char *indexr;
        int j;
        int numbytes;
        int result;
        int xsize;
        int ysize;
        int sz=120;
        xsize=sz;
        ysize=sz;
        rarray=NULL;
        garray=NULL;
        barray=NULL;
        numbytes=xsize*ysize*sizeof(unsigned char);
        rarray=(unsigned char*)malloc(numbytes);
        if(rarray==NULL){
            printf("\n");
            printf("BMP_WRITE_TEST: Fatal error!\n");
            printf("  Unable to allocate memory for data.\n");
            return 1;
            }
        garray=(unsigned char*)malloc(numbytes);
        if(garray==NULL){
            printf("\n");
            printf("BMP_WRITE_TEST: Fatal error!\n");
            printf("  Unable to allocate memory for data.\n");
            return 1;
            }
        barray=(unsigned char *)malloc(numbytes);
        if(barray==NULL){
            printf("\n");
            printf("BMP_WRITE_TEST: Fatal error!\n");
            printf("  Unable to allocate memory for data.\n");
            return 1;
            }
        indexr=rarray;
        indexg=garray;
        indexb=barray;
        for(j=0;j<ysize;j++){
            for(i=0;i<xsize;i++){
                if(j<sz/3){
                    *indexr=255;
                    *indexg=0;
                    *indexb=0;
                    }
                else if(j<sz/3*2){
                    *indexr=0;
                    *indexg=255;
                    *indexb=0;
                    }
                else{
                    *indexr=0;
                    *indexg=0;
                    *indexb=255;
                    }
                indexr=indexr+1;
                indexg=indexg+1;
                indexb=indexb+1;
                }
            }
        result=bmp_write(fileout_name,xsize,ysize,24,rarray,garray,barray);
        if(rarray!=NULL){
            free(rarray);
            }
        if(garray!=NULL){
            free(garray);
            }
        if(barray!=NULL){
            free(barray);
            }
        if(result==1){
            printf("\n");
            printf("BMP_WRITE_TEST: Fatal error!\n");
            printf("  BMP_WRITE failed.\n");
            return 1;
            }
        return 0;
        }
    int read_u_long_int(unsigned long int *u_long_int_val,FILE *filein){
        int retval;
        unsigned short int u_short_int_val_hi;
        unsigned short int u_short_int_val_lo;
        if(byte_swap==1){
            retval=read_u_short_int(&u_short_int_val_lo,filein);
            if(retval==1){
                return 1;
                }
            retval=read_u_short_int(&u_short_int_val_hi,filein);
            if(retval==1){
                return 1;
                }
            }
        else{
            retval=read_u_short_int(&u_short_int_val_hi,filein);
            if(retval==1){
                return 1;
                }
            retval=read_u_short_int(&u_short_int_val_lo,filein);
            if(retval==1){
                return 1;
                }
            }
        *u_long_int_val=(u_short_int_val_hi << 16)| u_short_int_val_lo;
        return 0;
        }
    int read_u_short_int(unsigned short int *u_short_int_val,FILE *filein){
        int chi;
        int clo;
        if(byte_swap==1){
            clo=fgetc(filein);
            if(clo==EOF){
                return 1;
                }
            chi=fgetc(filein);
            if(chi==EOF){
                return 1;
                }
            }
        else{
            chi=fgetc(filein);
            if(chi==EOF){
                return 1;
                }
            clo=fgetc(filein);
            if(clo==EOF){
                return 1;
                }
            }
        *u_short_int_val=(chi << 8)| clo;
        return 0;
        }
    int write_u_long_int(unsigned long int u_long_int_val,FILE *fileout){
        unsigned short int  u_short_int_val_hi;
        unsigned short int  u_short_int_val_lo;
        u_short_int_val_hi=(unsigned short)(u_long_int_val / 65536);
        u_short_int_val_lo=(unsigned short)(u_long_int_val % 65536);
        if(byte_swap==1){
            write_u_short_int(u_short_int_val_lo,fileout);
            write_u_short_int(u_short_int_val_hi,fileout);
            }
        else{
            write_u_short_int(u_short_int_val_hi,fileout);
            write_u_short_int(u_short_int_val_lo,fileout);
            }
        return 4;
        }
    int write_u_short_int(unsigned short int u_short_int_val,FILE *fileout){
        unsigned char chi;
        unsigned char clo;
        chi=(unsigned char)(u_short_int_val / 256);
        clo=(unsigned char)(u_short_int_val % 256);
        if(byte_swap==1){
            fputc(clo,fileout);
            fputc(chi,fileout);
            }
        else{
            fputc(chi,fileout);
            fputc(clo,fileout);
            }
        return 2;
        }
    typedef vector<vector<Color>> BMP;
    BMP ReadBMP(string in){
        unsigned char* rarray;
        unsigned char* garray;
        unsigned char* barray;
        int xsize,ysize,bsize;
        rarray=garray=barray=NULL;
        if(bmp_read(in.c_str(),&xsize,&ysize,&bsize,&rarray,&garray,&barray)==1){
            puts("1 BMP_READ failed.");
            }
        printf("%d %d\n",ysize,xsize);
        BMP pic;
        for(int i=0;i<ysize;i++){
            pic.push_back(vector<Color>());
            for(int j=0;j<xsize;j++){
                //printf("%d %d %d\n",i,j,i*xsize+j);
                //printf("%d %d %d\n",rarray[i*xsize+j],rarray[i*xsize+j],rarray[i*xsize+j]);
                pic[i].push_back(Color(rarray[i*xsize+j],garray[i*xsize+j],barray[i*xsize+j]));
                }
            }
        if(rarray)free(rarray);
        if(garray)free(garray);
        if(barray)free(barray);
        return pic;
        }
    int WriteBMP(string out,BMP pic){
        unsigned char* rarray;
        unsigned char* garray;
        unsigned char* barray;
        int xsize=pic.front().size(),ysize=pic.size();
        rarray=new unsigned char[ysize*xsize];
        garray=new unsigned char[ysize*xsize];
        barray=new unsigned char[ysize*xsize];
        for(int i=0;i<ysize;i++){
            for(int j=0;j<xsize;j++){
                rarray[i*xsize+j]=pic[i][j].R;
                garray[i*xsize+j]=pic[i][j].G;
                barray[i*xsize+j]=pic[i][j].B;
                }
            }
        if(bmp_write(out.c_str(),xsize,ysize,24,rarray,garray,barray)==1){
            printf("\n");
            printf("BMP_WRITE failed.\n");
            return 1;
            }
        delete []rarray;
        delete []garray;
        delete []barray;
        return 0;
        }
    vector<string> Dir(string s){
        char szDir[65535];
        char dir[65535];
        WIN32_FIND_DATA FileData;
        HANDLE          hList;
        sprintf(szDir, "%s\\*",s.c_str());
        vector<string> ret;
        if((hList=FindFirstFile(szDir, &FileData))==INVALID_HANDLE_VALUE)
            return ret;
        else{
            while(1){
                if(!FindNextFile(hList,&FileData))
                    if(GetLastError()==ERROR_NO_MORE_FILES)
                        break;
                sprintf(dir,"%s\\%s",s.c_str(),FileData.cFileName);
                ret.push_back(dir);
                }
            }
        FindClose(hList);
        return ret;
        }
    int FileExists(const char * file){
       WIN32_FIND_DATA FindFileData;
       HANDLE handle = FindFirstFile(file, &FindFileData) ;
       int found = handle != INVALID_HANDLE_VALUE;
       if(found){
            //FindClose(&handle); this will crash
            FindClose(handle);
            }
       return found;
    }
    string FileFullName(string s){
        char szBuffer[1000] = "";
        GetFullPathName(s.c_str(),sizeof(szBuffer),szBuffer,NULL);
        return szBuffer;
        }
    class rwlock {
        private:
            mutex _lock;
            condition_variable _wcon, _rcon;
            unsigned _writer, _reader;
            int _active;
        public:
            void read_lock() {
                unique_lock<mutex> lock(_lock);
                ++_reader;
                while(_active < 0 || _writer > 0)
                    _rcon.wait(lock);
                --_reader;
                ++_active;
                }
            void write_lock() {
                unique_lock<mutex> lock(_lock);
                ++_writer;
                while(_active != 0)
                    _wcon.wait(lock);
                --_writer;
                _active = -1;
                }
            void unlock() {
                unique_lock<mutex> lock(_lock);
                if(_active > 0) {
                    --_active;
                    if(_active == 0) _wcon.notify_one();
                    }
                else{
                    _active = 0;
                    if(_writer > 0) _wcon.notify_one();
                    else if(_reader > 0) _rcon.notify_all();
                    }

                }
            rwlock():_writer(0),_reader(0),_active(0){}
        };


    typedef RGBQUAD *pBGR;
    Thread Background_Update_Screen_Thread=NULL;
    pBGR Background_Update_Screen_Buff;
    bool Background_Update_Screen_Off=1;
    rwlock Background_Update_Screen_Lock;
    void Background_Update_Screen_Func(){
        HBITMAP bmp_copy;
        BITMAPINFO bi;
        HDC sr, sr_copy;
        sr=GetDC(GetDesktopWindow());
        sr_copy=CreateCompatibleDC(sr);
        bmp_copy= CreateCompatibleBitmap(sr, _ScreenX, _ScreenY);
        SelectObject(sr_copy, bmp_copy);
        bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
        bi.bmiHeader.biWidth = _ScreenX;
        bi.bmiHeader.biHeight = _ScreenY;
        bi.bmiHeader.biPlanes = 1;
        bi.bmiHeader.biBitCount = 32;
        bi.bmiHeader.biCompression = BI_RGB;
        bi.bmiHeader.biSizeImage = _ScreenX * _ScreenY * 4 ;
        bi.bmiHeader.biClrUsed = 0;
        bi.bmiHeader.biClrImportant = 0;

        while(1){
            //buf = (pBGR) malloc(_ScreenX * _ScreenY * 4);
            BitBlt(sr_copy, 0, 0, _ScreenX, _ScreenY, sr, 0, 0, SRCCOPY);
            Background_Update_Screen_Lock.write_lock();
            GetDIBits(sr_copy, bmp_copy, 0, _ScreenY, Background_Update_Screen_Buff, &bi, NULL);
            Background_Update_Screen_Lock.unlock();
            //Pos p=GetPos();
            if(Background_Update_Screen_Off)return;
            Delay(1);
            }
        }
    Color GetColFast(int x,int y){
        if(Background_Update_Screen_Off==1)
            Background_Update_Screen_Buff= (pBGR) malloc(_ScreenX * _ScreenY * 4),
            Background_Update_Screen_Off=0,
            Background_Update_Screen_Thread=ThreadCreate(Background_Update_Screen_Func);
        //Background_Update_Screen_Lock.read_lock();
        Color ret=Color(
            Background_Update_Screen_Buff[(_ScreenY-y-1)*_ScreenX+x].rgbRed,
            Background_Update_Screen_Buff[(_ScreenY-y-1)*_ScreenX+x].rgbGreen,
            Background_Update_Screen_Buff[(_ScreenY-y-1)*_ScreenX+x].rgbBlue);
        //Background_Update_Screen_Lock.unlock();
        return ret;
        }
    Color GetColFast(par p){
        return GetColFast(p.f,p.s);
        }
    void GetColFastStop(){
        if(Background_Update_Screen_Thread)
            free(Background_Update_Screen_Buff),
            Background_Update_Screen_Off=1,
            Wait(Background_Update_Screen_Thread);
        }
    void _SetConsoleTitle(const char* title){
        SetConsoleTitle(title);
        }
    void _GetConsoleTitle(char* title, DWORD nSize){
        GetConsoleTitle(title, nSize);
        }
    void gotoxy(int x, int  y){
        COORD point;
        point.X = x, point.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
        }
    void getxy(int &x, int &y){
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        x = csbi.dwCursorPosition.X;
        y = csbi.dwCursorPosition.Y;
        }
    void SetCursorVisible(BOOL Visible, DWORD Size){
        CONSOLE_CURSOR_INFO cci;
        cci.bVisible = Visible;
        cci.dwSize = Size;
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
        }
    void Clr(){
        COORD coordScreen = { 0, 0 };
        DWORD cCharsWritten;
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        DWORD dwConSize;
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        GetConsoleScreenBufferInfo(hConsole, &csbi);
        dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
        FillConsoleOutputCharacter(hConsole, TEXT(' '),
                dwConSize,
                coordScreen,
                &cCharsWritten);
        GetConsoleScreenBufferInfo(hConsole, &csbi);
        FillConsoleOutputAttribute(hConsole,
                csbi.wAttributes,
                dwConSize,
                coordScreen,
                &cCharsWritten);
        SetConsoleCursorPosition(hConsole, coordScreen);
        }
    void SetColor(int color=-1){
        switch (color){
        case 0:    // White on Black
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                FOREGROUND_INTENSITY | FOREGROUND_RED |
                FOREGROUND_GREEN | FOREGROUND_BLUE);
            break;
        case 1:    // Red on Black
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                FOREGROUND_INTENSITY | FOREGROUND_RED);
            break;
        case 2:    // Green on Black
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                FOREGROUND_INTENSITY | FOREGROUND_GREEN);
            break;
        case 3:    // Yellow on Black
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                FOREGROUND_INTENSITY | FOREGROUND_RED |
                FOREGROUND_GREEN);
            break;
        case 4:    // Blue on Black
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                FOREGROUND_INTENSITY | FOREGROUND_BLUE);
            break;
        case 5:    // Magenta on Black
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                FOREGROUND_INTENSITY | FOREGROUND_RED |
                FOREGROUND_BLUE);
            break;
        case 6:    // Cyan on Black
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                FOREGROUND_INTENSITY | FOREGROUND_GREEN |
                FOREGROUND_BLUE);
            break;
        case 7:    // Black on Gray
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                BACKGROUND_INTENSITY | BACKGROUND_INTENSITY);
            break;
        case 8:    // Black on White
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                BACKGROUND_INTENSITY | FOREGROUND_INTENSITY |
                BACKGROUND_RED | BACKGROUND_GREEN |
                BACKGROUND_BLUE);
            break;
        case 9:    // Red on White
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                BACKGROUND_INTENSITY | FOREGROUND_INTENSITY |
                BACKGROUND_RED | BACKGROUND_GREEN |
                BACKGROUND_BLUE |
                FOREGROUND_RED);
            break;
        case 10:    // Green on White
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                BACKGROUND_INTENSITY | FOREGROUND_INTENSITY |
                BACKGROUND_RED | BACKGROUND_GREEN |
                BACKGROUND_BLUE | FOREGROUND_GREEN);
            break;
        case 11:    // Yellow on White
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                BACKGROUND_INTENSITY | FOREGROUND_INTENSITY |
                BACKGROUND_RED | BACKGROUND_GREEN |
                BACKGROUND_BLUE | FOREGROUND_RED |
                FOREGROUND_GREEN);
            break;
        case 12:    // Blue on White
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                BACKGROUND_INTENSITY | FOREGROUND_INTENSITY |
                BACKGROUND_RED | BACKGROUND_GREEN |
                BACKGROUND_BLUE | FOREGROUND_BLUE);
            break;
        case 13:    // Magenta on White
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                BACKGROUND_INTENSITY | FOREGROUND_INTENSITY |
                BACKGROUND_RED | BACKGROUND_GREEN |
                BACKGROUND_BLUE | FOREGROUND_RED |
                FOREGROUND_BLUE);
            break;
        case 14:    // Cyan on White
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                BACKGROUND_INTENSITY | FOREGROUND_INTENSITY |
                BACKGROUND_RED | BACKGROUND_GREEN |
                BACKGROUND_BLUE | FOREGROUND_GREEN |
                FOREGROUND_BLUE);
            break;
        case 15:    // White on White
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                BACKGROUND_INTENSITY | FOREGROUND_INTENSITY |
                BACKGROUND_RED | BACKGROUND_GREEN |
                BACKGROUND_BLUE | FOREGROUND_RED |
                FOREGROUND_GREEN | FOREGROUND_BLUE);
            break;
        default :    // White on Black
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                FOREGROUND_INTENSITY | FOREGROUND_RED |
                FOREGROUND_GREEN | FOREGROUND_BLUE);
            break;
            }
        }
    BOOL SetConsoleSize(int W, int H){
        BOOL ret;
        SMALL_RECT SR;
        SR.Top = 0;
        SR.Left = 0;
        SR.Bottom = H-1;
        SR.Right = W-1;
        ret = SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE),TRUE, &SR);
        if(!ret) return ret;

        COORD Sz;
        Sz.X = W;
        Sz.Y = H;

        return SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),Sz);
        }
    void ConsoleFullScreen(){
        keybd_event(VK_MENU,0x38,0,0);
        keybd_event(VK_RETURN,0x1c,0,0);
        keybd_event(VK_MENU,0xb8,KEYEVENTF_KEYUP,0);
        keybd_event(VK_RETURN,0x9c,KEYEVENTF_KEYUP,0);
        }
    BOOL IsConsoleFullScreen(){
        // CONSOLE_FULLSCREEN(1), CONSOLE_FULLSCREEN_HARDWARE(2)
        DWORD mode;
        GetConsoleDisplayMode(&mode);
        if( (mode&CONSOLE_FULLSCREEN) == CONSOLE_FULLSCREEN) return TRUE;
        return FALSE;
        }
    void GetConsoleWindowSize(DWORD &W, DWORD &H){
        CONSOLE_FONT_INFO cfi;
        GetCurrentConsoleFont(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
        W = cfi.dwFontSize.X;
        H = cfi.dwFontSize.Y;
        }
    void _GetLargestConsoleWindowSize(DWORD &W, DWORD &H){
        COORD c = GetLargestConsoleWindowSize(GetStdHandle(STD_OUTPUT_HANDLE));
        W = c.X;
        H = c.Y;
        }

    void SetConsoleWindowSize(SHORT x, SHORT y){
        CONSOLE_FONT_INFOEX cfi;
        cfi.dwFontSize.X = x;
        cfi.dwFontSize.Y = y;
        SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE),
            FALSE, &cfi);
        }
    void SetTransparenty(HWND hWnd,int alpah=127){
        SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
        SetLayeredWindowAttributes(hWnd, 0, 255, LWA_ALPHA);
        }
    void SetTransparentyColor(HWND hWnd,int color,int alpah=255){
        SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
        SetLayeredWindowAttributes(hWnd, color, 255, LWA_COLORKEY);
        }
    HWND GetHwndFromPoint(Pos p){
        POINT pt;
        pt.x=p.f;
        pt.y=p.s;
        return WindowFromPoint(pt);
        }
    }
