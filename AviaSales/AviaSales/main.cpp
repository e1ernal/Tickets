#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "HashTable.hpp"
#include "Flight.hpp"
#include "AVLTree.hpp"
#include "SkipList.hpp"

using namespace std;

void menu() {
    printf("=============================================================\n");
    printf("[+]  1 - РЕГИСТРАЦИЯ нового пассажира                       ]\n");
    printf("[+]  2 - УДАЛЕНИЕ данных о пассажире                        ]\n");
    printf("[+]  3 - ПРОСМОТР всех зарегистрированных пассажиров        ]\n");
    printf("[+]  4 - ОЧИСТКА данных о пассажирах                        ]\n");
    printf("[+]  5 - ПОИСК пассажира по номеру паспорта                 ]\n");
    printf("[+]  6 - ПОИСК пассажира по ФИО                             ]\n");
    printf("[-----------------------------------------------------------]\n");
    printf("[+]  7 - ДОБАВЛЕНИЕ нового авиарейса                        ]\n");
    printf("[+]  8 - УДАЛЕНИЕ сведений об авиарейсе                     ]\n");
    printf("[+]  9 - ПРОСМОТР всех авиарейсов                           ]\n");
    printf("[+] 10 - ОЧИСТКА данных об авиарейсах                       ]\n");
    printf("[+] 11 - ПОИСК авиарейса по его номеру                      ]\n");
    printf("[+] 12 - ПОИСК авиарейса по названию аэропорта прибытия     ]\n");
    printf("[-----------------------------------------------------------]\n");
    printf("[+] 13 - РЕГИСТРАЦИЯ продажи пассажиру авиабилета           ]\n");
    printf("[+] 14 - ВОЗВРАТ пассажиром авиабилета                      ]\n");
    printf("[-----------------------------------------------------------]\n");
    printf("[+] 15 - МЕНЮ                                               ]\n");
    printf("[+] 16 - ЗАВЕРШЕНИЕ работы программы                        ]\n");
    printf("=============================================================\n");
}

void printInput() { printf("\n-> Введите команду: "); }

//Структуры данных
HashTable passengers(5);
AVLTree flights;
AVLNode* root = NULL;
SkipList tickets(3, 0.5);

//Поиск билета по номеру рейса и номеру паспорта
Ticket findTicket(string passNumber, string flightNumber) {
    Ticket ticket;
    auto header = tickets.header;
    Node *node = header->forward[0];
    bool ticketFound = false;
    while (node != NULL) {
        if (node->value.fligthNumber == flightNumber &&
            node->value.passNumber == passNumber) {
            ticketFound = true;
            ticket = node->value;
            break;
        }
        node = node->forward[0];
    }
    if (ticketFound == false) {
        cout << "[Ошибка] Билет для удаления c " << endl
        << "номером паспорта: " << passengers.LookupByPassNum(passNumber).getPassportNumber() << endl
        << " номером рейса: " << flightNumber << endl
        << "не найден.\n";
    }
    return ticket;
}

//Удаление билета по номеру рейса и номеру паспорта
void deleteTicket(string passNumber, string flightNumber) {
    //Поиск билета по номеру рейса и номеру паспорта
    auto ticket = findTicket(passNumber, flightNumber);
    if (!ticket.isEmpty()) {
        //Удаление билета с номером рейса и номером паспорта пассажира
        tickets.deleteElement(ticket.getTiketNumberInt(), ticket);
    }
}

//Удаление пассажира, пассажира из рейса, билета
void deletePassenger(Passenger man) {
    string passNumber = man.getPassportNumber();
    auto manFlights = man.getFlights();
    //Удаление пассажира из рейсов и удаление билетов
    for (auto flightNumber : manFlights) {
        //Удаление пассажира из рейса
        flights.findByNumber(root, flightNumber)->value.deletePassenger(passNumber, man.getName());
        //Удаление билета
        deleteTicket(passNumber, flightNumber);
        
    }
    //Удаление пассажира
    passengers.Delete(passNumber);
}

//Удаление самого рейса и его данных отовсюду
void deleteFlight(string flightNumber) {
    auto flight = flights.findByNumber(root, flightNumber);
    if (flight != NULL) {
        //Запрос пассажиров рейса
        auto shortPassengers = flight->value.getPassengers();
        for (auto shortMan : shortPassengers) {
            //Удаление рейса из каждого пассажира
            passengers.deleteFlightFromPassenger(flightNumber, shortMan.passNum);
            //Удалить билет на рейс
            deleteTicket(shortMan.passNum, flightNumber);
        }
        //Удаление самого рейса
        root = flights.Delete(root, flightNumber);
        cout << "Рейс № " << flightNumber << " удален.\n\n";
    } else cout << "[Ошибка] Нет рейса № " << flightNumber <<".\n";
}


