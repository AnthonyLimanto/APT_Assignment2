
#include "Tile.h"
#include <cstring>

Tile::Tile(Letter letter, Value value)
{
    this->letter = letter;
    this->value = value;
}

Tile::Tile(Letter letter){
    this->letter = letter;

    if (strchr("AEIOULNSTR", letter) != NULL) {
        this->value = 1;
    }
    if (strchr("DG", letter) != NULL) {
        this->value = 2;
    }
    if (strchr("BCMP", letter) != NULL) {
        this->value = 3;
    }
    if (strchr("FHVWY", letter) != NULL) {
        this->value = 4;
    }
    if (strchr("K", letter) != NULL) {
        this->value = 5;
    }
    if (strchr("JX", letter) != NULL) {
        this->value = 8;
    }
    if (strchr("QZ", letter) != NULL) {
        this->value = 10;
    }
}
Tile::Tile(Tile &other)
{
    this->letter = other.letter;
    this->value = other.value;
}
Tile::~Tile()
{
}
Letter Tile::getLetter()
{
    return letter;
}
Value Tile::getValue()
{
    return value;
}
