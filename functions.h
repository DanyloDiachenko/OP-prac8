#ifndef FUNCTIONS_H
#define FUNCTIONS_H

complex divideComplexNumbers(complex complexNumber1, complex complexNumber2);
void printComplexNumber(complex complexNumber);
double getResonantFrequency(double inductance, double capacitance);
complex getImpedance12(double resistance, double inductance, double capacitance, double omega);
complex getImpedance3(double resistance1, double resistance2, double inductance, double capacitance, double omega);
complex getImpedance4(double resistance1, double resistance2, double inductance, double capacitance, double omega);

#endif // FUNCTIONS_H
