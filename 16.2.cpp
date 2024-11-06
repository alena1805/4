#include <iostream>
#include <algorithm>

class LineSegment {
private:
    double x1; // левая граница отрезка
    double x2; // правая граница отрезка

public:
    // Конструкторы остаются без изменений
    LineSegment() : x1(0), x2(0) {}
    
    LineSegment(double start, double end) {
        setCoordinates(start, end);
    }
    
    LineSegment(const LineSegment& other) : x1(other.x1), x2(other.x2) {}

    // Существующие методы остаются без изменений
    void setCoordinates(double start, double end) {
        x1 = std::min(start, end);
        x2 = std::max(start, end);
    }

    double getStart() const { return x1; }
    double getEnd() const { return x2; }

    // Перегрузка унарного оператора !
    // Устанавливает меньшую координату в 0
    LineSegment operator!() const {
        return LineSegment(0, x2);
    }

    // Неявное преобразование в int
    // Возвращает целую часть правой координаты
    operator int() const {
        return static_cast<int>(x2);
    }

    // Явное преобразование в double
    // Возвращает левую координату
    explicit operator double() const {
        return x1;
    }

    // Перегрузка бинарного оператора +
    // Увеличивает обе координаты на заданное число
    LineSegment operator+(int value) const {
        return LineSegment(x1 + value, x2 + value);
    }

    // Перегрузка оператора >
    // Проверяет, включает ли текущий отрезок другой отрезок
    bool operator>(const LineSegment& other) const {
        return x1 <= other.x1 && x2 >= other.x2;
    }

    // Существующий дружественный оператор вывода
    friend std::ostream& operator<<(std::ostream& os, const LineSegment& seg) {
        os << "[" << seg.x1 << ", " << seg.x2 << "]";
        return os;
    }

    // Статический метод intersection остается без изменений
    static LineSegment* intersection(const LineSegment& seg1, const LineSegment& seg2) {
        if (seg1.x2 < seg2.x1 || seg2.x2 < seg1.x1) {
            return nullptr;
        }
        double start = std::max(seg1.x1, seg2.x1);
        double end = std::min(seg1.x2, seg2.x2);
        return new LineSegment(start, end);
    }
};

int main() {
    // Создаем тестовые отрезки
    LineSegment seg1(2.5, 7.8);
    LineSegment seg2(4.0, 6.0);
    LineSegment seg3(1.0, 10.0);

    std::cout << "Исходные отрезки:\n";
    std::cout << "seg1: " << seg1 << std::endl;
    std::cout << "seg2: " << seg2 << std::endl;
    std::cout << "seg3: " << seg3 << std::endl;

    // Демонстрация унарного оператора !
    std::cout << "\nПрименение оператора ! к seg1:\n";
    LineSegment negSeg = !seg1;
    std::cout << "!seg1: " << negSeg << std::endl;

    // Демонстрация преобразования типов
    int intValue = seg1;  // неявное преобразование в int
    double doubleValue = static_cast<double>(seg1);  // явное преобразование в double
    std::cout << "\nПреобразования типов для seg1:\n";
    std::cout << "В int: " << intValue << std::endl;
    std::cout << "В double: " << doubleValue << std::endl;

    // Демонстрация оператора +
    std::cout << "\nПрименение оператора + к seg1:\n";
    LineSegment shiftedSeg = seg1 + 3;
    std::cout << "seg1 + 3: " << shiftedSeg << std::endl;

    // Демонстрация оператора >
    std::cout << "\nСравнение отрезков с помощью оператора >:\n";
    std::cout << "seg3 > seg1: " << (seg3 > seg1 ? "true" : "false") << std::endl;
    std::cout << "seg1 > seg2: " << (seg1 > seg2 ? "true" : "false") << std::endl;
    std::cout << "seg2 > seg3: " << (seg2 > seg3 ? "true" : "false") << std::endl;

    // Демонстрация метода intersection
    std::cout << "\nПересечение отрезков:\n";
    LineSegment* intersection = LineSegment::intersection(seg1, seg2);
    if (intersection) {
        std::cout << "Пересечение seg1 и seg2: " << *intersection << std::endl;
        delete intersection;
    } else {
        std::cout << "Отрезки seg1 и seg2 не пересекаются" << std::endl;
    }

    return 0;
}
