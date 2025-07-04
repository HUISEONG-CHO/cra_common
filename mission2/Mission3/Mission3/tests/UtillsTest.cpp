#include <gtest/gtest.h>
#include <string>
#include <cstring>
#include "../src/utils.h"

class UtilsTest : public ::testing::Test {};

TEST_F(UtilsTest, IsValidInput_NumberOnly) {
    EXPECT_FALSE(isValidInput("a", CarType_Q, 1));
    EXPECT_TRUE(isValidInput("", CarType_Q, 1));
}

TEST_F(UtilsTest, IsValidInput_CarTypeRange) {
    EXPECT_FALSE(isValidInput("", CarType_Q, 0));
    EXPECT_FALSE(isValidInput("", CarType_Q, 4));
    EXPECT_TRUE(isValidInput("", CarType_Q, 1));
    EXPECT_TRUE(isValidInput("", CarType_Q, 2));
    EXPECT_TRUE(isValidInput("", CarType_Q, 3));
}

TEST_F(UtilsTest, IsValidInput_EngineRange) {
    EXPECT_FALSE(isValidInput("", Engine_Q, -1));
    EXPECT_FALSE(isValidInput("", Engine_Q, 5));
    EXPECT_TRUE(isValidInput("", Engine_Q, 0));
    EXPECT_TRUE(isValidInput("", Engine_Q, 1));
    EXPECT_TRUE(isValidInput("", Engine_Q, 2));
    EXPECT_TRUE(isValidInput("", Engine_Q, 3));
    EXPECT_TRUE(isValidInput("", Engine_Q, 4));
}

TEST_F(UtilsTest, IsValidInput_BrakeRange) {
    EXPECT_FALSE(isValidInput("", BrakeSystem_Q, -1));
    EXPECT_FALSE(isValidInput("", BrakeSystem_Q, 4));
    EXPECT_TRUE(isValidInput("", BrakeSystem_Q, 0));
    EXPECT_TRUE(isValidInput("", BrakeSystem_Q, 1));
    EXPECT_TRUE(isValidInput("", BrakeSystem_Q, 2));
    EXPECT_TRUE(isValidInput("", BrakeSystem_Q, 3));
}

TEST_F(UtilsTest, IsValidInput_SteeringRange) {
    EXPECT_FALSE(isValidInput("", SteeringSystem_Q, -1));
    EXPECT_FALSE(isValidInput("", SteeringSystem_Q, 3));
    EXPECT_TRUE(isValidInput("", SteeringSystem_Q, 0));
    EXPECT_TRUE(isValidInput("", SteeringSystem_Q, 1));
    EXPECT_TRUE(isValidInput("", SteeringSystem_Q, 2));
}

TEST_F(UtilsTest, IsValidInput_RunTestRange) {
    EXPECT_FALSE(isValidInput("", Run_Test, -1));
    EXPECT_FALSE(isValidInput("", Run_Test, 3));
    EXPECT_TRUE(isValidInput("", Run_Test, 0));
    EXPECT_TRUE(isValidInput("", Run_Test, 1));
    EXPECT_TRUE(isValidInput("", Run_Test, 2));
}

TEST_F(UtilsTest, PrintMenu_AllCases) {
    testing::internal::CaptureStdout();
    printMenu(CarType_Q);
    std::string out1 = testing::internal::GetCapturedStdout();
    EXPECT_NE(out1.find("어떤 차량 타입을 선택할까요?"), std::string::npos);

    testing::internal::CaptureStdout();
    printMenu(Engine_Q);
    std::string out2 = testing::internal::GetCapturedStdout();
    EXPECT_NE(out2.find("어떤 엔진을 탑재할까요?"), std::string::npos);

    testing::internal::CaptureStdout();
    printMenu(BrakeSystem_Q);
    std::string out3 = testing::internal::GetCapturedStdout();
    EXPECT_NE(out3.find("어떤 제동장치를 선택할까요?"), std::string::npos);

    testing::internal::CaptureStdout();
    printMenu(SteeringSystem_Q);
    std::string out4 = testing::internal::GetCapturedStdout();
    EXPECT_NE(out4.find("어떤 조향장치를 선택할까요?"), std::string::npos);

    testing::internal::CaptureStdout();
    printMenu(Run_Test);
    std::string out5 = testing::internal::GetCapturedStdout();
    EXPECT_NE(out5.find("멋진 차량이 완성되었습니다."), std::string::npos);
}

TEST_F(UtilsTest, Delay_Coverage) {

    delay(1);
}