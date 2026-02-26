#include "decimal.h"
#include "bitstring.h"


int main () {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    Array one(5);
    cout << "-------------------------------------------------" << endl;
    Decimal two(5, true);
    cout << "-------------------------------------------------" << endl;
    BitString three(5);

    return 0;
}