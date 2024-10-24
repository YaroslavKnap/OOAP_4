#include <iostream>
#include <string>
#include <memory>

// Клас для представлення моделі автомобіля
// Цей клас є продуктом, який буде створюватися за допомогою Будівельника.
class Car {
public:
    std::string engineType;           // Тип двигуна (бензиновий чи дизельний)
    double engineVolume;              // Об'єм двигуна
    bool hasABS;                      // Наявність ABS
    bool hasESP;                      // Наявність ESP
    int airbags;                      // Кількість подушок безпеки
    bool hasBoardComputer;            // Наявність бортового комп'ютера
    std::string climateSystem;        // Кондиціонер чи клімат-контроль
    std::string interior;             // Обшивка салону
    double price;                     // Вартість комплектації

    // Метод для виведення характеристик автомобіля на екран
    void showSpecifications() const {
        std::cout << "Тип двигуна: " << engineType << "\n";
        std::cout << "Об'єм двигуна: " << engineVolume << " л\n";
        std::cout << "ABS: " << (hasABS ? "є" : "немає") << "\n";
        std::cout << "ESP: " << (hasESP ? "є" : "немає") << "\n";
        std::cout << "Кількість подушок безпеки: " << airbags << "\n";
        std::cout << "Бортовий комп'ютер: " << (hasBoardComputer ? "є" : "немає") << "\n";
        std::cout << "Система клімату: " << climateSystem << "\n";
        std::cout << "Обшивка салону: " << interior << "\n";
        std::cout << "Вартість: " << price << " грн\n";
    }
};

// Абстрактний клас будівельника
// Він містить методи для покрокової побудови автомобіля. Кожен метод визначає одну з характеристик.
class CarBuilder {
public:
    virtual ~CarBuilder() {}
    virtual void setEngineType() = 0;      // Встановлення типу двигуна
    virtual void setEngineVolume() = 0;    // Встановлення об'єму двигуна
    virtual void setABS() = 0;             // Встановлення ABS
    virtual void setESP() = 0;             // Встановлення ESP
    virtual void setAirbags() = 0;         // Встановлення кількості подушок безпеки
    virtual void setBoardComputer() = 0;   // Встановлення наявності бортового комп'ютера
    virtual void setClimateSystem() = 0;   // Встановлення системи клімату
    virtual void setInterior() = 0;        // Встановлення обшивки салону
    virtual void setPrice() = 0;           // Встановлення ціни
    virtual std::unique_ptr<Car> getCar() = 0;  // Отримання збудованого автомобіля
};

// Конкретний будівельник для базової комплектації
// Цей клас відповідає за створення автомобіля з базовими характеристиками.
class BasicPackageBuilder : public CarBuilder {
private:
    std::unique_ptr<Car> car;
public:
    BasicPackageBuilder() { car = std::make_unique<Car>(); }  // Ініціалізація нового автомобіля

    void setEngineType() override { car->engineType = "Бензиновий"; }   // Тип двигуна
    void setEngineVolume() override { car->engineVolume = 1.6; }        // Об'єм двигуна
    void setABS() override { car->hasABS = false; }                     // ABS відсутній
    void setESP() override { car->hasESP = false; }                     // ESP відсутній
    void setAirbags() override { car->airbags = 2; }                    // 2 подушки безпеки
    void setBoardComputer() override { car->hasBoardComputer = false; } // Бортовий комп'ютер відсутній
    void setClimateSystem() override { car->climateSystem = "Кондиціонер"; }  // Система кондиціонування
    void setInterior() override { car->interior = "Тканина"; }          // Тканинна обшивка салону
    void setPrice() override { car->price = 200000; }                   // Вартість базової комплектації

    std::unique_ptr<Car> getCar() override { return std::move(car); }   // Повернення побудованого автомобіля
};

// Конкретний будівельник для стандартної комплектації
// Цей клас створює автомобіль зі стандартними характеристиками.
class StandardPackageBuilder : public CarBuilder {
private:
    std::unique_ptr<Car> car;
public:
    StandardPackageBuilder() { car = std::make_unique<Car>(); }

    void setEngineType() override { car->engineType = "Бензиновий"; }   // Тип двигуна
    void setEngineVolume() override { car->engineVolume = 2.0; }        // Об'єм двигуна
    void setABS() override { car->hasABS = true; }                      // ABS є
    void setESP() override { car->hasESP = true; }                      // ESP є
    void setAirbags() override { car->airbags = 4; }                    // 4 подушки безпеки
    void setBoardComputer() override { car->hasBoardComputer = true; }  // Бортовий комп'ютер є
    void setClimateSystem() override { car->climateSystem = "Клімат-контроль"; } // Система клімат-контроль
    void setInterior() override { car->interior = "Шкіра"; }            // Шкіряна обшивка салону
    void setPrice() override { car->price = 350000; }                   // Вартість стандартної комплектації

    std::unique_ptr<Car> getCar() override { return std::move(car); }   // Повернення побудованого автомобіля
};

// Клас Director для управління процесом побудови автомобіля
// Director відповідає за послідовність викликів методів будівельника для створення об'єкта.
class CarDirector {
private:
    CarBuilder* builder;
public:
    // Встановлення конкретного будівельника
    void setBuilder(CarBuilder* b) { builder = b; }

    // Покрокове створення автомобіля
    void constructCar() {
        builder->setEngineType();
        builder->setEngineVolume();
        builder->setABS();
        builder->setESP();
        builder->setAirbags();
        builder->setBoardComputer();
        builder->setClimateSystem();
        builder->setInterior();
        builder->setPrice();
    }
};

int main() {
    setlocale(LC_ALL, "ukr");
    CarDirector director;  // Об'єкт Director для управління побудовою автомобілів

    // Побудова автомобіля з базовою комплектацією
    BasicPackageBuilder basicBuilder;       // Створення будівельника для базової комплектації
    director.setBuilder(&basicBuilder);     // Передача будівельника директору
    director.constructCar();                // Виклик процесу побудови
    std::unique_ptr<Car> basicCar = basicBuilder.getCar();  // Отримання готового автомобіля
    std::cout << "Базова комплектація:\n";
    basicCar->showSpecifications();         // Виведення характеристик базової комплектації

    std::cout << "\n";

    // Побудова автомобіля зі стандартною комплектацією
    StandardPackageBuilder standardBuilder; // Створення будівельника для стандартної комплектації
    director.setBuilder(&standardBuilder);  // Передача будівельника директору
    director.constructCar();                // Виклик процесу побудови
    std::unique_ptr<Car> standardCar = standardBuilder.getCar();  // Отримання готового автомобіля
    std::cout << "Стандартна комплектація:\n";
    standardCar->showSpecifications();      // Виведення характеристик стандартної комплектації

    return 0;
}
