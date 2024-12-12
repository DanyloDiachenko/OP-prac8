#include "./includes.h"

int main()
{
    bool continueProgram = true;

    printf("Welcome! This program solves equations!\n"
           "1) cos(y/x) - 2sin(1/x) + 1/x = 0\n"
           "2) sin[ln(x)] - cos[ln(x)] + y*ln(x) = 0\n\n");

    do
    {
        enum EquationType equationType = 0;
        enum SolveEquationMethod solvingMethod = 0;
        double rangeStart = 0.0;
        double rangeEnd = 0.0;
        int y = 0;
        double epsilon = 0.0;

        getAndValidateEquationType(&equationType);
        getAndValidateY(&y);
        getAndValidateRange(&rangeStart, &rangeEnd);
        getAndValidateEquationSolvingMethod(&solvingMethod);
        getAndValidateEpsilon(&epsilon);

        if (solvingMethod == 1 && (solveTrigonometricFractionEquation(rangeStart, (double)y) * solveTrigonometricFractionEquation(rangeEnd, (double)y) > 0))
        {
            continueProgram = handleContinueWithErrorMessage("There are no results on this range or their number greater than 1.");
            if (!continueProgram)
            {
                break;
            };

            continue;
        }
        if (solvingMethod == 2 && (solveTrigonometricLogarithmEquation(rangeStart, (double)y) * solveTrigonometricLogarithmEquation(rangeEnd, (double)y) > 0))
        {
            continueProgram = handleContinueWithErrorMessage("There are no results on this range or their number greater than 1.");
            if (!continueProgram)
            {
                break;
            };

            continue;
        }

        double (*selectedEquation)(double, double) = NULL;
        double (*selectedDerivative)(double, double) = NULL;

        switch (equationType)
        {
        case TRIGONOMETRIC_FRACTIONS:
        {
            selectedEquation = solveTrigonometricFractionEquation;
            selectedDerivative = getTrigonometricFractionDerivative;
            break;
        }
        case TRIGONOMETRIC_LOGARITHM:
        {
            selectedEquation = solveTrigonometricLogarithmEquation;
            selectedDerivative = getTrigonometricLogarithmDerivative;
            break;
        }
        default:
        {
            continueProgram = handleContinueWithErrorMessage("Invalid equation type!");
            if (!continueProgram)
            {
                break;
            };

            continue;
        }
        }

        double result = 0.0;

        switch (solvingMethod)
        {
        case HALF_DIVIDING:
        {
            result = solveByHalfDividing(selectedEquation, rangeStart, rangeEnd, y, epsilon);
            break;
        }
        case NEWTON:
        {
            result = solveByNewton(selectedEquation, selectedDerivative, rangeEnd, y, epsilon);
            break;
        }
            {
                continueProgram = handleContinueWithErrorMessage("Invalid solving method type!");
                if (!continueProgram)
                {
                    break;
                };

                continue;
            }
        }

        if (isnan(result) || isinf(result))
        {
            continueProgram = handleContinueWithErrorMessage("Invalid result is NaN or infinity. Check your input or range and ty agait.");
            if (!continueProgram)
            {
                break;
            };

            continue;
        }

        printf("Result: x = %.*lf\n", getDecimalPlaces(epsilon), truncateNumber(result, getDecimalPlaces(epsilon)));
        printf("\n");

        continueProgram = askToContinue();
    } while (continueProgram);

    return 0;
}
