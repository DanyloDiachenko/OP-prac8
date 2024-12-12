#ifndef FUNCTIONS_H
#define FUNCTIONS_H

Complex divideComplexNumbers(Complex complexNumber1, Complex complexNumber2);
void printComplexNumber(Complex complexNumber);
double getResonantFrequency(double inductance, double capacitance);
Complex getSeriesLCImpedance(double resistance, double inductance, double capacitance, double omega);
Complex getParallelRLImpedance(double resistance1, double resistance2, double inductance, double capacitance, double omega);
Complex getParallelRLCImpedance(double resistance1, double resistance2, double inductance, double capacitance, double omega);
void getAndValidateCircuitChoice(int *circuitChoice);
void getAndValidateInductance(double *inductance);
void getAndValidateCapacitance(double *capacitance);
void getAndValidateResistance(double *resistance, const char* resistanceName);
void getAndValidateFrequencyRange(double *minFrequency, double *maxFrequency);
void getAndValidateFrequencyStep(double *frequencyStep);
bool askToContinue();

#endif // FUNCTIONS_H
