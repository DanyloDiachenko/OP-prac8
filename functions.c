#include "./includes.h";

Complex divideComplexNumbers(Complex complexNumber1, Complex complexNumber2)
{
    double complexSquare = complexNumber2.real * complexNumber2.real + complexNumber2.imaginary * complexNumber2.imaginary;

    Complex result;
    result.real = (complexNumber1.real * complexNumber2.real + complexNumber1.imaginary * complexNumber2.imaginary) / complexSquare;
    result.imaginary = (complexNumber1.imaginary * complexNumber2.real - complexNumber1.real * complexNumber2.imaginary) / complexSquare;

    return result;
}

void printComplexNumber(Complex complexNumber)
{
    printf("Value: %.12e + i * %.12e", complexNumber.real, complexNumber.imaginary);
}

double getResonantFrequency(double inductance, double capacitance)
{
    return 1.0 / (2.0 * M_PI * sqrt(inductance * capacitance));
}

Complex getSeriesLCImpedance(double resistance, double inductance, double capacitance, double omega)
{
    Complex numerator;
    numerator.real = inductance / capacitance;
    numerator.imaginary = -resistance / (omega * capacitance);

    Complex denominator;
    denominator.real = resistance;
    denominator.imaginary = omega * inductance - 1.0 / (omega * capacitance);

    return divideComplexNumbers(numerator, denominator);
}

Complex getParallelRLImpedance(double resistance1, double resistance2, double inductance, double capacitance, double omega)
{
    double a = resistance1 * resistance2;
    double b = resistance1 * (omega * inductance - 1.0 / (omega * capacitance));
    double c = resistance1 + resistance2;
    double d = omega * inductance - 1.0 / (omega * capacitance);

    Complex numerator;
    numerator.real = a + b;
    numerator.imaginary = d;

    Complex denominator;
    denominator.real = c;
    denominator.imaginary = d;

    return divideComplexNumbers(numerator, denominator);
}

Complex getParallelRLCImpedance(double resistance1, double resistance2, double inductance, double capacitance, double omega)
{
    double a = resistance1 * resistance2;
    double b = omega * inductance * resistance1 - resistance2 / (omega * capacitance);
    double c = resistance1 + resistance2;
    double d = omega * inductance - 1.0 / (omega * capacitance);

    Complex numerator;
    numerator.real = a + inductance / capacitance;
    numerator.imaginary = b;

    Complex denominator;
    denominator.real = c;
    denominator.imaginary = d;

    return divideComplexNumbers(numerator, denominator);
}


void getAndValidateCircuitChoice(int *circuitChoice)
{
    do
    {
        printf("Select the circuit {1, 2, 3, 4}: ");

        char circuitChoiceInput = getchar();
        fflush(stdin);

        switch (circuitChoiceInput)
        {
            case '1':
            {
                *circuitChoice = 1;
                break;
            }
            case '2':
            {
                *circuitChoice = 2;
                break;
            }
            case '3':
            {
                *circuitChoice = 3;
                break;
            }
            case '4':
            {
                *circuitChoice = 4;
                break;
            }
            default:
            {
                printf("Invalid value for circuit number. Please enter '1', '2', '3' or '4'.\n");
            }
        }
    } while (*circuitChoice == 0);
}

void getAndValidateInductance(double *inductance)
{
    do
    {
        printf("Enter the inductance in mHn from %d to %.0e: ", MIN_INDUCTANCE, MAX_INDUCTANCE);
        if (scanf("%lf", inductance) != 1)
        {
            printf("Invalid input for inductance. Please enter a valid number.\n");
            fflush(stdin);

            continue;
        }
        fflush(stdin);

        if (*inductance <= MIN_INDUCTANCE || *inductance > MAX_INDUCTANCE)
        {
            printf("Inductance value is out of range. Please enter a value between %d and %.0e.\n", MIN_INDUCTANCE, MAX_INDUCTANCE);
        }
    } while (*inductance <= MIN_INDUCTANCE || *inductance > MAX_INDUCTANCE);
}

