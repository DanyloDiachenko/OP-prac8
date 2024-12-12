#include "./includes.h"

int main()
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

    printf("Select the circuit {1, 2, 3, 4}: ");
    scanf("%d", &circuitChoice);

    if (circuitChoice < 1 || circuitChoice > 4)
    {
        printf("Invalid circuit choice!\n");

        return 0;
    }

    printf("Enter inductance (mH): ");
    scanf("%lf", &inductance);

    printf("Enter capacitance (uF): ");
    scanf("%lf", &capacitance);

    if (circuitChoice == 3 || circuitChoice == 4)
    {
        printf("Enter resistance 1 (Ohms): ");
        scanf("%lf", &resistance1);
        printf("Enter resistance 2 (Ohms): ");
        scanf("%lf", &resistance2);
    }
    else
    {
        printf("Enter resistance (Ohms): ");
        scanf("%lf", &resistance);
    }

    printf("Enter min frequency (Hz): ");
    scanf("%lf", &minFrequency);
    printf("Enter max frequency (Hz): ");
    scanf("%lf", &minFrequency);
    printf("Enter step (Hz): ");
    scanf("%lf", &frequencyStep);

    double resonantFrequency = getResonantFrequency(inductance, capacitance);
    printf("Resonant frequency: %.6e Hz\n", resonantFrequency);

    double frequency = minFrequency;

    do
    {
        double omega = 2.0 * M_PI * frequency;
        complex impedance;

        if (circuitChoice == 1 || circuitChoice == 2)
        {
            impedance = getImpedance12(resistance, inductance, capacitance, omega);
        }
        else if (circuitChoice == 3)
        {
            impedance = getImpedance3(resistance1, resistance2, inductance, capacitance, omega);
        }
        else if (circuitChoice == 4)
        {
            impedance = getImpedance4(resistance1, resistance2, inductance, capacitance, omega);
        }

        printf("%.6e\t", frequency);
        printComplexNumber(impedance);
        printf("\n");

        frequency += frequencyStep;
    } while (frequency <= maxFrequency);

    return 0;
}
