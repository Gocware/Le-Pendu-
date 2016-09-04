#ifndef ANIMATII_H
#define ANIMATII_H
#include<Sistem_Baza.h>
class Meniu_ArataImgResp
{
    public:
        static int ArataImgCoresp(string img, sf::RenderWindow &f, int niv);
};
class ArataImgCuvant
{
    public :
        static int AImgCuvant(string cuv, sf::RenderWindow &f);

};
class AfisSpanz
{
    public :
        static void DesSpanz(sf::RenderWindow &f, int niv);

};
#endif // ANIMATII_H
