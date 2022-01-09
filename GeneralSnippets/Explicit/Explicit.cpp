// =====================================================================================
// explicit
// =====================================================================================

#include <iostream>

namespace KeywordExplicit {

    class String {
    public:
        /* explicit */ String(int n); // allocate String object with n bytes length
        String(char* p); // initialize String object with char pointer
    };

    String::String([[ maybe_unused]] int n) {}
    String::String([[ maybe_unused]] char* p) {}

    void test_01() {

        // char 'x' will be implicitly converted to int
        // and the String(int) constructor will be called:
        // Did you intend this?

        [[maybe_unused]] String s1 = 'x';
        [[maybe_unused]] String s2 (10);
    }
}

void main_keyword_explicit()
{
    using namespace KeywordExplicit;
    test_01();
}

// =====================================================================================
// End-of-File
// =====================================================================================
