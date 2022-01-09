# C++ Standard Attribute

[Zur�ck](../../Readme.md)

---

[Quellcode](Attributes.cpp)

---

## �berblick

Im C++ Standard k�nnen Attribute in doppelten eckigen Klammern eingesetzt werden.
Die bekanntesten Attribute sind in der folgenden Tabelle aufgef�hrt:

| Name | Beschreibung |
|:-|:-|
| `[[noreturn]]` | Zeigt an, dass die Funktion nicht zur�ckkehrt. |
| `[[deprecated]]` | Zeigt an, dass die Verwendung des mit diesem Attribut deklarierten Namens zul�ssig ist, aber aus irgendeinem Grund davon abgeraten wird, dieses Sprachfeature einzusetzen. |
| `[[fallthrough]]` | Weist darauf hin, dass das Durchfallen des vorherigen `case`-Labels beabsichtigt ist und nicht von einem Compiler diagnostiziert werden sollte (so genanntes &ldquo;*fall-through*&rdquo;). |
| `[[nodiscard]]` | Der Compiler gibt eine Warnung aus, wenn der R�ckgabewert ignoriert wird. |
| `[[maybe_unused]]` | Unterdr�ckt eine Compiler-Warnung, wenn eine Variable/Objekt nicht verwendet wird. |

Tabelle: Einige C++ Standard Attribute.

Daneben gibt es noch weitere, recht spezielle Attribute, wie zum Beispiel `carries_dependency`,
`likely`, `unlikely` oder `no_unique_address`.

---

[Zur�ck](../../Readme.md)

---
