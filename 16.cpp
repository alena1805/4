#include <iostream>
#include <algorithm>

// Класс, представляющий отрезок на координатной прямой
class LineSegment {
private:
    double x1, x2; // координаты начала и конца отрезка

public:
    // Конструктор по умолчанию - создает отрезок с нулевыми координатами
    LineSegment() : x1(0), x2(0) {}

    // Конструктор с параметрами - создает отрезок с заданными координатами
    LineSegment(double start, double end) {
        setCoordinates(start, end);
    }

    // Конструктор копирования - создает копию существующего отрезка
    LineSegment(const LineSegment& other) : x1(other.x1), x2(other.x2) {}

    // Метод для установки координат отрезка
    void setCoordinates(double start, double end) {
        // Упорядочиваем координаты, чтобы x1 всегда был меньше x2
        x1 = std::min(start, end);
        x2 = std::max(start, end);
    }

    // Геттеры для получения координат
    double getStart() const { return x1; }
    double getEnd() const { return x2; }

    // Статический метод для определения пересечения двух отрезков
    static LineSegment* intersection(const LineSegment& seg1, const LineSegment& seg2) {
        // Проверяем, пересекаются ли отрезки
        // Если конец первого отрезка меньше начала второго или наоборот,
        // то отрезки не пересекаются
        if (seg1.x2 < seg2.x1 || seg2.x2 < seg1.x1) {
            return nullptr; // Отрезки не пересекаются
        }

        // Находим координаты пересечения:
        // - начало - максимум из начал отрезков
        // - конец - минимум из концов отрезков
        double start = std::max(seg1.x1, seg2.x1);
        double end = std::min(seg1.x2, seg2.x2);

        // Возвращаем новый отрезок, представляющий пересечение
        return new LineSegment(start, end);
    }

    // Перегрузка оператора вывода для удобного вывода отрезка
    friend std::ostream& operator<<(std::ostream& os, const LineSegment& seg) {
        os << "[" << seg.x1 << ", " << seg.x2 << "]";
        return os;
    }
};

// Вспомогательная функция для проверки корректности ввода
double getValidInput() {
    double value;
    // Пока ввод некорректен, запрашиваем повторный ввод
    while (!(std::cin >> value)) {
        std::cin.clear(); // Очищаем флаги ошибок
        std::cin.ignore(10000, '\n'); // Очищаем буфер ввода
        std::cout << "Некорректный ввод. Пожалуйста, введите число: ";
    }
    return value;
}

int main() {
    // Создание и ввод данных для первого отрезка
    std::cout << "Создание первого отрезка:\n";
    std::cout << "Введите координату начала: ";
    double start1 = getValidInput();
    std::cout << "Введите координату конца: ";
    double end1 = getValidInput();
    LineSegment segment1(start1, end1);

    // Создание и ввод данных для второго отрезка
    std::cout << "Создание второго отрезка:\n";
    std::cout << "Введите координату начала: ";
    double start2 = getValidInput();
    std::cout << "Введите координату конца: ";
    double end2 = getValidInput();
    LineSegment segment2(start2, end2);

    // Вывод созданных отрезков
    std::cout << "\nПервый отрезок: " << segment1 << std::endl;
    std::cout << "Второй отрезок: " << segment2 << std::endl;

    // Проверка пересечения отрезков
    LineSegment* intersection = LineSegment::intersection(segment1, segment2);
    if (intersection) {
        std::cout << "Отрезки пересекаются. Отрезок пересечения: " << *intersection << std::endl;
        delete intersection; // Освобождаем выделенную память
    } else {
        std::cout << "Отрезки не пересекаются." << std::endl;
    }

    // Демонстрация работы конструктора копирования
    LineSegment segment3(segment1);
    std::cout << "\nКопия первого отрезка: " << segment3 << std::endl;

    return 0;
}
