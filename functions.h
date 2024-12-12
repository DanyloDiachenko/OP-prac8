#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void getAndValidateEquationType(enum EquationType *equationType);
void getAndValidateEquationSolvingMethod(enum SolveEquationMethod *solvingMethod);
void getAndValidateRange(double *rangeStart, double *rangeEnd);
void getAndValidateEpsilon(double *epsilon);
bool askToContinue();
double truncateNumber(double value, int decimalPlaces);
int getDecimalPlaces(double epsilon);
double solveTrigonometricFractionEquation(double x, double y);
double solveTrigonometricLogarithmEquation(double x, double y);
double getTrigonometricFractionDerivative(double x, double y);
double getTrigonometricLogarithmDerivative(double x, double y);
double solveByHalfDividing(double (*equationFunc)(double, double), double rangeStart, double rangeEnd, double y, double epsilon);
double solveByNewton(double (*equationFunc)(double, double), double (*derivative)(double, double), double x0, double y, double epsilon);
bool handleContinueWithErrorMessage(char *errorMessage);

#endif // FUNCTIONS_H
