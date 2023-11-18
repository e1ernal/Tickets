#include "Flight.hpp"

using namespace std;

Flight::Flight() {
    fligthNumber = "";
    airlineName = "";
    departureAirport = "";
    arrivalAirport = "";
    departureDate = "";
    departureTime = "";
    seatsNumber = 0;
    seatsFree = 0;
    vector<Passenger> passengers;
}

void Flight::fligtInput() {
    fligthNumber = inputFlightNumber();
    airlineName = inputAirlineName();
    departureAirport = inputDepartureAirport();
    arrivalAirport = inputArrivalAirport();
    departureDate = inputDepartureDate();
    departureTime = inputDepartureTime();
    seatsNumber = inputSeatsNumber();
    seatsFree = seatsNumber;
}

void Flight::flightOutput() {
    cout << endl;
    cout << left << setw(10) << "Рейс.";
    cout << setw(4)  << " " << "Номер авиарейса           : " << fligthNumber << endl;
    cout << setw(10) << " " << "Название авиакопании      : " << airlineName << endl;
    cout << setw(10) << " " << "Аэропорт отправления      : " << departureAirport << endl;
    cout << setw(10) << " " << "Аэропорт прибытия         : " << arrivalAirport << endl;
    cout << setw(10) << " " << "Дата отправления          : " << departureDate << endl;
    cout << setw(10) << " " << "Время отправления         : " << departureTime << endl;
    cout << setw(10) << " " << "Количество мест всего     : " << seatsNumber << endl;
    cout << setw(10) << " " << "Количество мест свободных : " << seatsFree << endl;
    cout << setw(10) << " " << "ПАССАЖИРЫ" << endl;
    showPassengers();
    cout << endl;
}

//Запрос данных
string Flight::getFlightNumber() { return fligthNumber; }
string Flight::getAirlineName() { return airlineName; }
string Flight::getDepartureAirport() { return departureAirport; }
string Flight::getArrivalAirport() { return arrivalAirport; }
string Flight::getDepartureDate() { return departureDate; }
string Flight::getDepartureTime() {return departureTime; }
int Flight::getSeatsNumber() { return seatsNumber; }
int Flight::getSeatsFree() { return seatsFree; }
vector<shortPassenger> Flight::getPassengers() { return passengers; }


