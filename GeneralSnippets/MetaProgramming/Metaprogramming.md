# Metaprogramming

## �berblick

C++ -Metaprogrammierung bezeichnet die Technik der Metaprogrammierung innerhalb der Programmiersprache C++,
also eine Technik, um in C++ Programmcode zur �bersetzungszeit generieren zu lassen

Bei der Templatemetaprogrammierung macht man sich zunutze, dass Templates w�hrend des Kompilierens ausgewertet werden.
So kann man Code schreiben, der zur �bersetzungszeit ausgef�hrt wird. Obwohl sich so die Dauer des Kompilierens verl�ngert, hat das Verfahren den Vorteil, dass es zu einer Verk�rzung der Laufzeit kommen kann.

## Das klassische Beispiel

[Quellcode](MetaProgramming.cpp)

```cpp
template <int N>
struct Factorial {

    static int const value = N * Factorial<N - 1>::value;

};

template <>
struct Factorial<1> {
    static int const value = 1;
};
```

In den Code-Snippets wird zum Thema "*Metaprogrammierung*" das wohl bekannteste Beispiel demontriert, die Berechnung
der Fakult�t-Funktion zur �bersetzungszeit. Dabei ist zu beachten, dass es auch sehr wohl zur �bersetzungszeit zu Fehler kommen kann.

Diese werden vom Compiler - in meinem Fall als "*warning*" - gemeldet:

warning C4307: '*': signed integral constant overflow
message : see reference to class template instantiation 'Metaprogramming::Factorial<13>' being compiled

Es tritt also der (hinl�nglich bekannte) �berlauf in der Fakult�tfunktion bei Verwendung des Datentyps `int` auf.

Die Ausgabe des Programms - mit Fehlern - sieht auf meinem Rechner wie folgt aus:

```cpp
1
2
6
24
120
720
5040
40320
362880
3628800
39916800
479001600
1932053504
1278945280
2004310016
2004189184
-288522240
```

---

[Zur�ck](../../Readme.md)

---
