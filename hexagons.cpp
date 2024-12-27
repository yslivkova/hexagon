#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Shape2D {
private:
    string name;
    bool hasColour;
public:
    Shape2D(string, bool);
    void set_name(string n) { name = n; };
    void set_hasColour(bool c) { hasColour = c; };
    string getName() { return name; };
    bool getHasColour() { return hasColour; };
    void display_s();
    virtual double perimeter() const = 0;
};

Shape2D::Shape2D(string n, bool c)
{
    name = n; hasColour = c;
}

void Shape2D::display_s()
{
    cout << "Name: " << name << ", Has Colour: " << (hasColour ? "Yes" : "No") << endl;
}

class RegularHexagon : public Shape2D
{
private:
    double sideLength;
public:
    void set_sideLength(double l) { sideLength = l; };
    double getSideLength() { return sideLength; }
    RegularHexagon(string n, bool c, double l);
    void display_h();
    double perimeter() const {
        return 6 * sideLength;
    }
};

RegularHexagon::RegularHexagon(string n, bool c, double l) : Shape2D(n, c) {
    sideLength = l;
}

void RegularHexagon::display_h() {
    display_s();
    cout << "Side length: " << sideLength << ", Perimeter: " << perimeter() << endl;
}

int main() {
    const int MAX_HEXAGONS = 50;
    vector <RegularHexagon> hexagons;
    int n;
    cout << "Enter the number of hexagons (<=50): ";
    cin >> n;
    if (n > MAX_HEXAGONS) {
        cout << "Too many hexagons!" << endl;
        return 1;
    }
    for (int i = 0; i < n; ++i) {
        string name;
        bool hasColour;
        double sideLength;
        cout << "Enter name, Colour (1/0) and side length for hexagon " << i + 1 << ": ";
        cin >> name;
        while (true) {
            cin >> hasColour;
            if (hasColour == 0 || hasColour == 1) {
                break;
            }
            else {
                cout << "Invalid input for Colour. Please enter 1 (Yes) or 0 (No): ";
            }
        }
        cin >> sideLength;
        hexagons.emplace_back(name, hasColour, sideLength);
    }

    cout << "\nHexagon Details:\n";
    for (auto& hexagon : hexagons) {
            hexagon.display_h();
    }

    double maxPerimeter = 0;
    RegularHexagon* largestHexagon = nullptr;
    for (auto& hexagon : hexagons) {
        if (hexagon.perimeter() > maxPerimeter) {
            maxPerimeter = hexagon.perimeter();
            largestHexagon = &hexagon;
        }
    }

    cout << "\nTotal Hexagons: " << hexagons.size() << endl;
    if (largestHexagon) {
        cout << "Hexagon with the largest perimeter:\n";
        largestHexagon->display_h();
    }

    return 0;
}
