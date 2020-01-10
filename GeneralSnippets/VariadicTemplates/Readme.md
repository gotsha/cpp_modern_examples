# Variadische Templates und Fold-Ausdr�cke

Variadische Templates bestehen aus zwei Template-�berladungen:

  * Einem *normalen* Template
  * Einem *rekursiven* Template, das neben einem normalen Parameter ein so genannten *Parameter Pack* besitzt (Notation mit "..."). 
    Diese drei Punkte k�nnen sowohl links vom Argument (Parameter-Deklaration) als auch rechts stehen (Entpacken des Parameter Packs).

Ab C++ 17 kann man die zwei Templates eines variadischen Templates auch auf eines reduzieren. 
Dies erfolgt mit Hilfe eines sogenannten "*Fold-Ausdrucks*".

Der Addierer und ein einfacher Printer demonstrieren in den Code-Snippets *fold expressions*.

Ausgabe der Code-Snippets zu variadische Templates:

```cpp
Sum from 1 up to 10: 55
String Concatenation: ABCDEFGHIJKLMNO

Value: char
Value: short
Value: int
Value: long
Value: float
Value: double
Value: const char*
Value: bool

double - value: 3.1415
short - value: 123
int - value: 123
long - value: 123
float - value: 3.14
double - value: 3.14
char - value: A
const char* - value: ABC
bool - value: 0
```

Ausgabe der Code-Snippets zu *fold expressions*:

```cpp
123ABCDEFGHI
1 2 3 ABC DEF GHI
Sum from 1 up to 10: 55
```
