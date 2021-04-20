#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

class Point{
public:
    Point(){
        x = 0.0;
        y = 0.0;
    }
    Point(double x1, double y1) : x(x1), y(y1) {}
    double length(Point &p){
        return sqrt(pow(p.x - x,2) + pow(p.y - y,2));
    }
    friend istream &operator>>(istream &in, Point &p);
    friend ostream &operator<<(ostream &out, Point p);
    double x;
    double y;
};

istream &operator>>(istream &in, Point &p){
    in >> p.x;
    in >> p.y;
    return in;
}

ostream &operator<<(ostream &out, Point p){
    out << "(" << p.x << ";" << p.y << ");";
    return out;
}

class Figure{
public:
    Figure(){
        cout << "Creating figure..." << endl;
        name = "Unknown..";
    }
    ~Figure(){
        cout << "Deleting figure..." << endl;
    }
    vector<Point> vertices;
    string name;
    Point center(){
        double x_mid = 0, y_mid = 0;
        for (Point &p : vertices){
            x_mid += p.x;
            y_mid += p.y;
        }
        return Point(x_mid / vertices.size(),y_mid / vertices.size());
    }
    bool check_vertices(){
        double cur_len = vertices[0].length(vertices[vertices.size() - 1]);
        for (int i = 0; i < vertices.size() - 1; ++i){
            double fig_len = vertices[i].length(vertices[i + 1]);
            if (abs(fig_len - cur_len) >= 2e+1){
                cout << "Figure must have equal sides. Try again!" << endl;
                return false;
            }
            if (fig_len == 0){
                cout << "Points should be different. Try again!" << endl;
                return false;
            }
        }
        return true;
    }
    virtual double square() = 0;
    friend istream& operator>>(istream &in, Figure &figure);
    friend ostream& operator<<(istream &out, Figure &figure);
};

istream& operator>>(istream &in, Figure &figure){
    do{
        for (auto &vertex : figure.vertices){
            in >> vertex;
        }
    }while (!figure.check_vertices());

    return in;
}

ostream& operator<<(ostream &out, Figure &figure){
    out << figure.name << "{";
    for (Point &p : figure.vertices){
        out << p << " ";
    }
    out << "}";
    return out;
}

class Rectangle : public Figure{
public:
    Rectangle(){
        vertices.resize(4);
        name = "Rectangle";
        cout << "Rectangle is created!" << endl;
    }
    ~Rectangle(){
        cout << "Deleting Rectangle..." << endl << "Rectangle is successfully deleted!" << endl;
    }
    double square(){
        return vertices[0].length(vertices[1]) * vertices[1].length(vertices[2]);
    }
};

class Square : public Figure{
public:
    Square(){
        vertices.resize(4);
        name = "Square";
        cout << "Square is created!" << endl;
    }
    ~Square(){
        cout << "Deleting Square..." << endl << "Square is successfully deleted!" << endl;
    }
    double square(){
        return pow(vertices[0].length(vertices[1]),2);
    }
};

class Trapezoid : public Figure{
public:
    Trapezoid(){
        vertices.resize(4);
        name = "Trapezoid";
        cout << "Trapezoid is created!" << endl;
    }
    ~Trapezoid(){
        cout << "Deleting Trapezoid..." << endl << "Trapezoid is successfully deleted!" << endl;
    }
    double square(){
        double a = vertices[1].length(vertices[2]);
        double b = vertices[0].length(vertices[3]);
        double c = (vertices[0].length(vertices[1]));
        double p = (a + b + 2 * c) / 2;
        return sqrt((p - a) * (p - b) * pow((p - c),2));
    }
};

int main(){
    unsigned int amount;
    cout << "Enter the amount of figures you want to enter: " << endl;
    cin >> amount;

    vector<Figure *> figures;
    for (int i = 0; i < amount; ++i) {
        char type;
        do {
            cout << "Enter the type of figure (r - rectangle, t - trapezoid, s - square)" << endl;
            cin >> type;
            if (type != 'r' && type != 'R' && type != 't' && type != 'T' && type != 's' && type != 'S') {
                cout << "Incorrect type. Try again." << endl;
            }
        } while (type != 'r' && type != 'R' && type != 't' && type != 'T' && type != 's' && type != 'S');

        if (type == 'S' || type == 's') {
            auto *S = new Square;
            cout << "Enter vertices of this figure" << endl;
            cin >> *S;
            figures.push_back(S);
        } else if (type == 'T' || type == 't') {
            auto *T = new Trapezoid;
            cout << "Enter vertices of this figure" << endl;
            cin >> *T;
            figures.push_back(T);
        } else if (type == 'R' || type == 'r') {
            auto *R = new Rectangle;
            cout << "Enter vertices of this figure" << endl;
            cin >> *R;
            figures.push_back(R);
        }
    }
    cout << endl;

    double total_square = 0;
    cout << "List of figures:" << endl;
    for (auto &figure : figures) {
        cout << *figure << endl;
        double cur_square = figure->square();
        total_square += cur_square;
        cout << "Square: " << cur_square << endl;
        cout << "Center: " << figure->center() << endl;
        cout << endl;
    }
    cout << "Total square of figures is " << total_square << endl;
    cout << endl;

    unsigned int amount_delete;
    do {
        cout << "Enter the amount of figures you want to delete: " << endl;
        cin >> amount_delete;
        if (amount_delete > figures.size()) {
            cout << "Size of vector is less than your number. Try again" << endl;
        }
    } while (amount_delete > figures.size());
    cout << endl;

    for (int i = 0; i < amount_delete; ++i) {
        int id;
        do {
            cout << "Enter the id of figure you want to delete "
                         "(from " << 0 << " to " << figures.size() - 1 << "): " << endl;
            cin >> id;
            if (id < 0 || id >= figures.size()) {
                cout << "Wrong id. Try again" << endl;
            }
        } while (id < 0 || id >= figures.size());
        delete figures[id];
        figures.erase(figures.begin() + id);
    }
    cout << endl;

    cout << "List of remaining figures:" << endl;
    for (auto &figure : figures) {
        cout << *figure << endl;
        double cur_square = figure->square();
        total_square += cur_square;
        cout << "Square: " << cur_square << endl;
        cout << "Center: " << figure->center() << endl;
        cout << endl;
    }
    cout << endl;

    if (!figures.empty()) {
        cout << "Deleting remained figures:" << endl;
        for (auto &figure : figures) {
            delete figure;
        }
    }
    return 0;
}
