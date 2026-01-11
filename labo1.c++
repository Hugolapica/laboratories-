#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

class Player {
private:
    int number;
public:
    string name;
    int height;

    Player(string n = "Unknown", int h = 0, int num = 0)
        : name(n), height(h), number(num) {}

    friend ostream& operator<<(ostream& os, const Player& p) {
        os << "[Player: " << p.name << ", H:" << p.height << ", #: " << p.number << "]";
        return os;
    }

    friend void modifyVector(vector<Player>& v, int val);
    
    bool operator<(const Player& other) const {
        return this->height < other.height;
    }
};

// 1.
template <typename T>
T Smaller(T a, T b) {
    return (a < b) ? a : b;
}

// 2.
template <typename T>
void modifyVector(vector<T>& v, int n);

// 2a.
template <>
void modifyVector(vector<string>& v, int n) {
    for (auto& s : v) {
        string original = s;
        for (int i = 1; i < n; ++i) {
            s += original;
        }
    }
}

// 2b.
template <>
void modifyVector(vector<Player>& v, int val) {
    for (auto& p : v) {
        p.number *= val;
    }
}

// 3.
template <typename T>
class Top3 {
private:
    T first, second, third;
public:
    Top3() : first(T()), second(T()), third(T()) {}
    Top3(T a, T b, T c) : first(a), second(b), third(c) {}

    void print() {
        cout << "Top3: 1." << first << " 2." << second << " 3." << third << endl;
    }
};

// 4.
template <typename T, int Size>
class Top {
protected:
    T top[Size];
    bool isSet[Size];
public:
    Top() {
        for (int i = 0; i < Size; ++i) isSet[i] = false;
    }

    void set(T obj, int pos) {
        if (pos >= 0 && pos < Size) {
            top[pos] = obj;
            isSet[pos] = true;
        } else {
            cout << "Posicion invalida." << endl;
        }
    }

    void remove(int pos) {
        if (pos >= 0 && pos < Size) {
            isSet[pos] = false;
        }
    }

    void print() {
        cout << "--- Contenido Top ---" << endl;
        for (int i = 0; i < Size; ++i) {
            if (isSet[i]) cout << "Pos " << i << ": " << top[i] << endl;
            else cout << "Pos " << i << ": [Vacio]" << endl;
        }
    }
};

// 5.
template <typename T, int Size, typename DescType>
class TopDescription : public Top<T, Size> {
private:
    DescType description;
public:
    TopDescription(DescType desc) : description(desc) {}
    
    void printDescription() {
        cout << "Descripcion: " << description << endl;
        this->print();
    }
};

// 6.
template <int Size>
class TopPlayers : public Top<Player, Size> {
private:
    int minHeight;

    void updateMinHeight() {
        minHeight = INT_MAX;
        bool any = false;
        for (int i = 0; i < Size; ++i) {
            if (this->isSet[i]) {
                if (this->top[i].height < minHeight) {
                    minHeight = this->top[i].height;
                }
                any = true;
            }
        }
        if (!any) minHeight = 0;
    }

public:
    TopPlayers() : minHeight(0) {}

    void set(Player obj, int pos) {
        Top<Player, Size>::set(obj, pos);
        updateMinHeight();
    }

    void remove(int pos) {
        Top<Player, Size>::remove(pos);
        updateMinHeight();
    }

    int smallest() {
        return minHeight;
    }
};

int main() {
    // 1.
    cout << Smaller(5, 10) << endl;
    cout << Smaller(3.14, 2.71) << endl;

    // 2.
    vector<string> sVec = {"a", "b"};
    modifyVector(sVec, 3);
    cout << sVec[0] << ", " << sVec[1] << endl;
    
    vector<Player> pVec = {Player("P1", 180, 10), Player("P2", 170, 20)};
    modifyVector(pVec, 5);
    cout << pVec[0] << ", " << pVec[1] << endl;

    // 3.
    Top3<int> FavoritesNumbers(7, 42, 100);
    FavoritesNumbers.print();

    Top3<Player> FavoritePlayers(Player("Messi", 170), Player("Ronaldo", 187), Player("Neymar", 175));
    FavoritePlayers.print();

    // 4.
    Top<double, 3> FavoriteDouble;
    FavoriteDouble.set(3.14, 0);
    FavoriteDouble.set(2.71, 2);
    FavoriteDouble.print();

    Top<Player, 30> TopPlayersObj;
    TopPlayersObj.set(Player("Alice", 160), 5);
    TopPlayersObj.print();

    // 5.
    TopDescription<Player, 5, string> Best("Top Players 2023");
    Best.set(Player("Bob", 190), 0);
    Best.printDescription();

    TopDescription<double, 20, Player> BestTimes(Player("Describer", 0));
    BestTimes.set(9.58, 0);

    // 6.
    TopPlayers<3> Shortest;
    Shortest.set(Player("Shorty", 150), 0);
    Shortest.set(Player("Tall", 200), 1);
    Shortest.set(Player("Medium", 175), 2);
    
    cout << Shortest.smallest() << endl;
    
    Shortest.remove(0);
    cout << Shortest.smallest() << endl;

    return 0;
}
