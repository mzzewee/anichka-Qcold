#include <iostream>
#include <string>
using namespace std;

class Parent {
protected:
    string name;
public:
    Parent(const string& n) : name(n) {}
    virtual void printName() const {
        cout << "Parent: " << name << endl;
    }
    virtual ~Parent() {}
};

class Child : public Parent {
    string childName;
    string patronymic;
public:
    Child(const string& parentName, const string& n)
        : Parent(parentName), childName(n), patronymic(parentName + "ovych") {
    }
    void printName() const override {
        cout << "Child: " << childName << " " << patronymic << endl;
    }
};

int main() {
    for (int i = 1; i <= 2; i++) {
        string pn, cn;
        cout << "Set " << i << endl;
        cout << "Parent name: ";
        cin >> pn;
        cout << "Child name: ";
        cin >> cn;

        Parent p(pn);
        Child c(pn, cn);

        Parent* ptr = &p;
        ptr->printName();
        ptr = &c;
        ptr->printName();

        Parent& ref = c;
        ref.printName();

        Parent obj = c;
        obj.printName();
        cout << endl;
    }
    return 0;
}