#pragma once
enum QuestionType {
    CarType_Q,
    Engine_Q,
    BrakeSystem_Q,
    SteeringSystem_Q,
    Run_Test
};

enum class CarType { SEDAN = 1, SUV, TRUCK };
enum class EngineType { GM = 1, TOYOTA, WIA, MALFUNCTION };
enum class BrakeSystemType { MANDO = 1, CONTINENTAL, BOSCH };
enum class SteeringSystemType { BOSCH = 1, MOBIS };

class Car {
private:
    CarType carType;
    EngineType engineType;
    BrakeSystemType brakeSystemType;
    SteeringSystemType steeringSystemType;

public:
    void selectPart(int step, int answer);
    void setCarType(CarType type);
    void setEngineType(EngineType type);
    void setBrakeSystemType(BrakeSystemType type);
    void setSteeringSystemType(SteeringSystemType type);
    bool isValid();
    void runProducedCar();
    void testProducedCar();

    CarType getCarType() const;
    EngineType getEngineType() const;
    BrakeSystemType getBrakeSystemType() const;
    SteeringSystemType getSteeringSystemType() const;
};