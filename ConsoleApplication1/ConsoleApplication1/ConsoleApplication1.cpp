#include <iostream> 
#include <cmath>
#include <vector> 
#include <iomanip>

using namespace std;

class IsoscelesTriangle {
private:
    double side; // боковая сторона
    double angle; // угол при основани

public:
    // конструктор
    IsoscelesTriangle(double s = 1, double ang = 60) {
        if (!setProperties(s, ang)) {
            side = 1;
            angle = 60;
        }
    }
    // установка свойств и проверка
    bool setProperties(double s, double ang) {
        if (s <= 0) {
            cout << "Ошибка: Боковая сторона должна быть положительной!\n";
            return false;
        }
        if (ang <= 0 || ang >= 90) {
            cout << "Ошибка: угол должен быть в приделах (0;90) градусов!\n";
            return false;
        }
        side = s;
        angle = ang;
        return true;
    }
    void input() {
        double s, ang;
        bool ok = false;
        while (!ok) {
            cout << "Введите боковую сторону: ";
            cin >> s;
            cout << "ВВедите угол при основании в градусах: ";
            cin >> ang;
            ok = setProperties(s, ang);
            if (!ok) {
                cout << "Введите еще раз\n\n";
            }
        }
    }
    //масштабирование
    void scale(double k) {
        if (k <= 0) {
            cout << "Ошибка: коэффициент должен быть > 0!\n";
            return;
        }
        side *= k;
    }
    //получение сторон
    void getSides(double& a, double& b) const {
        a = side;

        double rad = angle * 3.14 / 180.0;
        b = 2 * side * cos(rad / 2.00);
    }
    //длина биссектрисы
    double bisectorLength(string which) const {
        double a, b;
        getSides(a, b);
        double rad = angle * 3.14 / 180.0;

        if (which == "1") {
            return sqrt(a * a + (b / 2) * (b / 2) - a * b * cos(rad / 2));
        }
        else if (which == "2") {
            return sqrt(a * a + a * a - 2 * a * a * cos(angle * 3.14 / 360.0));
        }
        return -1;
    }
    //длина высоты
    double heightTo(string sideName) const {
        double a, b;
        getSides(a, b);
        double rad = angle * 3.14 / 180.0;

        if (sideName == "1") {
            return a * sin(rad / 2.0);
        }
        else if (sideName == "2") {
            double area = 0.5 * b * (a * sin(rad / 2.0));
            return (2 * area) / a;
        }
        return -1;
    }
    //вывод свойств
    void print() const {
        double a, b;
        getSides(a, b);
        cout << fixed << setprecision(2);
        cout << "Боковая сторона = " << a
            << ", основание = " << b
            << ", угол при основании = " << angle << endl;
    }
    void showBisectors() const {
        cout << "  Биссектриса при основании = " << bisectorLength("1") << endl;
        cout << "  Биссектриса при вершине   = " << bisectorLength("2") << endl;
    }

    void showHeights() const {
        cout << "  Высота к основанию        = " << heightTo("1") << endl;
        cout << "  Высота к боковой стороне  = " << heightTo("2") << endl;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    int n;
    cout << "Введите количество треугольников: ";
    cin >> n;

    vector<IsoscelesTriangle> triangles(n);
    for (int i = 0; i < n; i++) {
        cout << "\nТреугольник " << i + 1 << ":\n";
        triangles[i].input();
    }

    int choice;
    do {
        cout << "\nМеню:\n";
        cout << "1. Масштабировать треугольник\n";
        cout << "2. Вычислить биссектрису\n";
        cout << "3. Вычислить высоту\n";
        cout << "4. Вывести стороны треугольников\n";
        cout << "0. Выход\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        if (choice == 0) break;

        int idx;
        cout << "Введите номер треугольника (1.." << n << "): ";
        cin >> idx;
        if (idx < 1 || idx > n) {
            cout << "Ошибка нверный индекс\n";
            continue;
        }
        IsoscelesTriangle& t = triangles[idx - 1];

        switch (choice) {
        case 1: {
            double k;
            cout << "Введите во сколько раз увеличить/уменьшить треугольник: ";
            cin >> k;
            t.scale(k);
            cout << "Измененный треуголник: ";
            t.print();
            break;
        }
        case 2: {
            string which;
            cout << "Биссектриса угла при основании (1) / при вершине (2): ";
            cin >> which;
            double res = t.bisectorLength(which);
            if (res > 0)
                cout << "Длина биссектрисы = " << res << endl;
            break;
        }
        case 3: {
            string side;
            cout << "Введите сторону (основание (1)/боковая (2)): ";
            cin >> side;
            double res = t.heightTo(side);
            if (res > 0)
                cout << "Длина высоты = " << res << endl;
            break;
        }
        case 4: {
            double a, b;
            t.getSides(a, b);
            cout << "Боковая сторона = " << a << ", основание = " << b << endl;
            break;
        }
        default:
            cout << "Ошибка: неверный пункт меню\n";
        }
    } while (choice != 0);
    cout << "Программа завершена\n";
    return 0;

}
