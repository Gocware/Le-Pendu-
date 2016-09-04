#include "Buton.h"
#include "Comunicare.h"
#include "Sistem_Baza.h"
#include "Animatii.h"
#include "windows.h"
#include "mgame1.cpp"
#define meniu_prof_add 1
#define meniu_norm 2
#define meniu_prof_sel 3
#define joc_selcateg 4
#define joc_spanz 5
#define INTRO 6
#define lose1 7
#define lose2 8
#define minigame1 9
#define minigame2 10
#define minigame3 11
#define adauga_categ 12
#include <sstream>
#define castig 30
#define fail2 31
Date_Utilizator *util_curent;
sf::Clock mAdd, mSel, mP, mW, jSPI, jSLCATEG;
int mesaj_interf = 0;
int nivelCurent = 0;
char categorie[100];
Lista_Utilizatori list_util;
sf::Font font;
sf::Sprite background;
sf::Texture bg;
sf::Music curent;
void miniGame3(sf::RenderWindow &f)
{
    static bool init = false;
    static sf::Clock intro, salt, global, tmpsalt;
    static sf::Text tmp;
    static int _salt, _tmp = 90;
    static int pozO = 2000;
    static float viteza = 10;
    static sf::Texture player, obstacol,bg,sp;
    static sf::Sprite pl,obs,bgmm,sep;
    string contor;
    if(global.getElapsedTime().asSeconds() > 1)
    {
        int cop = _tmp;
        while(cop)
        {
            contor += (cop%10 + '0');
            cop/= 10;
        }
        reverse(contor.begin(),contor.end());
        global.restart();
        _tmp-=1;
        tmp.setString(contor);
    }
    if(!_tmp)
    {
        init = false;
        nivelCurent = castig;
    }
    if(!init)
    {
        curent.stop();
        string pax = Sistem_Baza::path();
        pax += "audio/minigame.ogg";
        curent.openFromFile(pax);
        curent.setVolume(100);
        curent.play();
        tmpsalt.restart();
        tmp.setFont(font);
        tmp.setCharacterSize(60);
        tmp.setPosition(100,100);
        global.restart();
        _salt = 0;
        _tmp = 60;
        viteza = 10;
        intro.restart();
        salt.restart();
        global.restart();
        init = true;
        string pth = Sistem_Baza::path();
        pth += "grafica\\1.png";
        player.loadFromFile(pth);
        pth = Sistem_Baza::path();
        pth += "grafica\\mob.png";
        obstacol.loadFromFile(pth);
        pth = Sistem_Baza::path();
        pth += "grafica\\mm3bg.jpg";
        bg.loadFromFile(pth);
        pth = Sistem_Baza::path();
        pth += "grafica\\sp.png";
        sp.loadFromFile(pth);
        sep.setTexture(sp);
        sep.setScale(10,1);
        sep.setPosition(-800,350);
        pl.setTexture(player);
        //pl.setScale(0.07,0.07);
        bgmm.setTexture(bg);
        obs.setTexture(obstacol);
        obs.setPosition(pozO,350);
        pl.setPosition(200,350);
    }
    obs.setPosition(pozO,350);
    sf::FloatRect coliz1 = obs.getGlobalBounds();
    sf::FloatRect coliz2 = pl.getGlobalBounds();
    if(obs.getPosition() == pl.getPosition())
    {
        init = false;
        nivelCurent = fail2;
    }
    if(_salt)pl.setPosition(200,220);
    if(tmpsalt.getElapsedTime().asSeconds() > 0.4)
    {
        pl.setPosition(200,350);
        _salt = 0;
        tmpsalt.restart();
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && salt.getElapsedTime().asSeconds() > 0.4)
    {
        _salt = 1;
        salt.restart();
        tmpsalt.restart();
    }
    else _salt = 0;
    if(pozO < 0)
    {
        pozO = 2000;
        viteza+= 1;
    }
    pozO -= viteza;
    f.draw(bgmm);
    f.draw(pl);
    f.draw(obs);
    f.draw(tmp);
    f.draw(sep);
}
string getFisier(char *filter = "Selectionnez une image pour mot.\0*.*\0.png\0*.*\0.jpeg\0.\0", HWND owner = NULL)
{
   OPENFILENAME ofn;
   char fileName[MAX_PATH] = "";
   ZeroMemory(&ofn, sizeof(ofn));
   ofn.lStructSize = sizeof(OPENFILENAME);
   ofn.hwndOwner = owner;
   ofn.lpstrFilter = filter;
   ofn.lpstrFile = fileName;
   ofn.nMaxFile = MAX_PATH;
   ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
   ofn.lpstrDefExt = "";
   string fileNameStr;
   if(GetOpenFileName(&ofn) )fileNameStr = fileName;
   return fileNameStr;
}
void Fail2(sf::RenderWindow &f)
{
    static sf::Text t;
    static bool init = false;
    static sf::Clock p;
    if(!init)
    {
        string pz;
        pz = Sistem_Baza::path();
        pz+="audio/fail.ogg";
        curent.stop();
        curent.openFromFile(pz);
        curent.setVolume(100);
        curent.play();
        wstring m = L"Vous avez échoué!";
        t.setString(m);
        t.setCharacterSize(70);
        t.setPosition(380,300);
        t.setFont(font);
        p.restart();
        init = true;
    }
    if(p.getElapsedTime().asSeconds() < 3)f.draw(t);
    else
    {
        nivelCurent = meniu_norm;
        curent.stop();
        string pth;
        pth = Sistem_Baza::path();
        pth += "audio/meniu.ogg";
        curent.openFromFile(pth);
        curent.setVolume(100);
        curent.play();
        init = false;
    }
}
void Castig(sf::RenderWindow &f)
{
    static sf::Text t;
    static bool init = false;
    static sf::Clock p;
    if(!init)
    {
        curent.stop();
        string pz;
        pz = Sistem_Baza::path();
        pz+="audio/castig.ogg";
        curent.openFromFile(pz);
        curent.setVolume(100);
        curent.play();
        util_curent->rang += categorie;
        util_curent->rang += ' ';
        util_curent->rang += 'B';
        util_curent->rang += '\n';
        list_util.scrieListaInFisier();
        t.setString("Vous gagnez!");
        t.setCharacterSize(70);
        t.setPosition(390,350);
        t.setFont(font);
        p.restart();
        init = true;
    }
    if(p.getElapsedTime().asSeconds() < 3)f.draw(t);
    else
    {
        nivelCurent = meniu_norm;
        curent.stop();
        string pth;
        pth = Sistem_Baza::path();
        pth += "audio/meniu.ogg";
        curent.openFromFile(pth);
        curent.setVolume(100);
        curent.play();
        mP.restart();
        init = false;
    }
}
void adaugaCategorie(sf::RenderWindow &f,Comunicare &c)
{
    static sf::Clock timp;
    static bool init = false;
    static sf::Text mesajUtil,interact,yes,no;
    static int stadiuAdaug;
    static int x, y;
    static int tranzOut, gata;
    static string numeCateg, cuvant, bazaDate;
    static wstring msg;
    if(!init)
    {
        c.text_dl_tastatura.clear();
        bazaDate.clear();
        numeCateg.clear();
        msg.clear();
        cuvant.clear();
        timp.restart();
        tranzOut = 0;
        gata = 0;
        msg = L"Entrez le nom de la catégorie:";
        mesajUtil.setFont(font);
        mesajUtil.setCharacterSize(50);
        mesajUtil.setString(msg);
        yes.setString("Oui");
        yes.setFont(font);
        yes.setCharacterSize(60);
        yes.setPosition(580,350);
        no.setString("Non");
        no.setFont(font);
        no.setCharacterSize(60);
        no.setPosition(580,400);
        x = 580;
        y = -100;
        interact.setFont(font);
        interact.setCharacterSize(60);
        interact.setPosition(620,350);
        mesajUtil.setPosition(x,y);
        stadiuAdaug = 0;
        init = true;
    }
    if(stadiuAdaug == 0)
    {
        if(!c.text_dl_tastatura.empty() && sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
        {
            numeCateg = c.text_dl_tastatura;
            string linie;
            string pth = Sistem_Baza::path();
            pth += "bazaDate/baza.txt";
            ifstream fisier(pth.c_str());
            while(getline(fisier,linie))
            {
                linie += '\n';
                bazaDate += linie;
            }
            fisier.close();
            bazaDate += numeCateg;
            bazaDate += '\n';
            stadiuAdaug = 1;
            c.text_dl_tastatura.clear();
            timp.restart();
        }
    }
    if(stadiuAdaug == 1)
    {
        msg = L"Tapez le mot, sélectionnez une image:";
        if(!c.text_dl_tastatura.empty() && sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
        {
            cuvant = c.text_dl_tastatura;
            c.text_dl_tastatura.clear();
            for(int i = 0;i<cuvant.size();++i)
                if(cuvant[i]<=(int)'z' && cuvant[i]>=(int)'a')cuvant[i]-=32;
            bazaDate += cuvant;
            bazaDate += '\n';
            stadiuAdaug = 2;
            timp.restart();
        }
    }
    if(stadiuAdaug == 2)
    {
        string img;
        msg = L"Sélectionnez une image pour le mot:";
        mesajUtil.setString(msg);
        img = getFisier();
        if(!img.empty())
        {
            int i = img.size()-1;
            for(;img[i]!='\\';)--i;
            ++i;
            string destinatie;
            destinatie += Sistem_Baza::path();
            destinatie += "bazaDate\\Imagini\\";
            destinatie += cuvant;
            for(;img[i]!='.';)++i;
            for(;i<img.size();++i)destinatie+=img[i];
            CopyFile(img.c_str(),destinatie.c_str(),FALSE);
            stadiuAdaug = 3;
        }
        timp.restart();
    }
    static int alegere = 0;
    if(stadiuAdaug == 3)
    {
        msg = L"Souhaitez-vous ajouter un autre mot?";
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && alegere == 1)
        {
            bazaDate += numeCateg;
            string pth;
            pth += Sistem_Baza::path();
            pth += "bazaDate/baza.txt";
            ofstream baza(pth.c_str());
            baza<<bazaDate;
            baza.close();
            string listaCateg;
            pth = Sistem_Baza::path();
            pth+="bazaDate\\listacateg.txt";
            ifstream lista(pth.c_str());
            string linie;
            while(getline(lista,linie))
            {
                linie += '\n';
                listaCateg += linie;
            }
            lista.close();
            int i = listaCateg.size() - 1;
            for(;listaCateg[i]!='C';)--i;
            string copie;
            for(int j = 0;j<i;++j)copie += listaCateg[j];
            copie += numeCateg;
            copie += '\n';
            copie += "CATEGORII";
            listaCateg = copie;
            ofstream schimbaLista(pth.c_str());
            schimbaLista << listaCateg;
            schimbaLista.close();
            init = false;
            mP.restart();
            nivelCurent = meniu_norm;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && alegere == 0)stadiuAdaug = 1;
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))alegere = 1;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))alegere = 0;
        }
    }
    if((y < 300 || y > 800) && !tranzOut)
    {
        y+=10;
        mesajUtil.setPosition(x,y);
    }else tranzOut = 1;
    interact.setString(c.text_dl_tastatura);
    mesajUtil.setString(msg);
    f.draw(background);
    f.draw(mesajUtil);
    f.draw(interact);
    yes.setPosition(580,350);
    no.setPosition(580,400);
    if(alegere == 0)yes.setPosition(620,350);
    else if(alegere == 1)no.setPosition(620,400);
    if(stadiuAdaug == 3)
    {
        f.draw(yes);
        f.draw(no);
    }
    AfisSpanz::DesSpanz(f,0);
}
int asauf (sf::RectangleShape Patrat,sf::RectangleShape Dr[100])
    {
        for(int i=1;i<=48;i++)
        {
            sf::FloatRect p = Patrat.getGlobalBounds();
            if(p.intersects(Dr[i].getGlobalBounds()))return 0;
        }
        return 1;
    }
    int buton (sf::RectangleShape Patrat,sf::RectangleShape B1)
    {
            sf::FloatRect p = Patrat.getGlobalBounds();
            if(p.intersects(B1.getGlobalBounds()) )return 0;
        return 1;
    }
    int zid (sf::RectangleShape Patrat,sf::RectangleShape BD1)
    {
            sf::FloatRect p = Patrat.getGlobalBounds();
            if(p.intersects(BD1.getGlobalBounds()) )return 0;
        return 1;
    }
    int collision(sf::RectangleShape Patrat,sf::CircleShape C[100])
    {
        for(int i=1;i<=12;i++)
        {
            sf::FloatRect p = Patrat.getGlobalBounds();
            if(p.intersects(C[i].getGlobalBounds()))return 0;
        }
        return 1;
    }
    int Won(sf::RectangleShape Patrat,sf::RectangleShape End)
    {
        sf::FloatRect p = Patrat.getGlobalBounds();
            if(p.intersects(End.getGlobalBounds()))return 0;
        return 1;
    }

