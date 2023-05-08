#include <iostream>
#include <map>
#include "custom_map.h"


int main() {

    CustomMap<int, char> m;

    m.insert(8, 'a');
    m.insert(5, 'b');
    m.insert(7, 'c');
    m.insert(9, 'd');

    m.print();

    auto exists = m.contains(1);
    auto val = m.find(9);
    std::cout << (exists ? "true" : "false") << '\n';
    std::cout << (char)(val != nullptr ? *val : -1) << '\n';

    m.print();

    return 0;
}
