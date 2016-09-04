#include "Buton.h"
// Implementarea clasei Buton
/*
   Un buton reprezinta o entitate ce are posibilitatea de a
   returna mesaje si primi mesaje de la alte entitati.
   Acesta poate sa prezinte mai multe forme, de exemplu, poate
   avea un background pe care se afla scrisul butonului, poate
   butonul nu se comporta ca un "buton real", ci doar ca o
   "pancarda". De exemplu, poate dorim sa afisam un mesaj in
   mediul jocului. Putem sa avem un buton care nu este "apasabil"
   ci doar afiseaza scrisul de pe el. E ca si cum ai vedea un
   buton pe care scrie "OK" fara ca acesta sa faca ceva.
   Datorita versatilitatii acestei clasei Buton, ea sta la baza
   construirii interfetei aplicatei noastre.
*/
void Buton :: initButon(int tipButon, int mesajButon,int idButon, char textButon[100], char imgButon[100], int dimCaract, float x, float y)
{
    // Functia are rolul de a pregati obiectul Buton pentru utilizare.
    this->idButon = idButon;
    this->tipButon = tipButon;
    this->mesajButon = mesajButon;
    //NOTA : A NU SE FACE CONFUZIE INTRE MESAJUL SI TEXTUL BUTONULUI.
    //MESAJUL ESTE UTILIZAT IN LOGICA PROGRAMULUI.
    text.setString(textButon);
    font.loadFromFile("grafica/font1.ttf");
    //Acesta este fontul de baza pe care o sa il utilizam.
    text.setFont(font);
    text.setCharacterSize(dimCaract);
    texture.loadFromFile(imgButon);
    sprite.setTexture(texture);
    // Acum urmeaza sa pregatim butonul pentru manipularea coordonatelor.
    sf::IntRect spriteRect = sprite.getTextureRect();
    sf::FloatRect textRect = text.getGlobalBounds();
    sprite.setOrigin(spriteRect.width /2, spriteRect.height/2);
    sprite.setPosition(x,y);
    text.setOrigin(textRect.width + textRect.left / 2, textRect.height + textRect.top / 2);
    text.setPosition(x + (textRect.width/2), y + (textRect.height/2) );
}
void Buton :: schimbaTextButon(char textButon[100])
{
    text.setString(textButon);
}
void Buton::schimbaDimCatact(int dimCaract)
{
    text.setCharacterSize(dimCaract);
}
void Buton::schimbaPozButon(float y, float x)
{
    sf::FloatRect textRect = text.getGlobalBounds();
    sprite.setPosition(x,y);
    text.setPosition(x + (textRect.width/2), y + (textRect.height/2) );
}
void Buton::afisButon(sf::RenderWindow &fereastra, int A_fundal, int A_text)
{
    if(A_fundal)fereastra.draw(sprite);
    if(A_text)fereastra.draw(text);
}
int Buton::contineMouse(sf::Vector2i mouse)
{
    sf::FloatRect buton = sprite.getGlobalBounds();
    return buton.contains((float)mouse.x,(float)mouse.y);
}
