#include <bits/stdc++.h>
using namespace std;

// ---------- Data structures ----------
using Prod = vector<string>;                                // a production RHS sequence
unordered_map<string, vector<Prod>> G;                      // Grammar: A -> [ prod1, prod2, ... ]
unordered_set<string> NonT, Term;                           // Nonterminals, Terminals
unordered_map<string, unordered_set<string>> FIRST, FOLLOW; // FIRST(X), FOLLOW(A)
string Start;                                               // start symbol
const string EPS = "#";                                     // epsilon
const string END_MARK = "$";                                // end-marker for FOLLOW(start)

// ---------- Helpers ----------
static inline string trim(const string& s) {
    size_t i = s.find_first_not_of(" \t\r\n");
    if (i == string::npos) return "";
    size_t j = s.find_last_not_of(" \t\r\n");
    return s.substr(i, j - i + 1);
}

// Token rules:
// - Nonterminal: Uppercase letter followed by zero or more apostrophes, e.g., E, T', F''.
// - Terminal (multi-letter): a run of lowercase letters/digits (e.g., id, num).
// - Terminal (single-char): any punctuation like + * ( ) etc. (each one token).
// - EPSILON: "#"
static vector<string> tokenizeRHS(const string& s) {
    vector<string> tokens;
    for (size_t i = 0; i < s.size();) {
        char c = s[i];

        if (isspace((unsigned char)c)) { i++; continue; }

        if (c == '#') {                        // epsilon
            tokens.push_back(EPS);
            i++;
            continue;
        }

        if (isupper((unsigned char)c)) {       // Nonterminal possibly with primes
            string t(1, c);
            i++;
            while (i < s.size() && s[i] == '\'') { t.push_back('\''); i++; }
            tokens.push_back(t);
            continue;
        }

        if (islower((unsigned char)c) || isdigit((unsigned char)c)) { // multi-letter terminal (e.g., id, num)
            string t;
            while (i < s.size() && (islower((unsigned char)s[i]) || isdigit((unsigned char)s[i]) || s[i]=='_'))
                t.push_back(s[i++]);
            tokens.push_back(t);
            continue;
        }

        // Single char terminal (operators, parens, etc.)
        tokens.push_back(string(1, c));
        i++;
    }
    return tokens;
}

static bool isNonTerminalSym(const string& s) {
    return !s.empty() && isupper((unsigned char)s[0]);
}

// FIRST of a sequence β = Y1 Y2 ... Yk (using current FIRST map)
static unordered_set<string> firstOfSequence(const Prod& beta, size_t pos) {
    unordered_set<string> out;
    if (pos >= beta.size()) { out.insert(EPS); return out; }

    bool allEps = true;
    for (size_t i = pos; i < beta.size(); ++i) {
        const string& Y = beta[i];
        const auto& FY = FIRST[Y];
        // add FIRST(Y) \ {EPS}
        for (const auto& t : FY) if (t != EPS) out.insert(t);
        if (FY.find(EPS) == FY.end()) { allEps = false; break; }
    }
    if (allEps) out.insert(EPS);
    return out;
}

