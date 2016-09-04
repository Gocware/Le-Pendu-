#include <Sistem_Baza.h>
using namespace std;
unsigned Sistem_Baza :: liniiScrise(ifstream &fisier)
{
    unsigned numarLinii = 0;
    char stocare_date_temp[20];
    while(fisier.getline(stocare_date_temp,20))++numarLinii;
    return numarLinii;
}
void Sistem_Baza :: scrieParagraf(ifstream &fisier, char delimitare[20], Sectiune_Text_Lista &lista)
{
    char text[100];
    fisier.getline(text,20);
    while(!strstr(text,delimitare))
         fisier.getline(text,20);
    fisier.getline(text,20);
    while(!strstr(text,delimitare))
    {
        lista.adaugaLinie(text);
        fisier.getline(text,20);
    }
}
int Sistem_Baza :: AfiseazaNotificare(ObjAnimNotificare &notif,sf::RenderWindow &f, sf::Font &font)
{
    if(notif.stagiuNotificare == 1)
    {

        notif.timpAnimatie.restart();
        notif.timpEnter.restart();
        notif.apasatEnter = 0;
        sf::Color culoare(sf::Color::White);
        notif.titlu_notif.setColor(culoare);
        notif.sprite_notificare.setColor(culoare);
        notif.afis_notif.setColor(culoare);
        notif.press_enter.setColor(culoare);
        return 0;
    }
    float timpTrecut = notif.timpAnimatie.getElapsedTime().asSeconds();
    if(!notif.init)
    {
        notif.afis_notif_x = 320; notif.afis_notif_y = 360; notif.titlu_notif_x = 310; notif.titlu_notif_y = 300; notif.press_enter_x = 400; notif.press_enter_y = 550;
        notif.afis_sz = 80; notif.press_enter_sz = 40; notif.titlu_notif_sz = 150;
        notif.afis_notif.setString(notif.notificare);
        notif.afis_notif.setFont(font);

        notif.titlu_notif.setFont(font);
        notif.titlu_notif.setString("-ATTENTION!-");
        notif.titlu_notif.setCharacterSize(notif.titlu_notif_sz);

        notif.press_enter.setFont(font);
        notif.press_enter.setString("-Appuyez sur Entree pour continuer-");
        notif.press_enter.setCharacterSize(notif.press_enter_sz);

        notif.textura_notificare.loadFromFile("grafica/notif.png");
        notif.sprite_notificare.setTexture(notif.textura_notificare);

        notif.afis_sz -= (strlen(notif.notificare)/2.2);
        notif.afis_notif.setCharacterSize(notif.afis_sz);
        notif.titlu_notif_y = -100;
        notif.init = true;

        sf::Color culoare = notif.sprite_notificare.getColor();
        culoare.a = 0;
        notif.sprite_notificare.setColor(culoare);
    }
    // Prima parte a animatiei
    if(timpTrecut > 0.0001 && notif.apasatEnter != 1)
    {
        //Animatie - introducere notificare
        if(notif.titlu_notif_y < 300)notif.titlu_notif_y += 15;
        notif.titlu_notif.setPosition(notif.titlu_notif_x,notif.titlu_notif_y);
        sf::Color bg = notif.sprite_notificare.getColor();
        if(bg.a < 255)bg.a += 5;
        notif.sprite_notificare.setColor(bg);
        //Animatie - introducere notificare
        //Animatie - alternanta vizibilitate press enter
        sf::Color culoare = notif.press_enter.getColor();
        culoare.a += 2.5*notif.ratieCuloare;
        if(culoare.a  == 5)notif.ratieCuloare = 1;
        else if(culoare.a  >= 250)notif.ratieCuloare=-1;
        notif.press_enter.setColor(culoare);
        //Animatie - alternanta vizibilitate press enter
        notif.timpAnimatie.restart();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && notif.timpEnter.getElapsedTime().asSeconds() > 0.5)
        {
            notif.timpEnter.restart();
            notif.apasatEnter = 1;
        }
        //Notificare inchisa, -> animatie de inchidere
    }
    else if(timpTrecut > 0.0001 && notif.apasatEnter)
    {
        // Animatie - sfarsit notificare
        notif.titlu_notif_y += 15;
        notif.titlu_notif.setPosition(notif.titlu_notif_x,notif.titlu_notif_y);


        /* Original aveam 2 culori pt titlu_notif si notificare, dar
           am renuntat deoarece aveau aceleasi valori, nu avea sens
           sa alocam 2 obiecte de tip Color si sa le modificam.
        */

        sf::Color culoare = notif.titlu_notif.getColor();
        if(culoare.a)culoare.a -= 9;

        notif.titlu_notif.setColor(culoare);
        notif.sprite_notificare.setColor(culoare);
        notif.afis_notif.setColor(culoare);
        notif.press_enter.setColor(culoare);

        if(notif.titlu_notif_y>=720)
        {
            notif.stagiuNotificare = 1;
            return 0; // Nu se mai vede pe ecran notificarea
        }
        // Animatie - sfarsit notificare
    }
    notif.afis_notif_y = notif.titlu_notif_y + 150;
    notif.afis_notif.setPosition(notif.afis_notif_x,notif.afis_notif_y);
    notif.titlu_notif.setPosition(notif.titlu_notif_x,notif.titlu_notif_y);
    notif.press_enter_y = notif.afis_notif_y + (notif.afis_sz*2);
    notif.press_enter.setPosition(notif.press_enter_x,notif.press_enter_y);
    f.draw(notif.sprite_notificare);
    f.draw(notif.titlu_notif);
    f.draw(notif.afis_notif);
    f.draw(notif.press_enter);
    return 1; // Notificare inca vizibila
}
Sectiune_Text :: Sectiune_Text()
{
    urmatorul = 0;
    spate = 0;
}
Sectiune_Text_Lista :: Sectiune_Text_Lista()
{
    travers = 0;
    inceput = 0;
}
Sectiune_Text_Lista :: ~Sectiune_Text_Lista()
{
    stergeLista();
}
unsigned Sectiune_Text_Lista::nrElemente()
{
    Sectiune_Text *parcurgere = inceput;
    if(!parcurgere)return 0;
    else
    {
        unsigned nr_Elemente = 1;
        while(parcurgere->urmatorul)
        {
           ++nr_Elemente;
           parcurgere = parcurgere->urmatorul;
        }
        return nr_Elemente;
    }
}
void Sectiune_Text_Lista::adaugaLinie(char text[100])
{
    if(inceput == 0)
    {
        travers = new Sectiune_Text();
        travers->indice = 1;
        strcpy(travers->text,text);
        inceput = travers;
        //travers->spate = inceput;
    }
    else
    {
        int indice = travers->indice;
        travers->urmatorul = new Sectiune_Text();
        travers->urmatorul->indice = indice+1;
        travers->urmatorul->spate = travers;
        strcpy(travers->urmatorul->text,text);
        travers = travers->urmatorul;
    }
}
void Sectiune_Text_Lista::gasesteText(unsigned indice_cautare, char text[100])
{
    Sectiune_Text *parcurgere = inceput;
    while(indice_cautare != 1 && parcurgere->urmatorul!=0)
    {
        --indice_cautare;
        parcurgere = parcurgere->urmatorul;
    }
    strcpy(text,parcurgere->text);
}
void Sectiune_Text_Lista::stergeCuvant(unsigned indice_cautare)
{
    Sectiune_Text *parcurgere = inceput;
    if(indice_cautare == 1)
    {
        Sectiune_Text *c_urmatorul;
        c_urmatorul = parcurgere->urmatorul;
        delete inceput;
        inceput = c_urmatorul;
        return;
    }
    while(indice_cautare != 1 && parcurgere->urmatorul)
    {
        --indice_cautare;
        parcurgere = parcurgere->urmatorul;
    }
    if(parcurgere->urmatorul != 0)
    {
        Sectiune_Text *c_urmatorul;
        c_urmatorul =  parcurgere->urmatorul;
        parcurgere = parcurgere->spate;
        c_urmatorul->spate = parcurgere;
        delete parcurgere->urmatorul;
        parcurgere->urmatorul = c_urmatorul;
    }
    else
    {
        travers = travers->spate;
        delete travers->urmatorul;
        travers->urmatorul = 0;
    }
}
string Sistem_Baza::path()
{
    char dst[MAX_PATH];
    GetModuleFileName(NULL,dst,MAX_PATH);
    int j = strlen(dst) - 1;
    for(;dst[j]!='\\';)--j;
    ++j;
    dst[j] = 0;
    string ret;
    ret+=dst;
    return ret;
}
void Sectiune_Text_Lista::stergeLista()
{
    if(inceput != 0)
    {
        Sectiune_Text *parcurgere = inceput;
        while(parcurgere->urmatorul)
        {
            Sectiune_Text *ptr_copie = parcurgere->urmatorul;
            delete parcurgere;
            parcurgere = ptr_copie;
        }
        inceput = 0;
        travers = 0;
    }
}
Lista_Utilizatori :: Lista_Utilizatori()
{
    travers = 0;
}
void Lista_Utilizatori :: adauga(Date_Utilizator utilizator_nou)
{
    if(travers == 0)
    {
        travers = new Date_Utilizator();
        strcpy(travers->nume,utilizator_nou.nume);
        travers->rang = utilizator_nou.rang;
        travers->indice = 1;
        inceput = travers;
    }
    else
    {
        int indice = travers->indice;
        travers->urmatorul = new Date_Utilizator();
        strcpy(travers->urmatorul->nume,utilizator_nou.nume);
        travers->urmatorul->rang = utilizator_nou.rang;
        travers->urmatorul->indice = indice+1;
        travers = travers->urmatorul;
    }
}
Date_Utilizator *Lista_Utilizatori :: gaseste_utilizator(int poz)
{
    Date_Utilizator *verificare = inceput;
    while(verificare->urmatorul && verificare->indice != poz)
        verificare = verificare->urmatorul;
    return verificare;
}
unsigned Lista_Utilizatori ::nrUtilizatori()
{
    Date_Utilizator *verif = inceput;
    unsigned nr_Util = 1;
    if(!verif)return 0;
    while(verif->urmatorul)
    {
        ++nr_Util;
        verif = verif->urmatorul;
    }
    return nr_Util;
}
Lista_Utilizatori::~Lista_Utilizatori()
{
    if(inceput != 0)
    {
        Date_Utilizator *parcurs = inceput;
        while(parcurs->urmatorul)
        {
           Date_Utilizator *parcurs_copie = parcurs->urmatorul;
           delete parcurs;
           parcurs = parcurs_copie;
        }
    }
}
void Lista_Utilizatori::scrieListaInFisier()
{
    string pth;
    pth = Sistem_Baza::path();
    pth += "\\salvari\\";
    pth += "utilizatori.txt";
    ofstream l(pth.c_str());
    Date_Utilizator *parcurgere = inceput;
    char delimParagraf[100];
    strcpy(delimParagraf,inceput->nume);
    pth = Sistem_Baza::path();
    pth += delimParagraf;
    if(nrUtilizatori() == 0)
    {
        l<<delimParagraf<<'\n';
        pth= Sistem_Baza::path();
        pth += "\\salvari\\";
        pth += delimParagraf;
        pth +='.txt';
        ofstream f(pth.c_str());
        f<<parcurgere->rang<<'\n';
    }
    else while(parcurgere)
    {
        strcpy(delimParagraf,parcurgere->nume);
        l<<delimParagraf<<'\n';
        pth= Sistem_Baza::path();
        pth += "\\salvari\\";
        pth += delimParagraf;
        pth +=".txt";
        ofstream f(pth.c_str());
        f<<parcurgere->rang<<'\n';
        parcurgere = parcurgere->urmatorul;
    }
}
void Lista_Utilizatori::initializeazaListaDinFisier()
{
    Date_Utilizator utilizator;
    string pth;
    pth += Sistem_Baza::path();
    pth += "\\salvari\\";
    pth += "utilizatori.txt";
    ifstream fisier(pth.c_str());
    while(fisier >> utilizator.nume)
    {
        string linie;
        pth = Sistem_Baza::path();
        pth += "\\salvari\\";
        pth+= utilizator.nume;
        pth+= ".txt";
        ifstream f(pth.c_str());
        while(getline(f,linie))
        {
            linie+='\n';
            utilizator.rang += linie;
        }
        adauga(utilizator);
    }
    fisier.close();
}
int Joc::formeazaJoc(char categ_param[100], int mesaj, int &nrCuv)
{
    static Sectiune_Text_Lista paragraf;
    if(mesaj == 1)
    {
        string pth;
        pth += Sistem_Baza::path();
        pth += "bazaDate\\baza.txt";
        ifstream fisier(pth.c_str());
        Sistem_Baza::scrieParagraf(fisier,categ_param,paragraf);
        strcpy(categorie,categ_param);
        fisier.close();
        srand(time(NULL));
        unsigned maxim = paragraf.nrElemente();
        unsigned cuvantRandom;
        if(maxim == 0)return 0;
        else if(maxim == 1)cuvantRandom = 1;
        else
        {
            rand();
            cuvantRandom= 1 + (rand()%(int)(maxim - 1));
        }
        paragraf.gasesteText(cuvantRandom,string_curent);
        paragraf.stergeCuvant(cuvantRandom);
        interschimbare(string_curent,cuvant,strlen(string_curent));
        nrCuv = maxim;
    }
    else if(mesaj == 2)
    {
        //scoate ultimul cuvant
        srand(time(NULL));
        unsigned maxim = paragraf.nrElemente();
        unsigned cuvantRandom;
        if(maxim == 0)return 0;
        else if(maxim == 1)cuvantRandom = 1;
        else
        {
            rand();
            cuvantRandom= 1 + (rand()%(int)(maxim - 1));
        }
        paragraf.gasesteText(cuvantRandom,string_curent);
        paragraf.stergeCuvant(cuvantRandom);
        interschimbare(string_curent,cuvant,strlen(string_curent));
        nrCuv = maxim;
    }
    else if(mesaj == 3)paragraf.stergeLista();
    return 1;
}

