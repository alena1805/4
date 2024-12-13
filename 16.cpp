#include <iostream>
#include <limits>
#include <stdexcept>
#include <algorithm>

// Класс, представляющий отрезок на координатной прямой
class LineSegment {
private:
    double x1; // Начало отрезка
    double x2; // Конец отрезка

public:
    // Конструктор с двумя параметрами (начало и конец отрезка)
    LineSegment(double start, double end) {
        if (start > end) {
            throw std::invalid_argument("Начало отрезка не может быть больше конца.");
        }
        x1 = start; // Присваиваем начальную точку
        x2 = end;   // Присваиваем конечную точку
    }

    // Конструктор, представляющий отрезок, состоящий из одной точки
    LineSegment(double point) : x1(point), x2(point) {}

    // Копирующий конструктор
    LineSegment(const LineSegment& segment) : x1(segment.x1), x2(segment.x2) {}

    // Свойства для начала и конца отрезка
    double Start() const { return x1; }
    double End() const { return x2; }

    // Метод для нахождения пересечения между двумя отрезками
    LineSegment* Intersect(const LineSegment& other) const {
        double maxStart = std::max(this->Start(), other.Start()); // Максимальное начало
        double minEnd = std::min(this->End(), other.End());       // Минимальный конец

        // Проверка на наличие пересечения
        if (maxStart <= minEnd) {
            return new LineSegment(maxStart, minEnd); // Возвращаем новый отрезок пересечения
        }
        return nullptr; // Нет пересечения
    }

    // Перегрузка оператора вывода для отображения отрезка
    friend std::ostream& operator<<(std::ostream& os, const LineSegment& segment) {
        os << "Отрезок от " << segment.x1 << " до " << segment.x2;
        return os;
    }
};

// Функция для безопасного ввода числа от пользователя
double getUserInput(const std::string& prompt) {
    double value;
    
    while (true) {
        std::cout << prompt;
        std::cin >> value;

        // Проверяем, было ли введено значение корректно
        if (std::cin.fail()) {
            std::cin.clear(); // Сбрасываем флаг ошибки
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Удаляем некорректный ввод
            std::cout << "Ошибка: введите число." << std::endl;
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищаем буфер
            return value; // Возвращаем корректное значение
        }
    }
}

int main() {
    try {
        // Получаем ввод от пользователя
        double start = getUserInput("Введите начало отрезка: ");
        double end = getUserInput("Введите конец отрезка: ");

        // Создаём отрезок
        LineSegment segment(start, end);
        std::cout << segment << std::endl;

        // Пример пересечения с другим сегментом отрезка
        double otherStart = getUserInput("Введите начало другого отрезка: ");
        double otherEnd = getUserInput("Введите конец другого отрезка: ");
        LineSegment otherSegment(otherStart, otherEnd);
        
        // Нахождение пересечения
        LineSegment* intersection = segment.Intersect(otherSegment);
        if (intersection) {
            std::cout << "Пересечение: " << *intersection << std::endl;
            delete intersection; // Освобождаем память
        } else {
            std::cout << "Отрезки не пересекаются." << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}