bool isLetter(char a) {
    return (a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z');
}

bool isNumber(char a) {
    return (a >= '0' && a <= '9');
}


//Проверка данных
bool Flight::isFlightNumberCorrect(string number) {
    if (number.size() != 7) {
        cout << "[Ошибка] Неверная длина номера.\n";
        return false;
    }
    if (number[3] != '-') {
        cout << "[Ошибка] Неверный разделительный символ.\n";
        return false;
    }
    for (int i = 0; i <= 2; i++) {
        if (!isLetter(number[i]) || !isNumber(number[7 - i - 1])) {
            cout << "[Ошибка] Неверный формат ввода.\n";
            return false;
        }
    }
    return true;
}
bool Flight::isAirlineNameCorrect(string airlineName) {
    int maxAirLineName = 15;
    if (airlineName.size() > maxAirLineName) {
        cout << "[Ошибка] Неверная длина ввода.\n";
        return false;
    }
    return true;
}
bool Flight::isDepartureAirportCorrect(string departureAirport) {
    int maxDepartureAirport = 15;
    if (departureAirport.size() > maxDepartureAirport) {
        cout << "[Ошибка] Неверная длина ввода.\n";
        return false;
    }
    return true;
}
bool Flight::isArrivalAirportCorrect(string arrivalAirport) {
    int maxArrivalAirport = 15;
    if (arrivalAirport.size() > maxArrivalAirport) {
        cout << "[Ошибка] Неверная длина ввода.\n";
        return false;
    }
    return true;
}
bool Flight::isDepartureDateCorrect(string departureDate) {
    int maxDepartureDate = 10;
    if (departureDate.size() > maxDepartureDate) {
        cout << "[Ошибка] Неверная длина ввода.\n";
        return false;
    }
    return true;
}
bool Flight::isDepartureTimeCorrect(string departureTime) {
    int maxDepartureTime = 5;
    if (departureTime.size() > maxDepartureTime) {
        cout << "[Ошибка] Неверная длина ввода.\n";
        return false;
    }
    return true;
}
bool Flight::isSeatsNumberCorrect(int seatsNumber) {
    int maxSeatsNumber = 100;
    if (seatsNumber > maxSeatsNumber || seatsNumber <= 0) {
        cout << "[Ошибка] Неверное значение.\n";
        return false;
    }
    return true;
}
bool Flight::isSeatsFreeCorrect(int seatsFree) {
    int maxSeatsFree = 100;
    if (seatsFree > maxSeatsFree || seatsFree < 0 || seatsFree > seatsNumber) {
        cout << "[Ошибка] Неверное значение.\n";
        return false;
    }
    return true;
}
bool Flight::isEmpty() {
    return (fligthNumber == "" &&
            airlineName == "" &&
            departureAirport == "" &&
            arrivalAirport == "" &&
            departureDate == "" &&
            departureTime == "" &&
            seatsNumber == 0 &&
            seatsFree == 0);
}

//Ввод данных
string Flight::inputString(string word) {
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
int Flight::inputInt(string word) {
    bool iswork = true;
    while(iswork) {
        cout << "Введите " << word << endl;
        int number;

        cin.clear();
        fflush(stdin);
        cin >> number;

        if (!cin.fail()) {
            iswork = false;
            return number;
        } else {
            cout << "[Ошибка] Некорректный ввод числа.\n";
            iswork = true;
        }
    }
    return -1;
}
string Flight::inputFlightNumber() {
    bool iswork = true;
    while(iswork) {
        string flightNumber = inputString("номер авиарейса формата «AAA-NNN», где AAA – буквы латиницы; NNN – цифры");
        if (isFlightNumberCorrect(flightNumber)) {
            iswork = false;
            return flightNumber;
        } else {
            iswork = true;
        }
    }
    return "";
}
string Flight::inputAirlineName() {
    bool iswork = true;
    while(iswork) {
        string airlineName = inputString("название авиакомпании (макс. 15 символов).");
        if (isAirlineNameCorrect(airlineName)) {
            iswork = false;
            return airlineName;
        } else {
            iswork = true;
        }
    }
    return "";
}

string Flight::inputDepartureAirport() {
    bool iswork = true;
    while(iswork) {
        string departureAirport = inputString("аэропорт отправления (макс. 15 символов).");
        if (isDepartureAirportCorrect(departureAirport)) {
            iswork = false;
            return departureAirport;
        } else {
            iswork = true;
        }
    }
    return "";
}
string Flight::inputArrivalAirport() {
    bool iswork = true;
    while(iswork) {
        string arrivalAirport = inputString("аэропорт прибытия (макс. 15 символов).");
        if (isArrivalAirportCorrect(arrivalAirport)) {
            iswork = false;
            return arrivalAirport;
        } else {
            iswork = true;
        }
    }
    return "";
}
string Flight::inputDepartureDate() {
    bool iswork = true;
    while(iswork) {
        string departureDate = inputString("дату отправления (макс. 10 символов).");
        if (isDepartureDateCorrect(departureDate)) {
            iswork = false;
            return departureDate;
        } else {
            iswork = true;
        }
    }
    return "";
}
string Flight::inputDepartureTime() {
    bool iswork = true;
    while(iswork) {
        string departureTime = inputString("время отправления (макс. 5 символов).");
        if (isDepartureTimeCorrect(departureTime)) {
            iswork = false;
            return departureTime;
        } else {
            iswork = true;
        }
    }
    return "";
}
int Flight::inputSeatsNumber() {
    bool iswork = true;
    while(iswork) {
        int seatsNumber = inputInt("количество мест всего (макс. 100 мест).");
        if (isSeatsNumberCorrect(seatsNumber)) {
            iswork = false;
            return seatsNumber;
        } else {
            iswork = true;
        }
    }
    return -1;
}
int Flight::inputSeatsFree() {
    bool iswork = true;
    while(iswork) {
        int seatsFree = inputInt("количество свободных мест (макс. 100 мест).");
        if (isSeatsFreeCorrect(seatsFree)) {
            iswork = false;
            return seatsFree;
        } else {
            iswork = true;
        }
    }
    return -1;
}

bool Flight::registerPassenger(string passNum, string name) {
    shortPassenger man(passNum, name);
    if (seatsFree == 0) {
        cout << "[Ошибка] Нельзя зарегистрироваться, все места заняты.\n";
        return false;
    } else {
        passengers.push_back(man);
        seatsFree--;
        cout << "Пассажир добавлен в данные рейса.\n";
        return true;
    }
}

bool Flight::canRegisterPassenger(string passNum) {
    if (seatsFree == 0) {
        cout << "[Ошибка] Нельзя зарегистрироваться, все места заняты.\n";
        return false;
    } else {
        for (int i = 0; i < passengers.size(); i++) {
            if (passengers[i].passNum == passNum) {
                cout << "[Ошибка] Пассажир уже зарегистрирован на этот рейс." << endl;
                return false;
            }
        }
        return true;
    }
}

bool Flight::canReturnPassenger(string passNum) {
    if (seatsFree == seatsNumber) {
        cout << "[Ошибка] Нельзя вернуть билет, все места свободны.\n";
        return false;
    } else {
        for (int i = 0; i < passengers.size(); i++) {
            if (passengers[i].passNum == passNum) {
                return true;
            }
        }
        cout << "[Ошибка] Пассажир не зарегистрирован на этот рейс." << endl;
        return true;
    }
}

bool Flight::deletePassenger(string passNum, string name) {
    shortPassenger man(passNum, name);
    for (int i = 0; i < passengers.size(); i++) {
        if (passengers[i].passNum == man.passNum) {
            passengers.erase(passengers.begin() + i);
            seatsFree++;
            cout << "Из данных рейса № " << fligthNumber <<  " удален пассажир c паспортом № " << passNum << "\n";
            return true;
        }
    }
    cout << "[Ошибка] Такой пассажир не регистрировался на рейс.\n";
    return false;
}

void Flight::showPassengers() {
    if (passengers.size() == 0) {
        cout << setw(10) << " " << "На рейс никто не зарегистрировался.\n";
    } else {
        for (int i = 0; i < passengers.size(); i++) {
            cout << setw(10) << " ";
            cout << left << setw(3) << i + 1;
            cout << "  Номер паспорта       : " << passengers[i].passNum << endl;
            cout << setw(15) << " " << "ФИО                  : " << passengers[i].name << endl << endl;
        }
    }
}