int miniGame1(sf::RenderWindow &a)
{
    static bool init = false;
    static sf::RectangleShape Dr[100];
    static sf::CircleShape C[100];
    static int i;
    static string W="You Won!";
    static string GO="You Lose!";
    static sf::Clock time;
    //TEXT WIN/LOOSE
    static sf::Text t3;
    static sf::Font f3;
    static sf::Text t4;
    static sf::Font f4;
    static sf::Color S,E;
    static sf::RectangleShape Start (sf::Vector2f(40,37));
    static sf::RectangleShape End   (sf::Vector2f(40,37));
    static sf::Color color;
    static sf::RectangleShape Patrat(sf::Vector2f(20,20));
    static sf::Color b1,b2,b3;
    static sf::RectangleShape B1 (sf::Vector2f(37,37));
    static sf::RectangleShape B2 (sf::Vector2f(40,37));
    static sf::RectangleShape B3 (sf::Vector2f(38,40));
    static sf::RectangleShape B4 (sf::Vector2f(38,40));
    static sf::RectangleShape BD1 (sf::Vector2f(80,35));
    static sf::RectangleShape BD2 (sf::Vector2f(41,122));
    static sf::RectangleShape BD3 (sf::Vector2f(80,36));
    static sf::Color CC;
    static sf::Color cmap;
    static float x=640,y=125,m=0,n=0;
    static float Cy4=125,Cy5=125,Cy6=162,Cy7=162,Cy8=235,Cx1=478,Cx2=845,Cx3=479,Cx9=540,Cx10=740,Cx11=740,Cx12=540,x1=0,x2=0,x3=0,x9=0,x10=0,x11=0,x12=0,y4=0,y5=0,y6=0,y7=0,y8=0;
    static int L=1,Won1=0;
    if(!init)
    {
        curent.stop();
        string pax = Sistem_Baza::path();
        pax += "audio/minigame2.ogg";
        curent.openFromFile(pax);
        curent.setVolume(100);
        curent.play();
        Cy4=125,Cy5=125,Cy6=162,Cy7=162,Cy8=235,Cx1=478,Cx2=845,Cx3=479,Cx9=540,Cx10=740,Cx11=740,Cx12=540,x1=0,x2=0,x3=0,x9=0,x10=0,x11=0,x12=0,y4=0,y5=0,y6=0,y7=0,y8=0;
        x=640,y=125,m=0,n=0;
        L=1,Won1=0;
        string pth;
        pth += Sistem_Baza::path();
        pth += "grafica\\font1.ttf";
        f3.loadFromFile(pth);
        t3.setString(W);
        t3.setFont(f3);
        t3.setCharacterSize(75);
        t3.setPosition(540,635);
        f4.loadFromFile(pth);
        t4.setString(GO);
        t4.setFont(f4);
        t4.setCharacterSize(75);
        t4.setPosition(540,635);
        //TEXT WIN/LOOSE */

        //START + END SPOT
        S.r=127;
        S.g=255;
        S.b=215;
        E.r=0;
        E.g=191;
        E.b=255;
        Start.setPosition(621,104);
        End.setPosition(621,546);
        Start.setFillColor(S);
        End.setFillColor(E);
        //START + END SPOT

        //Patrat Principal
        color.r=211;
        color.g=211;
        color.b=211;
        Patrat.setFillColor(color);
        //Patrat Principal

    //Buton + Perete care dispare doar daca este activat
    b1.r=61;
    b1.g=102;
    b1.b=107;
    b2.r=107;
    b2.g=61;
    b2.b=107;
    b3.r=61;
    b3.g=107;
    b3.b=67;
    B1.setPosition(865,183);
    B2.setPosition(223,180);
    B3.setPosition(756,412);
    B4.setPosition(485,412);
    B1.setFillColor(b1);
    B2.setFillColor(b2);
    B3.setFillColor(b3);
    B4.setFillColor(b3);
    //Buton + Perete care dispare doar daca este activat

    //zid
    BD1.setPosition(379,181);
    BD2.setPosition(619,252);
    BD3.setPosition(600,510);
    BD1.setFillColor(b1);
    BD2.setFillColor(b2);
    BD3.setFillColor(b3);
    //zid

    //Mobi
    CC.r=255;
    CC.g=1;
    CC.b=10;
    for(i=1;i<=15;i++)
       C[i].setRadius(15);
    C[1].setPosition(478,162);
    C[2].setPosition(845,200);
    C[3].setPosition(478,235);
    C[4].setPosition(605,125);
    C[5].setPosition(678,125);
    C[6].setPosition(282,162);
    C[7].setPosition(360,162);
    C[8].setPosition(320,235);
    C[9].setPosition(540,390);
    C[10].setPosition(740,425);
    C[11].setPosition(740,460);
    C[12].setPosition(540,493);

    //Mobi

    //Mapa
    cmap.r=148;
    cmap.g=154;
    cmap.b=155;
    Dr[1].setSize(sf::Vector2f(120,4));
    Dr[2].setSize(sf::Vector2f(4,40));
    Dr[3].setSize(sf::Vector2f(120,4));
    Dr[4].setSize(sf::Vector2f(4,40));
    Dr[5].setSize(sf::Vector2f(80,4));
    Dr[6].setSize(sf::Vector2f(4,40));
    Dr[7].setSize(sf::Vector2f(80,4));
    Dr[8].setSize(sf::Vector2f(4,40));
    Dr[9].setSize(sf::Vector2f(160,4));
    Dr[10].setSize(sf::Vector2f(4,120));
    Dr[11].setSize(sf::Vector2f(100,4));
    Dr[12].setSize(sf::Vector2f(4,40));
    Dr[13].setSize(sf::Vector2f(40,4));
    Dr[14].setSize(sf::Vector2f(4,40));
    Dr[15].setSize(sf::Vector2f(40,4));
    Dr[16].setSize(sf::Vector2f(4,60));
    Dr[17].setSize(sf::Vector2f(80,4));
    Dr[18].setSize(sf::Vector2f(4,40));
    Dr[19].setSize(sf::Vector2f(20,4));
    Dr[20].setSize(sf::Vector2f(4,40));
    Dr[21].setSize(sf::Vector2f(40,4));
    Dr[22].setSize(sf::Vector2f(4,40));
    Dr[23].setSize(sf::Vector2f(20,4));
    Dr[24].setSize(sf::Vector2f(4,40));
    Dr[25].setSize(sf::Vector2f(80,4));
    Dr[26].setSize(sf::Vector2f(4,60));
    Dr[27].setSize(sf::Vector2f(40,4));
    Dr[28].setSize(sf::Vector2f(4,40));
    Dr[29].setSize(sf::Vector2f(40,4));
    Dr[30].setSize(sf::Vector2f(4,40));
    Dr[31].setSize(sf::Vector2f(100,4));
    Dr[32].setSize(sf::Vector2f(4,120));
    Dr[33].setSize(sf::Vector2f(160,4));
    Dr[34].setSize(sf::Vector2f(4,40));
    Dr[35].setSize(sf::Vector2f(80,4));
    Dr[36].setSize(sf::Vector2f(4,40));
    Dr[37].setSize(sf::Vector2f(120,4));
    Dr[38].setSize(sf::Vector2f(4,40));
    Dr[39].setSize(sf::Vector2f(40,4));
    Dr[40].setSize(sf::Vector2f(4,40));
    Dr[41].setSize(sf::Vector2f(40,4));
    Dr[42].setSize(sf::Vector2f(4,40));
    Dr[43].setSize(sf::Vector2f(120,4));
    Dr[44].setSize(sf::Vector2f(4,40));
    Dr[45].setSize(sf::Vector2f(80,4));
    Dr[46].setSize(sf::Vector2f(4,40));
    Dr[47].setSize(sf::Vector2f(126,4));
    Dr[48].setSize(sf::Vector2f(4,40));
    for(i=1;i<=48;i++)
    {
        sf::FloatRect r = C[i].getGlobalBounds();
        C[i].setFillColor(CC);
        C[i].setOrigin(r.height/2,r.width/2);
        Dr[i].setFillColor(cmap);
    }
        Dr[1].setPosition(580,100);
        Dr[2].setPosition(700,100);
        Dr[3].setPosition(700,140);
        Dr[4].setPosition(820,140);
        Dr[5].setPosition(820,180);
        Dr[6].setPosition(900,180);
        Dr[7].setPosition(820,216);
        Dr[8].setPosition(820,216);
        Dr[9].setPosition(660,252);
        Dr[10].setPosition(660,252);
        Dr[11].setPosition(660,370);
        Dr[12].setPosition(756,370);
        Dr[13].setPosition(756,410);
        Dr[14].setPosition(792,410);
        Dr[15].setPosition(756,450);
        Dr[16].setPosition(756,454);
        Dr[17].setPosition(676,510);
        Dr[18].setPosition(676,510);
        Dr[19].setPosition(658,546);
        Dr[20].setPosition(658,546);
        Dr[21].setPosition(618,582);
        Dr[22].setPosition(618,546);
        Dr[23].setPosition(599,546);
        Dr[24].setPosition(599,510);
        Dr[25].setPosition(519,510);
        Dr[26].setPosition(519,454);
        Dr[27].setPosition(483,450);
        Dr[28].setPosition(483,410);
        Dr[29].setPosition(483,410);
        Dr[30].setPosition(519,370);
        Dr[31].setPosition(519,370);
        Dr[32].setPosition(615,252);
        Dr[33].setPosition(455,252);
        Dr[34].setPosition(455,216);
        Dr[35].setPosition(379,216);
        Dr[36].setPosition(379,216);
        Dr[37].setPosition(259,252);
        Dr[38].setPosition(259,216);
        Dr[39].setPosition(220,216);
        Dr[40].setPosition(220,180);
        Dr[41].setPosition(220,180);
        Dr[42].setPosition(259,144);
        Dr[43].setPosition(259,140);
        Dr[44].setPosition(379,140);
        Dr[45].setPosition(379,180);
        Dr[46].setPosition(455,140);
        Dr[47].setPosition(458,140);
        Dr[48].setPosition(580,100);
    //Mapa

    //set origine
    sf::FloatRect r = Patrat.getGlobalBounds();
    Patrat.setOrigin(r.height/2,r.width/2);
    init = true;
    }
    //set origine

    //set Pozitie


    //set Pozitie
    float timpTrecut = time.getElapsedTime().asSeconds();
        //Mob Movement
    if(L==1)
        if(Won1==0)
    {
        if(timpTrecut > 0.025)
        {
            if(Cx1>=400 && x1==0){Cx1+=4;if(Cx1>=800)x1=1;}
            if(Cx1<=850 && x1==1){Cx1-=4;if(Cx1<=477)x1=0;}
        }
        C[1].setPosition(Cx1,162);
        if(timpTrecut > 0.025)
        {
            if(Cx3>=400 && x3==0){Cx3+=4;if(Cx3>=800)x3=1;}
            if(Cx3<=850 && x3==1){Cx3-=4;if(Cx3<=477)x3=0;}
        }
        C[3].setPosition(Cx3,235);
        if(timpTrecut > 0.025)
        {
            if(Cx2<=860 && x2==0){Cx2-=3;if(Cx2<=477)x2=1;}
            if(Cx2>=400 && x2==1){Cx2+=3;if(Cx2>=845)x2=0;}
        }
        C[2].setPosition(Cx2,200);
        if(timpTrecut > 0.025)
        {
            if(Cx9>=500 && x9==0){Cx9+=5;if(Cx9>=740)x9=1;}
            if(Cx9<=760 && x9==1){Cx9-=5;if(Cx9<=540)x9=0;}
        }
        C[9].setPosition(Cx9,390);
        if(timpTrecut > 0.025)
        {
            if(Cx12>=500 && x12==0){Cx12+=5;if(Cx12>=740)x12=1;}
            if(Cx12<=760 && x12==1){Cx12-=5;if(Cx12<=540)x12=0;}
        }
        C[12].setPosition(Cx12,493);
        if(timpTrecut > 0.025)
        {
            if(Cx10<=760 && x10==0){Cx10-=5;if(Cx10<=540)x10=1;}
            if(Cx10>=500 && x10==1){Cx10+=5;if(Cx10>=740)x10=0;}
        }
        C[10].setPosition(Cx10,425);
        if(timpTrecut > 0.025)
        {
            if(Cx11<=760 && x11==0){Cx11-=5;if(Cx11<=540)x11=1;}
            if(Cx11>=500 && x11==1){Cx11+=5;if(Cx11>=740)x11=0;}
        }
        C[11].setPosition(Cx11,460);
        if(timpTrecut > 0.025)
        {
            if(Cy4>=110 && y4==0){Cy4+=2;if(Cy4>=235)y4=1;}
            if(Cy4<=250 && y4==1){Cy4-=2;if(Cy4<=125)y4=0;}
        }
        C[4].setPosition(605,Cy4);
        if(timpTrecut > 0.025)
        {
            if(Cy5>=110 && y5==0){Cy5+=2;if(Cy5>=235)y5=1;}
            if(Cy5<=250 && y5==1){Cy5-=2;if(Cy5<=125)y5=0;}
        }
        C[5].setPosition(678,Cy5);
        if(timpTrecut > 0.025)
        {
            if(Cy6>=140 && y6==0){Cy6+=1;if(Cy6>=235)y6=1;}
            if(Cy6<=250 && y6==1){Cy6-=1;if(Cy6<=162)y6=0;}
        }
        C[6].setPosition(282,Cy6);
        if(timpTrecut > 0.025)
        {
            if(Cy7>=140 && y7==0){Cy7+=1;if(Cy7>=235)y7=1;}
            if(Cy7<=250 && y7==1){Cy7-=1;if(Cy7<=162)y7=0;}
        }
        C[7].setPosition(360,Cy7);
        if(timpTrecut > 0.025)
        {
            if(Cy8<=250 && y8==0){Cy8-=1;if(Cy8<=162)y8=1;}
            if(Cy8>=140 && y8==1){Cy8+=1;if(Cy8>=235)y8=0;}
        }
        C[8].setPosition(320,Cy8);
        //Mob Movement

        //Miscare Patrat
        if(buton(Patrat,B1)==0 && timpTrecut > 0.025) BD1.setPosition(1280,720);
        if(buton(Patrat,B2)==0 && timpTrecut > 0.025) BD2.setPosition(1280,720);
        if(buton(Patrat,B3)==0 && timpTrecut > 0.025) m=1;
        else if(buton(Patrat,B4)==0 && timpTrecut > 0.025) n=1;
        if(m==1 && n==1) BD3.setPosition(1280,720);
        if(Won(Patrat,End)==0 && timpTrecut > 0.025) Won1=1;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && timpTrecut > 0.025) //Merge la stanga;
        {
            if(asauf(Patrat,Dr)==1)x-=5;
            else {x=640;y=125;BD1.setPosition(379,181);BD2.setPosition(619,252);BD3.setPosition(600,510);m=0;n=0;}
            if(zid(Patrat,BD1)==0){x=640;y=125;BD1.setPosition(379,181);BD2.setPosition(619,252);BD3.setPosition(600,510);m=0;n=0;}
            time.restart();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && timpTrecut > 0.025)//Merge la dreapta;
        {
            if(asauf(Patrat,Dr)==1) x+=5;
            else {x=640;y=125;BD1.setPosition(379,181);BD2.setPosition(619,252);BD3.setPosition(600,510);m=0;n=0;}
            time.restart();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && timpTrecut > 0.025)//Merege in jos;
        {
            if(asauf(Patrat,Dr)==1) y+=5;
            else {x=640;y=125;BD1.setPosition(379,181);BD2.setPosition(619,252);BD3.setPosition(600,510);m=0;n=0;}
            if(zid(Patrat,BD2)==0){x=640;y=125;BD1.setPosition(379,181);BD2.setPosition(619,252);BD3.setPosition(600,510);m=0;n=0;}
            if(zid(Patrat,BD3)==0){x=640;y=125;BD1.setPosition(379,181);BD2.setPosition(619,252);BD3.setPosition(600,510);m=0;n=0;}
            time.restart();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && timpTrecut > 0.025)//Merge in sus;
        {
            if(asauf(Patrat,Dr)==1)y-=5;
            else {x=640;y=125;BD1.setPosition(379,181);BD2.setPosition(619,252);BD3.setPosition(600,510);m=0;n=0;}
            time.restart();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && timpTrecut > 0.025) //Merge la stanga;
        {
            if(asauf(Patrat,Dr)==1)x-=5;
            else {x=640;y=125;BD1.setPosition(379,181);BD2.setPosition(619,252);BD3.setPosition(600,510);m=0;n=0;}
            if(zid(Patrat,BD1)==0){x=640;y=125;BD1.setPosition(379,181);BD2.setPosition(619,252);BD3.setPosition(600,510);m=0;n=0;}
            time.restart();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && timpTrecut > 0.025)//Merge la dreapta;
        {
            if(asauf(Patrat,Dr)==1)x+=5;
            else {x=640;y=125;BD1.setPosition(379,181);BD2.setPosition(619,252);BD3.setPosition(600,510);m=0;n=0;}
            time.restart();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && timpTrecut > 0.025)//Merege in jos;
        {
            if(asauf(Patrat,Dr)==1)y+=5;
            else {x=640;y=125;BD1.setPosition(379,181);BD2.setPosition(619,252);BD3.setPosition(600,510);m=0;n=0;}
            if(zid(Patrat,BD2)==0){x=640;y=125;BD1.setPosition(379,181);BD2.setPosition(619,252);BD3.setPosition(600,510);m=0;n=0;}
            if(zid(Patrat,BD3)==0){x=640;y=125;BD1.setPosition(379,181);BD2.setPosition(619,252);BD3.setPosition(600,510);m=0;n=0;}
            time.restart();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && timpTrecut > 0.025)//Merge in sus;
        {

            if(asauf(Patrat,Dr)==1)y-=5;
            else {x=640;y=125;BD1.setPosition(379,181);BD2.setPosition(619,252);BD3.setPosition(600,510);m=0;n=0;}
            time.restart();
        }
        if(collision(Patrat,C)==0)L=0;
        Patrat.setPosition(x,y);
    }
        a.draw(Start);
        a.draw(End);
        //Mobi
        for(i=1;i<=12;i++)
            a.draw(C[i]);
        //Mobi

        //zid
        a.draw(BD1);
        a.draw(BD2);
        a.draw(BD3);
        //zid

        //Buton + Perete care dispare doar daca este activat
        a.draw(B1);
        a.draw(B2);
        a.draw(B3);
        a.draw(B4);
        //Buton + Perete care dispare doar daca este activat

        //Mapa
        for(i=1;i<=48;i++)
                a.draw(Dr[i]);
        //Mapa
        a.draw(Patrat);
        //if(Patrat.intersect(Dr[i]))
        if(L==0)
        {
            init = false;
            nivelCurent = fail2;
            return 0; //Loose
        }
        if(Won1==1)
        {
            init = false;
            nivelCurent = castig;
            return 1; //WIn
        }
}
int piatra(float &xp,float &yp,int dirX,int dirY,int peVert,int peOriz)
{
        if(peOriz)xp += (17)*dirX;
        if(peVert)yp += (17)*dirY;
        if(xp > 1280 || xp<0 || yp > 720 || yp<0)return 1;
        return 0;
}
int miscare(float &x, float &y,sf::Clock c,float &xp,float &yp)
{
    float r=c.getElapsedTime().asSeconds();
    static int dirX , dirY , peVert , peOriz ;
    static int b=0,d;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)&& r>0.005 )
        {
            if(x>10)x-=15;
            if( !b)
            {
                     peOriz = 1;
             peVert = 0;
             dirX = -1;
             b++;}
             d=2;
             c.restart();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && r>0.005)
        {
            if(x<1230)x+=15;
            if( !b){peOriz = 1;
            peVert = 0;
            dirX = 1;b++;}
            d=3;
            c.restart();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && r>0.005 )
        {
            if(y<700)y+=15;
            if( !b){peVert = 1;
            peOriz = 0;
            dirY = 1;b++;}
            d=1;
            c.restart();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)&& r>0.005 )
        {
            if( y>10)y-=15;
            if( !b){peOriz = 0;
            peVert = 1;
            dirY = -1;b++;}
            d=0;
            c.restart();
        }
        int k=piatra(xp,yp,dirX,dirY,peVert,peOriz);
        if(k)
            {
                xp = x;
                yp = y;
                b=0;
            }
        else piatra(xp,yp,dirX,dirY,peVert,peOriz);
        return d;
}
int miniGame2(sf::RenderWindow &f)
{

srand(time(NULL));

    static string W="You Won!";
    static string GO="You Lose!";

    static sf::Clock c;
    static sf::Clock cr;

    static const int n=30;
    static bool init=true;

    static sf::Text t3;
    static sf::Font f3;
    static sf::Text t4;
    static sf::Font f4;


    //Timp pe ecran
    static sf::Text ceas;
    static sf::Font font;



    //Player
    static sf::Texture textura[4];
    static sf::Sprite sprite;


    //Background
    static sf::Texture pamant;
    static sf::Sprite backgound;


    //Proiectil
    static sf::Sprite proiectil;
    static sf::Texture t;


    ////MOBI
    static sf::Sprite mob[30];
    static sf::Texture m;
    static sf::FloatRect r2[30];
    static float xm[30],ym[30];


    //Viata
    static sf::Sprite viata[3];
    static sf::Texture v;

    if(init)
    {
        curent.stop();
        string pax = Sistem_Baza::path();
        pax += "audio/minigame.ogg";
        curent.openFromFile(pax);
        curent.setVolume(100);
        curent.play();
        f3.loadFromFile("t+i/font1.ttf");
        t3.setString(W);
        t3.setFont(f3);
        t3.setCharacterSize(75);
        t3.setPosition(540,635);
        f4.loadFromFile("t+i/font1.ttf");
        t4.setString(GO);
        t4.setFont(f4);
        t4.setCharacterSize(75);
        t4.setPosition(540,635);
        textura[0].loadFromFile("grafica/0.png");
        textura[1].loadFromFile("grafica/1.png");
        textura[2].loadFromFile("grafica/2.png");
        textura[3].loadFromFile("grafica/3.png");
        font.loadFromFile("grafica/font1.ttf");
        ceas.setFont(font);
        ceas.setCharacterSize(50);
        ceas.setPosition(100,100);
        cr.restart();
        sprite.setTexture(textura[1]);
        sprite.setOrigin(50,50);
        pamant.loadFromFile("grafica/bg_mn.jpg");
        backgound.setTexture(pamant);
        t.loadFromFile("grafica/proiectil.png");
        proiectil.setTexture(t);
        proiectil.scale(0.015,0.015);
        proiectil.setPosition(640,360);
        m.loadFromFile("grafica/mob.png");
        for(int i=0;i<n;i++)
            {
                mob[i].setTexture(m);
                //mob[i].scale(1,1);
                xm[i]=rand()%900+20;
                ym[i]=rand()%500+1;
                mob[i].setPosition(xm[i],ym[i]);
            }
        v.loadFromFile("grafica/heart.png");
        for(int i=0;i<3;i++)
            {
                viata[i].setTexture(v);
                viata[i].setPosition(600+i*50,30);
            }
        init=false;
    }

    static float x=640,y=360,xp=640,yp=360;
    static int j=1,k=3;
    int cronometru=cr.getElapsedTime().asSeconds();
    std::stringstream f_str;
    f_str<<60-cronometru;
    ceas.setString(f_str.str());
    sf::FloatRect r1=proiectil.getGlobalBounds();
    sf::FloatRect p=sprite.getGlobalBounds();

    for(int i=0;i<n;i++)
    {
            r2[i]=mob[i].getGlobalBounds();
    }
    int d= miscare(x,y,c,xp,yp);
    proiectil.setPosition(xp,yp);
    sprite.setPosition(x,y);

    sprite.setTexture(textura[d]);
        if(cronometru<30)for(int i=0;i<cronometru;i++)
        {
           if(r2[i].intersects(r1) )
            {
                xm[i]=rand()%900+20;
                ym[i]=rand()%500+1;
                mob[i].setPosition(xm[i],ym[i]);
                xp=x;
                yp=y;
            }
            if(p.intersects(r2[i]))j++;//cout<<j<<" ";}
            if(xm[i]>x)xm[i]-=0.5;
            if(xm[i]<x)xm[i]+=0.5;
            if(ym[i]>y)ym[i]-=0.5;
            if(ym[i]<y)ym[i]+=0.5;
            mob[i].setPosition(xm[i],ym[i]);

        }
        else for(int i=0;i<n;i++)
        {
           if(r2[i].intersects(r1) )
            {
                xm[i]=rand()%900+20;
                ym[i]=rand()%500+1;
                mob[i].setPosition(xm[i],ym[i]);
                xp=x;
                yp=y;
            }
            if(p.intersects(r2[i]))j++;//cout<<j<<" ";}
            if(xm[i]>x)xm[i]-=1;
            if(xm[i]<x)xm[i]+=1;
            if(ym[i]>y)ym[i]-=1;
            if(ym[i]<y)ym[i]+=1;
            mob[i].setPosition(xm[i],ym[i]);

        }




        f.draw(backgound);
        if(k && cronometru<60)
        {
            f.draw(proiectil);
            f.draw(ceas);
            if(j%50==0){k--;}
           for(int i=0;i<k;i++)f.draw(viata[i]);
           if(cronometru<60)
            {
                if(cronometru<30)for(int i=0;i<cronometru;i++)f.draw(mob[i]);
                else for(int i=0;i<n;i++)f.draw(mob[i]);
            }
            f.draw(sprite);
        }
      if(k==0){f.draw(t4);nivelCurent = fail2;return 0;} //Loose}
      if (cronometru>=60){f.draw(t3);nivelCurent = castig;return 1;} //WIn
}
void Intro(sf::RenderWindow &f)
{
    static sf::Text txt;
    static wstring msj;
    static bool nume = true;
    static bool init = false;
    static int x = -200,y = 290;
    static sf::Clock ceas;
    if(!init)
    {
        string pax = Sistem_Baza::path();
        pax+="audio/intro.ogg";
        curent.stop();
        curent.openFromFile(pax);
        curent.play();
        nume = true;
        txt.setString(util_curent->nume);
        txt.setFont(font);
        txt.setPosition(x,y);
        txt.setCharacterSize(80);
        init = true;
    }
    if(x <= 250)
    {
        x+=20;
        txt.setPosition(x,y);
    }
    if(x > 250 && x <= 600)
    {
        x+=5;
        txt.setPosition(x,y);
    }
    if(x >= 600)
    {
        x+=20;
        txt.setPosition(x,y);
    }
    if(msj == L"... réside dans vos mains!")
    {
        float volume = curent.getVolume();
        if(volume > 1)volume-=1;
        curent.setVolume(volume);
    }
    if(x > 4280)
    {
        x = -200;
        if(nume)
        {
            nume = false;
            msj = L"Le sort de ces âmes ...";
            txt.setString(msj);
        }
        else if(msj == L"Le sort de ces âmes ...")
        {
            msj = L"... réside dans vos mains!";
            txt.setString(msj);
        }
        else if(msj == L"... réside dans vos mains!")
        {
            init = false;
            nivelCurent = joc_spanz;
        }
    }
    f.draw(txt);
}
int nrMorti;
#define fail1 20
void Fail1(sf::RenderWindow &f)
{
    static sf::Text txt;
    static wstring msj;
    static bool nume = true;
    static bool init = false;
    static int x = -200,y = 290;
    static int ultimG = 0;
    static sf::Clock ceas;
    if(!init)
    {
        string pax = Sistem_Baza::path();
        pax+="audio/intro.ogg";
        curent.stop();
        curent.openFromFile(pax);
        curent.play();
        nume = true;
        txt.setString(util_curent->nume);
        txt.setFont(font);
        txt.setPosition(x,y);
        txt.setCharacterSize(80);
        init = true;
    }
    if(x <= 250)
    {
        x+=20;
        txt.setPosition(x,y);
    }
    if(x > 250 && x <= 600)
    {
        x+=5;
        txt.setPosition(x,y);
    }
    if(x >= 600)
    {
        x+=20;
        txt.setPosition(x,y);
    }
    if(msj == L"...vous vous déplacez!")
    {
        float volume = curent.getVolume();
        if(volume > 1)volume-=1;
        curent.setVolume(volume);
    }
    if(x > 4280)
    {
        x = -200;
        if(nume)
        {
            nume = false;
            msj = L"Vous êtes responsable de la mort ...";
            txt.setString(msj);
        }
        else if(msj == L"Vous êtes responsable de la mort ...")
        {
            wstring nr;
            int cp = nrMorti;
            while(cp)
            {
                nr += (cp%10 + '0');
                cp/= 10;
            }
            reverse(nr.begin(),nr.end());
            msj = L"de ";
            msj +=nr;
            msj += L" personnes";
            txt.setString(msj);
        }
        else if(msj.find(L"personnes") != string::npos)
        {
            msj = L"Mais vous avez une autre chance!";
            txt.setString(msj);
        }
        else if(msj == L"Mais vous avez une autre chance!")
        {
            msj = L"Si vous gagnez le prochain match ...";
            txt.setString(msj);
        }
        else if(msj == L"Si vous gagnez le prochain match ...")
        {
            msj = L"...vous vous déplacez!";
            txt.setString(msj);
        }
        else
        {
            init = false;
            if(ultimG == 0)ultimG = minigame1;
            else if(ultimG == minigame1)ultimG = minigame2;
            else if(ultimG == minigame2)ultimG = minigame3;
            else if(ultimG == minigame3)ultimG == minigame1;
            nivelCurent = ultimG;
        }
    }
    f.draw(txt);
}
void Meniu_Welcome(sf::RenderWindow &f)
{
    float timpRamas = mW.getElapsedTime().asSeconds();
    static sf::Text titlu;
    static bool init = false;
    static int titlu_x, titlu_y;
    static sf::Clock timpTranz;
    static int tranzOut = 0;
    static sf::Clock intro;
    if(!init)
    {
        string pth;
        pth += Sistem_Baza::path();
        curent.openFromFile(pth + "audio/meniu.ogg");
        curent.setLoop(true);
        curent.setVolume(100);
        curent.play();
        bg.loadFromFile(pth + "grafica/bg_mn.jpg");
        background.setTexture(bg);
        titlu.setString("Le Pendu");
        font.loadFromFile(pth + "grafica/font1.ttf");
        titlu.setFont(font);
        titlu.setCharacterSize(100);
        titlu_x = 550;
        titlu_y = -200;
        titlu.setPosition(titlu_x,titlu_y);
        sf::Color c = titlu.getColor();
        c.a = 0;
        titlu.setColor(c);
        background.setColor(c);
        init = true;
    }
    if(intro.getElapsedTime().asSeconds() < 3)
    {
        sf::Color c = titlu.getColor();
        if(c.a < 250)
        {
            ++c.a;
            titlu.setColor(c);
            background.setColor(c);
        }
    }
    else
    {
        if(timpTranz.getElapsedTime().asSeconds() > 0.0005 && titlu_y <= 300)
        {
            titlu_y += 10;
            titlu.setPosition(titlu_x,titlu_y);
            timpTranz.restart();
        }
        else if(tranzOut && timpTranz.getElapsedTime().asSeconds() > 0.0005)
        {
            titlu_y += 10;
            titlu.setPosition(titlu_x,titlu_y);
            timpTranz.restart();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))tranzOut = 1;
        if(titlu_y > 720)
        {
            list_util.initializeazaListaDinFisier();
            unsigned nrLista = list_util.nrUtilizatori();
            if(nrLista)
            {
               mSel.restart();
               nivelCurent = meniu_prof_sel;
            }
            else
            {
               mAdd.restart();
               nivelCurent = meniu_prof_add;
            }
        }
    }
    f.draw(background);
    f.draw(titlu);
    AfisSpanz::DesSpanz(f,0);
}
void Meniu_AdaugaUtilizator(sf::RenderWindow &f, Comunicare &c)
{
    static float tranzOut = 0;
    float timpRamas = mAdd.getElapsedTime().asSeconds();
    static float interactUtil_x = 560,interactUtil_y = 400, mesaj_y = 0;
    static bool init = false;
    static sf::Text mesaj, interactUtil;
    if(!init)
    {
        mesaj.setString("Entrez un nom de profil : ");
        mesaj.setFont(font);
        mesaj.setCharacterSize(60);
        interactUtil.setFont(font);
        interactUtil.setCharacterSize(60);
        mesaj.setPosition(490,320);
        interactUtil.setPosition(550,400);
        init = true;
    }
    if(mesaj_y < 320)
    {
        c.text_dl_tastatura.clear();
        mesaj_y+=20;
        mesaj.setPosition(490,mesaj_y);
    }
    if(tranzOut)
    {
        mesaj_y+=20;
        interactUtil_y +=20;
        mesaj.setPosition(490,mesaj_y);
        interactUtil.setPosition(interactUtil_x,interactUtil_y);
    }
    if(!c.text_dl_tastatura.empty() && sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) && timpRamas > 0.5)
    {
        Date_Utilizator dt;
        strcpy(dt.nume,c.text_dl_tastatura.c_str());
        list_util.adauga(dt);
        list_util.scrieListaInFisier();
        util_curent = list_util.gaseste_utilizator(list_util.nrUtilizatori());
        mP.restart();
        tranzOut = 1;
        c.text_dl_tastatura.clear();
    }
    if(mesaj_y > 720)
    {
        nivelCurent = meniu_norm;
        mesaj_y = 0;
        tranzOut = 0;
        interactUtil_y = 400;
        interactUtil.setPosition(interactUtil_x,interactUtil_y);
    }
    interactUtil.setString(c.text_dl_tastatura);
    f.draw(background);
    f.draw(mesaj);
    f.draw(interactUtil);
    AfisSpanz::DesSpanz(f,0);
}

