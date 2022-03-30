#include "Ticket.hpp"
#include <cstdlib>

using namespace std;

Ticket::Ticket() {
    string passNumber = "";
    string fligthNumber = "";
    string ticketNumber = "";
}

bool Ticket::isEmpty() {
    return (passNumber == "" &&
            fligthNumber == "" &&
            ticketNumber == "");
}

Ticket::Ticket(string pass, string flight, string ticket) {
    passNumber = pass;
    fligthNumber = flight;
    ticketNumber = ticket;
}
string Ticket::generateTicket() {
    return to_string(100000000 + rand() % 100000000);
}

int Ticket::getTiketNumberInt() {
    if (ticketNumber != "") return atoi(ticketNumber.c_str());
    else return 0;
}

void Ticket::outputTicket() {
    cout << endl;
    cout << setw(10) << "Билет. ";
    cout << setw(3) << " " << "Номер паспорта            : " << passNumber << endl;
    cout << setw(10) << " " << "Номер рейса               : " << fligthNumber << endl;
    cout << setw(10) << " " << "Номер билета              : " << ticketNumber << endl;
    cout << endl;
}
