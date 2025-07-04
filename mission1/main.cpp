#ifdef _DEBUG

#include "gmock/gmock.h"

int main()
{
    testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}

#else

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define CLEAR_SCREEN "\033[H\033[2J"

#define MAX_STACK 10

int stack[MAX_STACK];

enum QuestionType
{
    CarType_Q,
    Engine_Q,
    brakeSystem_Q,
    SteeringSystem_Q,
    Run_Test
};

enum CarType
{
    SEDAN = 1,
    SUV,
    TRUCK
};

enum Engine
{
    GM = 1,
    TOYOTA,
    WIA,
    MALFUNCTION
};

enum brakeSystem
{
    MANDO = 1,
    CONTINENTAL,
    BOSCH_B
};

enum SteeringSystem
{
    BOSCH_S = 1,
    MOBIS
};

const char* carTypes[] = { "Sedan", "SUV", "Truck" };
const char* engineNames[] = { "GM", "TOYOTA", "WIA", "고장난 엔진" };
const char* brakeNames[] = { "MANDO", "CONTINENTAL", "BOSCH" };
const char* steerNames[] = { "BOSCH", "MOBIS" };

void delay(int ms) {
    volatile int sum = 0;
    for (int i = 0; i < 1000; i++)
        for (int j = 0; j < 1000; j++)
            for (int t = 0; t < ms; t++) sum++;
}

bool isValidInput(const char* endptr, int step, int answer) {
    bool ret = true;
    const char* message = "";

    if (*endptr != '\0') {
        message = "숫자만 입력 가능";
        ret = false;
    }
    else if (step == CarType_Q && (answer < 1 || answer > 3)) {
        message = "차량 타입은 1 ~ 3 범위만 선택 가능";
        ret = false;
    }
    else if (step == Engine_Q && (answer < 0 || answer > 4)) {
        message = "엔진은 1 ~ 4 범위만 선택 가능";
        ret = false;
    }
    else if (step == brakeSystem_Q && (answer < 0 || answer > 3)) {
        message = "제동장치는 1 ~ 3 범위만 선택 가능";
        ret = false;
    }
    else if (step == SteeringSystem_Q && (answer < 0 || answer > 2)) {
        message = "조향장치는 1 ~ 2 범위만 선택 가능";
        ret = false;
    }
    else if (step == Run_Test && (answer < 0 || answer > 2)) {
        message = "Run 또는 Test 중 하나를 선택 필요";
        ret = false;
    }

    if (ret == false) {
        printf("ERROR :: %s\n", message);
        delay(800);
    }

    return ret;
}

void printMenu(int step) {
    printf(CLEAR_SCREEN);
    switch (step) {
    case CarType_Q:
        printf("        ______________\n");
        printf("       /|            | \n");
        printf("  ____/_|_____________|____\n");
        printf(" |                      O  |\n");
        printf(" '-(@)----------------(@)--'\n");
        printf("===============================\n");
        printf("어떤 차량 타입을 선택할까요?\n1. Sedan\n2. SUV\n3. Truck\n"); break;
    case Engine_Q:
        printf("어떤 엔진을 탑재할까요?\n0. 뒤로가기\n1. GM\n2. TOYOTA\n3. WIA\n4. 고장난 엔진\n"); break;
    case brakeSystem_Q:
        printf("어떤 제동장치를 선택할까요?\n0. 뒤로가기\n1. MANDO\n2. CONTINENTAL\n3. BOSCH\n"); break;
    case SteeringSystem_Q:
        printf("어떤 조향장치를 선택할까요?\n0. 뒤로가기\n1. BOSCH\n2. MOBIS\n"); break;
    case Run_Test:
        printf("멋진 차량이 완성되었습니다.\n어떤 동작을 할까요?\n0. 처음 화면으로 돌아가기\n1. RUN\n2. Test\n"); break;
    }
    printf("===============================\n");
    printf("INPUT > ");
}