#define SP 1
#define MP 2
#define AC 3
#define SC 4
#define EX 5

void Meniu_Principal(sf::RenderWindow &f, Comunicare &c)
{
    c.text_dl_tastatura.clear();
    static int idButon = SP;
    float timpRamas = mP.getElapsedTime().asSeconds();
    static sf::Text txtSP, txtMP, txtAC, txtSC, txtEX;
    static sf::Texture texSel; static sf::Sprite sprSel;
    static int sel_x = 540, sel_y = 320;
    static bool init = false;
    static int x = 1290;
    static int tranzOut = 0;
    if(!init)
    {
        string pth;
        pth = Sistem_Baza::path();
        texSel.loadFromFile(pth + "grafica/select.png");
        texSel.setSmooth(true);
        sprSel.setTexture(texSel);
        sprSel.setPosition(sel_x,sel_y);
        sprSel.setScale(0.3, 0.22);

        txtSP.setString("Jouer");
        wstring tmp = L"Ajouter une catégorie";
        txtMP.setString(tmp);
        txtAC.setString("Ajouter un utilisateur");
        txtSC.setString("Changer d'utilisateur.");
        txtEX.setString("Exit");

        txtSP.setFont(font);
        txtMP.setFont(font);
        txtAC.setFont(font);
        txtSC.setFont(font);
        txtEX.setFont(font);

        txtSP.setCharacterSize(50);
        txtMP.setCharacterSize(50);
        txtAC.setCharacterSize(50);
        txtSC.setCharacterSize(50);
        txtEX.setCharacterSize(50);

        txtSP.setPosition(x,300);
        txtMP.setPosition(x,350);
        txtAC.setPosition(x,400);
        txtSC.setPosition(x,450);
        txtEX.setPosition(x,500);
        init = true;
    }
    if(x > 590)
    {
        x-=20;
        txtSP.setPosition(x,300);
        txtMP.setPosition(x,350);
        txtAC.setPosition(x,400);
        txtSC.setPosition(x,450);
        txtEX.setPosition(x,500);
    }

    if(timpRamas > 0.3)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            mP.restart();
            sel_y -= 50 * (idButon != SP);
            idButon -= (idButon != SP);
            sprSel.setPosition(sel_x,sel_y);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            mP.restart();
            sel_y += 50 * (idButon != EX);
            idButon += (idButon != EX);
            sprSel.setPosition(sel_x,sel_y);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
        {
            tranzOut = 1;
        }
        if(tranzOut)
        {
            x-=20;
            txtSP.setPosition(x,300);
            txtMP.setPosition(x,350);
            txtAC.setPosition(x,400);
            txtSC.setPosition(x,450);
            txtEX.setPosition(x,500);
        }
        if(idButon == AC && x < -300)
        {
            nivelCurent = meniu_prof_add;
            x = 1290;
            mAdd.restart();
            tranzOut = 0;
        }
        else if(idButon == MP && x < -300)
        {
            nivelCurent = adauga_categ;
            x = 1290;
            tranzOut = 0;

        }
        else if(idButon == SC && x < -300 )
        {
            nivelCurent = meniu_prof_sel;
            x = 1290;
            mSel.restart();
            tranzOut = 0;
        }
        else if(idButon == SP && x < -300)
        {
            nivelCurent = joc_selcateg;
            x = 1290;
            jSLCATEG.restart();
            tranzOut = 0;
        }
        else if(idButon == EX && x < -300)
            f.close();
    }
    f.draw(background);
    AfisSpanz::DesSpanz(f,idButon);
    f.draw(txtSP);
    f.draw(txtMP);
    f.draw(txtAC);
    f.draw(txtSC);
    f.draw(txtEX);
    f.draw(sprSel);

}
void Meniu_SelectareUtil(sf::RenderWindow &f)
{
    static ObjAnimTranzTxt tr_numeUtil, tr_rangUtil;
    static char numePrev[100], rangPrev[100];
    static int idUtil = 1;
    static sf::Text numeUtil, rangUtil;
    static bool init = false;
    static int nrUtil;
    static int trNUt, trRAt;
    static int primaTranzitie = 1;
    static int y = -300;
    static int tranzOut = 0;
    float timpRamas = mSel.getElapsedTime().asSeconds();
    if(!init)
    {
        numeUtil.setFont(font);
        numeUtil.setCharacterSize(100);
        strcpy(numePrev,list_util.gaseste_utilizator(idUtil)->nume);
        numeUtil.setString(numePrev);
        numeUtil.setPosition(500,300);

        tr_numeUtil.afis = &numeUtil;
        tr_numeUtil.pozXinit = numeUtil.getPosition().x;
        tr_numeUtil.pozYinit = numeUtil.getPosition().y;
        strcpy(tr_numeUtil.str1,numePrev);
        tr_numeUtil.terminat = 0;

        rangUtil.setFont(font);
        rangUtil.setCharacterSize(100);
        rangUtil.setString(rangPrev);
        rangUtil.setPosition(500,380);

        tr_rangUtil.afis = &rangUtil;
        tr_rangUtil.pozXinit = rangUtil.getPosition().x;
        tr_rangUtil.pozYinit = rangUtil.getPosition().y;
        strcpy(tr_rangUtil.str1,rangPrev);
        tr_rangUtil.terminat = 0;

        init = true;
    }
    if(y < 300)
    {
        y+=20;
        numeUtil.setPosition(500,y);
        rangUtil.setPosition(500,y+80);
    }
    if(tranzOut)
    {
        y+=20;
        numeUtil.setPosition(500,y);
        rangUtil.setPosition(500,y+80);
    }
    if(y > 720)
    {
        y = -300;
        tranzOut = 0;
        util_curent = list_util.gaseste_utilizator(idUtil);
        nivelCurent = meniu_norm;
        mP.restart();
    }
    if(timpRamas > 0.3)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            nrUtil = list_util.nrUtilizatori();
            if(idUtil + 1 > nrUtil)idUtil = 0;
            ++idUtil;
            util_curent = list_util.gaseste_utilizator(idUtil);

            strcpy(tr_numeUtil.str1,numePrev);
            strcpy(tr_numeUtil.str2,util_curent->nume);
            strcpy(numePrev,util_curent->nume);
            strcpy(tr_rangUtil.str1,rangPrev);

            trNUt = 1;
            trRAt = 1;
            tr_numeUtil.terminat = 0;
            tr_rangUtil.terminat = 0;
            tr_numeUtil.timpAnim.restart();
            tr_rangUtil.timpAnim.restart();
            primaTranzitie = 0;
            mSel.restart();
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            nrUtil = list_util.nrUtilizatori();
            if(idUtil - 1 == 0)idUtil = nrUtil + 1;
            --idUtil;
            util_curent = list_util.gaseste_utilizator(idUtil);

            strcpy(tr_numeUtil.str1,numePrev);
            strcpy(tr_numeUtil.str2,util_curent->nume);
            strcpy(numePrev,util_curent->nume);
            strcpy(tr_rangUtil.str1,rangPrev);

            trNUt = 1;
            trRAt = 1;
            tr_numeUtil.terminat = 0;
            tr_rangUtil.terminat = 0;
            tr_numeUtil.timpAnim.restart();
            tr_rangUtil.timpAnim.restart();
            primaTranzitie = 0;
            mSel.restart();
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
        {
            tranzOut = 1;
        }
    }
    f.draw(background);
    if(!primaTranzitie)
    {
        trNUt = Sistem_Baza::Anim_TranzSelectTxt(tr_numeUtil,f);
        trRAt = Sistem_Baza::Anim_TranzSelectTxt(tr_rangUtil,f);
    }
    if(!trNUt && !trRAt);
    {
        f.draw(numeUtil);
        f.draw(rangUtil);
    }
    AfisSpanz::DesSpanz(f,0);

}

