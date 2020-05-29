# SFINAE and enable_if

[Quellcode 1](Sfinae01.cpp) und [Quellcode 2](Sfinae02.cpp)

---

## Einleitung

Es gibt ein interessantes Problem, das es bei der gleichzeitigen Verwendung von Funktions�berladungen
mit Templates zu ber�cksichtigen gilt. Das Problem besteht darin, dass Templates in ihrem Gebrauch (Instanziierung)
normalerweise zu allgemein gehalten sind.
Wenn Templates mit �berladungen gemischt werden, kann das Ergebnis �berraschend sein:

```cpp
void foo(unsigned i) {
    std::cout << "unsigned " << i << "\n";
}

template <typename T>
void foo(const T& t) {
    std::cout << "template " << t << "\n";
}
```

Welche der beiden Funktionen `foo` wird Ihrer Meinung nach beim Aufruf von `foo(123);` verwendet?
Die Antwort lautet: Es ist die Funktions-Template Variante, die Ausgabe lautet folglich "`template 123`".
Der Grund daf�r ist, dass ganzzahlige Literale (wie zum Beispiel `123`) standardm��ig `signed` sind
(sie werden nur mit dem Suffix `U` vorzeichenlos). Wenn der Compiler die �berladungs-Kandidaten untersucht,
aus denen er f�r diesen Aufruf ausw�hlen kann, stellt er fest, dass die erste Funktion eine Konvertierung ben�tigt,
w�hrend die zweite perfekt �bereinstimmt, so dass diese ausgew�hlt wird.

## Prinzip der Substitution

Wenn der Compiler �berladungs-Kandidaten betrachtet, bei denen es sich um Templates handelt,
muss er tats�chlich die explizit angegebenen oder abgeleiteten Typen in die Template Argumente einsetzen.
Dies f�hrt nicht immer zu sinnvollem Code, wie das folgende Beispiel zeigt.
Es ist zwar einerseits ein nicht so sehr praxisrelevantes Beispiel, daf�r aber repr�sentativ f�r viele generische Quellcodes,
die in Modern C ++ geschrieben werden:

```cpp
int negate(int i) {
    return -i;
}

template <typename T>
typename T::value_type negate(const T& t) {
    return -T(t);
}
```

Wir betrachten einen Aufruf `negate(123)`. Es kommt die erste �berladung zum Tragen, es
wird der Wert -123 zur�ckgegeben. Bei der Suche nach der besten �berladung m�ssen jedoch alle Kandidaten ber�cksichtigt werden.
Wenn der Compiler die Schablone `negate` analysiert, substituiert er den abgeleiteten Argumenttyp 
(*deduced argument type*) des Aufrufs (in diesem Fall `int`) in der Vorlage und erh�lt damit die folgende Deklaration:

```cpp
int::value_type negate(const int& t);
```

Dieser Code ist nat�rlich ung�ltig, da `int` keinen Member des Namens `value_type` hat.
Man k�nnte also die Frage stellen, ob der Compiler in diesem Fall eine Fehlermeldung ausgeben sollte?
Er tut es nicht, denn in diesem Fall w�re das Schreiben von generischem Code in C ++ noch schwieriger.
Tats�chlich enth�lt der C ++ - Standard f�r solche F�lle eine spezielle Klausel,
die genau erkl�rt, wie sich ein Compiler verhalten soll:

## SFINAE

Um es nicht zu formal werden zu lassen: Wenn ein Substitutionsfehler wie der oben gezeigte auftritt, schl�gt die "type deduction" f�r diesen Typ fehl -
was aber nicht einen �bersetzungsfehler nach sich zieht:
Der Compiler ignoriert diesen Kandidaten einfach und sieht sich die anderen M�glichkeiten an.

Im C ++ Sprachjargon bezeichnet man diese Regel als **SFINAE**: "**Substitution Failure Is Not An Error**".

Hierbei gilt es f�r den Programmierer aber Folgendes zu beachten - siehe dazu das n�chste Beispiel:

```cpp
template <typename T>
void negate(const T& t) {
  typename T::value_type n = -t();
}
```

Wenn die "*Type Deduction*" f�r eine bestimmte �berladung einen "Treffer" vermeldet,
wird aufgrund des vorliegenden Ausdrucks `T::value_type` im Rumpf der Funktion tats�chlich ein Kompilierungsfehler angezeigt!
Die Moral von der Geschichte ist: Wenn wir ein Template schreiben wollen, das nur f�r einige Typen sinnvoll ist,
dann m�ssen wir daf�r Sorge tragen, dass der Mechanismus der "*Type Deduction*" bereits in der *Deklaration*
f�r ung�ltige Typen fehlschl�gt, um auf diese Weise einen Substitutionsfehler zu verursachen.
Wenn sich der ung�ltige Typ in die �bersetzungsphase *nach* der Auswahl der �berladungskandidaten schleicht,
also in den eigentlichen Rumpf der �bersetzungseinheit, wird das Programm nicht kompiliert:

