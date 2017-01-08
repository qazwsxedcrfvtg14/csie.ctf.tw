#include<bits/stdc++.h>
using namespace std;
string dream="appleappleappleap%ff%ff%ff%ffpleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleappleGGGGG%GGGGGGGGGGGGGGGGGGGGGGGGgGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGgGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGg";
int main(){
    char *s,*ss;
    s=(char*)malloc(4096);
    strcpy(s,dream.c_str());
    for(int i=0;s[i];i++)
        if(s[i]=='&'||s[i]=='#'){
            s[i]='\0';
            break;
            }
    ss=(char*)malloc(strlen(s));
    //strcpy(ss,ss);
    for(int i=0,j=0;;i++,j++){
        if(s[i]=='%'){
            s[j]=s[i+1]<'a'?s[i+1]-'0':(s[i+1]|32)-'a'+10;
            s[j]*=16;
            s[j]+=s[i+2]<'a'?s[i+2]-'0':(s[i+2]|32)-'a'+10;
            i+=2;
            }
        else if(s[i]=='+')
            s[j]=' ';
        else{
            s[j]=s[i];
            if(!s[j])break;
            }
        }
    printf("{\"lehgth\"=%d,\"Come_True\":true,\"dream\"=\"%s\"}",(int)strlen(s),s);
    }
