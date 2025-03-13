#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

struct Clause {
    vector<int> literals;
};

struct Formula {
    int num_vars;
    int num_clauses;
    vector<Clause> clauses;
};

bool read_dimacs(const string &filename, Formula &cnf) {
    ifstream in(filename);
    string line;
    while (getline(in, line)) {
        if (line[0] != 'c') {
            if (line[0] == 'p') {
                istringstream iss(line);
                string tmp;
                iss >> tmp >> tmp >> cnf.num_vars >> cnf.num_clauses;
            } else {
                Clause clause;
                istringstream iss(line);
                int literal;
                while (iss >> literal && literal != 0) {
                    clause.literals.push_back(literal);
                }
                cnf.clauses.push_back(clause);
            }
        }
    }
    return true;
}

bool is_clause_satisfied(const Clause &clause, const vector<int> &assignment) {
    for (int literal : clause.literals) {
        int var = abs(literal) - 1;
        if ((literal > 0 && assignment[var] == 1) || (literal < 0 && assignment[var] == 0)) {
            return true;
        }
    }
    return false;
}

bool unit_propagation(Formula &cnf, vector<int> &assignment) {
    bool changed = true;
    while (changed) {
        changed = false;
        for (size_t i = 0; i < cnf.clauses.size(); ++i) {
            Clause &clause = cnf.clauses[i];
            if (is_clause_satisfied(clause, assignment)) 
                continue;

            int unassigned_count = 0, last_unassigned = 0;
            for (int literal : clause.literals) {
                int var = abs(literal) - 1;
                if (assignment[var] == -1) {
                    unassigned_count++;
                    last_unassigned = literal;
                } 
            }
            
            if (unassigned_count == 1) { 
                int var = abs(last_unassigned) - 1;
                if (assignment[var] == -1) {
                    assignment[var] = (last_unassigned > 0) ? 1 : 0;
                    changed = true;
                }
            }
        }
    }
    return true;
}

bool dpll(Formula &cnf, vector<int> &assignment) {
    if (!unit_propagation(cnf, assignment)) {
        return false;
    }

    bool satisfied = true;
    for (size_t i = 0; i < cnf.clauses.size(); ++i) {
        Clause &clause = cnf.clauses[i];
        if (!is_clause_satisfied(clause, assignment)) {
            satisfied = false;
            break;
        }
    }
    if (satisfied) {
        return true; 
    }

    for (int i = 0; i < cnf.num_vars; i++) {
        if (assignment[i] == -1) {
            vector<int> buffer = assignment;
            assignment[i] = 1;
            if (dpll(cnf, assignment)) 
                return true;

            assignment = buffer;
            assignment[i] = 0;
            if (dpll(cnf, assignment)) 
                return true;
        }
    }
    return false;
}

int main(int argc, char *argv[]) {
    Formula cnf;
    read_dimacs(argv[1], cnf);

    vector<int> assignment(cnf.num_vars, -1);
    bool result = dpll(cnf, assignment);

    ofstream out(argv[2]);

    if (result) {
        out << "s SATISFIABLE\nv ";
        for (int i = 1; i <= cnf.num_vars; ++i) {
            int var_output = (assignment[i - 1] == 1) ? i : -i;
            out << var_output << " ";
        }
        out << "0\n";
    } else {
        out << "s UNSATISFIABLE\n";
    }

    return 0;
}
