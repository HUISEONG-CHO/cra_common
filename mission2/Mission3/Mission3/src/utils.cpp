#include "utils.h"
#include <stdio.h>

void delay(int ms) {
    volatile int sum = 0;
    for (int i = 0; i < 1000; i++)
        for (int j = 0; j < 1000; j++)
            for (int t = 0; t < ms; t++) sum++;
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
    case BrakeSystem_Q:
        printf("어떤 제동장치를 선택할까요?\n0. 뒤로가기\n1. MANDO\n2. CONTINENTAL\n3. BOSCH\n"); break;
    case SteeringSystem_Q:
        printf("어떤 조향장치를 선택할까요?\n0. 뒤로가기\n1. BOSCH\n2. MOBIS\n"); break;
    case Run_Test:
        printf("멋진 차량이 완성되었습니다.\n어떤 동작을 할까요?\n0. 처음 화면으로 돌아가기\n1. RUN\n2. Test\n"); break;
    }
    printf("===============================\n");
    printf("INPUT > ");
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
    else if (step == BrakeSystem_Q && (answer < 0 || answer > 3)) {
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