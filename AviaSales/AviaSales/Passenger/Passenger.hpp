#ifndef Passenger_hpp
#define Passenger_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class Passenger {
private:
    string passportNumber = "";
    string placeAndDate = "";
    string name = "";
    string dateOfBirth = "";
    //Номера рейсов, на которые зарегистрирован пассажир
    vector<string> flights;
    
public:
    //Ввод&вывод данных
    Passenger();
    void passengerInit();
    void outputPassenger();
    
    //Запрос данных
    string getPassportNumber();
    string getPlaceAndDate();
    string getName();
    string getDateOfBirth();
    vector<string> getFlights();
    
    //Проверка данных
    bool isPassportNumberCorrect(string number);
    bool isPlaceAndDateCorrect(string placeAndDate);
    bool isNameCorrect(string name);
    bool isDateOfBirthCorrect(string date);
    bool isEmpty();
    
    //Ввод данных
    string inputString(string word);
    string inputPassportNumber();
    string inputPlaceAndDate();
    string inputName();
    string inputDateOfBirth();
    
    //Добавление номера рейса пассажиру
    bool addFlight(string flightNumber);
    //Удаление номера рейса из данных пассажира
    bool deleteFlight(string flightNumber);
    //Проверка регистрации пассажира на рейс
    bool containsFlight(string flightNumber);
    //Вывод номеров рейсов пассажира
    void showFlights();
};

#endif /* Passenger_hpp */
