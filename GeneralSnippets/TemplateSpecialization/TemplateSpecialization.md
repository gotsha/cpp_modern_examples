# Template Spezialisierung (Template Specialization)

[Zur�ck](../../Readme.md)

---

[Quellcode](TemplateSpecialization.cpp)

---

## Template Spezialisierung

Unter Template Spezialisierung (Template Specialization) versteht mal die M�glichkeit,
dass eine Schablone (ein Template) Sonderf�lle behandelt.
Manchmal k�nnte ein generischer Algorithmus f�r eine bestimmte Art von Sequenz (Container) viel effizienter arbeiten
(z.B. wenn man Iteratoren mit wahlfreiem Zugriff - *random-access* - verwendet).
Daher ist es sinnvoll, den Algorithmus und damit das Template auf diesen Fall zu spezialisieren,
w�hrend f�r alle anderen F�lle der langsamere, aber allgemeinere Ansatz verwendet wird.

Performance ist ein h�ufiger Grund f�r die Templatespezialisierung, aber nicht der einzige.
Man kann beispielsweise eine Schablone auch spezialisieren, um mit bestimmten Objekten zu arbeiten,
die nicht der normalen Schnittstelle entsprechen, die von der generischen Vorlage erwartet wird.
Diese Betrachtungen bzw. Ausnahmef�lle k�nnen mit zwei Arten der Templatespezialisierung behandelt werden:
der expliziten Template Spezialisierung und der teilweise (partielle) Template Spezialisierung
("*explicit template specialization*" und "*partial template specialization*").

## Explizite Template Spezialisierung

Mit der expliziten Template Spezialisierung k�nnen Sie eine bestimmte Implementierung
f�r eine bestimmte Kombination von Templateparametern schreiben.

Beispiel: 

```cpp
template<typename T>
class GenericSorter
{
public:
    static void sort(std::vector<T>& values)
    {
        /* ... */
    };
};
```

Wenn wir eine schnellere (oder andere spezialisierte) M�glichkeit haben,
speziell mit Vektoren von `char`-Variablen (Zeichen) umzugehen,
dann kann man die Klasse `GenericSorter` explizit spezialisieren:

```cpp
template<>
class GenericSorter<char>
{
public:
    static void sort(std::vector<char>& values)
    {
        /* ... */
    };
};
```

Der Compiler w�hlt dann die am besten geeignete Schablone aus:

```cpp
std::vector<int>  vi;
std::vector<char> vc;

GenericSorter<int>::sort(vi);   // calls sort<std::vector<int>>
GenericSorter<char>::sort(vc);  // calls specialized sort<std::vector<char>>
```

## Partielle Template Spezialisierung

F�r Klassen Templates (nicht: Funktionstemplates / Funktionsschablonen) kann man Teilspezialisierungen definieren,
die nicht alle Parameter der prim�ren (nicht spezialisierten) Klassenvorlage ersetzen m�ssen.

Betrachten wir dazu das folgende Beispiel. Die erste Vorlage ist die prim�re Klassenvorlage:

```cpp
template<typename T1, typename T2, int I>
class A {};                               // #1
```

Wir k�nnen `A` f�r den Fall spezialisieren, dass `T2` ein `T1*` ist:

```cpp
template<typename T, int I>
class A<T, T*, I> {};                     // #2
```

Oder f�r den Fall, dass `T1` ein Zeiger ist:

```cpp
template<typename T1, typename T2, int I>
class A<T1*, T2, I> {};                   // #3
```

Oder f�r den Fall, dass `T1` ein `int` ist und `T2` ein beliebiger Zeiger ist und `I` gleich 5 ist::

```cpp
template<typename T>
class A<int, T*, 5> {};                   // #4
```

Oder f�r den Fall, dass `T2` ein Zeiger ist:

```cpp
template<typename T1, typename T2, int I>
class A<T1, T2*, I> {};                   // #5
```

In den Deklarationen 2 bis 5 werden Teilspezialisierungen der prim�ren Vorlage deklariert.
Der Compiler w�hlt dann die entsprechende Vorlage aus:


```cpp
A<int, int, 1>   a1;  // uses #1

A<int, int*, 1>  a2;  // uses #2, T is int,
                      //          I is 1

A<int, char*, 5> a3;  // uses #4, T is char

A<int, char*, 1> a4;  // uses #5, T1 is int,
                      //          T2 is char,
                      //          I is 1

A<int*, int*, 2> a5;  // ambiguous:
                      // matches #3 and #5
```

---

Die Anregungen zu den Beispielen dieses Code Snippets stammen aus

[Template Specialization and Overloading](http://www.gotw.ca/gotw/049.htm)

---

[Zur�ck](../../Readme.md)

---
