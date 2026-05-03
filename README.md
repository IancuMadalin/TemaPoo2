# TemaPoo2
Repo pt tema2

Un joc de tip Deck Builder, in care player-ul colecteaza cărți pe care le folosește pentru a învinge diferiți inamici (WIP)

1. Librării utilizate și scopul lor
Proiectul folosește o serie de librării standard din C++ (STL) pentru a asigura o execuție eficientă și organizată:

<iostream>: Folosită pentru interacțiunea cu utilizatorul prin consolă (citirea opțiunilor din terminal via std::cin și afișarea stării jocului via std::cout).

<string>: Folosită pentru manipularea eficientă a textului (numele cărților, numele entităților etc.).

<vector>: Folosită în clasa Player și Monster pentru a gestiona dinamic pachetul de cărți (deck) și cărțile din mână (hand).

<map>: Utilizată în CardCompedium pentru a stoca toate cărțile disponibile în joc sub forma unei colecții indexate (std::map<int, Card*>), unde cheia este ID-ul cărții.

<fstream>: Folosită în CardCompedium pentru citirea datelor din fișiere text externe (cards.txt), permițând popularea bazei de date cu cărți la pornirea aplicației.

<random>: Folosită pentru generarea numerelor aleatorii (prin std::mt19937 și std::uniform_int_distribution) pentru a trage cărți aleatorii din deck în timpul luptei.

<stdexcept>: Folosită pentru gestionarea erorilor prin mecanismul de excepții (ex. std::runtime_error atunci când fișierul de cărți nu poate fi deschis).

<utility>: Folosită pentru optimizarea copierilor prin std::move și operații de tip std::swap.

2. Ierarhia Claselor
Proiectul este structurat pe baza a două ierarhii principale de clase, demonstrând utilizarea corectă a programării orientate pe obiecte (POO).

A. Ierarhia Cărților (Card)
Toate cărțile din joc derivă dintr-o clasă de bază abstractă, care dictează comportamentul comun.

Card (Clasă de bază abstractă): Conține datele fundamentale ale unei cărți: name (numele) și id (identificatorul unic). Are metode pur virtuale pentru afișare și clonare.

Attack (Clasă derivată): Reprezintă o carte de atac fizic. Are atribute suplimentare precum dmg (daune) și hits (numărul de lovituri).

Spell (Clasă derivată): Reprezintă o carte de tip vrajă. Pe lângă daune și lovituri, introduce atributul cost (costul de mană necesar utilizării).

Mana (Clasă derivată): Reprezintă o carte de utilitate care îi permite jucătorului să își refacă resursele. Conține atributul mana_gain (cantitatea de mană primită).

B. Ierarhia Entităților (Entity)
Modelează personajele care pot lua parte la luptă.

Entity (Clasă de bază abstractă): Definește atributele comune tuturor personajelor (name, hp, max_hp, mana, max_mana) și comportamentul abstract de primire a daunelor prin metoda pur virtuală takeDamage(int dmg).

Player (Clasă derivată): Reprezintă utilizatorul. Deține un pachet de cărți (deck), o mână curentă de cărți (hand), nivel (lvl) și bani (money). Implementează funcționalitățile de tragere a cărților, jucare a cărților și gestionare a inventarului.

Monster (Clasă derivată): Reprezintă inamicul. Are o recompensă în bani la înfrângere (money_reward) și un comportament specific la moarte.

3. Tehnici de Programare Utilizate
Proiectul pune în valoare concepte avansate de C++ și bune practici în ingineria software:

1. Polimorfism și Funcții Virtuale
Clasele Card și Entity definesc metode virtuale pure (virtual void display() = 0;, virtual void takeDamage(int dmg) = 0;), transformându-le în interfețe (clase abstracte). Acest lucru garantează că fiecare clasă derivată își implementează propria logică specifică, iar motorul de luptă poate apela aceste funcții polimorfic, fără să îi pese de tipul exact al obiectului în acel moment.

2. NVI (Non-Virtual Interface Idiom)
În clasa Card, interfața publică este separată de implementarea virtuală:

Funcțiile publice print() și copy() sunt non-virtuale.

Acestea apelează intern funcțiile protejate virtuale display() și clone().

Scop: Acest idiom oferă un control mai bun asupra modului în care funcțiile virtuale sunt apelate și permite adăugarea de cod înainte/după execuția metodei derivate, dacă este necesar.

3. Rule of Three & Memory Management
Deoarece cărțile sunt alocate dinamic pe heap (folosind pointeri Card*), proiectul respectă cu strictețe managementul memoriei:

Destructori virtuali: Clasa Card are un destructor virtual (virtual ~Card();) pentru a preveni pierderile de memorie (memory leaks) atunci când un obiect derivat este șters printr-un pointer de clasă de bază.

Deep Copying: Constructorul de copiere al clasei Player realizează o clonare profundă a cărților din deck și hand apelând metoda copy().

Copy and Swap Idiom: Clasa Player implementează operatorul de atribuire (operator=) prin tehnica Copy and Swap, asigurând siguranță la excepții și evitând duplicarea codului.

4. RTTI & Dynamic Casting
În metoda Player::playAndReturnToDeck, se utilizează dynamic_cast pentru a identifica în siguranță, la rulare, tipul exact al cărții din mână (Attack*, Spell* sau Mana*) și a aplica efectul corespunzător asupra monstrului.

5. Încapsularea Exception Handling (Tratarea Excepțiilor)
În CardCompedium::loadCardsFromFile, citirea din fișier este protejată de un bloc try-catch:

Dacă fișierul cu cărți nu există sau are probleme la deschidere, se aruncă o excepție de tip std::runtime_error.

Excepția este prinsă imediat în cadrul aceleiași funcții, prevenind crash-ul aplicației. Jocul afișează un avertisment și continuă rularea normală (cu un compendiu gol), oferind stabilitate codului.

6. Supraîncărcarea Operatorilor
operator<<: Supraîncărcat ca funcție friend pentru clasa CardCompedium pentru a permite afișarea întregii librării de cărți direct prin fluxul std::cout << CC;.

Review: O sa îi fac review lui Ivănuș Victor
