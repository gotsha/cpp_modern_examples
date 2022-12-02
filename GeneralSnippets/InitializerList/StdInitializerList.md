# Klasse `std::initializer_list<T>`

[Zur�ck](../../Readme.md)

---

[Quellcode](InitializerList.cpp)

---

Um f�r Konstruktoren eine variable Anzahl von Parametern (desselben Typs) zu erm�glichen,
wurde in C++ das Konzept von *Initialisierungslisten* eingef�hrt.

Eine Klasse muss dann einen entsprechenden Konstruktor zur Verf�gung stellen, der das Klassentemplate `std::initializer_list<>`
verwendet.

---

Wenn der Compiler eine `std::initializer_list`-Objekt erstellt,
werden die Elemente der Liste auf dem Stapel konstruiert (als konstante Objekte).

Danach erstellt der Compiler das `std::initializer_list`-Objekt selbst,
das die Adresse des ersten und letzten Elements enth�lt
(genauer in Bezug auf das letzte Element: die Adresse des ersten Elements *nach* dem letzten Element).

Folglich besteht ein `std::initializer_list`-Objekt nur aus zwei Zeigervariablen,
es handelt sich also um ein recht kleines Objekt.
Damit ist es nicht wirklich notwendig, bei der Parameter�bergabe 
eine Referenz zu verwenden &ndash; die Parameter�bergabe *Call-by-Value* ist v�llig ausreichend.

<img src="cpp_initializer_list.svg" width="300">

*Abbildung* 1: Konstruktion des Inhalts eines `std::initializer_list`-Objekts auf dem Stack.

---

[Zur�ck](../../Readme.md)

---
