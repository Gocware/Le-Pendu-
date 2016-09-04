#ifndef SISTEM_BAZA_H
#define SISTEM_BAZA_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<string>
#include<windows.h>
using namespace std;
class ObjAnimTranzTxt
{
   public :
       void reset();
       sf::Text *afis;
       sf::Clock timpAnim;
       char str1[100],str2[100];
       float pozXinit, pozYinit;
       int terminat, initializat, schimba = -1;
};
class ObjAnimNotificare
{
   public :
       char notificare[500];
       sf::Text afis_notif, titlu_notif, press_enter;
       sf::Texture textura_notificare;
       sf::Sprite sprite_notificare;
       sf::Clock timpAnimatie;
       sf::Clock timpEnter;
       int stagiuNotificare = 0;
       int ratieCuloare = -1;
       int apasatEnter = 0;
       float afis_notif_x = 320, afis_notif_y = 360, titlu_notif_x = 310, titlu_notif_y = 300 , press_enter_x = 400, press_enter_y = 550;
       float afis_sz = 80, press_enter_sz = 40, titlu_notif_sz = 150;
       bool init = false;

};
class Sectiune_Text
{
    public :
        Sectiune_Text();
        Sectiune_Text *urmatorul,*spate;
        unsigned indice;
        char text[100];
};
class Sectiune_Text_Lista
{
    public :
        Sectiune_Text_Lista(); // Implementat
        ~Sectiune_Text_Lista(); // Implementat
        unsigned nrElemente(); // Implementat
        void stergeLista(); // Implementat
        void adaugaLinie(char text[100]); // Implementat
        void stergeCuvant(unsigned indice_stergere);
        void gasesteText(unsigned indice_cautare, char text[100]); // Implementat
    private :
        Sectiune_Text *travers, *inceput;
};

class Sistem_Baza
{
    public:
        static unsigned liniiScrise(ifstream &fisier); // Implementat
        static void scrieParagraf(ifstream &fisier, char delimitare[20], Sectiune_Text_Lista &lista); // Implementat
        static int Anim_TranzSelectTxt(ObjAnimTranzTxt &tranz, sf::RenderWindow &f); // Imlementat
        static int AfiseazaNotificare(ObjAnimNotificare &notif,sf::RenderWindow &f, sf::Font &font); // Implementat
        static string path();
    private:
};
#define J_MSG_INITT 1
#define J_MSG_DC 2
class Joc
{
    public :
        char string_curent[100];
        short interschimbare(char string_curent[100],char cuvant[100],short n);//Implementat
        int formeazaJoc(char categ_param[100], int mesaj, int &nrCuv); // Implementat
        int actualizareInteractiuneJucator(const char *mesaj);//Implementat
        void reset();
        char cuvant[100];
        char categorie[100];
    private :
};
class Date_Utilizator
{
     public :
         Date_Utilizator *urmatorul;
         int nrVictorii, nrPierderi, jocuriActive;
         int indice;
         char nume[100];
         string rang;
         Joc joc_curent;
         Date_Utilizator();
         void formareUtilizator(char nume_param[100], Joc &joc);
};
class Lista_Utilizatori
{
     public :
         Lista_Utilizatori(); // Implementat
         ~Lista_Utilizatori(); // Implementat
         Date_Utilizator *inceput, *travers;
         void adauga(Date_Utilizator utilizator_nou); // Implementat
         void scrieListaInFisier();
         void initializeazaListaDinFisier();
         Date_Utilizator *gaseste_utilizator(int poz); // Implementat
         unsigned nrUtilizatori(); // Implementat

};
#endif // SISTEM_BAZA_H
