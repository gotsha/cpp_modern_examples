# Variadische Templates: Mixins

## Einleitung

Parameter Packs k�nnen auch bei der Vererbung eingesetzt werden,
um die Menge der Basisklassen zu definieren,
von denen eine Unterklasse abgeleitet werden soll. Neben dem Begriff *Mixin*
spricht man hier auch von der so genannten *variadischen Vererbung* (*"Variadic" Inheritance*).

## Mixins

Wir betrachten das Ganze am besten an einem Beispiel:

```cpp
// need some classes with default constructors
class A { public: A() = default; };
class B { public: B() = default; };
class C { public: C() = default; };

template <typename ... TS>
class X : public TS...
{
public:
    X(const TS&... mixins) : TS(mixins)... {}
};

void main() {
    A a;
    B b;
    C c;
    X<A, B> xAB(a, b);
    // X<B, A> xBA;   // Error, needs arguments
    X<C> xC(c);
    X<> xNoBases;
}
```

Das Parameter Pack `TS` wird so erweitert, dass jeder darin enthaltene Typ zu einer Basisklasse von `X` wird.
Beachte jedoch, dass die Reihenfolge, in der sie angegeben werden, von Bedeutung ist,
da das �ndern der Reihenfolge zu einem anderen Typ f�hrt - wie unterschiedlich dieser auch sein mag.

---

*Hinweis*:

Bei Mehrfachvererbung gilt:
"Die Reihenfolge der Ableitung ist relevant, um die Reihenfolge der Standardinitialisierung
durch Konstruktoren und der Bereinigung durch Destruktoren zu bestimmen".

---

Aus diesem Grund ist die hier vorgestellte Technik eine ziemlich fragile Methode
zum Spezifizieren von Basisklassen. Sie kann jedoch n�tzlich sein,
wenn sie als Teil einer Template-Implementierung verwendet wird,
die derlei Abh�ngigkeiten ausschlie�en kann.

Betrachen wir den Konstruktor der Klasse X noch einmal detaillierter.
Es sind **zwei** Parameter Pack Expansionen vorhanden:

```cpp
X(const TS&... mixins) : TS(mixins)... {}
```

Das Muster wird f�r jedes Argument im Parameter Pack einmal instanziiert, also:
Bei beiden oben genannten Erweiterungen wird `TS` durch jeden Typ aus dem Parameterpaket ersetzt,
und `mixins` fungiert als Platzhalter f�r den jeweiligen Parameternamen.

*Beispiel*:

Der Konstruktor einer Klasse

```cpp
X<A,B,C>
```

wird effektiv erweitert zu


```cpp
X(const A& a, const B& b, const C& c) : A(a), B(b), C(c) {}
```

Wir k�nnen uns davon auch mit dem Tool *CppInsight.io* �berzeugen:

```cpp
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class X<A, B, C> : public A, public B, public C
{
    public: 
    inline X(const A & __mixins0, const B & __mixins1, const C & __mixins2) :
        A(__mixins0) , B(__mixins1), C(__mixins2) {}
};
#endif
```

Wir k�nnen also in C++ eine Klasse erstellen, die von einer beliebigen Anzahl von Basisklassen erbt.
Eine **class C: public T...** wird folglich in eine Klasse `C` wie folgt "transformiert": **class C: public A, public B**.

## Eine Anwendung zu Mixins

Als Beispiel betrachten wir eine *Repository*-Klasse im Sinne eines Assoziativ-Speichers. 
Das Repository-Objekt soll �ber ein oder mehrere so genannte so genannte *Slots* verf�gen,
auf die mit einem Schl�ssel (*Key*) zugegriffen werden kann. Ferner enth�lt ein Slot einen Wert.

Die genaue Intention im Aussehen eines `Repository`-Objekts entnehmen Sie bitte Abbildung 1:

<img src="cpp_snippets_mixins_01.png" width="500">

Abbildung 1: `Repository`-Klasse mit Schl�ssel-Wert-Paaren, die via Vererbung verf�gbar gemacht werden.

Wir stellen im Folgenden zwei Implementierungen gegen�ber:

  * klassischer Ansatz
  * Ansatz mit Mixins

#### Klassischer Realisierung

###### Realisierung:

```cpp
class SlotA
{
public:
    int value;
};

class SlotB
{
public:
    std::string value;
};

// Note: private inheritance, no one can access
// the slots other than Repository itself
class Repository : private SlotA, private SlotB
{
public:
    void setSlotA(const int& value)
    {
        // Access the base-class's value: since we have multiple bases
        // with a 'value' field, we need to "force" the access to SlotA.
        SlotA::value = value;
    }

    int getSlotA() 
    {
        return SlotA::value;
    }

    void setSlotB(const std::string& b)
    {
        SlotB::value = b;
    }

    std::string getSlotB()
    {
        return SlotB::value;
    }
};
```

###### Testrahmen:

