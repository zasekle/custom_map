#include <iostream>
#include <map>
#include "custom_map.h"

struct ReadStuff {
    int value = 0;

    ReadStuff() {
        std::cout << "Constructor\n";
    }

    ~ReadStuff() {
        std::cout << "Destructor\n";
    }

    ReadStuff(const ReadStuff& c) {
        std::cout << "Copy\n";
        value = c.value;
    }

    ReadStuff(ReadStuff&& m)  noexcept {
        std::cout << "Move\n";
        value = m.value;
    }

    ReadStuff& operator=(const ReadStuff& c) {
        std::cout << "Operator=\n";
        value = c.value;
        return *this;
    }
};

int main() {

    CustomMap<int, char> m;

    m.insert(8, 'a');
    m.insert(5, 'b');
    m.insert(7, 'c');
    m.insert(9, 'd');

    m.print();
//    std::cout << m.erase(12)->value << '\n';

    return 0;
}
