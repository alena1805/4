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
    // Унарная операция: установить соответствующую координату в 0
    LineSegment operator!() {
        return LineSegment(0, std::max(x1, x2)); // Устанавливаем начало в 0
    }

    // Приведение типа для int (неявное) – целая часть координаты y
    operator int() const {
        return static_cast<int>(x1);
    }

    // Приведение типа для double (явное) – результатом является координата x
    explicit operator double() const {
        return x1;
    }

    // Бинарная операция: сложение с целым числом
    LineSegment operator+(int offset) {
        return LineSegment(x1 + offset, x2 + offset); // Увеличиваем координаты
    }

    // Бинарная операция: оператор сравнения
    bool operator>(const LineSegment& other) const {
        return (x1 <= other.x1 && x2 >= other.x2); // Проверяем, включает ли левый отрезок правый
    }

    // Метод для нахождения пересечения между двумя отрезками
    LineSegment* Intersect(const LineSegment& other) {
        double newStart = std::max(x1, other.x1);// Находим максимальное значение начала обоих отрезков
        double newEnd = std::min(x2, other.x2);// Находим минимальное значение конца обоих отрезков
        if (newStart <= newEnd) {// Проверяем, пересекаются ли отрезки
            return new LineSegment(newStart, newEnd);// Если пересечение существует, создаем и возвращаем новый отрезок
        }
        return nullptr; // Нет пересечения
    }

    // Метод для отображения отрезка
    void Display() const {
        std::cout << "Отрезок от " << x1 << " до " << x2 << " " << std::endl;
    }
};

// Функция для безопасного ввода числа от пользователя
double A(const std::string& prompt) {
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
        double start = A("Введите начало отрезка: ");
        double end = A("Введите конец отрезка: ");

        // Создаём отрезок
        LineSegment segment1(start, end);
        std::cout << segment1 << std::endl;

        // Создаём отрезок 2
        LineSegment segment2(start, end);
        std::cout << segment2 << std::endl;
        
        // Пример пересечения с другим сегментом отрезка
        double otherStart = A("Введите начало другого отрезка: ");
        double otherEnd = A("Введите конец другого отрезка: ");
        LineSegment otherSegment(otherStart, otherEnd);
        
        // Нахождение пересечения
        LineSegment* intersection = segment1.Intersect(otherSegment); // Находим пересечение
        if (intersection) {// Если пересечение существует, выводим его на экран
            std::cout << "Пересечение: " << *intersection << std::endl;
            delete intersection; // Освобождаем память
        } else {// Если пересечения нет, сообщаем об этом 
            std::cout << "Отрезки не пересекаются." << std::endl;
        }
        // Применение унарной операции
        LineSegment updatedSegment = !segment1;// Применяем унарную операцию к segment1 и сохраняем результат в updatedSegment
        std::cout << "После унарной операции: ";// Выводим обновленный отрезок на экран
        updatedSegment.Display();

        // Приведение типов
        int intValue = segment1; // Неявное приведение
        std::cout << "Неявное приведение к int: " << intValue << std::endl;

        double doubleValue = static_cast<double>(segment1); // Явное приведение
        std::cout << "Явное приведение к double: " << doubleValue << std::endl;

        // Сложение с целым числом
        LineSegment newSegment = segment1 + 2;
        std::cout << "После сложения с 2: ";
        newSegment.Display();

        // Проверка операторов сравнения
        if (segment1 > segment2) {
            std::cout << "Первый отрезок включает второй." << std::endl;
        } else {
            std::cout << "Первый отрезок не включает второй." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
    
    return 0;
}