void getAndValidateCapacitance(double *capacitance)
{
    do
    {
        printf("Enter the capacitance in mcF from %d to %.0e: ", MIN_CAPACITANCE, MAX_CAPACITANCE);
        if (scanf("%lf", capacitance) != 1)
        {
            printf("Invalid input for capacitance. Please enter a valid number.\n");
            fflush(stdin);

            continue;
        }
        fflush(stdin);

        if (*capacitance <= MIN_CAPACITANCE || *capacitance > MAX_CAPACITANCE)
        {
            printf("Capacitance value is out of range. Please enter a value between %d and %.0e.\n", MIN_CAPACITANCE, MAX_CAPACITANCE);
        }
    } while (*capacitance <= MIN_CAPACITANCE || *capacitance > MAX_CAPACITANCE);
}

void getAndValidateResistance(double *resistance, const char* resistanceName)
{
    do
    {
        printf("Enter %s in Ohm (from %.0e to %.0e): ", resistanceName, MIN_RESISTANCE, MAX_RESISTANCE);

        if (scanf("%lf", resistance) != 1)
        {
            printf("Invalid input for %s. Please enter a valid number.\n", resistanceName);
            fflush(stdin);

            continue;
        }
        fflush(stdin);

        if (*resistance < MIN_RESISTANCE || *resistance > MAX_RESISTANCE)
        {
            printf("%s value is out of range. Please enter a value between %.0e and %.0e.\n", resistanceName, MIN_RESISTANCE, MAX_RESISTANCE);
        }
    } while (*resistance < MIN_RESISTANCE || *resistance > MAX_RESISTANCE);
}

void getAndValidateFrequencyRange(double *minFrequency, double *maxFrequency)
{
    bool isValid = false;

    do
    {
        printf("Enter minimal frequency, in Hz less than max (between %d and %.0e): ", MIN_FREQUENCY, MAX_FREQUENCY);
        isValid = scanf("%lf", minFrequency);
        fflush(stdin);

        if (!isValid)
        {
            printf("Invalid input for minimal frequency. Please enter an integer.\n");

            continue;
        }

        if (*minFrequency < MIN_FREQUENCY || *minFrequency > MAX_FREQUENCY)
        {
            printf("Minimal frequency range is out of range. Please enter a value between %d and %.0e.\n", MIN_FREQUENCY, MAX_FREQUENCY);

            isValid = false;
        }
    } while (!isValid);

    do
    {
        printf("Enter the maximum frequency, in Hz greater than left (between %d and %.0e): ", MIN_FREQUENCY, MAX_FREQUENCY);
        isValid = scanf("%lf", maxFrequency);
        fflush(stdin);

        if (!isValid)
        {
            printf("Invalid input for maximum frequency. Please enter an integer.\n");

            continue;
        }

        if (*maxFrequency <= *minFrequency)
        {
            printf("Invalid input for maximum frequency. It must be greater than left range value.\n");

            isValid = false;
        }
        else if (*maxFrequency < MIN_FREQUENCY || *maxFrequency > MAX_FREQUENCY)
        {
            printf("Maximum frequency is out of range. Please enter a value between %d and %.0e.\n", MIN_FREQUENCY, MAX_FREQUENCY);

            isValid = false;
        }

    } while (!isValid);
}

void getAndValidateFrequencyStep(double *frequencyStep)
{
    do
    {
        printf("Enter frequency step in Hz (from %.0e to %.0e): ", MIN_FREQUENCY_STEP, MAX_FREQUENCY_STEP);

        if (scanf("%lf", frequencyStep) != 1)
        {
            printf("Invalid input for frequency step. Please enter a valid number.\n");
            fflush(stdin);

            continue;
        }
        fflush(stdin);

        if (*frequencyStep < MIN_FREQUENCY_STEP || *frequencyStep > MAX_FREQUENCY_STEP)
        {
            printf("Frequency step value is out of range. Please enter a value between %.0e and %.0e.\n", MIN_FREQUENCY_STEP, MAX_FREQUENCY_STEP);
        }
    } while (*frequencyStep < MIN_FREQUENCY_STEP || *frequencyStep > MAX_FREQUENCY_STEP);
}

bool askToContinue()
{
    printf("Do you want to run program again? Press 'y' to continue or any other key to exit: ");

    int key = getchar();
    fflush(stdin);

    return key == 'y';
}