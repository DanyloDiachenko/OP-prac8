#ifndef FUNCTIONS_H
#define FUNCTIONS_H

complex divideComplexNumbers(complex complexNumber1, complex complexNumber2);
void printComplexNumber(complex complexNumber);
double getResonantFrequency(double inductance, double capacitance);
complex getImpedance12(double resistance, double inductance, double capacitance, double omega);
complex getImpedance3(double resistance1, double resistance2, double inductance, double capacitance, double omega);
complex getImpedance4(double resistance1, double resistance2, double inductance, double capacitance, double omega);
void getAndValidateCircuitChoice(int *circuitChoice);
void getAndValidateInductance(double *inductance);
void getAndValidateCapacitance(double *capacitance);
void getAndValidateResistance(double *resistance, const char* resistanceName);
void getAndValidateFrequencyRange(double *minFrequency, double *maxFrequency);
void getAndValidateFrequencyStep(double *frequencyStep);
bool askToContinue();

#endif // FUNCTIONS_H
