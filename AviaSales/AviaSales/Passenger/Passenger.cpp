#include "Passenger.hpp"

using namespace std;

Passenger::Passenger() {
    string passportNumber = "";
    string placeAndDate = "";
    string name = "";
    string dateOfBirth = "";
}

void Passenger::passengerInit() {
    passportNumber = inputPassportNumber();
    placeAndDate = inputPlaceAndDate();
    name = inputName();
    dateOfBirth = inputDateOfBirth();
}

void Passenger::outputPassenger() {
    cout << endl;
    cout << setw(10) << "Пассажир. ";
    cout << "Номер паспорта            : " << passportNumber << endl;
    cout << setw(10) << " " << "Место и дата выдачи       : " << placeAndDate << endl;
    cout << setw(10) << " " << "ФИО                       : " << name << endl;
    cout << setw(10) << " " << "Дата рождения             : " << dateOfBirth << endl;
    cout << setw(10) << " " << "РЕЙСЫ                     : ";
    showFlights();
    cout << endl;
    
}

string Passenger::getPassportNumber() { return passportNumber; }
string Passenger::getPlaceAndDate() { return placeAndDate; }
string Passenger::getName() { return name; }
string Passenger::getDateOfBirth() { return dateOfBirth; }
vector<string> Passenger::getFlights() { return flights; }

bool Passenger::isPassportNumberCorrect(string number) {
    if (number.size() != 11) {
        cout << "[Ошибка] Неверная длина номера.\n";
        return false;
    }
    if (number[4] != '-') {
        cout << "[Ошибка] Неверный разделительный символ.\n";
        return false;
    }
    for (int i = 0; i <= 10; i++) {
        if (i != 4) {
            char a = number[i];
            if (!(a >= '0' && a <= '9')) {
                cout << "[Ошибка] Неверный формат ввода.\n";
                return false;
            }
        }
    }
    return true;
}

bool Passenger::isPlaceAndDateCorrect(string placeAndDate) {
    if (placeAndDate.size() > 20) {
        cout << "[Ошибка] Неверная длина ввода.\n";
        return false;
    }
    return true;
}

bool Passenger::isNameCorrect(string name) {
    if (name.size() > 30) {
        cout << "[Ошибка] Неверная длина ввода.\n";
        return false;
    }
    return true;
}

bool Passenger::isDateOfBirthCorrect(string date) {
    if (date.size() > 10) {
        cout << "[Ошибка] Неверная длина ввода.\n";
        return false;
    }
    return true;
}

bool Passenger::isEmpty() {
    return (passportNumber == "" &&
            placeAndDate == "" &&
            name == "" &&
            dateOfBirth == "");
}

string Passenger::inputString(string word) {
    bool iswork = true;
    while(iswork) {
        cout << "Введите " << word << endl;
        string s;
        
        cin.clear();
        fflush(stdin);
        getline(cin, s);

        if (!cin.fail()) {
            iswork = false;
            return s;
        } else {
            cout << "[Ошибка] Некорректный ввод строки.\n";
            iswork = true;
        }
    }
    return "";
}

string Passenger::inputPassportNumber() {
    bool iswork = true;
    while(iswork) {
        string passportNumber = inputString("номер паспорта в формате «NNNN-NNNNNN»");
        if (isPassportNumberCorrect(passportNumber)) {
            iswork = false;
            return passportNumber;
        } else {
            iswork = true;
        }
    }
    return "";
}

string Passenger::inputPlaceAndDate() {
    bool iswork = true;
    while(iswork) {
        string placeAndDate = inputString("место и дату выдачи паспорта (макс. 20 символов)");
        if (isPlaceAndDateCorrect(placeAndDate)) {
            iswork = false;
            return placeAndDate;
        } else {
            iswork = true;
        }
    }
    return "";
}

string Passenger::inputName() {
    bool iswork = true;
    while(iswork) {
        string name = inputString("ФИО (макс. 30 символов)");
        if (isNameCorrect(name)) {
            iswork = false;
            return name;
        } else {
            iswork = true;
        }
    }
    return "";
}

string Passenger::inputDateOfBirth() {
    bool iswork = true;
    while(iswork) {
        string date = inputString("дату рождения (макс. 10 символов)");
        if (isDateOfBirthCorrect(date)) {
            iswork = false;
            return date;
        } else {
            iswork = true;
        }
    }
    return "";
}

bool Passenger::containsFlight(string flightNumber) {
    for (auto x : flights) {
        if (x == flightNumber) return true;
    }
    return false;
}

bool Passenger::addFlight(string flightNumber) {
    if (containsFlight(flightNumber)) {
            cout << "Пассажир уже зарегистрирован на этот рейс.\n";
            return false;
    } else {
        flights.push_back(flightNumber);
        cout << "Номер рейса добавлен в данные пассажира.\n";
        return true;
    }
}

bool Passenger::deleteFlight(string flightNumber) {
    for (int i = 0; i < flights.size(); i++) {
        if (flights[i] == flightNumber) {
            flights.erase(flights.begin() + i);
            cout << "Из данных пассажира c паспортом № " << passportNumber << " удален рейс № " << flightNumber << ".\n";
            return true;
        }
    }
    cout << "[Ошибка] Пассажир не регистрировался на данный рейс.\n";
    return false;
}

void Passenger::showFlights() {
    if (flights.size() == 0) {
        cout << "пусто" << endl;
        return;
    }
    for (auto x : flights) {
        cout << x << "; ";
    }
    cout << endl;
}
