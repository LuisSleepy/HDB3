/*
 * C implementation of HDB3 line coding scheme
 *
 * Authored by Jan Luis Antoc
 * DLSU-Manila, BS CpE
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main() {
    int initSize = 100;
    char *str = (char *) malloc(initSize * sizeof(char));

    scanf("%s", str);

    int len = strlen(str);
    int hdb3[len];

    int currLvl = 1;
    // For counting the pulses for each substitution
    int pulseCounter = 0;
    // subIndicator - true if the initial substitution has been done
    bool initSub = false;

    for (int i = 0; i < len; i++) {
        switch (str[i]) {

            case '0':
                // Checking for a sequence of for bits of zeroes
                if (str[i + 1] == '0' && str[i + 2] == '0' && str[i + 3] == '0') {
                    //For initial substitution or odd number of pulses between substitution,
                    //use 0 0 0 1 substitution.
                    if (initSub == false || pulseCounter % 2 == 1) {
                        initSub = true;
                        hdb3[i] = hdb3[i + 1] = hdb3[i + 2] = 0;
                        hdb3[i + 3] = 1;

                    } else {
                        // For even number of pulses between substitution,
                        // use B (bipolar) 0 0 1 substitution.
                        hdb3[i] = currLvl;
                        currLvl = -currLvl;
                        hdb3[i + 1] = hdb3[i + 2] = 0;
                        hdb3[i + 3] = 1;
                    }

                    // Moves the index of the string to the index after the fourth zero in the sequence
                    // Then, reset the counter of pulses
                    i = i + 3;
                    pulseCounter = 0;

                // No substitution if there is no sequence of four zeroes
                } else {
                    // Only count pulses after initial substitution has been done
                    if (initSub == true) {
                        pulseCounter++;
                    }
                    hdb3[i] = 0;
                }
                break;

            case '1':
                if (initSub == true) {
                    pulseCounter++;
                }
                hdb3[i] = currLvl;
                currLvl = -currLvl;
                break;

            default:
                break;
        }
    }

    for (int i = 0; i < len; i++) {
        printf("%i ", hdb3[i]);
    }

    free(str);

    return 0;
}