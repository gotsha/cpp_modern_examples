# Die Deklarationen `int& const`, `int const&`, `const& int` und `const int&` im Vergleich.

In diesem Unterverzeichnis gibt es keine Quellcode-Datei, also kein Code-Snippet.
Dieses Snippet stellt viel mehr eine Merkhilfe dar, wie man die unterschiedlichen M�glichkeiten
in der Deklaration eines Formalparameters mit den erg�nzenden Kennzeichnungen const und & gestalten kann
bzw. welche Bedeutung diese haben.

*Fragestellung*:
Welches sind die Unterschiede zwischen `int& const`, `int const&`, `const& int` und `const int&` in C++?

Um diese Deklarationen verstehen, liest man sie immer am besten von *rechts* nach *links*:

  * `int& const`:

  Eine konstante (`const`) Referenz (`&`) auf einen `int`-Wert. Da Referenzen prinzipell nach ihrer Definition immer auf dasselbe Objekt verweisen, sind sie immer konstant.
  Das `const`-Schl�ssertwort ist in diesem Fall daher �berfl�ssig. Manche Compiler quittieren dies mit einer Warning, anderen �bersehen diese Deklaration geflissentlich.

  * `int const&`: 

  reference (&) to a constant (const) int. The integer can't be modified through the reference.

  Eine Referenz (`&`) zu einen unver�nderbaren (`const`) `int`-Wert. Der Wert kann durch diese Referenz nicht ver�ndert werden.

  * `const& int`:

  Ein `int`-Wert, der sich auf eine `const`-Referenz bezieht. Weder dieser Satz geschweige denn diese Deklaration ergeben Sinn.
  Diese Deklaration ist nicht �bersetzungsf�hig.

  * `const int&`:

  Eine Referenz f�r einen `int`-Wert, der als konstant (`const`) deklariert wird. Dieser Fall ist identisch zu `int const&`.

