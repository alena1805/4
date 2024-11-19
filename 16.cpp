#include <iostream>
#include <algorithm>

// Класс для представления отрезка
class Line {
private:
    double begin, finish; // Начало и конец отрезка

public:
    // Конструктор по умолчанию
    Line() : begin(0), finish(0) {}

    // Конструктор с параметрами
    Line(double b, double f) {
        setPoints(b, f);
    }

    // Конструктор копирования
    Line(const Line& other) : begin(other.begin), finish(other.finish) {}

    // Метод для установки координат отрезка
    void setPoints(double b, double f) {
        begin = std::min(b, f);
        finish = std::max(b, f);
    }

    // Получаем начало и конец отрезка
    double getBegin() const { return begin; }
    double getFinish() const { return finish; }

    // Статический метод для нахождения пересечения двух отрезков
    static Line* findOverlap(const Line& line1, const Line& line2) {
        // Если один отрезок заканчивается до начала другого, они не пересекаются
        if (line1.finish < line2.begin || line2.finish < line1.begin) {
            return nullptr; // Нет пересечения
        }

        // Находим координаты пересечения
        double overlapBegin = std::max(line1.begin, line2.begin);
        double overlapFinish = std::min(line1.finish, line2.finish);

        // Возвращаем новый отрезок, представляющий пересечение
        return new Line(overlapBegin, overlapFinish);
    }

    // Перегрузка оператора вывода
    friend std::ostream& operator<<(std::ostream& os, const Line& line) {
        os << "[" << line.begin << ", " << line.finish << "]";
        return os;
    }
};

// Функция для проверки корректного ввода от пользователя
double getInput() {
    double value;
    while (!(std::cin >> value)) {
        std::cin.clear(); // Сбрасываем флаги ошибок
        std::cin.ignore(10000, '\n'); // Очищаем буфер ввода
        std::cout << "Ошибка ввода. Пожалуйста, введите число: ";
    }
    return value;
}

int main() {
    // Создание первого отрезка и ввод его координат
    std::cout << "Давайте создадим первый отрезок:\n";
    std::cout << "Введите координату начала: ";
    double start1 = getInput();
    std::cout << "Введите координату конца: ";
    double end1 = getInput();
    Line line1(start1, end1);

    // Создание второго отрезка и ввод его координат
    std::cout << "Теперь создадим второй отрезок:\n";
    std::cout << "Введите координату начала: ";
    double start2 = getInput();
    std::cout << "Введите координату конца: ";
    double end2 = getInput();
    Line line2(start2, end2);

    // Вывод информации о созданных отрезках
    std::cout << "\nПервый отрезок: " << line1 << std::endl;
    std::cout << "Второй отрезок: " << line2 << std::endl;

    // Проверяем, пересекаются ли отрезки
    Line* overlap = Line::findOverlap(line1, line2);
    if (overlap) {
        std::cout << "Отрезки пересекаются. Вот отрезок пересечения: " << *overlap << std::endl;
        delete overlap; // Освобождаем память после использования
    } else {
        std::cout << "К сожалению, отрезки не пересекаются." << std::endl;
    }

    // Демонстрация работы конструктора копирования
    Line line3(line1);
    std::cout << "\nВот копия первого отрезка: " << line3 << std::endl;

    return 0;
}
