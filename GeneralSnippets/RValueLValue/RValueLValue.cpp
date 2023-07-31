// =====================================================================================
// LValue / RValue
// =====================================================================================

module modern_cpp:rvalue_lvalue;

namespace LValueRValue {

    // schlechteste Möglichkeit für sayHello Funktion: Übergeben einer Kopie
    /*void sayHello(std::string message) {
        std::cout << "sayHello [std::string&]:  " << message << std::endl;
    }*/

    // was noch möglich wäre
    /*void sayHello(const std::string& message) {
        ...
    }*/

    // lvalue reference
    void sayHello(std::string& message) {
        std::cout << "sayHello [std::string&]:  " << message << std::endl;
    }

    // rvalue reference
    void sayHello(std::string&& message) {
        std::cout << "sayHello [std::string&&]: " << message << std::endl;
    }

    void test01() {

        std::string a = "Hello";
        std::string b = " World";

        sayHello(a);
        sayHello("ABC"); //"ABC" wird intern als temp. Objekt angelegt -> Anonymes Objekt -> sayHello(std::string&& message)
        sayHello(a + b); //Konkatenation -> temp. Objekt
    }

    // -------------------------------------------------------------------

    void helper(std::string&& message) {

        sayHello(message); // i)  RValue: string&& ==> sayHello (&&)
                           // ii) message ist ein Name (Bezeichner): ==> sayHello (&)
                           // richtiges Ergebnis: ii)
                           // wenn ich aber, weil mein message temporär ist, auch die temporäre Fkt mit rvalue Ref aufrufen möchte muss ich sayHello(std::move(message)) nutzen
        // sayHello(std::move(message));    // casting an lvalue to an rvalue
    }

    void test02() {

        helper(std::string("Where are we going :)"));
    }

    // -------------------------------------------------------------------

    void test03() {

        std::string a = "Hello";

        // put first 'sayHello' overload into comment: won't  compile
        // "cannot convert argument 1 from 'std::string' to 'std::string &&'" -
        // "an rvalue reference cannot be bound to an lvalue"

        // sayHello(a);

        // but:
        sayHello(std::move(a));  // casts an lvalue to an rvalue
    }

    // -------------------------------------------------------------------

    void test04() {

        //int& i = 2;       // invalid: reference to a constant

        //int a = 2;
        //int b = 3;

        //int& k = a + b;     // invalid: reference to a temporary

        int&& i = 2;     // works: reference to a constant

        int a = 2;
        int b = 3;

        int&& k = a + b;     // works: reference to a temporary
    }
}

void main_rvalue_lvalue()
{
    using namespace LValueRValue;
    std::cout << "test01" << std::endl;
    test01();
    std::cout << "test02" << std::endl;
    test02();
    std::cout << "test03" << std::endl;
    test03();
    std::cout << "test04" << std::endl;
    test04();
    
}

// =====================================================================================
// End-of-File
// =====================================================================================

