#include "Animatii.h"
#include "Sistem_Baza.h"
int Meniu_ArataImgResp :: ArataImgCoresp(string img, sf::RenderWindow &f, int niv)
{
    static sf::Texture text;
    static sf::Sprite sprite;
    static string img_c = "NULL";
    static int x = -200, y = 320;
    if(img_c != img)
    {
        string path = Sistem_Baza::path() + "bazaDate\\Imagini\\";
        path += img;
        path += ".png";
        if(!text.loadFromFile(path))
        {
            path = Sistem_Baza::path() + "bazaDate\\Imagini\\";
            path += img;
            path += ".jpg";
            text.loadFromFile(path);
        }
        img_c = img;
        sprite.setTexture(text,true);
        sprite.setScale(300/sprite.getLocalBounds().width,220/sprite.getLocalBounds().height);
        sprite.setOrigin(sprite.getLocalBounds().width/2,sprite.getLocalBounds().height/2);
        sprite.setPosition(-200,y);
    }
    if(niv == 1 && x < 300)sprite.setPosition(x+=10,y);
    else if(niv == 0 && x > -200)sprite.setPosition(x-=10,y);
    f.draw(sprite);
}
void AfisSpanz::DesSpanz(sf::RenderWindow &f, int niv)
{
    static bool primaData = true;
    static bool init = false;
    static sf::Clock timpAnimIntro;
    static sf::Clock timpAnim1;
    static float unghiRotatie = 0.5;
    static int ratieRotatie = -1;
    static sf::Texture s1, s2;
    static sf::Sprite sp1, sp2;
    static int nivC = niv;
    if(!init)
    {
        s1.loadFromFile(Sistem_Baza::path() + "grafica\\sp_pt1.png");
        s2.loadFromFile(Sistem_Baza::path() + "grafica\\sp_pt2.png");
        s1.setSmooth(true);
        s2.setSmooth(true);
        sp1.setTexture(s1);
        sp2.setTexture(s2);
        sp1.setPosition(-100,100);
        sp1.setScale(0.8,0.8);
        sp2.setScale(0.8,0.8);
        sp2.setOrigin(sp2.getGlobalBounds().width/2,sp2.getGlobalBounds().height/2);
        sp2.setPosition(280,320);
        sf::Color c = sp1.getColor();
        c.a = 0;
        sp1.setColor(c);
        sp2.setColor(c);
        timpAnimIntro.restart();
        init = true;
    }
    if(timpAnimIntro.getElapsedTime().asSeconds() > 1)
    {
        sf::Color c = sp1.getColor();
        if(c.a < 250)
        {
            ++c.a;
            sp1.setColor(c);
            sp2.setColor(c);
        }
    }
    sf::Color c = sp2.getColor();
    if(niv == 6)
    {
        nivC = niv;
        if(primaData)
        {
            primaData = false;
            c.a = 255;
        }
        if(c.a >= 5)
        {
            c.a-=5;
            sp1.setColor(c);
            sp2.setColor(c);
        }
    }
    if(nivC != niv)
    {
        if(niv == 1)
        {
            primaData = true;
            c.a = 255;
            sp1.setColor(c);
            sp2.setColor(c);
            nivC = niv;
            s2.loadFromFile(Sistem_Baza::path() + "grafica\\sp_pt2cry.png");
            sp1.setPosition(-100,100);
            sp2.setPosition(280,320);
        }
        else if(niv == 5)
        {
            primaData = true;
            c.a = 255;
            sp1.setColor(c);
            sp2.setColor(c);
            nivC = niv;
            s2.loadFromFile(Sistem_Baza::path() + "grafica\\sp_pt2happy.png");
        }
        else if(niv == 10)
        {
            timpAnimIntro.restart();
            primaData = true;
            nivC = niv;
            s2.loadFromFile(Sistem_Baza::path() + "grafica\\sp_pt2.png");
            sp1.setPosition(200,-100);
            sp2.setPosition(580,120);

        }
        else if(niv == 11)
        {
            timpAnimIntro.restart();
            primaData = true;
            nivC = niv;
            s2.loadFromFile(Sistem_Baza::path() + "grafica\\sp_pt2nsp.png");
            sp1.setPosition(200,-100);
            sp2.setPosition(580,120);
        }
        else
        {
            nivC = niv;
            s2.loadFromFile(Sistem_Baza::path() + "grafica\\sp_pt2.png");
        }
    }
    if(timpAnim1.getElapsedTime().asSeconds()>0.04 && niv != 11)
    {
        if(unghiRotatie <= -0.5)ratieRotatie = 1;
        else if(unghiRotatie >= 0.5)ratieRotatie = -1;
        sp2.rotate(unghiRotatie);
        unghiRotatie += (0.05)*ratieRotatie;
        timpAnim1.restart();
    }
    f.draw(sp2);
    f.draw(sp1);
}

