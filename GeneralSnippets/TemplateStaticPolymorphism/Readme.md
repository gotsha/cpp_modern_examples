# Templates und statischer Polymorphismus

Man kann - speziell f�r Programmiersprachen, die Polymorphismus unterst�tzen - zwei Varianten des Polymorphismus
unterscheinden:

  * statischer Polymorphismus
  * dynamischer Polymorphismus

Prinzipiell bedeutet der klassische (dynamische) Polymorphismus, dass die Auswahl des Aufrufs einer Methode bzw. Funktion
in Abh�ngigkeit des tats�chlich zur Laufzeit vorliegenden Objekts zur Laufzeit erfolgt.

Sind Schablonen (Templates) im Spiel, kann diese Festlegung statisch (also zur �bersetzungszeit) erfolgen.

Eine Gegen�berstellung der beiden Varianten findet im vorliegenden Code-Snippet statt.

Gegen�berstellung "Statischer vs. dynamischer Polymorphismus in C++":

  * Vorteile dynamischer Polymorphismus in C++:

    Unterst�tzung heterogener Datenstrukturen, etwa einer Liste graphischer Objekte.

    Die Schnittstelle ist durch eine Basisklasse fest definiert.

  * Vorteile statischer Polymorphismus in C++:

    Erh�hte Typsicherheit.

    Die fehlende Beschr�nkung auf eine Basisklasse erweitert den potentiellen Anwendungsbereich.

