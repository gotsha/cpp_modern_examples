// =====================================================================================
// Erase Remove Idiom
// =====================================================================================

#include <iostream>
#include <algorithm>
#include <vector>

namespace EraseRemoveIdiom
{
    auto print = [](const std::vector<int>& v) {
        std::cout << "Length:   " << v.size() << std::endl;
        std::cout << "Capacity: " << v.capacity() << std::endl;
        std::for_each(std::begin(v), std::end(v), [](const auto& e) {
            std::cout << e << ' ';
            }
        );
        std::cout << std::endl << std::endl;
    };

    void test_01()
    {
        std::vector<int> v = { 0, 1, 2, 5, 4, 5, 6, 5, 8, 9 };
        print(v);

        // remove all '5' elements
        auto it = std::remove(v.begin(), v.end(), 5);
        std::cout << "Position of iterator: " << std::distance(v.begin(), it) << std::endl;
        print(v);

        // erase the unspecified values and reduce the physical size
        // of the container to match its new logical size
        v.erase(it, v.end());
        print(v);
    }

    void test_02()
    {
        std::vector<int> v = { 0, 1, 2, 5, 4, 5, 6, 5, 8, 9 };
        print(v);

        // remove all elements with the value 5
        v.erase(std::remove(v.begin(), v.end(), 5), v.end());
        print(v);

        // request the container to reduce its capacity to fit its size
        v.shrink_to_fit();
        print(v);
    }
}

void main_erase_remove_idiom()
{
    using namespace EraseRemoveIdiom;
    test_01();
    // test_02();
}

// =====================================================================================
// End-of-File
// =====================================================================================
