#ifndef COMUNICARE_H
#define COMUNICARE_H

#include<string>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<iostream>

#define TST_SCRIS 1
#define TST_BACKSP 2

class Comunicare
{
    public:
        void verifInchidere(sf::RenderWindow &fereastra,sf::Event &ev);
        void interactTastatura(sf::RenderWindow &fereastra,sf::Event &ev, int &msg);
        std::string text_dl_tastatura;

};

#endif // COMUNICARE_H
