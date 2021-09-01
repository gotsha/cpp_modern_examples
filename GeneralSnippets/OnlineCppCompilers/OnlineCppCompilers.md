# Online C++ Compiler

[Zur�ck](../../Readme.md)

---

## Allgemeines

Unter 

[List of Online C++ Compilers](https://arnemertz.github.io/online-compilers/)

findet man eine Liste mit Informationen zu verf�gbaren C++ Online Compilern und ihren wichtigsten Funktionen vor.
Auch unterst�tzen viele dieser WebSites andere Sprachen als C++,
war f�r unsere Zwecke an dieser Stelle nicht weiter relevant ist.
Je nach Version des verwendeten Compilers stehen unterschiedliche Versionen des C++&ndash;Standards zur Verf�gung.

Neben der blo�en Kompilierung f�hren die meisten Online-Compiler auch das kompilierte Programm aus.
Die M�glichkeiten, die Kompilierung �ber Compiler-Flags zu parametrisieren,
Kommandozeilen- und/oder Laufzeitparameter an das ausgef�hrte Programm zu �bergeben und Eingaben f�r Standardeingaben bereitzustellen,
variieren zwischen den verschiedenen WebSites.

Es folgen einige Details zu drei sehr popul�ren Online C++ Compilern.

---

### Wandbox

[Wandbox](https://wandbox.org/).

*Wandbox* bietet so ziemlich alle Funktionen, die Sie sich von einem typischen Online-Compiler w�nschen,
einschlie�lich der Unterst�tzung mehrerer Dateien und verschiedener Editor-Tastenkombinationen.
Neben der Standardbibliothek enth�lt es einige Bibliotheken, darunter *Boost* (bis zu 1.64), *Sprout* und *MessagePack*.
Die kompilierten Programme laufen in einer Sandbox-Umgebung,
die Datei-I/O erm�glicht. Die mitgelieferten Snapshot-Versionen von *GCC* und *Clang* erm�glichen das Spielen
mit den neuesten C++17/20&ndash;Features.

<img src="Wandbox.png" width="700">

*Abbildung* 1: Oberfl�che des Online &ldquo;Wandbox&rdquo; Compilers.

---

### Compiler Explorer (Godbolt)

[Wandbox](https://wandbox.org/).

*Compiler Explorer* ist eine &ldquo;*compile-as-you-type*&rdquo; IDE mit einer besonderen Funktion,
da sie den von den Compilern erzeugten Assemblercode darstellt.
Der resultierende Assemblercode kann dem urspr�nglichen C++-Code farblich zugeordnet werden.
*Compiler Explorer* unterst�tzt die gleichzeitige Verwendung verschiedener Quellen und mehrerer Compiler,
sodass wir den Assemblercode, der von verschiedenen Compilern, mit unterschiedlichene Optimierungsflags usw. erzeugt wird,
vergleichen k�nnen. Der Compiler-Explorer ist auf GitHub zu finden und kann lokal verwendet werden.

<img src="CompilerExplorer.png" width="700">

*Abbildung* 2: Oberfl�che des Online &ldquo;Compiler Explorer&rdquo; Compilers.

---

### Cppinsights

[Cppinsights](https://cppinsights.io/).

*Cppinsights* ist weniger eine Online-IDE im herk�mmlichen Sinne,
denn sie erlaubt es nicht, kompilierte Programme auszuf�hren.
Stattdessen zeigt die IDE eine andere Version des Quellcodes, die einen Teil der Magie zeigt,
die der Compiler unter der Haube macht. Man k�nnte auch sagen, dass *Cppinsights* eine Art
&ldquo;C++ nach C++&rdquo;&ndash;Pr�compiler mit dem Ziel ist, den urspr�nglichen Quellcode besser verst�ndlich umzuwandeln.
*Cppinsights* ist ein Tool geschrieben von [Andreas Fertig](https://andreasfertig.info/).

<img src="Cppinsights.png" width="700">

*Abbildung* 3: Oberfl�che des Online &ldquo;Cppinsights&rdquo; Compilers.

---

[Zur�ck](../../Readme.md)

---
