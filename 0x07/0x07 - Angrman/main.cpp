#pragma GCC optimize ("O3")
#include<bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;
#define f first
#define s second
typedef pair<int,int>par;
typedef pair<int,par>pr;
typedef long long int LL;
char key[15];
int main(){
    char val1,val2,val3,val4,val5,val6,val7,val8,val9,valA,valB,valC,valD,valE,valF;
    for(char a1='0';a1<='9';a1++)
    for(char a2='0';a2<='9';a2++)
    for(char a3='0';a3<='9';a3++){
        val1 = 1 ^ (4 + a2) ^ (a1 - 2) ^ (unsigned __int8)(a3 + (a2 & a3) - a1);
        val2 = (4 + a2) ^ (a1 - 2) ^ val1 ^ (a3 + a2);
        val3 = a1 - (a3 ^ (a1 - val2) ^ val1 ^ (4 + a2));
        if(val1==44&&val2==82&&val3==58){
            key[0]=a1;
            key[5]=a2;
            key[10]=a3;
            a1=a2=a3=99;
            }
        }
    for(char a1='0';a1<='9';a1++)
    for(char a2='0';a2<='9';a2++)
    for(char a3='0';a3<='9';a3++){
        val4 = (4 + a2) ^ (a1 * val1 - val2) ^ (((a1 + a2) / a3) + a3);
        val5 = (a1 - a2 * val3 + 5) ^ val2 ^ ((unsigned int)((a3 + (char)a1) / (char)a1) + a3);
        val6 = (a1 - val4) ^ val3 ^ (a2 + a1 + a2 + a3 * 6 + a3);
        if(val4==67&&val5==-125&&val6==56){
            key[1]=a1;
            key[6]=a2;
            key[11]=a3;
            a1=a2=a3=99;
            }
        }
    for(char a1='0';a1<='9';a1++)
    for(char a2='0';a2<='9';a2++)
    for(char a3='0';a3<='9';a3++){
        val7 = (7 + a2) ^ (a1 - val2) ^ val4 ^ (a3 + a1);
        val8 = (8 + a2) ^ (a1 - val3) ^ val5 ^ (a3 + a2);
        val9 = (9 + a2) ^ (a1 - val4) ^ val6 ^ 2 * a3;
        if(val7==-2&&val8==39&&val9==-110){
            key[2]=a1;
            key[7]=a2;
            key[12]=a3;
            a1=a2=a3=99;
            }
        }
    for(char a1='0';a1<='9';a1++)
    for(char a2='0';a2<='9';a2++)
    for(char a3='0';a3<='9';a3++){
        valA = (val2 + a2) ^ (a1 - val3) ^ val4 ^ (a3 - a1);
        valB = (val7 + a2) ^ (a1 - val6) ^ val5 ^ (a3 - a2);
        valC = (a1 - val9) ^ val8 ^ (((val2 + a2) ^ (a1 - val3) ^ val4 ^ (a3 - a1)) + a2);
        if(valA==50&&valB==75&&valC==-36){
            key[3]=a1;
            key[8]=a2;
            key[13]=a3;
            a1=a2=a3=99;
            }
        }
    for(char a1='0';a1<='9';a1++)
    for(char a2='0';a2<='9';a2++)
    for(char a3='0';a3<='9';a3++){
        valD = 0xD^(val7 + a2) ^ (a1 - valA) ^ (unsigned __int8)(a3 + a1);
        valE = (val8 + a2) ^ (a1 - 0xE) ^ valB ^ (a3 + a2);
        valF = (0xF + a2) ^ (a1 - valC) ^ val6 ^ 2 * a3;
        if(valD==-65&&valE==82&&valF==79){
            key[4]=a1;
            key[9]=a2;
            key[14]=a3;
            a1=a2=a3=99;
            }
        }
    for(int i=0;i<15;i++)
        putchar(key[i]);
    }
