# PA - TEMA 2 - GIGEL, MEREU OCUPAT -
### Stefan Diana Maria - 322CC

## SUPERCOMPUTER

 - Am folosit ca punct de start implementarea `sortarii topologice` din laborator, avand insa ***doua cozi***, una pentru taskurile cu setul de date 1, iar cealalta pentru setul de date 2. Initial, se adauga in cozi taskurile care sunt deja gata sa fie rulate. Apoi, se scoate cate un nod si se scade numarul de conditii ce mai trebuie indeplinite al fiecarui task ce depinde de cel curent si se adauga noile noduri gata in cozi (vectorul `ready` retine ***gradul intern*** al nodurilor).
 - Din moment ce se doreste un ***numar minim de context switchuri***, se scot din coada toate nodurile cu acelasi set de date ca cel curent, dupa care se trece la cealalta coada, realizandu-se un `context switch`. Se realizeaza aceasta parcurgere de doua ori, o data pornind cu setul de date 1 si o data cu setul de date 2.
 - La sfarsit de afiseaza ***minimul*** dintre rezultate.

Complexitate: `O(n + m)`

## CAI FERATE

 - Am folosit ca punct de start implementarea algoritmului `Tarjan` din laborator, care genereaza multimea de `componente tare conexe` a grafului. Numarul de arce care ar trebui adaugate pentru a se putea ajunge din sursa in orice alt nod este numarul de `SCC`, eliminand componenta care contine ***nodul sursa*** si componentele la care se poate ajunge dintr-o alta componenta.
 - Am folosit o `lista de adiacenta` pentru arcurile ce intra in fiecare nod (`adj_int`). 
 - Astfel, pentru fiecare componenta, daca in ea exista un nod care are in `adj_int` un nod care nu apartine acelei componente, se scade o muchie din numarul celor care trebuie adaugate. 

Complexitate: `O(n + m + n * m) = O(n * m)`

## TELEPORTARE

 - Am folosit ca punct de start implementarea algoritmului `Dijkstra` din laborator, inlocuid perechile `{node, weight}` cu tupluri `{node, weight, period}`.
 - In momentul cand s-ar dori adaugarea unui drum, se verifica si daca distanta parcursa pana in acel moment este un `multiplu de P`.

Complexitate: `O(m ∗ logn)`

## MAGAZIN

 - Am folosit ca punct de start implementarea algoritmului de `DFS` din laborator, adaugand si un vector `dfs_indexes`, care contine indexul fiecarui nod in dfs. Numarul de ***descendenti*** ai unui nod poate fi calculat prin formula: `(finish[nod] - start[nod] - 1) / 2`. 
 - In cazul in care numarul de descendenti este mai mic decat numarul de expedieri, acestea nu se pot realiza si se afiseaza `-1`.
 - In caz contrar, se adauga numarul de expedieri la pozitia ***nodului de start***, in dfs.

Complexitate: `O(n + m + Q)`