```cpp
void main() {
    Repository repo;

    repo.setSlotA(123);
    std::cout << repo.getSlotA() << std::endl; // printing 123

    repo.setSlotB(std::string("ABC"));
    std::cout << repo.getSlotB() << std::endl; // printing "ABC"
}
```

Man kann unschwer die Nachteile dieser Realisierung erkennen: F�r jeden Slot muss man eine eigene Slot-Klasse
definieren. Und zum zweiten muss man f�r jeden dieser Slots eine separate *getter*- und *setter*-Methode implementieren. 
Die kann man nur als "Copy-Paste"-Programmierung bezeichnen, es muss andere L�sungswege geben.

#### Ansatz mit Mixins

###### Realisierung:

```cpp
template <typename T>
class Slot
{
protected:
    T& get()
    {
        return m_value;
    }

    void set(const T& value) // Same encapsulation.
    {
        m_value = value;
    }

private:
    T m_value;
};

template <typename... Slots>
class RepositoryEx : private Slots...  // inherit private from our slots...
{
public:
    template <typename T> // select type
    T& get()
    {
        return Slot<T>::get(); // select base class
    }

    template <typename T>
    void set(const T& value)
    {
        Slot<T>::set(value);
    }
};
```

###### Testrahmen:

```cpp
using MyRepo = RepositoryEx< Slot<int>, Slot<std::string> >;

void test_04() {
    MyRepo repo;

    repo.set<std::string>("XYZ");
    repo.set(987); // note type deduction: we pass an int, so it writes to the int slot

    std::cout << repo.get<int>() << std::endl; // printing 987
    std::cout << repo.get<std::string>() << std::endl; // printing "XYZ"
}
```

Dieser zweite Ansatz in der Implementierung einer Klasse `RepositoryEx` nimmt Gestalt an, aber wir sind noch nicht fertig!
Wenn Sie versuchen, zwei `int`-Slots anzulegen, wird ein Kompilierungsfehler ausgegeben:
"*Basisklasse 'Slot' wurde mehrmals als direkte Basisklasse angegeben*".

#### Verbesserung des Mixins-Ansatzes

Wir m�ssen unsere `Slot`-Klasse um einen zus�tzlichen Template Parameter erweiteren (Typ f�r Schl�ssel mit Standardwert).
In Abbildung 2 k�nnen wir die Modifikationen erkennen. Wollen wir zwei Slot-Eintr�ge
desselben Typs haben (siehe Typ `std::string` in Abbildung 2), dann sind diese beiden
Eintr�ge durch eine zus�tzlichen Schl�sseltyp zu unterscheiden.

<img src="cpp_snippets_mixins_02.png" width="600">

Abbildung 2: Modifikationen am Konzept der Klasse `Slot`.

Dies zieht allerdings eine �nderung der Repository-Methoden nach sich:

###### Realisierung:

```cpp
struct DefaultSlotKey; // forward definition sufficient

template <typename T, typename Key = DefaultSlotKey>
class SlotEx
{
protected:
    T& get()
    {
        return m_value;
    }

    void set(const T& value)
    {
        m_value = value;
    }

private:
    T m_value;
};

template <typename... Slots>
class RepositoryExEx : private Slots...  // inherit private from our slots...
{
public:
    template <typename T, typename Key = DefaultSlotKey>
    T& get()
    {
        return SlotEx<T, Key>::get(); // select base class
    }

    template <typename T, typename Key = DefaultSlotKey>
    void set(const T& value)
    {
        SlotEx<T, Key>::set(value);
    }
};
```

###### Testrahmen:

```cpp
// again forward definition sufficient, definition not needed
struct Key1;
struct Key2;

// repository definition with keys
using MyRepoEx = RepositoryExEx
    <
    SlotEx<int>,
    SlotEx<std::string, Key1>,
    SlotEx<std::string, Key2>
    >;

void test_06() {
    MyRepoEx repo;

    repo.set(12345); // note type deduction: we pass an int, so it writes to the int slot
    repo.set<std::string, Key1>("AAA");
    repo.set<std::string, Key2>("BBB");

    std::cout << repo.get<int>() << std::endl; // printing 12345
    std::cout << repo.get<std::string, Key1>() << std::endl; // printing "AAA"
    std::cout << repo.get<std::string, Key2>() << std::endl; // printing "BBB"
}
```

#### Realisierung einer `emplace`-Methode


#### Fehlerbehandlung mit static_assert


## Literaturhinweise:

Die Anregungen zu den Beispielen auf diesem Abschnitt sind entnommen aus

[Practical uses for variadic templates](https://crascit.com/2015/03/21/practical-uses-for-variadic-templates/)<br>(abgerufen am 12.05.2020).

und

[Jean Guegant' Blog](https://jguegant.github.io/blogs/tech/thread-safe-multi-type-map.html)<br>(abgerufen am 12.05.2020).
