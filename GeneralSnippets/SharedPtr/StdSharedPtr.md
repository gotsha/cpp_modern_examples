# Shared Pointer: Klasse `std::shared_ptr`

[Zur�ck](../../Readme.md)

---

[Quellcode](StdSharedPtr.cpp)

---

## &ldquo;It's about ownership&rdquo;

###### Exklusiver Besitz: `std::unique_ptr<T>`

#### Geteilter Besitz: `std::shared_ptr<T>`

###### Tempor�rer Besitz: `std::weak_ptr<T>`

---

*Hinweis*:

Die beiden Varianten, ein `std::shared_ptr`-Objekt anzulegen, sind nicht
ganz identisch:

  * `std::shared_ptr` und expliziter `new` Aufruf
  * `std::make_shared` Aufruf

Ein `std::shared_ptr`-Objekt verwaltet zwei Speicherbereiche:

  * einen so genannten `Control-Block` (speichert Metadaten wie Referenz-Z�hler, den *Deleter* f�r das Objekt usw.)
  * das zu allokierende Objekt selbst

Ein Aufruf von `std::make_shared` l�st eine einzige Heap-Speicherplatzanforderung aus,
die den `Controlblock` und den f�r die Daten erforderlichen Speicherplatz umfasst.

Im anderen Fall bewirkt `new Obj ("foo")` eine Heap-Speicherplatzanforderung f�r die zu verwaltenden Daten,
und der Konstruktor von `std::shared_ptr` f�hrt die zweite Anforderung
f�r den Kontrollblock aus.

Man kann damit zusammenfassen, dass die Verwendung der `std::make_shared`-Funktion
effizienter ist.

---

[Zur�ck](../../Readme.md)

---

