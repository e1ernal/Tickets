#ifndef Ticket_hpp
#define Ticket_hpp

#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <iomanip>
#include <iostream>

using namespace std;

struct Ticket {
    //Номер паспорта
    string passNumber = "";
    //Номер авиарейса
    string fligthNumber = "";
    //Номер авиабилета – строка из 9 цифр
    string ticketNumber = "";
    
    Ticket();
    Ticket(string pass, string flight, string ticket);
    bool isEmpty();
    //Генерация номера билета
    string generateTicket();
    //Запрос номера билета
    int getTiketNumberInt();
    //Вывод данных билета
    void outputTicket();
};

#endif /* Ticket_hpp */
