# Tema 2 – Card Game în C++

## Descriere generală

Acest proiect reprezintă implementarea unui joc de cărți bazat pe turnuri, scris în C++ cu accent pe principiile programării orientate pe obiecte. Jucătorul controlează un personaj care trebuie să înfrunte o serie de monștri într-o succesiune de lupte, folosind un pachet de cărți pe care îl poate îmbunătăți între runde prin intermediul unui magazin. Proiectul a fost structurat cu grijă pentru a reflecta concepte fundamentale din OOP: ierarhii de clase, polimorfism, gestionarea memoriei pe heap, și șabloane de proiectare (design patterns).

---

## Structura proiectului

Codul este împărțit în mai multe module cu responsabilități clare:

- **cards.h / Card.cpp** — definește ierarhia de cărți
- **cardCollection.h / cardCollection.cpp** — gestionează baza de date de cărți
- **cardFactory.h** — centralizează crearea obiectelor de tip carte
- **entity.h / entity.cpp** — definește entitățile din joc (jucător, monstru, magazin)
- **main.cpp** — punctul de intrare și logica principală a jocului

---

## Ierarhia de cărți și NVI

Clasa de bază `Card` definește interfața comună pentru toate tipurile de cărți din joc. Aceasta folosește pattern-ul **NVI (Non-Virtual Interface)**: metodele publice `print()` și `copy()` sunt non-virtuale și apelează intern metodele protejate virtuale `display()` și `clone()`. Avantajul acestei abordări este că logica de control rămâne în clasa de bază, iar subclasele nu pot fi apelate direct din exterior fără a trece prin interfața definită.

Cele trei tipuri concrete de cărți sunt:

- **Attack** — carte de atac cu daune și număr de lovituri
- **Spell** — vrajă cu daune, lovituri și un cost de mana
- **Mana** — carte care regenerează mana jucătorului sau monstrului

Fiecare subclasă implementează `display()` și `clone()`, permițând afișarea și copierea polimorfică corectă prin pointeri de tip `Card*`. Copierea profundă este esențială deoarece cărțile sunt alocate pe heap și gestionate manual.

---

## Gestionarea memoriei

Un aspect important al proiectului este gestionarea corectă a memoriei dinamice. Fiecare entitate (jucător sau monstru) deține pointeri către cărțile din pachet și din mână, pe care le alocă și le eliberează în destructori. Clasa `Player` implementează și **operatorul de atribuire prin copiere** folosind idiomul copy-and-swap, garantând că nu există scurgeri de memorie sau copieri incomplete în cazul auto-atribuirii.

Magazinul (`Shop`) deține pointeri către cărțile originale din compendiu — nu copii — și prin urmare nu le eliberează în destructor. Această distincție dintre proprietar și observator este importantă pentru a evita double-free.

---

## Design Pattern 1: Singleton — CardCompedium

`CardCompedium` este clasa care funcționează ca o bază de date centrală pentru toate cărțile din joc. Aceasta este implementată folosind pattern-ul **Singleton**, care garantează că există o singură instanță a bazei de date pe toată durata execuției programului.

Implementarea respectă cele trei reguli ale Singleton-ului:

1. **Constructor privat** — nimeni din exterior nu poate instanția direct clasa
2. **Ștergerea constructorului de copiere și a operatorului de atribuire** — previne duplicarea instanței
3. **Metodă statică `getInstance()`** — singura modalitate de a accesa instanța, care este creată lazy (la primul apel)

```cpp
static CardCompedium& getInstance() {
    static CardCompedium instance;
    return instance;
}
```

Această abordare este thread-safe în C++11 și ulterior, deoarece inițializarea variabilelor statice locale este garantată a fi atomică de standard. În `main.cpp`, accesul se face prin `CardCompedium::getInstance()`, eliminând necesitatea unei variabile globale explicite.

---

## Design Pattern 2: Factory — CardFactory

Clasa `CardFactory` implementează pattern-ul **Factory Method** pentru crearea obiectelor de tip carte. Înainte de introducerea acestui pattern, metoda `loadCardsFromFile` din `CardCompedium` conținea direct apeluri `new Attack(...)`, `new Spell(...)`, `new Mana(...)`, cuplând strâns logica de parsing cu logica de creare a obiectelor.

Prin extragerea creării într-o metodă statică centralizată:

```cpp
static Card* create(char type, std::string name, int id,
                    int dmg=0, int hits=0, int cost=0, int gain=0);
```

se obțin mai multe avantaje: dacă se adaugă un nou tip de carte în viitor, modificarea se face într-un singur loc. De asemenea, codul din `loadCardsFromFile` devine mai curat și mai ușor de citit, concentrându-se pe parsarea fișierului și nu pe detaliile de construcție ale obiectelor.

---

## Entitățile și logica de luptă

Clasa abstractă `Entity` stă la baza ierarhiei de entități și definește atributele comune: nume, puncte de viață, mana. Metoda `takeDamage()` este pur virtuală, lăsând subclaselor libertatea de a defini comportamentul la primirea daunelor, inclusiv apelul metodei `death()`.

`Player` și `Monster` extind `Entity` și implementează logica specifică de joc: tragerea cărților din pachet în mână (`startTurn`), jucarea unei cărți cu efect asupra adversarului (`playAndReturnToDeck`), și returnarea cărților în pachet după utilizare. Monștrii joacă automat o carte aleasă aleatoriu, în timp ce jucătorul interacționează prin consolă.

Selectarea tipului de carte la momentul jucării se face prin `dynamic_cast`, o soluție pragmatică dată fiind structura ierarhiei și nevoia de a apela overload-ul corect al metodei `playCard`.

---

## Magazinul

Clasa `Shop` oferă jucătorului posibilitatea de a adăuga o carte nouă în pachet între lupte. La construcție, magazinul alege aleatoriu trei cărți din compendiu și le prezintă jucătorului. Cărțile afișate sunt pointeri către originalele din `CardCompedium` — nu copii — iar la cumpărare, `addCardToDeck` face o copie profundă înainte de a o adăuga în pachetul jucătorului.

---

## Concluzie

Proiectul acoperă o gamă largă de concepte C++ aplicate într-un context practic și coerent: polimorfism prin pointeri la clasa de bază, NVI pentru encapsularea comportamentului virtual, gestionarea manuală a memoriei cu destructori și copy-and-swap, și două șabloane de proiectare clasice — Singleton și Factory — integrate natural în arhitectura aplicației. Codul este structurat modular, cu separare clară între responsabilități, și poate fi extins relativ ușor cu noi tipuri de cărți, entități sau mecanici de joc.
