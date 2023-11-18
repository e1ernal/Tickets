#ifndef Flight_hpp
#define Flight_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "Passenger.hpp"

using namespace std;

struct shortPassenger {
    string passNum = "";
    string name = "";
    shortPassenger(string s1, string s2) {
        passNum = s1;
        name = s2;
        
    }
};

class Flight {
private:
    string fligthNumber = "";
    string airlineName = "";
    //Аэропорт отправления
    string departureAirport = "";
    //Аэропорт прибытия
    string arrivalAirport = "";
    string departureDate = "";
    string departureTime = "";
    int seatsNumber = 0;
    int seatsFree = 0;
    //Зарегистрированные на рейс пассажиры
    vector<shortPassenger> passengers;
    
public:
    //Ввод&вывод данных
    Flight();
    void fligtInput();
    void flightOutput();
    
    //Запрос данных
    string getFlightNumber();
    string getAirlineName();
    string getDepartureAirport();
    string getArrivalAirport();
    string getDepartureDate();
    string getDepartureTime();
    int getSeatsNumber();
    int getSeatsFree();
    vector<shortPassenger> getPassengers();
    
    //Проверка данных
    bool isFlightNumberCorrect(string number);
    bool isAirlineNameCorrect(string airlineName);
    bool isDepartureAirportCorrect(string departureAirport);
    bool isArrivalAirportCorrect(string arrivalAirport);
    bool isDepartureDateCorrect(string departureDate);
    bool isDepartureTimeCorrect(string departureTime);
    bool isSeatsNumberCorrect(int seatsNumber);
    bool isSeatsFreeCorrect(int seatsFree);
    bool isEmpty();
    
    //Ввод данных
    int inputInt(string word);
    string inputString(string word);
    string inputFlightNumber();
    string inputAirlineName();
    string inputDepartureAirport();
    string inputArrivalAirport();
    string inputDepartureDate();
    string inputDepartureTime();
    int inputSeatsNumber();
    int inputSeatsFree();
    
    //Регистрация на рейс
    bool registerPassenger(string passNum, string name);
    //Проверка возможности регистрации на рейс
    bool canRegisterPassenger(string passNum);
    //Проверка возможности сдачи билета
    bool canReturnPassenger(string passNum);
    //Возврат билета
    bool deletePassenger(string passNum, string name);
    //Вывод зарегистрированных на рейс пассажиров
    void showPassengers();
};

#endif /* Flight_hpp */
