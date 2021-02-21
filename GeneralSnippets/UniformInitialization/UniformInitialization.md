# Einheitliche Initialisierung

[Zur�ck](../../Readme.md)

---

*Hinweis*:

Siehe dazu auch das Sprachfeature [Default-Initialisierung f�r Member-Variablen](../../GeneralSnippets/DefaultInitialization/DefaultInitialization.md).

---

[Quellcode](UniformInitialization.cpp)

---

Die Initialisierung mit geschweiften Klammern '{' und '}' ist ab der Version C++ 11 eine einheitliche Methode zum Initialisieren von Daten.
Sie wird auch als "*Uniform Initialization*" bezeichnet.

<img src="cpp_init.gif" width="400">

Abbildung 1: C++ und Initialisierung: *Relax*!

---

*Vorbemerkung*:

Bei der Initialisierung in C++ gilt es generell zwischen zwei verschiedenene Formen zu unterscheiden:

  * Der sogenannten *direkten Initialisierung*, die ein Objekt mit einem expliziten Konstruktor und einem entsprechenden Satz an Konstruktorargumenten initialisiert.
  * Der sogenannten *Kopier-Initialisierung*, die ein Objekt mit einem anderen Objekt initialisiert.

```cpp
std::string s1("test");   // direct initialization
std::string s2 = "test";  // copy initialization
```

Diese beiden Varianten gibt es auch bei der *Uniform Initialization*, 
man spricht dann syntaktisch von der so genannten "*Direct List*" bzw. "*Copy List*" Initialisierung:

```cpp
T object {other};     // direct list initialization
T object = {other};   // copy list initialization
```

---

Es lassen sich mit geschweiften Klammern ("*Uniform Initialization*") alle m�glichen Arten einer Variablen-Initialisierung (auch Objekte)
mit einer einheitlichen Schreibweise initialisieren.
Am besten studiert man die einzelnen M�glichkeiten an Hand der folgenden Systematisierung:



  * Variablen elementaren Datentyps: Initialisierung mit datentyp-spezifischem Null-Wert.   
  * Variablen elementaren Datentyps: allgemeine Initialisierung.
  * Standard STL Container.
  * Dynamisch allokierte Felder.
  * Statisch allokierte (bzw. definierte) Felder.
  * Benutzerdefinierte Objekte (C++ Klassen).
  * Benutzerdefinierte Variable eines POD Typs (Struktur, 'Plain-Old-Data').
  * Kombinationen dieser Regeln.

---

*Bemerkung*:

Ein POD-Datentyp ist in C++ vereinfacht ausgedr�ckt ein Strukturtyp. Etwas ausf�hrlicher betrachtet gilt folgende Definition:

"*In C++ ist ein POD-Datentyp entweder ein skalarer Datentyp oder eine POD-Klasse. Eine POD-Klasse hat keinen benutzerdefinierten Kopier-Zuweisungs-Operator,
keinen benutzerdefinierten Konstruktor und keine nicht-statischen Attribute, die nicht selbst PODs sind.
Dar�ber hinaus muss eine POD-Klasse ein Aggregat-Typ oder eine `union` sein, das hei�t,
sie darf keine benutzerdefinierten Konstruktoren haben,
keine nicht-statischen Attribute, die als `private` oder `protected` definiert sind, keine Basisklassen und keine virtuelle Funktionen.
Der C++ -Standard enth�lt weitere Details �ber das Verhalten von PODs in C++.*"

---

Die Ausgabe des Code-Snippets sieht so aus:

```cpp
n: 0
f: 0
d: 0
s:
v.size(): 0
n: 1
f: 1.5
d: 2.5
s: 123
1, 2, 3, 4, 5,
Hans - 1958
Sepp - 1956
1, 2, 3, 4, 5,
1, 2, 3, 4, 5,
1, 2, 3, 4, 5,
a: 0, b: 0
a: 42, b: 1.2
a: 42, b: 0
a: 42, b: 1.2
x: 111, y: 1.23
x: 123, y: 99.9
m_n: 98
0: 10
1: 20
2: 30
3: 40
4: 50
m_n: 99
0: 11
1: 12
2: 13
3: 14
4: 15
m_n: 26
0: 21
1: 22
2: 23
3: 24
4: 25
0: 50
1: 51
2: 52
```

---

[Zur�ck](../../Readme.md)

---
