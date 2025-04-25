

 Programul implementeaza un arbore de sufixe, pornind de la mai multe cuvinte citite. Afiseaza arborele de sufixe, calculeaza numarul de frunze,
 numarul de sufixe de o anumita lungime si numarul maxim de fii ai unui nod din arbore. Totodata, verifica daca un anumit sufix apare sau nu arbore.


    Taskul 1:

 Implementeaza si afiseaza un arbore de sufixe, utilizand cuvintele din fisierul de intrare. Sufixele sunt afisate in fisierul de iesire in ordine
 lexicografica, fiecare sufix terminandu se cu caracterul special "$", care prin conventie va sta inaintea primei litere "a"; 
 
    Taskul 2:

 Afiseaza 3 statistici despre arborele de sufixe:
 
 - numarul de frunze din arbore, lucru echivalent cu numarul de aparitii alea caracterului $ in arbore. Astfel, in functia de afisare
 void printSuffixTree(Node * root, FILE *out, int k), daca parametrul k este 2 (este vorba de taskul 2), cand parcurg arborele in latime
 numar de cate ori apare $.

 - numarul maxim de fii ai unui nod, calculat de functia void numar_fii(Node *radacina, int *max_fii) parcurge arborele in adancime, iar pentru
 fiecare nod numara cati fii are. Salveaza si afiseaza valoarea maxima.

 - numarul de sufixe de lungime k (primit ca parametru la rulare) este calculat de functia void sufixe_k(Node *radacina, int k, int *nr, int len). 
 Practic, daca un sufix are lungimea k, atunci caracterul $ se va afla pe nivelul k in arborle de sufixe. Asadar, functia parcurge arborele pe niveluri
 si numara cate caractere $ apar pe nivelul k dat.


    Taskul 3:
 Verfica daca arborele format din anumite cuvinte primite in fisierul de intrare are sau nu in componenta sa un set de sufixe primite tot la intrare.
 Astfel daca un sufix apare deja in arborele de sufixe, inseamna ca daca as incerca sa l inserez din nou, nu se va schimba nimic la arbore (nu
 se va crea niciun nod nou in arbore). Astfel in functia void insert_word(Node *radacina, const char *cuvant, int k, FILE *out), verific daca se creeaza 
 sau nu un nod nou la apelarea functiei pentru sufixul curespunzator. Se va afisa 0, daca se modifica arborele si 1 in caz contar.

 