Date_Utilizator :: Date_Utilizator()
{
    urmatorul = 0;
}
short Joc :: interschimbare(char string_curent[100],char cuvant[100],short n)
{
    short k=0;
    cuvant[0]=string_curent[0];
    cuvant[n-1] = string_curent[n-1];
    cuvant[n] = 0;
    for(int i=1;i<n-1;i++)cuvant[i]= '_';
    return k;
}
int Joc ::actualizareInteractiuneJucator(const char *mesaj)
{
    short s=0,litExist = 0;
    static short greseli=0;
    short n = strlen(string_curent);
    for(int i=1;i<n-1;i++)
    {
        if(cuvant[i] == *mesaj)
        {
            litExist = 1;
            break;
        }
        else if(string_curent[i] == *mesaj && cuvant[i] == '_')
                {
                    cuvant[i] = *mesaj;
                    litExist = 0;
                    s = 1;
                }
        else if(string_curent[i] == ' ' || string_curent[i] == '-')cuvant[i] = string_curent[i];
    }
    if(litExist)return 4;
    else if(greseli==7)
    {
        greseli = 0;
        return 2;// nu a reusit sa ghiceasca cuvantul
    }
    else if(!s){++greseli;return 0;}//nunu  a gasit nici o litera in cuvantul cautat care sa fie buna
    else if(strcmp(cuvant,string_curent)==0)
    {
        greseli = 0;
        return 3;//a reusit sa ghiceasca cuvantul,deci a castigat
    }
    else if(s) return 1;// a ghicit litera
}
int Sistem_Baza::Anim_TranzSelectTxt(ObjAnimTranzTxt &tranz, sf::RenderWindow &f)
{
    if(!tranz.terminat)
    {
        float timpTrecut = tranz.timpAnim.getElapsedTime().asSeconds();
        if(timpTrecut > 0.0001)
        {
            float x = tranz.afis->getPosition().x;
            sf::Color culoare = tranz.afis->getColor();
            if(x >= tranz.pozXinit)
                x-=10;
            if(x <= 0)
            {
                x = 1280;
                tranz.schimba = 1;
                culoare.a = 0;
                tranz.afis->setString(tranz.str2);
            }
            if(x <= tranz.pozXinit && tranz.schimba == 1)
            {
                tranz.afis->setPosition(tranz.pozXinit,tranz.pozYinit);
                tranz.terminat = 1;
                tranz.schimba = -1;

                tranz.timpAnim.restart();
                return 0;
            }
            x-= 62;
            float testSchimbCuloare = culoare.a + (tranz.schimba*26);
            if(testSchimbCuloare <= 255 && testSchimbCuloare>=0)culoare.a = testSchimbCuloare;
            tranz.afis->setColor(culoare);
            tranz.afis->setPosition(x,tranz.pozYinit);
            f.draw(*tranz.afis);
            tranz.timpAnim.restart();
            return 1;
        }
    }else
        return 0;
}