void selectPart(int step, int answer) {
    stack[step] = answer;
    const char* val1 = "";
    const char* val2 = "";
    const char* val3 = "";

    switch (step) {
    case CarType_Q: val1 = "차량 타입으로"; val2 = carTypes[answer - 1]; val3 = "을"; break;
    case Engine_Q: val1 = engineNames[answer - 1]; val2 = "엔진"; val3 = "을"; break;
    case brakeSystem_Q: val1 = brakeNames[answer - 1]; val2 = "제동장치"; val3 = "를"; break;
    case SteeringSystem_Q: val1 = steerNames[answer - 1]; val2 = "조향장치"; val3 = "를";  break;
    }
    printf("%s %s%s 선택하셨습니다.\n", val1, val2, val3);
}

bool isValidCombination() {
    return !(stack[CarType_Q] == SEDAN && stack[brakeSystem_Q] == CONTINENTAL) &&
        !(stack[CarType_Q] == SUV && stack[Engine_Q] == TOYOTA) &&
        !(stack[CarType_Q] == TRUCK && stack[Engine_Q] == WIA) &&
        !(stack[CarType_Q] == TRUCK && stack[brakeSystem_Q] == MANDO) &&
        !(stack[brakeSystem_Q] == BOSCH_B && stack[SteeringSystem_Q] != BOSCH_S);
}

void runProducedCar() {
    if (!isValidCombination()) {
        printf("자동차가 동작되지 않습니다\n");
    }
    else if (stack[Engine_Q] == MALFUNCTION) {
        printf("엔진이 고장나있습니다.\n자동차가 움직이지 않습니다.\n");
    }
    else {
        printf("Car Type : %s\n", carTypes[stack[CarType_Q] - 1]);
        printf("Engine : %s\n", engineNames[stack[Engine_Q] - 1]);
        printf("Brake System : %s\n", brakeNames[stack[brakeSystem_Q] - 1]);
        printf("Steering System : %s\n", steerNames[stack[SteeringSystem_Q] - 1]);
        printf("자동차가 동작됩니다.\n");
    }
}

void testProducedCar() {
    if (!isValidCombination()) {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");

        if (stack[CarType_Q] == SEDAN && stack[brakeSystem_Q] == CONTINENTAL)
            printf("Sedan에는 Continental제동장치 사용 불가\n");
        else if (stack[CarType_Q] == SUV && stack[Engine_Q] == TOYOTA)
            printf("SUV에는 TOYOTA엔진 사용 불가\n");
        else if (stack[CarType_Q] == TRUCK && stack[Engine_Q] == WIA)
            printf("Truck에는 WIA엔진 사용 불가\n");
        else if (stack[CarType_Q] == TRUCK && stack[brakeSystem_Q] == MANDO)
            printf("Truck에는 Mando제동장치 사용 불가\n");
        else
            printf("Bosch제동장치에는 Bosch조향장치 이외 사용 불가\n");
    }
    else {
        printf("자동차 부품 조합 테스트 결과 : PASS\n");
    }
}


int main() {
    char buf[100];
    int step = CarType_Q;

    while (1) {
        printMenu(step);
        fgets(buf, sizeof(buf), stdin);

        char* p = strchr(buf, '\n');
        if (p) *p = '\0';

        if (!strcmp(buf, "exit")) {
            printf("바이바이\n");
            break;
        }

        char* endptr;
        int answer = strtol(buf, &endptr, 10);

        if (!isValidInput(endptr, step, answer)) {
            continue;
        }

        if (step == Run_Test && answer == 0) {
            step = CarType_Q;
            continue;
        }

        if (answer == 0 && step > 0) {
            step--;
            continue;
        }

        if (step <= SteeringSystem_Q) {
            selectPart(step, answer);
            delay(800);
            step++;
        }
        else if (step == Run_Test) {
            if (answer == 1) {
                runProducedCar();
                delay(2000);
            }
            else if (answer == 2) {
                printf("Test...\n");
                delay(1500);
                testProducedCar();
                delay(2000);
            }
        }
    }
    return 0;
}

#endif