#include <bits/stdc++.h>
using namespace std;

// === Хувийн бутархай (Fraction) class ===
class flo {
private:
    int numerator, denominator;

    int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

    void simplify() {
        int _gcd = gcd(numerator, denominator);
        numerator /= _gcd;
        denominator /= _gcd;
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

public:
    flo(int num = 0, int denom = 1) {
        if (denom == 0) throw invalid_argument("Denominator cannot be zero!");
        numerator = num;
        denominator = denom;
        simplify();
    }

    int getNumerator() const { return numerator; }
    int getDenominator() const { return denominator; }

    void print() const {
        printf(" %d", numerator);
        if (denominator != 1) printf("/%d", denominator);
    }

    // Үйлдлүүд
    flo operator+(const flo &other) const {
        return flo(numerator * other.denominator + other.numerator * denominator, denominator * other.denominator);
    }

    flo operator-(const flo &other) const {
        return flo(numerator * other.denominator - other.numerator * denominator, denominator * other.denominator);
    }

    flo operator*(const flo &other) const {
        return flo(numerator * other.numerator, denominator * other.denominator);
    }

    flo operator/(const flo &other) const {
        if (other.numerator == 0) throw invalid_argument("Cannot divide by zero!");
        return flo(numerator * other.denominator, denominator * other.numerator);
    }

    bool operator==(const flo &other) const {
        return numerator == other.numerator && denominator == other.denominator;
    }

    bool operator!=(const flo &other) const { return !(*this == other); }

    bool operator<(const flo &other) const {
        return (static_cast<long long>(numerator) * other.denominator) < 
               (static_cast<long long>(other.numerator) * denominator);
    }

    bool operator>(const flo &other) const { return other < *this; }
    bool operator<=(const flo &other) const { return !(other < *this); }
    bool operator>=(const flo &other) const { return !(*this < other); }

    friend ostream &operator<<(ostream &os, const flo &f) {
        os << f.numerator;
        if (f.denominator != 1) os << "/" << f.denominator;
        return os;
    }
};

// === Matrix-ийн нэг нүд (item) ===
struct item {
    string x;
    int index;
    flo val;
};

// === Тээвэрлэлтийн class ===
class teever {
private:
    int n, m;
    int isMax;
    int nuutsiluudel = 0;
    pair<int, int> last_selected;
    const flo ZERO = flo(0, 1);

    string cellToString(item &it, int i, int j, int m) {
        ostringstream oss;
        if (it.x == "c") {
            if (i == 0 && j == m) {
                oss << it.x;
            } else {
                oss << it.val;
            }
        } else {
            if (it.val < ZERO) oss << "-";
            oss << it.x << it.index;
        }
        return oss.str();
    }

    vector<size_t> computeColumnWidths(const vector<vector<string>> &table) {
        vector<size_t> widths(table[0].size(), 0);
        for (const auto &row : table)
            for (size_t j = 0; j < row.size(); j++)
                widths[j] = max(widths[j], row[j].size());
        return widths;
    }

    void printBorder(const vector<size_t> &widths) {
        cout << "+";
        for (auto w : widths) cout << string(w + 2, '-') << "+";
        cout << "\n";
    }

    void printTable(const vector<vector<string>> &table) {
        auto widths = computeColumnWidths(table);
        printBorder(widths);
        for (const auto &row : table) {
            cout << "|";
            for (size_t j = 0; j < row.size(); j++)
                cout << " " << setw(widths[j]) << left << row[j] << " |";
            cout << "\n";
            printBorder(widths);
        }
    }

    void print(vector<vector<item>> &arr) {
        vector<vector<string>> table;
        for (int i = 0; i < n; i++) {
            vector<string> row;
            for (int j = 0; j < m; j++) {
                row.push_back(cellToString(arr[i][j], i, j, m));
            }
            table.push_back(row);
        }
        printTable(table);
    }

    // === Матрицыг хэрэглэгчээс авах ===
    void get_matrix(vector<vector<item>> &arr) {
        flo nuuts = ZERO, heregtsee = ZERO;

        printf("=> Kheregtseeg oruulna uu (destination-iin shaardalagtai):\n");
        for (int i = 1; i < m; i++) {
            int a; scanf("%d", &a);
            flo el(a, 1);
            arr[0][i].val = el;
            heregtsee = heregtsee + el;
        }

        printf("=> Nuutsiig oruulna uu (source-iin khuchin chadal):\n");
        for (int i = 1; i < n; i++) {
            int a; scanf("%d", &a);
            flo el(a, 1);
            arr[i][0].val = el;
            nuuts = nuuts + el;
        }

        printf("=> Niit khereglee ="); heregtsee.print();
        printf(", Niit nuuts ="); nuuts.print(); printf("\n");

        if (heregtsee < nuuts) {
            arr[0][m++].val = nuuts - heregtsee;
            nuutsiluudel = 1;
            printf("=> Nuuts iluudeltei tul nemelt bagana (dummy column) uusgev.\n");
        }

        printf("=> Zardliin matrixiig oruulna uu (unit cost from i to j):\n");
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < m; j++) {
                if (nuutsiluudel && j == m - 1) continue;
                int a; scanf("%d", &a);
                arr[i][j].val = flo(a, 1);
            }
        }
    }

public:
    teever(int equation, int variables) {
        n = equation;
        m = variables;
        last_selected = {-1, -1};
    }

    // === Тулгуур аргаар бодох ===
    void tulguur() {
        vector<vector<item>> arr(n, vector<item>(m + 1, {"c", 0, flo(0, 1)}));
        get_matrix(arr);
        print(arr);

        flo cost = flo(0, 1);
        int i = 1;

        for (int j = 1; j < m; j++) {
            while (i < n && arr[i][0].val <= arr[0][j].val) {
                cost = cost + (arr[i][j].val * arr[i][0].val);
                arr[0][j].val = arr[0][j].val - arr[i][0].val;
                arr[i][0].val = flo(0, 1);
                printf("=> Shiidliin yavts:\n");
                print(arr);
                i++;
            }

            if (i == n) break;

            cost = cost + (arr[i][j].val * arr[0][j].val);
            arr[i][0].val = arr[i][0].val - arr[0][j].val;
            arr[0][j].val = flo(0, 1);
            printf("=> Shiidliin yavts:\n");
            print(arr);
        }

        printf("=> Niit zardal Z =");
        cost.print(); printf("\n");
    }
};

// === Гол функц ===
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int t;
    printf("=> Shiidekh bodlogiin toog oruulna uu:\n");
    scanf("%d", &t);

    for (int i = 1; i <= t; i++) {
        printf("\n\n=> %d. Shine bodlogo:\n", i);
        printf("=>Ilgeekh gazriin too bolon khuleen abakh gazriin toog oruulna uu:\n");
        int n, m; scanf("%d %d", &n, &m);
        teever T(n + 1, m + 1);
        T.tulguur();
    }

    return 0;
}