int main() {
    menu();
    bool work = true;
    while (work) {
        printInput();
        int input = 0;
        cin >> input;
        if (!cin.fail()) {
            cout << endl;
            switch (input) {
                case 1:
                {
                    Passenger man;
                    man.passengerInit();
                    passengers.Insert(man.getPassportNumber(), man);
                }
                    break;
                case 2:
                {
                    Passenger man;
                    string passNumber = man.inputPassportNumber();
                    man = passengers.LookupByPassNum(passNumber);
                    deletePassenger(man);
                }
                    break;
                case 3:
                    passengers.Output();
                    break;
                case 4:
                {
                    auto passengersArray = passengers.getPassengers();
                    for (auto man : passengersArray) {
                        deletePassenger(man);
                    }
                    passengers.Clear();
                }
                    break;
                case 5:
                {
                    Passenger man;
                    man = passengers.LookupByPassNum(man.inputPassportNumber());
                    if (man.isEmpty()) cout << "[Ошибка] Пассажир не найден.\n";
                    else man.outputPassenger();
                }
                    break;
                case 6:
                {
                    Passenger man;
                    man = passengers.LookupByName(man.inputName());
                    if (man.isEmpty()) cout << "[Ошибка] Пассажир не найден.\n";
                    else man.outputPassenger();
                }
                    break;
                case 7:
                {
                    Flight flight;
                    flight.fligtInput();
                    if (flights.findByNumber(root, flight.getFlightNumber()) == NULL) {
                        root = flights.Insert(root, flight.getFlightNumber(), flight);
                    } else cout << "[Ошибка] Номер рейса совпадает.\n";
                }
                    break;
                case 8:
                {
                    Flight flight_;
                    string flightNumber = flight_.inputFlightNumber();
                    deleteFlight(flightNumber);
                }
                    break;
                case 9:
                    if (root == NULL) cout << "[Ошибка] Нет информации о рейсах.\n";
                    else root->outputNode(root);
                    break;
                case 10:
                    
                    while (root != NULL) {
                        deleteFlight(root->value.getFlightNumber());
                    }
                    cout << "Информация о рейсах удалена.\n";
                    break;
                case 11:
                {
                    Flight flight;
                    AVLNode* x;
                    x = flights.findByNumber(root, flight.inputFlightNumber());
                    if (x == NULL) cout << "[Ошибка] Не найдено.\n";
                    else {
                        cout << "Рейс найден.\n";
                        x->value.flightOutput();
                    }
                }
                    break;
                case 12:
                {
                    Flight flight;
                    vector<AVLNode*> v;
                    flights.findByArrivalAirport(root, flight.inputArrivalAirport(), v);
                    if (v.size() == 0) cout << "[Ошибка] Не найдено.\n";
                    else {
                        cout << "Найдено рейсов: " << v.size() << endl << endl;
                        for (auto f : v) {
                            f->value.flightOutput();
                            cout << endl;
                        }
                    }
                }
                    break;
                case 13:
                {
                    cout << "Формат: <номер паспорта> <номер авиарейса>\n";
                    Passenger man;
                    string passNumber = man.inputPassportNumber();
                    //проверка на существование такого номера паспорта пассажира
                    if (passengers.LookupByPassNum(passNumber).isEmpty()) {
                        cout << "[Ошибка] Такого пассажира нет.\n";
                        break;
                    }
                    man = passengers.LookupByPassNum(passNumber);
                    
                    Flight flight_;
                    string flightNumber = flight_.inputFlightNumber();
                    //проверка на существование такого номера рейса
                    if (flights.findByNumber(root, flightNumber) == NULL) {
                        cout << "[Ошибка] Такого рейса нет.\n";
                        break;
                    }
                    auto flight = flights.findByNumber(root, flightNumber);
                    
                    Ticket ticket;
                    //Генерация уникального номера билета
                    string ticketNumber = ticket.generateTicket();
                    bool work = true;
                    while (work) {
                        if (tickets.contains(ticket.getTiketNumberInt())) {
                            ticketNumber = ticket.generateTicket();
                        } else work = false;
                    }
                    
                    ticket = Ticket(passNumber, flightNumber, ticketNumber);
                   
                    cout << "Билет на рейс сформирован:\n";
                    ticket.outputTicket();
            
                    bool f1 = !man.containsFlight(flightNumber);
                    bool f2 = flight->value.canRegisterPassenger(passNumber);
                    //Проверка на возможность зарегистрировать на рейс
                    if (f1 && f2) {
                        passengers.addFlightToPassenger(flightNumber, passNumber);
                        flight->value.registerPassenger(passNumber, man.getName());
                        tickets.insertElement(ticket.getTiketNumberInt(), ticket);
                    }
                }
                    break;
                case 14:
                {
                    cout << "Формат: <номер паспорта> <номер авиарейса>\n";
                    Passenger man;
                    string passNumber = man.inputPassportNumber();
                    //проверка на существование такого номера паспорта пассажира
                    if (passengers.LookupByPassNum(passNumber).isEmpty()) {
                        cout << "[Ошибка] Такого пассажира нет.\n";
                        break;
                    }
                    man = passengers.LookupByPassNum(passNumber);
                    
                    Flight flight_;
                    string flightNumber = flight_.inputFlightNumber();
                    //проверка на существование такого номера рейса
                    if (flights.findByNumber(root, flightNumber) == NULL) {
                        cout << "[Ошибка] Такого рейса нет.\n";
                        break;
                    }
                    auto flight = flights.findByNumber(root, flightNumber);
                    
                    //Поиск билета по номеру рейса и номеру паспорта
                    Ticket ticket = findTicket(passNumber, flightNumber);
                    if (!ticket.isEmpty()) {
                        cout << "Билет для возврата найден:\n";
                        ticket.outputTicket();
                    } else break;
                    
                    bool f1 = man.containsFlight(flightNumber);
                    bool f2 = flight->value.canReturnPassenger(passNumber);
                    //Проверка на возможность сдать билет
                    if (f1 && f2) {
                        passengers.deleteFlightFromPassenger(flightNumber, passNumber);
                        flight->value.deletePassenger(passNumber, man.getName());
                        tickets.deleteElement(ticket.getTiketNumberInt(), ticket);
                    }
                }
                    break;
                case 15:
                    menu();
                    break;
                case 16:
                    return 0;
                default:
                    cout << "[Ошибка] Введенное значение не пункт меню.\n";
            }
        } else {
            cout << "[Ошибка] Введено не целочисленное значение.\n";
        }
        cin.clear();
        fflush(stdin);
    }
    return 0;
}

