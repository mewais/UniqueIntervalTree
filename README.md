[![FreePalestine.Dev](https://freepalestine.dev/header/1)](https://freepalestine.dev)

# Unique Interval Tree

## Background
An interval tree is a special type of tree structure that is used to find any numeric intervals overlapping with another. Interval trees are usually built using any type of binary search tree.

## Implementation
This is a C++11 implementation for a special type of an interval tree. Specifically, interval trees usually allow overlapping ranges or intervals to exist within the tree, but this implementation does not, hence the name `UniqueIntervalTree`.  
This is a header only implementation, based on a red black tree. The implementation is templated and can work with any type of key and value provided the following:
1. The key type adheres to the following restrictions:
   1. Must be comparable (i.e. must support/override the `==` and `!=` operators)
   2. Must be totally ordered (i.e. must support/override the `<`, `<=`, `>`, and `>=` operators)
   3. Must be printable (i.e. must support the `<<` stream operator)
2. The value type adheres to at least ONE OF the following restrictions:
   1. Be default constructible
   2. Be move constructible
   3. Be copy constructible

## Usage
Add `#include "UniqueIntervalTree/Tree.hpp"` in your source file. Then use any of the API functions in the following example:
```cpp
UIT::Tree<KeyType, ValueType> tree;
// Insertion and Deletion
tree.Insert(range_start, range_end, value);
tree.Insert(range_start, range_end);
tree.Delete(range_start, range_end);
// Checking
bool ret = tree.Has(point);
bool ret = tree.Has(range_start, range_end);
// Accessing
ValueType ret = tree.Access(point);
ValueType ret = tree.Access(range_start, range_end);
ValueType ret = tree.Access(point, &including_range_start, &including_range_end);
ValueType ret = tree.Access(range_start, range_end, &including_range_start, &including_range_end);
bool ret = tree.Access(point, *return_value);
bool ret = tree.Access(range_start, range_end, *return_value);
bool ret = tree.Access(point, &including_range_start, &including_range_end, *return_value);
bool ret = tree.Access(range_start, range_end, &including_range_start, &including_range_end, *return_value);
// Modification
tree.GrowStart(range_start, range_end, new_range_start);
tree.GrowEnd(range_start, range_end, new_range_end);
tree.ShrinkStart(range_start, range_end, new_range_start);
tree.ShrinkEnd(range_start, range_end, new_range_end);
// Printing
std::string str = tree.ToString();
```

## Current State
The library is tested and working. It is currently being used as part of the [DCSim simulator](https://github.com/DCArch/DCSim). If you encounter any bugs, please open an issue, or submit a pull request.

## Author
[Mohammad Ewais](https://mohammad.ewais.ca)

## License
This library is licensed under the CC-BY-NC-SA 4.0 License - see the [LICENSE](LICENSE) file for details.
