// Copyright(c) 2021-present, Mohammad Ewais & contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <iostream>

#include "UniqueIntervalTree/Tree.hpp"

int main(int argc, char** argv)
{
    std::cout << "test started\n";
    UIT::Tree<uint64_t, uint64_t> map;
    uint64_t value = 1;
    map.Insert(0x00007FFFF3F3C040, 0x00007FFFF3F3C278, value);
    value = 2;
    map.Insert(0x00007FFFF3F3C000, 0x00007FFFF3F3C010, value);
    value = 3;
    map.Insert(0x00007FFFF3F3A000, 0x00007FFFF3F3A08F, value);
    value = 4;
    map.Insert(0x00007FFFFFF88000, 0x00007FFFFFFFF000, value);
    value = 5;
    map.Insert(0x00007FFFF7FF8080, 0x00007FFFF7FF8218, value);
    value = 6;
    map.Insert(0x00007FFFF7FF7040, 0x00007FFFF7FF8078, value);
    value = 7;
    map.Insert(0x00007FFFF7FEB000, 0x00007FFFF7FF0CDB, value);
    value = 8;
    map.Insert(0x00007FFFF7B62620, 0x00007FFFF7B6B208, value);
    value = 9;
    map.Insert(0x00007FFFF7B601A0, 0x00007FFFF7B617C0, value);
    value = 10;
    map.Insert(0x00007FFFF7B11000, 0x00007FFFF7B36228, value);
    value = 11;
    map.Insert(0x00007FFFF7523104, 0x00007FFFF7523110, value);
    value = 12;
    map.Insert(0x00007FFFF75230F8, 0x00007FFFF7523104, value);
    value = 13;
    map.Insert(0x00007FFFF748B000, 0x00007FFFF75160D4, value);

    std::cout << "Post-insertion:\n";
    std::cout << map.ToString() << "\n";

    return 0;
}