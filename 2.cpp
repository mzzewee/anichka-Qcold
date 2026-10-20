#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Library {
private:
    string title, theme, actors, fileName, date;
    float rating, playSpeed;
    int length;

public:
    Library() {
        rating = 0; playSpeed = 1; length = 0;
    }

    Library(string t, string th, string a, float r, int len, float sp, string f, string d) {
        title = t; theme = th; actors = a; rating = r;
        length = len; playSpeed = sp; fileName = f; date = d;
    }

    ~Library() {}

    string getTitle() const { return title; }
    string getTheme() const { return theme; }
    string getActors() const { return actors; }
    float getRating() const { return rating; }
    int getLength() const { return length; }
    float getPlaySpeed() const { return playSpeed; }
    string getFileName() const { return fileName; }
    string getDate() const { return date; }

    void print() const {
        cout << "Title: " << title << "\n";
        cout << "Theme: " << theme << "\n";
        cout << "Actors: " << actors << "\n";
        cout << "Rating: " << rating << "\n";
        cout << "Length: " << length << " min\n";
        cout << "Speed: " << playSpeed << "\n";
        cout << "File: " << fileName << "\n";
        cout << "Date: " << date << "\n";
        cout << "------------------\n";
    }
};

class Player {
private:
    vector<Library> movies;

public:
    Player() {}
    ~Player() {}

    void addMovie(const Library& m) {
        movies.push_back(m);
    }

    void printAll() const {
        for (size_t i = 0; i < movies.size(); i++)
            movies[i].print();
    }

    void searchByTitle(const string& query) const {
        cout << "Search by title: " << query << "\n";
        for (size_t i = 0; i < movies.size(); i++)
            if (movies[i].getTitle().find(query) != string::npos)
                movies[i].print();
    }

    void searchByActor(const string& query) const {
        cout << "Search by actor: " << query << "\n";
        for (size_t i = 0; i < movies.size(); i++)
            if (movies[i].getActors().find(query) != string::npos)
                movies[i].print();
    }

    void searchByTheme(const string& query) const {
        cout << "Search by theme: " << query << "\n";
        for (size_t i = 0; i < movies.size(); i++)
            if (movies[i].getTheme().find(query) != string::npos)
                movies[i].print();
    }
};

int main() {
    Player player;

    player.addMovie(Library("Matrix", "SciFi", "Keanu Reeves", 9.0f, 136, 1.0f, "matrix.mp4", "1999"));
    player.addMovie(Library("Inception", "SciFi", "Leonardo DiCaprio", 8.8f, 148, 1.0f, "inception.mp4", "2010"));
    player.addMovie(Library("Titanic", "Drama", "Leonardo DiCaprio", 7.9f, 195, 1.0f, "titanic.mp4", "1997"));

    cout << "ALL MOVIES:\n";
    player.printAll();

    player.searchByActor("Leonardo DiCaprio");
    player.searchByTitle("Matrix");
    player.searchByTheme("Drama");

    return 0;
}