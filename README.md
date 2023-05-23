# LanParty
Tema numarul 1 la PA
Acest exercițiu implică organizarea și desfășurarea unei competiții între echipe, urmând un set de reguli specifice. Vom utiliza structuri de date precum liste, cozi, stive și arbori binari pentru a gestiona meciurile și a determina echipele câștigătoare.

Detalii Tehnice
Punctajul de echipă: Fiecare echipă are un punctaj de echipă, care reprezintă scorul acumulat în timpul competiției. Modul de calcul al acestui punctaj nu este specificat în acest exercițiu.

Instrucțiuni
Citirea și crearea listei:

Se va citi conținutul fișierului "d.in".
Se va crea o listă prin adăugarea elementelor la începutul listei. Aceasta se va face într-un timp constant (O(1)) pentru fiecare element adăugat.
Eliminarea echipelor cu cel mai mic punctaj:

Se vor elimina echipele cu cel mai mic punctaj de echipă din lista creată anterior. Dacă există mai multe echipe cu același scor, se va elimina prima echipă găsită în listă.
Procesul de eliminare se va realiza după fiecare eliminare a unei echipe, se va relua parcurgerea listei de la început.
Se vor păstra în listă doar primele n echipe, unde n este un număr maxim și este o putere a lui 2.
Crearea structurilor de date pentru meciuri:

Se va crea o coadă în care se vor pune meciurile dintre echipe. Meciurile se vor forma în ordinea în care echipele apar în lista creată anterior. Primele două echipe vor forma primul meci, apoi următoarele două echipe vor forma al doilea meci, și așa mai departe.
Se vor crea două stive: una pentru învinși și una pentru câștigători. Stiva pentru învinși va conține echipele care au pierdut meciul anterior, iar stiva pentru câștigători va conține echipele care au câștigat meciul anterior.
Echipele vor fi adăugate în stive în funcție de rezultatul meciului și se va adăuga un punct la punctajul de echipă al echipelor câștigătoare.
Eliminarea echipelor învinse:

La finalul fiecărei etape, se vor șterge echipele din stiva de învinși.
De exemplu, într-o rundă cu 8 echipe, eliminarea se va face după ce au fost eliminate toate cele 4 echipe. În runda următoare, vor fi adăugate alte 2 echipe în stiva de învinși, după care stiva de învinși va fi eliberată din nou.
Reumplerea cozii de meciuri:

Din stiva de câștigători se vor extrage echipele și se va umple din nou coada de meciuri, formându-se meciurile cu echipele consecutive. Prima echipă scoasă din stivă va juca cu a doua echipă scoasă din stivă în primul meci, a treia echipă cu a patra echipă în al doilea meci, și așa mai departe.
Repetarea pașilor:

Se vor repeta pașii de la 2 la 5 până când se vor determina echipele de pe primele 8 locuri. Aceste echipe vor fi salvate într-o altă listă.
Realizarea clasamentului cu un BST:

Se va crea un arbore binar de căutare (BST) utilizând echipele salvate la subpunctul anterior.
Acest BST va fi ordonat după punctajul pe echipă, în ordine descrescătoare. În cazul în care două echipe au același punctaj, se vor ordona în funcție de nume, în ordine descrescătoare.
Conținutul arborelui va fi afișat în ordine descrescătoare, astfel încât echipele cu cel mai mare punctaj vor fi afișate primele.
Realizarea unui arbore AVL:

Utilizând echipele salvate la subpunctul 6, se va crea un arbore AVL.
Echipele din arbore vor fi sortate în același mod ca în subpunctul 4 (punctaj descrescător, iar în caz de egalitate, se va ordona după nume în ordine descrescătoare).
Se vor afișa echipele de pe nivelul 2 al arborelui AVL.
