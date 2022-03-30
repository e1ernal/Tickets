#include "HashNode.hpp"

HashNode::HashNode() {
    key = "";
    value = Passenger();
}

HashNode::HashNode(string _key, Passenger _value) {
    value = _value;
    key = _key;
}

bool HashNode::isEmpty() {
    return (key == "" &&
        value.getPassportNumber() == "" &&
        value.getDateOfBirth() == "" &&
        value.getName() == "" &&
        value.getPlaceAndDate() == "");
}
