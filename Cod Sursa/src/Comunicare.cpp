#include "Comunicare.h"
void Comunicare :: interactTastatura(sf::RenderWindow &fereastra, sf::Event &ev, int &msg)
{
    static sf::Clock timpActiune;
    float timpRamas = timpActiune.getElapsedTime().asSeconds();
    if(ev.type == sf::Event::TextEntered && !sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
    {
        text_dl_tastatura += (char)ev.text.unicode;
        msg = TST_SCRIS;
        //timpActiune.restart();
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && text_dl_tastatura.size() > 0 && timpRamas>0.05)
    {
        text_dl_tastatura.erase(text_dl_tastatura.size()-1,1);
        msg = TST_BACKSP;
        timpActiune.restart();
    }
}
void Comunicare :: verifInchidere(sf::RenderWindow &fereastra,sf::Event &ev)
{
        if(ev.type == sf::Event::Closed)
            fereastra.close();
}
