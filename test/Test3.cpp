// Copyright(c) 2021-present, Mohammad Ewais & contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <iostream>

#include "UniqueIntervalTree/Tree.hpp"

int main(int argc, char** argv)
{
    std::cout << "test started\n";
    UIT::Tree<uint64_t, uint64_t> map;
    uint64_t value = 1;

    map.Insert(210, 220, value);
    map.Insert(140, 150, value);
    map.Insert(130, 140, value);
    map.Insert(250, 260, value);
    map.Insert(270, 280, value);
    map.Insert(0, 10, value);
    map.Insert(50, 60, value);
    map.Insert(160, 170, value);
    map.Insert(280, 290, value);
    map.Insert(100, 110, value);
    map.Insert(120, 130, value);
    map.Insert(30, 40, value);
    map.Insert(240, 250, value);
    map.Insert(220, 230, value);
    map.Insert(40, 50, value);
    map.Insert(290, 300, value);
    map.Insert(20, 30, value);
    map.Insert(150, 160, value);
    map.Insert(80, 90, value);
    map.Insert(60, 70, value);
    map.Insert(10, 20, value);
    map.Insert(200, 210, value);
    map.Insert(230, 240, value);
    map.Insert(180, 190, value);
    map.Insert(90, 100, value);
    map.Insert(110, 120, value);
    map.Insert(260, 270, value);
    map.Insert(190, 200, value);
    map.Insert(70, 80, value);
    map.Insert(170, 180, value);

    std::cout << "Post-insertion:\n";
    std::cout << map.ToString(true) << "\n";

    // Use the iterators to compare
    for (auto it = map.begin(); it != map.end(); ++it)
    {
        std::cout << "it: " << it->range_start << ", " << it->range_end << ": " << it->range_value << "\n";
    }

    for (auto it = map.rbegin(); it != map.rend(); ++it)
    {
        std::cout << "it: " << it->range_start << ", " << it->range_end << ": " << it->range_value << "\n";
    }

    return 0;
}