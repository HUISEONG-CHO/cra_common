#include <gtest/gtest.h>
#include "../src/Car.h"

class CarTest : public ::testing::Test {
protected:
    Car car;

    CarTest() : car() {}
};

TEST_F(CarTest, SelectPart_CarType) {
    car.selectPart(CarType_Q, 1);
    EXPECT_EQ(car.getCarType(), CarType::SEDAN);
    car.selectPart(CarType_Q, 2);
    EXPECT_EQ(car.getCarType(), CarType::SUV);
    car.selectPart(CarType_Q, 3);
    EXPECT_EQ(car.getCarType(), CarType::TRUCK);
}

TEST_F(CarTest, SelectPart_Engine) {
    car.selectPart(Engine_Q, 1);
    EXPECT_EQ(car.getEngineType(), EngineType::GM);
    car.selectPart(Engine_Q, 2);
    EXPECT_EQ(car.getEngineType(), EngineType::TOYOTA);
    car.selectPart(Engine_Q, 3);
    EXPECT_EQ(car.getEngineType(), EngineType::WIA);
    car.selectPart(Engine_Q, 4);
    EXPECT_EQ(car.getEngineType(), EngineType::MALFUNCTION);
}

TEST_F(CarTest, SelectPart_Brake) {
    car.selectPart(BrakeSystem_Q, 1);
    EXPECT_EQ(car.getBrakeSystemType(), BrakeSystemType::MANDO);
    car.selectPart(BrakeSystem_Q, 2);
    EXPECT_EQ(car.getBrakeSystemType(), BrakeSystemType::CONTINENTAL);
    car.selectPart(BrakeSystem_Q, 3);
    EXPECT_EQ(car.getBrakeSystemType(), BrakeSystemType::BOSCH);
}

TEST_F(CarTest, SelectPart_Steering) {
    car.selectPart(SteeringSystem_Q, 1);
    EXPECT_EQ(car.getSteeringSystemType(), SteeringSystemType::BOSCH);
    car.selectPart(SteeringSystem_Q, 2);
    EXPECT_EQ(car.getSteeringSystemType(), SteeringSystemType::MOBIS);
}

TEST_F(CarTest, IsValid_AllValid) {
    car.setCarType(CarType::SEDAN);
    car.setEngineType(EngineType::GM);
    car.setBrakeSystemType(BrakeSystemType::MANDO);
    car.setSteeringSystemType(SteeringSystemType::BOSCH);
    EXPECT_TRUE(car.isValid());
}

TEST_F(CarTest, IsValid_Sedan_Continental) {
    car.setCarType(CarType::SEDAN);
    car.setEngineType(EngineType::GM);
    car.setBrakeSystemType(BrakeSystemType::CONTINENTAL);
    car.setSteeringSystemType(SteeringSystemType::BOSCH);
    EXPECT_FALSE(car.isValid());
}

TEST_F(CarTest, IsValid_SUV_Toyota) {
    car.setCarType(CarType::SUV);
    car.setEngineType(EngineType::TOYOTA);
    car.setBrakeSystemType(BrakeSystemType::MANDO);
    car.setSteeringSystemType(SteeringSystemType::BOSCH);
    EXPECT_FALSE(car.isValid());
}

TEST_F(CarTest, IsValid_Truck_WIA) {
    car.setCarType(CarType::TRUCK);
    car.setEngineType(EngineType::WIA);
    car.setBrakeSystemType(BrakeSystemType::MANDO);
    car.setSteeringSystemType(SteeringSystemType::BOSCH);
    EXPECT_FALSE(car.isValid());
}

TEST_F(CarTest, IsValid_Truck_Mando) {
    car.setCarType(CarType::TRUCK);
    car.setEngineType(EngineType::GM);
    car.setBrakeSystemType(BrakeSystemType::MANDO);
    car.setSteeringSystemType(SteeringSystemType::BOSCH);
    EXPECT_FALSE(car.isValid());
}

TEST_F(CarTest, IsValid_BoschBrake_NotBoschSteer) {
    car.setCarType(CarType::SEDAN);
    car.setEngineType(EngineType::GM);
    car.setBrakeSystemType(BrakeSystemType::BOSCH);
    car.setSteeringSystemType(SteeringSystemType::MOBIS);
    EXPECT_FALSE(car.isValid());
}

