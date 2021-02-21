# RValue Referenzen / LValue Referenzen

[Zur�ck](../../Readme.md)

---

*Allgemeines*:

Wenn `X` ein Typ ist, wird `X&&` als *RValue* Referenz auf `X` bezeichnet.
Zur besseren Unterscheidung wird die gew�hnliche Referenz `X&` jetzt auch als *LValue* Referenz bezeichnet.
Eine *RValue* Referenz ist ein Typ, der sich - von einigen Ausnahmen abgesehen - �hnlich
wie die normale *LValue* Referenz `X&` verh�lt.

Das Wichtigste ist, dass *LValue*s bei der Aufl�sung von Funktions�berladungen die
herk�mmlichen *LValue*-Referenzen bevorzugen, w�hrend *RValue*s
die neuen *RValue*-Referenzen bevorzugen:

```cpp
void foo(X& x);   // lvalue reference overload
void foo(X&& x);  // rvalue reference overload

X x;
X foobar();

foo(x);         // argument is lvalue: calls foo(X&)
foo(foobar());  // argument is rvalue: calls foo(X&&)
```

Eine der Kernaussagen bei RValue Referenzen / LValue Referenzen lautet also:
 
Mit *Rvalue*-Referenzen kann eine Funktion zur �bersetzungszeit (mittels �berladung)
unter der Bedingung "*Werde ich f�r einen L-Wert oder einen R-Wert aufgerufen?*" verzweigen.

Siehe weiteres dazu im korrespondieren [Quellcode](RValueLValue.cpp).

---

[Zur�ck](../../Readme.md)

---


