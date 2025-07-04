#include "Car.h"
#include <stdio.h>

const char* carTypes[] = { "Sedan", "SUV", "Truck" };
const char* engineNames[] = { "GM", "TOYOTA", "WIA", "고장난 엔진" };
const char* brakeNames[] = { "Mando", "Continental", "Bosch" };
const char* steerNames[] = { "Bosch", "Mobis" };

void Car::selectPart(int step, int answer) {
	switch (step) {
		case CarType_Q:
			printf("차량 타입으로 %s을 선택하셨습니다.\n", carTypes[answer - 1]);
			setCarType(static_cast<CarType>(answer));
			break;
		case Engine_Q:
			printf("%s 엔진을 선택하셨습니다.\n", engineNames[answer - 1]);
			setEngineType(static_cast<EngineType>(answer));
			break;
		case BrakeSystem_Q:
			printf("%s 제동장치를 선택하셨습니다.\n", brakeNames[answer - 1]);
			setBrakeSystemType(static_cast<BrakeSystemType>(answer));
			break;
		case SteeringSystem_Q:
			printf("%s 조향장치를 선택하셨습니다.\n", steerNames[answer - 1]);
			setSteeringSystemType(static_cast<SteeringSystemType>(answer));
			break;
	}
}
void Car::setCarType(CarType type) { carType = type; }
void Car::setEngineType(EngineType type) { engineType = type; }
void Car::setBrakeSystemType(BrakeSystemType type) { brakeSystemType = type; }
void Car::setSteeringSystemType(SteeringSystemType type) { steeringSystemType = type; }
bool Car::isValid() {
	if (getCarType() == CarType::SEDAN && getBrakeSystemType() == BrakeSystemType::CONTINENTAL)
		return false;
	if (getCarType() == CarType::SUV && getEngineType() == EngineType::TOYOTA)
		return false;
	if (getCarType() == CarType::TRUCK && getEngineType() == EngineType::WIA)
		return false;
	if (getCarType() == CarType::TRUCK && getBrakeSystemType() == BrakeSystemType::MANDO)
		return false;
	if (getBrakeSystemType() == BrakeSystemType::BOSCH && getSteeringSystemType() != SteeringSystemType::BOSCH)
		return false;

	return true;
}
void Car::runProducedCar() {
	if (!isValid()) {
		printf("자동차가 동작되지 않습니다\n");
	}
	else if (getEngineType() == EngineType::MALFUNCTION) {
		printf("엔진이 고장나있습니다.\n자동차가 움직이지 않습니다.\n");
	}
	else {
		printf("Car Type : %s\n", carTypes[static_cast<int>(getCarType()) - 1]);
		printf("Engine : %s\n", engineNames[static_cast<int>(getEngineType()) - 1]);
		printf("Brake System : %s\n", brakeNames[static_cast<int>(getBrakeSystemType()) - 1]);
		printf("Steering System : %s\n", steerNames[static_cast<int>(getSteeringSystemType()) - 1]);
		printf("자동차가 동작됩니다.\n");
	}
}
void Car::testProducedCar() {
	if (!isValid()) {
		printf("자동차 부품 조합 테스트 결과 : FAIL\n");

		if (getCarType() == CarType::SEDAN && getBrakeSystemType() == BrakeSystemType::CONTINENTAL)
			printf("Sedan에는 Continental제동장치 사용 불가\n");
		else if (getCarType() == CarType::SUV && getEngineType() == EngineType::TOYOTA)
			printf("SUV에는 TOYOTA엔진 사용 불가\n");
		else if (getCarType() == CarType::TRUCK && getEngineType() == EngineType::WIA)
			printf("Truck에는 WIA엔진 사용 불가\n");
		else if (getCarType() == CarType::TRUCK && getBrakeSystemType() == BrakeSystemType::MANDO)
			printf("Truck에는 Mando제동장치 사용 불가\n");
		else
			printf("Bosch제동장치에는 Bosch조향장치 이외 사용 불가\n");
	}
	else {
		printf("자동차 부품 조합 테스트 결과 : PASS\n");
	}
}


CarType Car::getCarType() const { return carType; }
EngineType Car::getEngineType() const { return engineType; }
BrakeSystemType Car::getBrakeSystemType() const { return brakeSystemType; }
SteeringSystemType Car::getSteeringSystemType() const { return steeringSystemType; }