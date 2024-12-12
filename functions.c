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
    return 1.0 / (2.0 * M_PI * sqrt(inductance * capacitance));
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