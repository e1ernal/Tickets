#include "HashTable.hpp"
#include "HashNode.hpp"

HashNode* HashTable::resize() {
    const int oldSize = maxSize;
    maxSize = maxSize * 12 + 1;
    
    HashNode *temp = new HashNode[oldSize]();
    for (int i = 0; i < oldSize; i++) temp[i] = arr[i];
    
    HashNode x;
    arr = new HashNode[maxSize]();
    for (int i = 0; i < oldSize; i++) {
        if (!temp[i].isEmpty()) {
            arr[i] = temp[i];
        }
        else arr[i] = x;
    }
    return arr;
}

HashTable::~HashTable() {
    delete[]data;
    delete[] arr;
}

unsigned int HashTable::Hash(string key, int M) {
    unsigned int result = 0;
    unsigned int length = key.size();

    for (int i = 0; i < length; i++) {
        int c = (int)((char)key[i]);
        int temp = (int)(c * pow((float)128, (float)(length - i - 1))) % M;
        result += temp;
    }
    result %= M;
    return  result;
}

HashTable::HashTable(int M) {
    arr = new HashNode[M]();
    size = 0;
    maxSize = M;
}

void HashTable::Insert(string key, Passenger value) {
    if (!LookupByPassNum(key).isEmpty()) {
        cout << "[Ошибка] Пассажир с таким номером паспорта уже существует.\n";
        return;
    }
    
    int pos = Hash(key, maxSize);
    int i = 1;
    while (!arr[pos].isEmpty()) {
        pos += i * i;
        pos %= maxSize;
        i++;
    }
    HashNode x(key, value);
    arr[pos] = x;
    ++size;
    cout << "Пассажир добавлен.\n";
    if (size / maxSize >= 0.75) {
        size = 0;
        resize();
    }

}

Passenger HashTable::LookupByPassNum(string key) {
    int pos = Hash(key, maxSize);
    int i = 1;
    while (!arr[pos].isEmpty()) {
        if (arr[pos].key == key) return arr[pos].value;
        pos += i * i;
        pos %= maxSize;
        i++;
    }
    return Passenger();
}

bool HashTable::addFlightToPassenger(string flightNumber, string passNumber) {
    string key = passNumber;
    int pos = Hash(key, maxSize);
    int i = 1;
    while (!arr[pos].isEmpty()) {
        if (arr[pos].key == key) {
            arr[pos].value.addFlight(flightNumber);
            return true;
        }
        pos += i * i;
        pos %= maxSize;
        i++;
    }
    return false;
}

bool HashTable::deleteFlightFromPassenger(string flightNumber, string passNumber) {
    string key = passNumber;
    int pos = Hash(key, maxSize);
    int i = 1;
    while (!arr[pos].isEmpty()) {
        if (arr[pos].key == key) {
            arr[pos].value.deleteFlight(flightNumber);
            return true;
        }
        pos += i * i;
        pos %= maxSize;
        i++;
    }
    cout << "[Ошибка] Удаление рейса из данных пассажира не произведено.\n";
    return false;
}

Passenger HashTable::LookupByName(string name) {
    int pos = 0;
    while (pos < maxSize) {
        if (arr[pos].value.getName() == name) return arr[pos].value;
        pos++;
    }
    return Passenger();
}

void HashTable::Delete(string key) {
    int pos = Hash(key, maxSize);
    int i = 1;
    bool isFound = false;
    while (!arr[pos].isEmpty()) {
        if (arr[pos].key == key) {
            cout << "Пассажир с паспортом № " << arr[pos].value.getPassportNumber() << " удален.\n";
            HashNode x;
            arr[pos] = x;
            isFound = true;
            break;
        }
        pos += i * i;
        pos %= maxSize;
        i++;
    }
    if (isFound) {
        size--;
    }
    else cout << "[Ошибка] Пассажир не найден.\n";
}

void HashTable::Output() {
    if (size == 0) cout << "Таблица пуста.\n";
    else {
        int number = 1;
        for (int i = 0; i < maxSize; i++) {
            if (!arr[i].isEmpty()) {
                arr[i].value.outputPassenger();
                number++;
            }
        }
    }
}

vector<Passenger> HashTable::getPassengers() {
    vector<Passenger> result;
    for (int i = 0; i < maxSize; i++) {
        if (!arr[i].isEmpty()) {
            result.push_back(arr[i].value);
        }
    }
    return result;
}

void HashTable::Clear() {

    int M = 5;
    arr = new HashNode[M]();
    size = 0;
    maxSize = M;
    cout << "Таблица очищена. Приведено к размеру: " << M << endl;
}
