#ifdef _DEBUG

#include "gmock/gmock.h"

int main()
{
    testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}

#else

#include "Car.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
    Car car;
    char buf[100];
    int step = CarType_Q;

    while (true)
    {
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

        if (answer == 0) {
            if (step == Run_Test)
                step = CarType_Q;
            else
                step--;
            continue;
        }

        if (step < Run_Test) {
            car.selectPart(step, answer);
            delay(800);
            step++;
        }
        else {
            if (answer == 1) {
                car.runProducedCar();
            }
            else {
                printf("Test...\n");
                delay(1500);
                car.testProducedCar();
            }
            delay(2000);
        }
    }

    return 0;
}

#endif