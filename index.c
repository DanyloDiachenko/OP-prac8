#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
    double real;
    double imaginary;
} complex;

complex divideComplexNumbers(complex complexNumber1, complex complexNumber2)
{
    double complexSquare = complexNumber2.real * complexNumber2.real + complexNumber2.imaginary * complexNumber2.imaginary;

    complex result;
    result.real = (complexNumber1.real * complexNumber2.real + complexNumber1.imaginary * complexNumber2.imaginary) / complexSquare;
    result.imaginary = (complexNumber1.imaginary * complexNumber2.real - complexNumber1.real * complexNumber2.imaginary) / complexSquare;

    return result;
}

void printComplexNumber(complex complexNumber)
{
    printf("%.6e + i * %.6e", complexNumber.real, complexNumber.imaginary);
}

double getResonantFrequency(double inductance, double capacitance)
{
    return 1.0 / (2 * M_PI * sqrt(inductance * capacitance));
}

complex getImpedance12(double resistance, double inductance, double capacitance, double omega)
{
    complex numerator;
    numerator.real = inductance / capacitance;
    numerator.imaginary = -resistance / (omega * capacitance);

    complex denominator;
    denominator.real = resistance;
    denominator.imaginary = omega * inductance - 1.0 / (omega * capacitance);

    return divideComplexNumbers(numerator, denominator);
}

complex getImpedance3(double resistance1, double resistance2, double inductance, double capacitance, double omega)
{
    double a = resistance1 * resistance2;
    double b = resistance1 * (omega * inductance - 1.0 / (omega * capacitance));
    double c = resistance1 + resistance2;
    double d = omega * inductance - 1.0 / (omega * capacitance);

    complex numerator;
    numerator.real = a + b;
    numerator.imaginary = d;

    complex denominator;
    denominator.real = c;
    denominator.imaginary = d;

    return divideComplexNumbers(numerator, denominator);
}

complex getImpedance4(double resistance1, double resistance2, double inductance, double capacitance, double omega)
{
    double a = resistance1 * resistance2;
    double b = omega * inductance * resistance1 - resistance2 / (omega * capacitance);
    double c = resistance1 + resistance2;
    double d = omega * inductance - 1.0 / (omega * capacitance);

    complex numerator;
    numerator.real = a + inductance / capacitance;
    numerator.imaginary = b;

    complex denominator;
    denominator.real = c;
    denominator.imaginary = d;

    return divideComplexNumbers(numerator, denominator);
}

int main()
{
    int circuitChoice;
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
