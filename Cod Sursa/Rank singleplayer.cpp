#include <iostream>
#include <string.h>
using namespace std;
void scor (int &x)//x=0 la apelare
    if(actualizareInteractiuneJucator()==3)x=x+1;
const char * ranksp (int x)
{
        if(x>=0){
                        if(x>=0 && x<5) return  "E"; //
                        if(x>=5 && x<10)return  "D";
                        if(x>=10 && x<15)return "C"; //
                        if(x>=15 && x<20)return "B"; //
                        if(x==20 && timp()==1)return "S";
                        if(x==20)return "A";
                }
}
int minigame101 (int x)
{
    if(x>=15)return 1;
    else return 0;
}
