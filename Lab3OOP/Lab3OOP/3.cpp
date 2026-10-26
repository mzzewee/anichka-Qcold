#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

class Entry {
    string surname, name, phone;
    int day, month, year;
    static bool leap(int y) { return (y % 4 == 0 && y % 100 != 0) || y % 400 == 0; }
    static int daysIn(int m, int y) {
        static const int d[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
        return (m == 2 && leap(y)) ? 29 : d[m - 1];
    }
public:
    Entry() : day(0), month(0), year(0) {}
    Entry(const string& s, const string& n, const string& p, int d, int m, int y) : day(0), month(0), year(0) {
        setSurname(s); setName(n); setPhone(p); setBirthday(d, m, y);
    }
    Entry(const Entry& o) : surname(o.surname), name(o.name), phone(o.phone), day(o.day), month(o.month), year(o.year) {}
    Entry& operator=(const Entry& o) {
        if (this != &o) {
            surname = o.surname; name = o.name; phone = o.phone;
            day = o.day; month = o.month; year = o.year;
        }
        return *this;
    }
    ~Entry() {}

    void setSurname(const string& s) {
        if (s.empty()) throw invalid_argument("Surname is empty");
        surname = s;
    }
    void setName(const string& n) {
        if (n.empty()) throw invalid_argument("Name is empty");
        name = n;
    }
    void setPhone(const string& p) {
        size_t start = (!p.empty() && p[0] == '+') ? 1 : 0;
        if (p.size() - start < 7 || p.size() - start > 12) throw invalid_argument("Phone length is invalid");
        for (size_t i = start; i < p.size(); i++)
            if (p[i] < '0' || p[i] > '9') throw invalid_argument("Phone contains invalid characters");
        phone = p;
    }
    void setBirthday(int d, int m, int y) {
        if (y < 1900 || y > 2026) throw invalid_argument("Year is out of range");
        if (m < 1 || m > 12) throw invalid_argument("Month is out of range");
        if (d < 1 || d > daysIn(m, y)) throw invalid_argument("Day is out of range");
        day = d; month = m; year = y;
    }

    string getSurname() const { if (surname.empty()) throw runtime_error("Surname is not set"); return surname; }
    string getName() const { if (name.empty()) throw runtime_error("Name is not set"); return name; }
    string getPhone() const { if (phone.empty()) throw runtime_error("Phone is not set"); return phone; }
    int getDay() const { if (!day) throw runtime_error("Birthday is not set"); return day; }
    int getMonth() const { if (!month) throw runtime_error("Birthday is not set"); return month; }
    int getYear() const { if (!year) throw runtime_error("Birthday is not set"); return year; }

    long key() const { return year * 10000L + month * 100L + day; }
    bool operator<(const Entry& o) const { return key() < o.key(); }

    friend ostream& operator<<(ostream& os, const Entry& e) {
        return os << e.getSurname() << " " << e.getName() << ", " << e.getPhone() << ", "
            << e.getDay() << "." << e.getMonth() << "." << e.getYear();
    }
};

class Notebook {
    Entry* data;
    int count, cap;
    void grow() {
        cap *= 2;
        Entry* t = new Entry[cap];
        for (int i = 0; i < count; i++) t[i] = data[i];
        delete[] data;
        data = t;
    }
    void add(const Entry& e) {
        e.getSurname(); e.getName(); e.getPhone(); e.getYear();
        if (count == cap) grow();
        data[count++] = e;
    }
public:
    Notebook() : data(new Entry[4]), count(0), cap(4) {}
    Notebook(const Notebook& o) : data(new Entry[o.cap]), count(o.count), cap(o.cap) {
        for (int i = 0; i < count; i++) data[i] = o.data[i];
    }
    Notebook& operator=(const Notebook& o) {
        if (this != &o) {
            Entry* t = new Entry[o.cap];
            for (int i = 0; i < o.count; i++) t[i] = o.data[i];
            delete[] data;
            data = t; count = o.count; cap = o.cap;
        }
        return *this;
    }
    ~Notebook() { delete[] data; }

    int size() const { return count; }
    const Entry& operator[](int i) const {
        if (i < 0 || i >= count) throw out_of_range("Index is out of range");
        return data[i];
    }

    Notebook operator+(const Entry& e) const {
        Notebook r(*this);
        r.add(e);
        return r;
    }
    Notebook operator-(const string& surname) const {
        Notebook r(*this);
        int j = 0;
        for (int i = 0; i < r.count; i++)
            if (r.data[i].getSurname() != surname) r.data[j++] = r.data[i];
        if (j == r.count) throw runtime_error("Entry with this surname was not found");
        r.count = j;
        return r;
    }

    Notebook find(const string& surname) const {
        Notebook r;
        for (int i = 0; i < count; i++)
            if (data[i].getSurname() == surname) r.add(data[i]);
        if (r.count == 0) throw runtime_error("Nothing found by surname");
        return r;
    }
    Notebook find(int d, int m, int y) const {
        Notebook r;
        for (int i = 0; i < count; i++)
            if (data[i].getDay() == d && data[i].getMonth() == m && data[i].getYear() == y) r.add(data[i]);
        if (r.count == 0) throw runtime_error("Nothing found by birthday");
        return r;
    }

    void sortByBirthday() {
        for (int i = 0; i < count - 1; i++)
            for (int j = 0; j < count - 1 - i; j++)
                if (data[j + 1] < data[j]) {
                    Entry t;
                    t = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = t;
                }
    }

    friend ostream& operator<<(ostream& os, const Notebook& n) {
        if (n.count == 0) return os << "Notebook is empty" << endl;
        for (int i = 0; i < n.count; i++) os << i + 1 << ") " << n.data[i] << endl;
        return os;
    }
};

int main() {
    Notebook book;
    try {
        book = book + Entry("Shevchenko", "Taras", "380501112233", 9, 3, 2001);
        book = book + Entry("Kovalenko", "Olha", "+380672223344", 15, 7, 1999);
        book = book + Entry("Bondar", "Andrii", "380633334455", 2, 12, 2000);
        book = book + Entry("Kovalenko", "Ivan", "380504445566", 21, 1, 2002);

        cout << "Notebook:" << endl << book << endl;

        book.sortByBirthday();
        cout << "Sorted by birthday:" << endl << book << endl;

        cout << "Find by surname Kovalenko:" << endl << book.find("Kovalenko") << endl;
        cout << "Find by birthday 2.12.2000:" << endl << book.find(2, 12, 2000) << endl;

        book = book - "Bondar";
        cout << "After removing Bondar:" << endl << book << endl;
    }
    catch (const invalid_argument& e) { cout << "Invalid argument: " << e.what() << endl; }
    catch (const out_of_range& e) { cout << "Out of range: " << e.what() << endl; }
    catch (const exception& e) { cout << "Error: " << e.what() << endl; }

    try { book = book + Entry("Test", "User", "12ab", 1, 1, 2000); }
    catch (const invalid_argument& e) { cout << "Invalid argument: " << e.what() << endl; }

    try { book = book + Entry("Test", "User", "380501112233", 31, 2, 2000); }
    catch (const invalid_argument& e) { cout << "Invalid argument: " << e.what() << endl; }

    try { book.find("Unknown"); }
    catch (const exception& e) { cout << "Error: " << e.what() << endl; }

    try { Entry empty; cout << empty.getSurname(); }
    catch (const exception& e) { cout << "Error: " << e.what() << endl; }

    try { cout << book[10]; }
    catch (const out_of_range& e) { cout << "Out of range: " << e.what() << endl; }

    return 0;
}