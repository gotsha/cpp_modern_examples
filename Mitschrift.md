# RValue - LValue
```cpp
int n;
int *ip;
ip = &n;

//Zuweisen des Wertes 123
// a)
n=123 

// b)
*ip=123; 
ip++; // Adresse wird abh�ngig vom Datentyp um x Byte erh�ht // Zeigerarithmetik

// Referenz
int& ri = n;// ri ist ein Alias // Stellvertretername
// Zuordnung mittels
ri = 456; // -> ohne Dereferenzierung...
ri++; // Wert von n wird erh�ht -> 457

// Wozu Referenzen wenn es auch Pointer gibt?
// Schreibweise einfacher (keine * und & bei Zuweisungen...)
// Adresse erh�hen (Zeigerarithmetik) gef�hrlich
```
sayHello(std::string&& message) - && zeigt an, dass Referenz auf Objekte ohne Name �bergeben werden, z.B. sayHello(strA + strB)

LValue und RValue aus C. (C ist in C++ komplett (zu 99%) enthalten)
- LValue -> links von Zuweisungszeichen -> hat eine Adresse.
- RVAlue -> hat keine Adresse bzw. ich kenn diese nicht

std::move ist keine Fkt sondern ein cast

# Move Semantics
new Anweisung entspricht malloc in C
BigData::BigData(const BigData& data) {} //das ist der copy Constructor. 
vec.push_back(BigData(10, 1)); //dadurch wird ein tempor�res Objekt angelegt; dieses wird danach auch wieder freigegeben -> destructor

um diese unn�tze Kopie zu vermeiden gibt es move anstatt copy semantics. Eigentlich klauen wir dadurch das Objekt
BigData::BigData(BigData&& data) noexcept;

wenn new... brauchen wir immer ein delete -> nicht den Standard-Destruktor nutzen

_Rule of Three_
Klassen ben�tigen standardm��ig diese Elemente wenn es bei dynamische Objekte davon gibt oder R�ckgaben mit return.
(new, oder z.B. int* array)

_Rule of Five_
um unn�tze Kopien zu vermeiden -> move constructor + assignment
bei dynamischen Zeigern (new, oder z.B. int* array)


_Rule of Zero_
auch hier dyn Speicherverwaltung m�glich: reserve => initialer Speicher

in C++ liegt ein std::vector<int> vec; auf dem Stack, der r�umt sich von allein auf. Zus�tzlich gibt es den heap. In Java gibt es nur den heap.

# auto
Funktionen mit R�ckgabewert auto: R�ckgabewerte in der Fkt m�ssen �bereinstimmen
```cpp
auto tueWas(bool flag, float f1, double d1) {
	if (flag) {
		return f2;
	}
	else {
		return f1;
	}
}
```
ist nicht valide.  
Was geht
```cpp
template <typename T, typename U>
auto tueWas(bool flag, T f1, U f2) -> decltype (f1 + v2) {
	if (flag) {
		return f2;
	}
	else {
		return f1;
	}
}

void anwendung() 
{
	auto result = tueWas(false, 123, 456l);
	auto result2 = tueWas(false, 123.0f, 345.5(;
}
```
oder:
```cpp
template <typename T, typename U>
decltype ( std::declval<T>() + std::declval<U>() ) tueWas(bool flag, T f1, U f2) {
	if (flag) {
		return f2;
	}
	else {
		return f1;
	}
}

void anwendung() 
{
	auto result = tueWas(false, 123, 456l);
	auto result2 = tueWas(false, 123.0f, 345.5(;
}
```

declval gibt ohne declval keinen Sinn. 

auto wird h�ufig mit Referenz-Keyword & verwendet um unbeabsichtigte Kopien zu vermeiden

const Schl�sselwort wird verwendet wenn m�glich da der Compiler solche Objekte effizienter �bersetzt.  