```cpp
negate(123);
```

resultiert in einem �bersetzungsfehler der Art *"'T': must be a class or namespace when followed by '::'"** bzw. *"'T': left of '::' must be a class/struct/union"*.
Wie lassen sich derartige �bersetzungsfehler vermeiden?

## `enable_if` - Ein Schalter f�r Templates zur �bersetzungszeit

Der Trick in der Vermeidung derartiger �bersetzungsfehler liegt in der Definition von Templates 
des folgenden Aussehens:

```cpp
template <bool, typename T = void>
struct enable_if
{};

template <typename T>
struct enable_if<true, T> {
    using type = T;
};
```

Damit lassen sich nun Funktionen (genauer gesagt: Funktionsschablonen) in der folgenden Art und Weise definieren:

```cpp
template <typename T, typename enable_if<std::is_integral<T>::value, T>::type* = nullptr>
void doSomething(const T& t) {
    // an implementation for integral types (int, char, unsigned, etc.)
    std::cout << "doSomething integral type: " << t << std::endl;
}

template <typename T, typename enable_if<std::is_class<T>::value, T>::type* = nullptr>
void doSomething(const T& t) {
    // an implementation for class types
    std::cout << "doSomething class type: " << t() << std::endl;
}
```

Lassen Sie uns SFINAE bei der Arbeit betrachten:
Wenn wir den Aufruf `doSomething (<int var>)` absetzen wollen,
w�hlt der Compiler die erste �berladung aus: Da die Bedingung `std::is_integral<int>` mit `true` evaluiert,
wird die Spezialisierung von `struct enable_if` f�r `true` verwendet,
der Strukturmember `type` ist in Folge dessen definiert und der interne Typ (*type deduction*) wird auf `int` gesetzt.
Die zweite �berladung wird weggelassen, da ohne die `true`-Spezialisierung (`std::is_class<int>` ist `false`) 
die allgemeine Form von `struct enable_if` ausgew�hlt wird, diese keinen Member `type` hat, 
sodass der Typ des Arguments zu einem Substitutionsfehler f�hrt:

*Beispiel*:

```cpp
class SomeClass {
public:
    std::string operator()() const {
        return "SomeClass object";
    }
};

void test_04() {
    doSomething(123);
    doSomething(SomeClass{});
}
```

*Ausgabe*:

```cpp
doSomething integral type: 123
doSomething class type: SomeClass object
```

**Beachte**: Die Strukturen `enable_if` sind auch in der C++-Klassenbibliothek definiert (`inlude`-Datei `<type_traits>`),
Sie m�ssen diese also nicht selbst definieren.

Die beiden Templates `doSomething` sind in ihrer Definition etwas schwerf�llig geraten. Mit der zus�tzlichen
Schablone `enable_if_t` kann man diese etwas vereinfachen:

```cpp
template <bool B, typename T = void>
using enable_if_t = typename enable_if<B, T>::type;

template <typename T, typename enable_if_t<std::is_integral<T>::value, T>* = nullptr>
void doSomething2(const T& t) {
    // an implementation for integral types (int, char, unsigned, etc.)
    std::cout << "doSomething integral type: " << t << std::endl;
}

template <typename T, typename enable_if_t<std::is_class<T>::value, T>* = nullptr>
void doSomething2(const T& t) {
    // an implementation for class types
    std::cout << "doSomething class type: " << t() << std::endl;
}
```

## Literaturhinweise:

Die Anregungen zu den Beispielen aus diesem Code-Snippet finden sich unter

[Eli Bendersky's website](https://eli.thegreenplace.net/2014/sfinae-and-enable_if/)<br>(abgerufen am 22.05.2020).

und

[Fernando Garc�a](https://medium.com/@mortificador/choose-between-different-implementations-depending-on-type-properties-at-compile-time-in-c-68e3fd5cd2f8)<br>(abgerufen am 22.05.2020).

Eine weitere Empfehlung:

[Jean Guegant](http://jguegant.github.io/blogs/tech/sfinae-introduction.html)<br>(abgerufen am 29.05.2020).

---

[Zur�ck](../../Readme.md)

---

