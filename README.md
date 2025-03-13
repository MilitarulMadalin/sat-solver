# SAT Solver

Acest program implementeaza un **solver SAT** folosind algoritmul **DPLL (Davis-Putnam-Logemann-Loveland)**. Scopul sau este de a rezolva probleme de satisfiabilitate logica (SAT) reprezentate in **formatul DIMACS CNF**. Programul poate determina daca o formula booleana (forma unei conjunctii de clauze) este satisfiabila sau nu si poate furniza o atribuire a variabilelor care face formula adevarata, in cazul in care aceasta este satisfiabila.

---

## Algoritmul folosit

### Algoritmul DPLL

Programul implementeaza algoritmul **DPLL**, care este un algoritm recursiv pentru rezolvarea problemelor SAT. DPLL este o imbunatatire a algoritmului de cautare a solutiilor prin backtracking si include optimizari precum **propagarea unitatilor**.

### Propagarea unitatilor

**Propagarea unitatilor** este o tehnica prin care, daca o clauza contine un singur literal neatribuit, acest literal poate fi atribuit automat pentru a satisface clauza respectiva. Aceasta poate duce la simplificarea semnificativa a problemei, reducand numarul de variabile neatribuite.

### Backtracking

In cazul in care **propagarea unitatilor** nu ajuta la rezolvarea problemei, algoritmul **backtrackeaza**, adica incearca sa atribuie valori variabilelor neatribuite. Daca o atribuire nu duce la o solutie satisfiabila, algoritmul revine asupra alegerii facute si incearca o alta valoare.