TEST_F(CarTest, RunProducedCar_Valid) {
    car.setCarType(CarType::SEDAN);
    car.setEngineType(EngineType::GM);
    car.setBrakeSystemType(BrakeSystemType::MANDO);
    car.setSteeringSystemType(SteeringSystemType::BOSCH);
    testing::internal::CaptureStdout();
    car.runProducedCar();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("자동차가 동작됩니다."), std::string::npos);
}

TEST_F(CarTest, RunProducedCar_Invalid) {
    car.setCarType(CarType::SEDAN);
    car.setEngineType(EngineType::GM);
    car.setBrakeSystemType(BrakeSystemType::CONTINENTAL);
    car.setSteeringSystemType(SteeringSystemType::BOSCH);
    testing::internal::CaptureStdout();
    car.runProducedCar();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("자동차가 동작되지 않습니다"), std::string::npos);
}

TEST_F(CarTest, RunProducedCar_Malfunction) {
    car.setCarType(CarType::SEDAN);
    car.setEngineType(EngineType::MALFUNCTION);
    car.setBrakeSystemType(BrakeSystemType::MANDO);
    car.setSteeringSystemType(SteeringSystemType::BOSCH);
    testing::internal::CaptureStdout();
    car.runProducedCar();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("엔진이 고장나있습니다."), std::string::npos);
}

TEST_F(CarTest, TestProducedCar_Pass) {
    car.setCarType(CarType::SEDAN);
    car.setEngineType(EngineType::GM);
    car.setBrakeSystemType(BrakeSystemType::MANDO);
    car.setSteeringSystemType(SteeringSystemType::BOSCH);
    testing::internal::CaptureStdout();
    car.testProducedCar();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("PASS"), std::string::npos);
}

TEST_F(CarTest, TestProducedCar_Fail_SedanContinental) {
    car.setCarType(CarType::SEDAN);
    car.setEngineType(EngineType::GM);
    car.setBrakeSystemType(BrakeSystemType::CONTINENTAL);
    car.setSteeringSystemType(SteeringSystemType::BOSCH);
    testing::internal::CaptureStdout();
    car.testProducedCar();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Sedan에는 Continental제동장치 사용 불가"), std::string::npos);
}

TEST_F(CarTest, TestProducedCar_Fail_SUVToyota) {
    car.setCarType(CarType::SUV);
    car.setEngineType(EngineType::TOYOTA);
    car.setBrakeSystemType(BrakeSystemType::MANDO);
    car.setSteeringSystemType(SteeringSystemType::BOSCH);
    testing::internal::CaptureStdout();
    car.testProducedCar();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("SUV에는 TOYOTA엔진 사용 불가"), std::string::npos);
}

TEST_F(CarTest, TestProducedCar_Fail_TruckWIA) {
    car.setCarType(CarType::TRUCK);
    car.setEngineType(EngineType::WIA);
    car.setBrakeSystemType(BrakeSystemType::MANDO);
    car.setSteeringSystemType(SteeringSystemType::BOSCH);
    testing::internal::CaptureStdout();
    car.testProducedCar();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Truck에는 WIA엔진 사용 불가"), std::string::npos);
}

TEST_F(CarTest, TestProducedCar_Fail_TruckMando) {
    car.setCarType(CarType::TRUCK);
    car.setEngineType(EngineType::GM);
    car.setBrakeSystemType(BrakeSystemType::MANDO);
    car.setSteeringSystemType(SteeringSystemType::BOSCH);
    testing::internal::CaptureStdout();
    car.testProducedCar();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Truck에는 Mando제동장치 사용 불가"), std::string::npos);
}

TEST_F(CarTest, TestProducedCar_Fail_BoschBrakeNotBoschSteer) {
    car.setCarType(CarType::SEDAN);
    car.setEngineType(EngineType::GM);
    car.setBrakeSystemType(BrakeSystemType::BOSCH);
    car.setSteeringSystemType(SteeringSystemType::MOBIS);
    testing::internal::CaptureStdout();
    car.testProducedCar();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Bosch제동장치에는 Bosch조향장치 이외 사용 불가"), std::string::npos);
}