#include <iostream>
#include <algorithm>

class Segment {
private:
    double left;  // левая граница отрезка
    double right; // правая граница отрезка

public:
    // Конструкторы
    Segment() : left(0), right(0) {}

    Segment(double start, double end) {
        setBounds(start, end);
    }

    Segment(const Segment& other) : left(other.left), right(other.right) {}

    // Установка границ отрезка
    void setBounds(double start, double end) {
        left = std::min(start, end);
        right = std::max(start, end);
    }

    double getLeft() const { return left; }
    double getRight() const { return right; }

    // Перегрузка унарного оператора !
    Segment operator!() const {
        return Segment(0, right);
    }

    // Неявное преобразование в int
    operator int() const {
        return static_cast<int>(right);
    }

    // Явное преобразование в double
    explicit operator double() const {
        return left;
    }

    // Перегрузка бинарного оператора +
    Segment operator+(int value) const {
        return Segment(left + value, right + value);
    }

    // Перегрузка оператора >
    bool operator>(const Segment& other) const {
        return left <= other.left && right >= other.right;
    }

    // Дружественный оператор вывода
    friend std::ostream& operator<<(std::ostream& os, const Segment& seg) {
        os << "[" << seg.left << ", " << seg.right << "]";
        return os;
    }

    // Статический метод для нахождения пересечения
    static Segment* findIntersection(const Segment& seg1, const Segment& seg2) {
        if (seg1.right < seg2.left || seg2.right < seg1.left) {
            return nullptr;
        }
        double newLeft = std::max(seg1.left, seg2.left);
        double newRight = std::min(seg1.right, seg2.right);
        return new Segment(newLeft, newRight);
    }
};

int main() {
    // Создание тестовых отрезков
    Segment s1(2.5, 7.8);
    Segment s2(4.0, 6.0);
    Segment s3(1.0, 10.0);

    std::cout << "Исходные отрезки:\n";
    std::cout << "s1: " << s1 << std::endl;
    std::cout << "s2: " << s2 << std::endl;
    std::cout << "s3: " << s3 << std::endl;

    // Демонстрация унарного оператора !
    std::cout << "\nПрименение оператора ! к s1:\n";
    Segment negSegment = !s1;
    std::cout << "!s1: " << negSegment << std::endl;

    // Демонстрация преобразования типов
    int intValue = s1;  // неявное преобразование в int
    double doubleValue = static_cast<double>(s1);  // явное преобразование в double
    std::cout << "\nПреобразования типов для s1:\n";
    std::cout << "В int: " << intValue << std::endl;
    std::cout << "В double: " << doubleValue << std::endl;

    // Демонстрация оператора +
    std::cout << "\nПрименение оператора + к s1:\n";
    Segment shiftedSegment = s1 + 3;
    std::cout << "s1 + 3: " << shiftedSegment << std::endl;

    // Демонстрация оператора >
    std::cout << "\nСравнение отрезков с помощью оператора >:\n";
    std::cout << "s3 > s1: " << (s3 > s1 ? "true" : "false") << std::endl;
    std::cout << "s1 > s2: " << (s1 > s2 ? "true" : "false") << std::endl;
    std::cout << "s2 > s3: " << (s2 > s3 ? "true" : "false") << std::endl;

    // Демонстрация метода findIntersection
    std::cout << "\nПересечение отрезков:\n";
    Segment* intersection = Segment::findIntersection(s1, s2);
    if (intersection) {
        std::cout << "Пересечение s1 и s2: " << *intersection << std::endl;
        delete intersection;
    } else {
        std::cout << "Отрезки s1 и s2 не пересекаются" << std::endl;
    }

    return 0;
}