sf::Clock initSP;
sf::Clock timer;
void Joc_JoacaSP(sf::RenderWindow &f, Comunicare &c)
{
    static int nrCuv;
    f.draw(background);
    static int nrPierderi;
    static int nivImg = 0;
    static int msjJocForm;
    static int rezJoc;
    static int potAfisaNotif;
    static ObjAnimNotificare litEx;
    static int terminatJoc;
    static sf::Texture texturaCuv;
    static sf::Sprite spriteCuv;
    static int statutJoc;
    static bool init = false;
    static Joc joc_g;
    static sf::Text cuvDeGhicit, interactUtil;
    static sf::Text timp;
    static int ceSpanz;
    static int timpTrecut = 60;
    static sf::Text pierderi;
    if(!init)
    {
        pierderi.setString("");
        nrCuv = 0;
        nrMorti = 0;
        string pth;
        pth += Sistem_Baza::path();
        nrPierderi = 0;
        nivImg = 0;
        timpTrecut = 60;
        timer.restart();
        initSP.restart();
        msjJocForm = J_MSG_INITT;
        ceSpanz = 11;
        potAfisaNotif= 0;
        terminatJoc = 0;
        potAfisaNotif = 0;
        initSP.restart();
        curent.stop();
        curent.openFromFile(pth + "audio/spanz.ogg");
        curent.setLoop(true);
        curent.setVolume(200);
        curent.play();
        litEx.stagiuNotificare = 1;
        statutJoc = joc_g.formeazaJoc(categorie,msjJocForm,nrCuv);
        msjJocForm = J_MSG_DC;
        c.text_dl_tastatura.clear();
        timp.setFont(font);
        timp.setCharacterSize(60);
        timp.setPosition(100,100);
        pierderi.setFont(font);
        pierderi.setCharacterSize(50);
        pierderi.setPosition(100,600);

        cuvDeGhicit.setString(joc_g.string_curent);
        cuvDeGhicit.setFont(font);
        cuvDeGhicit.setOrigin(0,0);
        cuvDeGhicit.setCharacterSize(120);
        sf::FloatRect r = cuvDeGhicit.getGlobalBounds();
        cuvDeGhicit.setOrigin((r.width + r.left)/2,(r.height + r.top)/2);
        cuvDeGhicit.setPosition(640,490);

        interactUtil.setFont(font);
        interactUtil.setCharacterSize(100);
        interactUtil.setPosition(550,520);
        sf::Color c = cuvDeGhicit.getColor();
        c.a = 0;
        cuvDeGhicit.setColor(c);
        background.setColor(c);
        strcpy(litEx.notificare,"Lettre existante dans le mot!");

        init = true;
    }
    int apasatEnter = 0;
    if(curent.Stopped)curent.play();
    if(initSP.getElapsedTime().asSeconds() < 6)
    {
        sf::Color c = cuvDeGhicit.getColor();
        if(c.a < 250)c.a += 1;
        cuvDeGhicit.setColor(c);
        background.setColor(c);
    }
    interactUtil.setString(c.text_dl_tastatura);
    const char *msg = c.text_dl_tastatura.c_str();
    float timpActiune = jSPI.getElapsedTime().asSeconds();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && timpActiune > 0.2 && c.text_dl_tastatura.size() == 1)
    {
        apasatEnter = 1;
        jSPI.restart();
        rezJoc = joc_g.actualizareInteractiuneJucator(msg);
        c.text_dl_tastatura.clear();
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && timpActiune > 0.2)
    {
        mP.restart();
        float v = curent.getVolume();
        while(v)curent.setVolume(v--);
        curent.stop();
        init = false;
        joc_g.formeazaJoc(categorie,3,nrCuv);
        nivelCurent = meniu_norm;
    }
    if(timer.getElapsedTime().asSeconds() > 1)
    {
        --timpTrecut;
        string tmp;
        char cif;
        int cp = timpTrecut;
        while(cp)
        {
            cif = cp%10 + '0';
            tmp+=cif;
            cp/=10;
        }
        reverse(tmp.begin(),tmp.end());
        timp.setString(tmp);
        timer.restart();
    }
    if(timpTrecut < 1)
    {
        rezJoc = 2;
    }
    switch (rezJoc)
    {
    case 0 :
        break;
    case 1 :
        break;
    case 2 :
        //a dat fail
        {
            ++nrPierderi;
            string perderi = "Nombre de personnes pendu : ";
            string nrp;
            int cpP = nrPierderi;
            while(cpP)
            {
               nrp += cpP%10 + '0';
               cpP /= 10;
            }
            reverse(nrp.begin(),nrp.end());
            perderi+=nrp;
            pierderi.setString(perderi);
            f.draw(spriteCuv);
            timpTrecut = 60;
            ceSpanz = 10;
            c.text_dl_tastatura.clear();
            if(!terminatJoc)
            {
               jSPI.restart();
               terminatJoc = 1;
            }
            rezJoc = -1;
        }
        break;
    case 3 :
        // a castigat
        timpTrecut = 60;
        f.draw(spriteCuv);
        c.text_dl_tastatura.clear();
        if(!terminatJoc)
        {
            jSPI.restart();
            terminatJoc = 1;
        }
        break;
    case 4 :
        // a pus litera existenta
        litEx.stagiuNotificare = 0;
        litEx.init = false;
        rezJoc = -1;
    default :
        break;
    }
    string rang;
    if(!nrPierderi)rang = 'S';
    else if(nrPierderi <= nrCuv - 3)rang = 'A';
    else if(nrPierderi <= nrCuv - 6)rang = 'B';
    else if(nrPierderi <= nrCuv - 9)rang = 'C';
    else rang = 'D';
    cuvDeGhicit.setString(joc_g.cuvant);
    if(timpActiune > 2 && terminatJoc)nivImg = 0;
    if(timpActiune > 3 && terminatJoc)
    {
        ceSpanz = 11;
        rezJoc = -1;
        c.text_dl_tastatura.clear();
        terminatJoc = 0;
        jSPI.restart();
        statutJoc = joc_g.formeazaJoc(categorie,msjJocForm,nrCuv);
        cuvDeGhicit.setString(joc_g.cuvant);
        sf::FloatRect r = cuvDeGhicit.getLocalBounds();
        cuvDeGhicit.setOrigin((r.width + r.left)/2,(r.height + r.top)/2);
        cuvDeGhicit.setPosition(640,490);
        if(!statutJoc)
        {
            float v = curent.getVolume();
            while(v)curent.setVolume(v--);
            curent.stop();
            init = false;
            joc_g.formeazaJoc(categorie,3,nrCuv);
            if(rang != "B" && rang != "C" && rang != "D")
            {
                mP.restart();
                util_curent->rang += categorie;
                util_curent->rang += ' ';
                util_curent->rang += rang;
                util_curent->rang += '\n';
                list_util.scrieListaInFisier();
                nivelCurent = meniu_norm;
            }
            else
            {
                nrMorti = nrPierderi;
                nivelCurent = fail1;
            }
        }
    }else if(terminatJoc && timpActiune < 2)nivImg = 1;
    Meniu_ArataImgResp::ArataImgCoresp(joc_g.string_curent,f,nivImg);
    f.draw(cuvDeGhicit);
    f.draw(interactUtil);
    f.draw(timp);
    f.draw(pierderi);
    AfisSpanz::DesSpanz(f,ceSpanz);
    Sistem_Baza::AfiseazaNotificare(litEx,f,font);
}
void Joc_SelectCateg(sf::RenderWindow &f)
{
    f.draw(background);
    static sf::Clock t;
    static bool next = true;
    static ObjAnimTranzTxt tranzCateg;
    static Sectiune_Text_Lista categorii;
    static bool init = false;
    static sf::Text T_categorie;
    static int idCateg, nrCateg;
    static char categPrev[100];
    static int primaTranzitie;
    static int trCont;
    static int tranzOut;
    static int y;
    static int afisSpanz = 0;
    float timpTrecut = jSLCATEG.getElapsedTime().asSeconds();
    static sf::Text T_rang;
    if(!init)
    {
        T_rang.setString("-");
        T_rang.setFont(font);
        T_rang.setCharacterSize(60);
        T_rang.setPosition(300,130);
        t.restart();
        next = true;
        string pth;
        pth += Sistem_Baza::path();
        pth += "bazaDate\\listacateg.txt";
        ifstream f(pth.c_str());
        Sistem_Baza::scrieParagraf(f,"CATEGORII",categorii);
        f.close();
        idCateg = 1;
        y = -200;
        tranzOut = 0;
        primaTranzitie = 1;
        nrCateg = categorii.nrElemente();
        categorii.gasesteText(idCateg,categorie);
        strcpy(categPrev,categorie);
        T_categorie.setString(categorie);
        T_categorie.setCharacterSize(110);
        T_categorie.setPosition(600,350);
        T_categorie.setFont(font);
        tranzCateg.afis = &T_categorie;
        tranzCateg.pozXinit = T_categorie.getPosition().x;
        tranzCateg.pozYinit = T_categorie.getPosition().y;
        tranzCateg.terminat = 0;
        strcpy(tranzCateg.str1,categPrev);
        init = true;
    }
    size_t indice = util_curent->rang.find(categorie);
    if(indice != string::npos)
    {
        for(;util_curent->rang[indice] != ' ';++indice);
        T_rang.setString(util_curent->rang[indice+1]);
    }else T_rang.setString('-');
    if(y < 350)
    {
        y+=20;
        T_categorie.setPosition(600,y);
    }
    else if(y >= 350 && y <= 370)f.draw(T_rang);
    if(tranzOut)
    {
        y+=20;
        T_categorie.setPosition(600,y);
    }
    if(y > 720)
    {
        afisSpanz = 6;
        float volum = curent.getVolume();
        if(curent.getLoop())curent.setLoop(false);
        if(volum >= 1 && next)
        {
            volum -= 1.0;
            curent.setVolume(volum);
        }
        else if(next)
        {
            next = false;
            curent.stop();
            string pth;
            pth += Sistem_Baza::path();
            curent.openFromFile(pth + "audio/intro.ogg");
            curent.setVolume(200);
            curent.play();
        }
        sf::Color c = background.getColor();
        if(c.a>5)
        {
            c.a -= 5;
            background.setColor(c);
        }
        if(t.getElapsedTime().asSeconds() > 5)
        {
            c.a = 255;
            background.setColor(c);
            tranzOut = 0;
            afisSpanz = 0;
            init = false;
            nivelCurent = INTRO;
            jSPI.restart();
        }
    }
    if(timpTrecut > 0.3)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            if(idCateg == nrCateg)idCateg = 0;
            ++idCateg;
            categorii.gasesteText(idCateg,categorie);
            strcpy(tranzCateg.str1,categPrev);
            strcpy(tranzCateg.str2,categorie);
            strcpy(categPrev,categorie);
            tranzCateg.timpAnim.restart();
            tranzCateg.terminat = 0;
            primaTranzitie = 0;
            jSLCATEG.restart();
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            if(idCateg == 1)idCateg = nrCateg + 1;
            --idCateg;
            categorii.gasesteText(idCateg,categorie);
            strcpy(tranzCateg.str1,categPrev);
            strcpy(tranzCateg.str2,categorie);
            strcpy(categPrev,categorie);
            tranzCateg.timpAnim.restart();
            primaTranzitie = 0;
            tranzCateg.terminat = 0;
            jSLCATEG.restart();

        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
        {
            tranzOut = 1;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            mP.restart();
            tranzOut = 0;
            y = -200;
            init = false;
            nivelCurent = meniu_norm;
        }
    }
    if(!primaTranzitie)trCont = Sistem_Baza::Anim_TranzSelectTxt(tranzCateg,f);
    if(!trCont)f.draw(T_categorie);
    AfisSpanz::DesSpanz(f,afisSpanz);
}
void afisAccente(sf::RenderWindow &f, Comunicare &c)
{
    static std::wstring accente = L"ÀÂÄÈÉÊËÎÔÙÛÜŸÇ";
    static sf::Clock timp;
    static int accentCurent;
    static int tit = 0;
    static bool init = false;
    static sf::Text ac1,ac2,ac3;
    if(!init)
    {
        tit = 0;
        timp.restart();
        accentCurent = 0;
        ac1.setCharacterSize(40);
        ac1.setColor(sf::Color::White);
        ac2.setColor(sf::Color::White);
        ac3.setColor(sf::Color::White);
        ac2.setCharacterSize(40);
        ac3.setCharacterSize(40);
        ac1.setFont(font);
        ac1.setPosition(60,110);
        ac2.setPosition(60,150);
        ac3.setPosition(60,190);
        ac1.setString(accente[0]);
        ac2.setString(accente[1]);
        ac3.setString(accente[2]);
        ac2.setFont(font);
        ac3.setFont(font);
        init = true;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && timp.getElapsedTime().asSeconds() > 0.1 && accentCurent <= 15)
    {
        ++tit;
        ++accentCurent;
        timp.restart();
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && timp.getElapsedTime().asSeconds() > 0.1 && accentCurent >= 0)
    {
        --tit;
        --accentCurent;
        timp.restart();
    }
    if((tit == 2 || tit == -2) && accentCurent && accentCurent+1 <= 14)
    {
        tit = 0;
        ac1.setString(accente[accentCurent-1]);
        ac2.setString(accente[accentCurent]);
        ac3.setString(accente[accentCurent+1]);
    }
    ac1.setPosition(60,110);
    ac2.setPosition(60,150);
    ac3.setPosition(60,190);
    if(ac1.getString() == accente[accentCurent])ac1.setPosition(80,110);
    else if(ac2.getString() == accente[accentCurent])ac2.setPosition(80,150);
    else if(ac3.getString() == accente[accentCurent])ac3.setPosition(80,190);
    if(timp.getElapsedTime().asSeconds() > 0.2 && sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
    {
        c.text_dl_tastatura += accente[accentCurent];
        timp.restart();
    }
    f.draw(ac1);
    f.draw(ac2);
    f.draw(ac3);
}
int main()
{
    Comunicare instanta_comunic;
    sf::RenderWindow f(sf::VideoMode(1280,720),"Le Pendaison");
    f.setFramerateLimit(60);
    while(f.isOpen())
    {
        sf::Event ev;
        while(f.pollEvent(ev))
        {
            instanta_comunic.verifInchidere(f,ev);
            instanta_comunic.interactTastatura(f,ev,mesaj_interf);
        }
        f.clear();
        //miniGame2(f);
        //miniGame1(f);
        //miniGame3(f);
        if(nivelCurent == 0)Meniu_Welcome(f);
        else if(nivelCurent == meniu_prof_add)Meniu_AdaugaUtilizator(f,instanta_comunic);
        else if(nivelCurent == meniu_norm)Meniu_Principal(f, instanta_comunic);
        else if(nivelCurent == meniu_prof_sel)Meniu_SelectareUtil(f);
        else if(nivelCurent == joc_selcateg)Joc_SelectCateg(f);
        else if(nivelCurent == joc_spanz)Joc_JoacaSP(f,instanta_comunic);
        else if(nivelCurent == INTRO)Intro(f);
        else if(nivelCurent == fail1)Fail1(f);
        else if(nivelCurent == fail2)Fail2(f);
        else if(nivelCurent == castig)Castig(f);
        else if(nivelCurent == minigame1)miniGame1(f);
        else if(nivelCurent == minigame2)miniGame2(f);
        else if(nivelCurent == minigame3)miniGame3(f);
        else adaugaCategorie(f,instanta_comunic);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))afisAccente(f,instanta_comunic);
        f.display();
    }
    return 0;
}
