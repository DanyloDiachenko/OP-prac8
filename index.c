#include "./includes.h"

int main()
{
    bool continueProgram = true;

    printf("Welcome! This program helps you calculate complex resistance of various circuits based on your input parameters.\n\n");

    do
    {
        int circuitChoice = 0;
        double resistance = 0.0;
        double resistance1 = 0.0;
        double resistance2 = 0.0;
        double inductance = 0.0;
        double capacitance = 0.0;
        double minFrequency = 0.0;
        double maxFrequency = 0.0;
        double frequencyStep = 0.0;

        getAndValidateCircuitChoice(&circuitChoice);
        getAndValidateInductance(&inductance);
        getAndValidateCapacitance(&capacitance);

        if (circuitChoice == 3 || circuitChoice == 4)
        {
            getAndValidateResistance(&resistance1, "resistance 1");
            getAndValidateResistance(&resistance2, "resistance 2");
        }
        else
        {
            getAndValidateResistance(&resistance, "resistance");
        }

        getAndValidateFrequencyRange(&minFrequency, &maxFrequency);
        getAndValidateFrequencyStep(&frequencyStep);

        double resonantFrequency = getResonantFrequency(inductance, capacitance);
        printf("\n");
        printf("Resonant frequency: %.12e Hz\n", resonantFrequency);

        double frequency = minFrequency;
        do
        {
            double omega = 2.0 * M_PI * frequency;
            Complex impedance;

            switch (circuitChoice)
            {
            case 1:
            case 2:
            {
                impedance = getSeriesLCImpedance(resistance, inductance, capacitance, omega);
                break;
            }

            case 3:
            {
                impedance = getParallelRLImpedance(resistance1, resistance2, inductance, capacitance, omega);
                break;
            }

            case 4:
            {
                impedance = getParallelRLCImpedance(resistance1, resistance2, inductance, capacitance, omega);
                break;
            }

            default:
            {
                printf("Invalid circuit choice!\n");

                continueProgram = askToContinue();
                if (!continueProgram)
                {
                    break;
                }
            }
            }

            printf("Frequency: %.1e\t", frequency);
            printComplexNumber(impedance);
            printf("\n");

            frequency += frequencyStep;
        } while (frequency <= maxFrequency);

        printf("\n");
        continueProgram = askToContinue();
    } while (continueProgram);

    return 0;
}