// ---------- Parsing input grammar ----------
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ifstream fin("input_23BDS1095.txt");
    if (!fin) {
        cerr << "Cannot open input_23BDS1095.txt\n";
        return 1;
    }

    string line;
    bool seenStart = false;

    vector<pair<string,string>> rawRules; // (LHS, RHS-string)
    while (getline(fin, line)) {
        line = trim(line);
        if (line.empty()) continue;

        // split at "->"
        size_t pos = line.find("->");
        if (pos == string::npos) {
            cerr << "Malformed rule (missing '->'): " << line << "\n";
            return 1;
        }
        string LHS = trim(line.substr(0, pos));
        string RHS = trim(line.substr(pos + 2));

        if (LHS.empty()) {
            cerr << "Empty LHS: " << line << "\n";
            return 1;
        }
        // LHS should be a single nonterminal token (like E or E')
        auto lhsTokens = tokenizeRHS(LHS);
        if (lhsTokens.size() != 1 || !isNonTerminalSym(lhsTokens[0])) {
            cerr << "LHS must be a single nonterminal (e.g., E or E'): " << LHS << "\n";
            return 1;
        }
        string A = lhsTokens[0];

        if (!seenStart) { Start = A; seenStart = true; }
        NonT.insert(A);

        rawRules.push_back({A, RHS});
    }
    fin.close();

    // Build grammar G from raw rules (split RHS by '/' or '|', then tokenize each alternative)
    for (auto& rr : rawRules) {
        const string& A = rr.first;
        string RHS = rr.second;

        // Normalize separators: treat '|' same as '/'
        for (char& c : RHS) if (c == '|') c = '/';

        // Split by '/'
        string alt;
        stringstream ss(RHS);
        vector<string> alts;
        while (getline(ss, alt, '/')) {
            alt = trim(alt);
            if (!alt.empty()) alts.push_back(alt);
        }
        if (alts.empty()) { // allow empty RHS? No, but handle gracefully
            alts.push_back(EPS);
        }

        for (const string& a : alts) {
            auto tokens = tokenizeRHS(a);
            if (tokens.size() == 1 && tokens[0] == EPS) {
                // epsilon production
                G[A].push_back(Prod{}); // empty RHS represents epsilon
            } else {
                G[A].push_back(tokens);
            }
        }
    }

    // Collect terminals by scanning RHS tokens
    for (auto& [A, prods] : G) {
        for (auto& rhs : prods) {
            if (rhs.empty()) continue; // epsilon
            for (auto& sym : rhs) {
                if (!isNonTerminalSym(sym) && sym != EPS)
                    Term.insert(sym);
            }
        }
    }

    // Initialize FIRST sets
    // - For terminals: FIRST(a) = {a}
    // - For epsilon:   FIRST(#) = {#}
    for (const auto& a : Term) FIRST[a].insert(a);
    FIRST[EPS].insert(EPS);
    for (const auto& A : NonT) FIRST[A]; // ensure key exists

    // Compute FIRST by fixed-point iteration
    bool changed = true;
    while (changed) {
        changed = false;
        for (const auto& [A, prods] : G) {
            auto& FA = FIRST[A];
            size_t before = FA.size();

            for (const auto& rhs : prods) {
                if (rhs.empty()) { // epsilon production
                    FA.insert(EPS);
                    continue;
                }
                bool allEps = true;
                for (size_t i = 0; i < rhs.size(); ++i) {
                    const auto& Y = rhs[i];
                    const auto& FY = FIRST[Y];
                    // add FIRST(Y) \ {EPS}
                    for (const auto& t : FY) if (t != EPS) FA.insert(t);
                    if (FY.find(EPS) == FY.end()) { allEps = false; break; }
                }
                if (allEps) FA.insert(EPS);
            }

            if (FA.size() != before) changed = true;
        }
    }

    // Initialize FOLLOW sets
    for (const auto& A : NonT) FOLLOW[A];       // ensure keys exist
    FOLLOW[Start].insert(END_MARK);             // $ in FOLLOW(start)

    // Compute FOLLOW by fixed-point iteration
    changed = true;
    while (changed) {
        changed = false;
        for (const auto& [A, prods] : G) {
            for (const auto& rhs : prods) {
                for (size_t i = 0; i < rhs.size(); ++i) {
                    const string& B = rhs[i];
                    if (!isNonTerminalSym(B)) continue;

                    // β = rhs[i+1 .. end]
                    Prod beta;
                    for (size_t j = i + 1; j < rhs.size(); ++j) beta.push_back(rhs[j]);

                    auto FBeta = firstOfSequence(beta, 0);
                    size_t before = FOLLOW[B].size();

                    // Add FIRST(β) \ {EPS} to FOLLOW(B)
                    for (const auto& t : FBeta) if (t != EPS) FOLLOW[B].insert(t);

                    // If β ⇒* EPS, add FOLLOW(A) to FOLLOW(B)
                    if (FBeta.find(EPS) != FBeta.end() || beta.empty()) {
                        const auto& FAA = FOLLOW[A];
                        FOLLOW[B].insert(FAA.begin(), FAA.end());
                    }

                    if (FOLLOW[B].size() != before) changed = true;
                }
            }
        }
    }

    // Write output
    ofstream fout("output_23BDS1095.txt");
    if (!fout) {
        cerr << "Cannot open output_23BDS1095.txt for writing\n";
        return 1;
    }

    auto printSet = [&](const unordered_set<string>& S) {
        vector<string> v(S.begin(), S.end());
        sort(v.begin(), v.end(), [](const string& a, const string& b){
            // Put EPS last within FIRST, and $ last within FOLLOW for readability if equal length
            if (a == EPS && b != EPS) return false;
            if (b == EPS && a != EPS) return true;
            if (a == END_MARK && b != END_MARK) return false;
            if (b == END_MARK && a != END_MARK) return true;
            return a < b;
        });
        fout << "{ ";
        for (size_t i = 0; i < v.size(); ++i) {
            if (i) fout << ", ";
            fout << v[i];
        }
        fout << " }";
    };

    // Deterministic order of nonterminals in output
    vector<string> nts(NonT.begin(), NonT.end());
    sort(nts.begin(), nts.end());

    fout << "FIRST and FOLLOW Sets:\n\n";
    for (const auto& A : nts) {
        fout << "FIRST(" << A << ") = ";
        printSet(FIRST[A]);
        fout << "\n";

        fout << "FOLLOW(" << A << ") = ";
        printSet(FOLLOW[A]);
        fout << "\n\n";
    }
    fout.close();

    cout << "FIRST and FOLLOW sets computed successfully. See output_23BDS1095.txt\n";
    return 0;
}