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
const char* engineNames[] = { "GM", "TOYOTA", "WIA", "���峭 ����" };
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
        message = "���ڸ� �Է� ����";
        ret = false;
    }
    else if (step == CarType_Q && (answer < 1 || answer > 3)) {
        message = "���� Ÿ���� 1 ~ 3 ������ ���� ����";
        ret = false;
    }
    else if (step == Engine_Q && (answer < 0 || answer > 4)) {
        message = "������ 1 ~ 4 ������ ���� ����";
        ret = false;
    }
    else if (step == brakeSystem_Q && (answer < 0 || answer > 3)) {
        message = "������ġ�� 1 ~ 3 ������ ���� ����";
        ret = false;
    }
    else if (step == SteeringSystem_Q && (answer < 0 || answer > 2)) {
        message = "������ġ�� 1 ~ 2 ������ ���� ����";
        ret = false;
    }
    else if (step == Run_Test && (answer < 0 || answer > 2)) {
        message = "Run �Ǵ� Test �� �ϳ��� ���� �ʿ�";
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
        printf("� ���� Ÿ���� �����ұ��?\n1. Sedan\n2. SUV\n3. Truck\n"); break;
    case Engine_Q:
        printf("� ������ ž���ұ��?\n0. �ڷΰ���\n1. GM\n2. TOYOTA\n3. WIA\n4. ���峭 ����\n"); break;
    case brakeSystem_Q:
        printf("� ������ġ�� �����ұ��?\n0. �ڷΰ���\n1. MANDO\n2. CONTINENTAL\n3. BOSCH\n"); break;
    case SteeringSystem_Q:
        printf("� ������ġ�� �����ұ��?\n0. �ڷΰ���\n1. BOSCH\n2. MOBIS\n"); break;
    case Run_Test:
        printf("���� ������ �ϼ��Ǿ����ϴ�.\n� ������ �ұ��?\n0. ó�� ȭ������ ���ư���\n1. RUN\n2. Test\n"); break;
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
    case CarType_Q: val1 = "���� Ÿ������"; val2 = carTypes[answer - 1]; val3 = "��"; break;
    case Engine_Q: val1 = engineNames[answer - 1]; val2 = "����"; val3 = "��"; break;
    case brakeSystem_Q: val1 = brakeNames[answer - 1]; val2 = "������ġ"; val3 = "��"; break;
    case SteeringSystem_Q: val1 = steerNames[answer - 1]; val2 = "������ġ"; val3 = "��";  break;
    }
    printf("%s %s%s �����ϼ̽��ϴ�.\n", val1, val2, val3);
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
        printf("�ڵ����� ���۵��� �ʽ��ϴ�\n");
    }
    else if (stack[Engine_Q] == MALFUNCTION) {
        printf("������ ���峪�ֽ��ϴ�.\n�ڵ����� �������� �ʽ��ϴ�.\n");
    }
    else {
        printf("Car Type : %s\n", carTypes[stack[CarType_Q] - 1]);
        printf("Engine : %s\n", engineNames[stack[Engine_Q] - 1]);
        printf("Brake System : %s\n", brakeNames[stack[brakeSystem_Q] - 1]);
        printf("Steering System : %s\n", steerNames[stack[SteeringSystem_Q] - 1]);
        printf("�ڵ����� ���۵˴ϴ�.\n");
    }
}

void testProducedCar() {
    if (!isValidCombination()) {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");

        if (stack[CarType_Q] == SEDAN && stack[brakeSystem_Q] == CONTINENTAL)
            printf("Sedan���� Continental������ġ ��� �Ұ�\n");
        else if (stack[CarType_Q] == SUV && stack[Engine_Q] == TOYOTA)
            printf("SUV���� TOYOTA���� ��� �Ұ�\n");
        else if (stack[CarType_Q] == TRUCK && stack[Engine_Q] == WIA)
            printf("Truck���� WIA���� ��� �Ұ�\n");
        else if (stack[CarType_Q] == TRUCK && stack[brakeSystem_Q] == MANDO)
            printf("Truck���� Mando������ġ ��� �Ұ�\n");
        else
            printf("Bosch������ġ���� Bosch������ġ �̿� ��� �Ұ�\n");
    }
    else {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : PASS\n");
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
            printf("���̹���\n");
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