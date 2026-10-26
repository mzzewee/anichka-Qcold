#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Person {
protected:
    string surname, name;
    int age;
public:
    Person() : age(0) {}
    Person(const string& s, const string& n, int a) : surname(s), name(n), age(a) {}
    Person& operator=(const Person& o) {
        if (this != &o) { surname = o.surname; name = o.name; age = o.age; }
        return *this;
    }
    string fullName() const { return surname + " " + name; }
    int getAge() const { return age; }
    void show() const { cout << "Person: " << fullName() << ", age " << age << endl; }
    friend ostream& operator<<(ostream& os, const Person& p) {
        return os << p.surname << '\n' << p.name << '\n' << p.age << '\n';
    }
    friend istream& operator>>(istream& is, Person& p) {
        string a;
        getline(is, p.surname);
        getline(is, p.name);
        getline(is, a);
        p.age = a.empty() ? 0 : stoi(a);
        return is;
    }
};

class Student : public Person {
protected:
    string group;
    double avg;
public:
    Student() : avg(0) {}
    Student(const string& s, const string& n, int a, const string& g, double m) : Person(s, n, a), group(g), avg(m) {}
    Student& operator=(const Student& o) {
        if (this != &o) { Person::operator=(o); group = o.group; avg = o.avg; }
        return *this;
    }
    double getAvg() const { return avg; }
    void show() const {
        Person::show();
        cout << "Student: group " << group << ", average " << avg << endl;
    }
    friend ostream& operator<<(ostream& os, const Student& s) {
        os << static_cast<const Person&>(s);
        return os << s.group << '\n' << s.avg << '\n';
    }
    friend istream& operator>>(istream& is, Student& s) {
        string a;
        is >> static_cast<Person&>(s);
        getline(is, s.group);
        getline(is, a);
        s.avg = a.empty() ? 0 : stod(a);
        return is;
    }
};

class Graduate : public Student {
    string topic, supervisor;
public:
    Graduate() {}
    Graduate(const string& s, const string& n, int a, const string& g, double m, const string& t, const string& sv)
        : Student(s, n, a, g, m), topic(t), supervisor(sv) {
    }
    Graduate& operator=(const Graduate& o) {
        if (this != &o) { Student::operator=(o); topic = o.topic; supervisor = o.supervisor; }
        return *this;
    }
    void show() const {
        Student::show();
        cout << "Graduate: topic \"" << topic << "\", supervisor " << supervisor << endl;
    }
    friend ostream& operator<<(ostream& os, const Graduate& g) {
        os << static_cast<const Student&>(g);
        return os << g.topic << '\n' << g.supervisor << '\n';
    }
    friend istream& operator>>(istream& is, Graduate& g) {
        is >> static_cast<Student&>(g);
        getline(is, g.topic);
        getline(is, g.supervisor);
        return is;
    }
};

int main() {
    Person p("Shevchenko", "Taras", 45);
    Student s("Kovalenko", "Olha", 20, "KN-21", 88.5);
    Graduate g("Bondar", "Andrii", 22, "KN-41", 92.3, "Sorting algorithms analysis", "Melnyk O.P.");

    ofstream out("data.txt");
    if (!out.is_open()) {
        cout << "Cannot open file for writing" << endl;
        return 1;
    }
    out << p << s << g;
    out.close();

    Person p2;
    Student s2;
    Graduate g2;
    ifstream in("data.txt");
    if (!in.is_open()) {
        cout << "Cannot open file for reading" << endl;
        return 1;
    }
    in >> p2 >> s2 >> g2;
    in.close();

    cout << "Read from file:" << endl;
    p2.show();
    s2.show();
    g2.show();

    Student s3;
    s3 = g2;
    cout << endl << "After assignment Student = Graduate:" << endl;
    s3.show();

    cout << endl << "Inherited methods: " << g2.fullName() << ", age " << g2.getAge() << ", average " << g2.getAvg() << endl;
    return 0;
}