#include <iostream>
#include <string.h>
void scor (int k,int &x)
{
    if(x<0)x=0;
    if(actualizareInteractiuneJucator()==3)x=x+5;  // nu stiu ce trebuie bagat in Joc.
    if(actualizareInteractiuneJucator()==2){x=x-5;k=0;}
}
const char * rankp (int x)
{
        if(x>=0){
                        if(x>=75 && x<100) return "Bronze"; //
                        if(x>=100 && x<125)return "Silver"; //
                        if(x>=125 && x<150)return "Gold"; //
                        if(x>=150 && x<175)return "Platinum"; //
                        if(x>=175 && x<200)return "Diamond"; //
                        if(x>=200)return "Challenger"; //
                          }
}
const char * titlu (int x)
{
    if(strcmp(rankp(x),"Bronze")==0) return "Novice";
    if(strcmp(rankp(x),"Silver")==0) return "Learner";
    if(strcmp(rankp(x),"Gold")==0) return "Master of Words";
    if(strcmp(rankp(x),"Platinum")==0) return "Grand Master of Words";
    if(strcmp(rankp(x),"Diamond")==0) return "The Supreme Master of Words";
    if(strcmp(rankp(x),"Challenger")==0) return "Knowledge Conqueror";
}
