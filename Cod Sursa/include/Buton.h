#ifndef BUTON_H
#define BUTON_H

// "Comenzi" specifice clasei Buton
#define Y_AFIS_TXT 1
#define Y_AFIS_FND 1
#define N_AFIS_TXT 0
#define N_AFIS_FND 0
// Sfarsit comenzi
#include<SFML/Graphics.hpp>

class Buton
{
    public:
        int tipButon;
        int mesajButon;
        int idButon;
        void afisButon(sf::RenderWindow &fereastra, int A_fundal, int A_text);
        void initButon(int tipButon, int mesajButon,int idButon, char textButon[100], char imgButon[100], int dimCaract, float x, float y);
        void schimbaTextButon(char textButon[100]);
        void schimbaDimCatact(int dimCaract);
        void schimbaPozButon(float x, float y);
        int contineMouse(sf::Vector2i mouse);
    private:
        sf::Texture texture;
        sf::Sprite sprite;
        sf::Text text;
        sf::Font font;
        sf::Color color;
};

#endif // BUTON_H
