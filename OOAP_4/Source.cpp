#include <iostream>
#include <string>
#include <memory>

// ���� ��� ������������� ����� ���������
// ��� ���� � ���������, ���� ���� ������������ �� ��������� �����������.
class Car {
public:
    std::string engineType;           // ��� ������� (���������� �� ���������)
    double engineVolume;              // ��'�� �������
    bool hasABS;                      // �������� ABS
    bool hasESP;                      // �������� ESP
    int airbags;                      // ʳ������ ������� �������
    bool hasBoardComputer;            // �������� ��������� ����'�����
    std::string climateSystem;        // ����������� �� �����-��������
    std::string interior;             // ������� ������
    double price;                     // ������� ������������

    // ����� ��� ��������� ������������� ��������� �� �����
    void showSpecifications() const {
        std::cout << "��� �������: " << engineType << "\n";
        std::cout << "��'�� �������: " << engineVolume << " �\n";
        std::cout << "ABS: " << (hasABS ? "�" : "����") << "\n";
        std::cout << "ESP: " << (hasESP ? "�" : "����") << "\n";
        std::cout << "ʳ������ ������� �������: " << airbags << "\n";
        std::cout << "�������� ����'����: " << (hasBoardComputer ? "�" : "����") << "\n";
        std::cout << "������� ������: " << climateSystem << "\n";
        std::cout << "������� ������: " << interior << "\n";
        std::cout << "�������: " << price << " ���\n";
    }
};

// ����������� ���� �����������
// ³� ������ ������ ��� ��������� �������� ���������. ����� ����� ������� ���� � �������������.
class CarBuilder {
public:
    virtual ~CarBuilder() {}
    virtual void setEngineType() = 0;      // ������������ ���� �������
    virtual void setEngineVolume() = 0;    // ������������ ��'��� �������
    virtual void setABS() = 0;             // ������������ ABS
    virtual void setESP() = 0;             // ������������ ESP
    virtual void setAirbags() = 0;         // ������������ ������� ������� �������
    virtual void setBoardComputer() = 0;   // ������������ �������� ��������� ����'�����
    virtual void setClimateSystem() = 0;   // ������������ ������� ������
    virtual void setInterior() = 0;        // ������������ ������� ������
    virtual void setPrice() = 0;           // ������������ ����
    virtual std::unique_ptr<Car> getCar() = 0;  // ��������� ����������� ���������
};

// ���������� ���������� ��� ������ ������������
// ��� ���� ������� �� ��������� ��������� � �������� ����������������.
class BasicPackageBuilder : public CarBuilder {
private:
    std::unique_ptr<Car> car;
public:
    BasicPackageBuilder() { car = std::make_unique<Car>(); }  // ����������� ������ ���������

    void setEngineType() override { car->engineType = "����������"; }   // ��� �������
    void setEngineVolume() override { car->engineVolume = 1.6; }        // ��'�� �������
    void setABS() override { car->hasABS = false; }                     // ABS �������
    void setESP() override { car->hasESP = false; }                     // ESP �������
    void setAirbags() override { car->airbags = 2; }                    // 2 ������� �������
    void setBoardComputer() override { car->hasBoardComputer = false; } // �������� ����'���� �������
    void setClimateSystem() override { car->climateSystem = "�����������"; }  // ������� ���������������
    void setInterior() override { car->interior = "�������"; }          // �������� ������� ������
    void setPrice() override { car->price = 200000; }                   // ������� ������ ������������

    std::unique_ptr<Car> getCar() override { return std::move(car); }   // ���������� ������������ ���������
};

// ���������� ���������� ��� ���������� ������������
// ��� ���� ������� ��������� � ������������ ����������������.
class StandardPackageBuilder : public CarBuilder {
private:
    std::unique_ptr<Car> car;
public:
    StandardPackageBuilder() { car = std::make_unique<Car>(); }

    void setEngineType() override { car->engineType = "����������"; }   // ��� �������
    void setEngineVolume() override { car->engineVolume = 2.0; }        // ��'�� �������
    void setABS() override { car->hasABS = true; }                      // ABS �
    void setESP() override { car->hasESP = true; }                      // ESP �
    void setAirbags() override { car->airbags = 4; }                    // 4 ������� �������
    void setBoardComputer() override { car->hasBoardComputer = true; }  // �������� ����'���� �
    void setClimateSystem() override { car->climateSystem = "�����-��������"; } // ������� �����-��������
    void setInterior() override { car->interior = "����"; }            // ������ ������� ������
    void setPrice() override { car->price = 350000; }                   // ������� ���������� ������������

    std::unique_ptr<Car> getCar() override { return std::move(car); }   // ���������� ������������ ���������
};

// ���� Director ��� ��������� �������� �������� ���������
// Director ������� �� ����������� ������� ������ ����������� ��� ��������� ��'����.
class CarDirector {
private:
    CarBuilder* builder;
public:
    // ������������ ����������� �����������
    void setBuilder(CarBuilder* b) { builder = b; }

    // ��������� ��������� ���������
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
    CarDirector director;  // ��'��� Director ��� ��������� ��������� ���������

    // �������� ��������� � ������� �������������
    BasicPackageBuilder basicBuilder;       // ��������� ����������� ��� ������ ������������
    director.setBuilder(&basicBuilder);     // �������� ����������� ���������
    director.constructCar();                // ������ ������� ��������
    std::unique_ptr<Car> basicCar = basicBuilder.getCar();  // ��������� �������� ���������
    std::cout << "������ ������������:\n";
    basicCar->showSpecifications();         // ��������� ������������� ������ ������������

    std::cout << "\n";

    // �������� ��������� � ����������� �������������
    StandardPackageBuilder standardBuilder; // ��������� ����������� ��� ���������� ������������
    director.setBuilder(&standardBuilder);  // �������� ����������� ���������
    director.constructCar();                // ������ ������� ��������
    std::unique_ptr<Car> standardCar = standardBuilder.getCar();  // ��������� �������� ���������
    std::cout << "���������� ������������:\n";
    standardCar->showSpecifications();      // ��������� ������������� ���������� ������������

    return 0;
}
