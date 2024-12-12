void getAndValidateEquationType(enum EquationType *equationType)
{
    do
    {
        printf("Enter the equation type to solve: '1' - 1) '2' - 2): ");

        char equationTypeInput = getchar();
        fflush(stdin);

        switch (equationTypeInput)
        {
        case '1':
        {
            *equationType = TRIGONOMETRIC_FRACTIONS;
            break;
        }
        case '2':
        {
            *equationType = TRIGONOMETRIC_LOGARITHM;
            break;
        }
        default:
        {
            printf("Invalid value for equation type. Please enter '1' or '2'.\n");
        }
        }
    } while (*equationType == 0);
}

void getAndValidateEquationSolvingMethod(enum SolveEquationMethod *solvingMethod)
{
    do
    {
        printf("Enter the equation solving method '1' - Half Dividing, '2' - Newton method: ");

        char solvingMethodInput = getchar();
        fflush(stdin);

        switch (solvingMethodInput)
        {
        case '1':
        {
            *solvingMethod = HALF_DIVIDING;
            break;
        }
        case '2':
        {
            *solvingMethod = NEWTON;
            break;
        }
        default:
        {
            printf("Invalid value for solving method. Please enter '1' or '2'.\n");
        }
        }
    } while (*solvingMethod == 0);
}

void getAndValidateRange(double *rangeStart, double *rangeEnd)
{
    bool isValid = false;

    do
    {
        printf("Enter the left range value, less than right (between %d and %d): ", MIN_RANGE_LIMIT, MAX_RANGE_LIMIT);
        isValid = scanf("%lf", rangeStart);
        fflush(stdin);

        if (!isValid)
        {
            printf("Invalid input for left range value. Please enter an integer.\n");

            continue;
        }

        if (*rangeStart < MIN_RANGE_LIMIT || *rangeEnd > MAX_RANGE_LIMIT)
        {
            printf("Left range value is out of range. Please enter a value between %d and %d.\n", MIN_RANGE_LIMIT, MAX_RANGE_LIMIT);

            isValid = false;
        }
    } while (!isValid);

    do
    {
        printf("Enter the right range value, greater than left (between %d and %d): ", MIN_RANGE_LIMIT, MAX_RANGE_LIMIT);
        isValid = scanf("%lf", rangeEnd);
        fflush(stdin);

        if (!isValid)
        {
            printf("Invalid input for right range value. Please enter an integer.\n");

            continue;
        }

        if (*rangeEnd <= *rangeStart)
        {
            printf("Invalid input for right range value. It must be greater than left range value.\n");

            isValid = false;
        }
        else if (*rangeEnd < MIN_RANGE_LIMIT || *rangeEnd > MAX_RANGE_LIMIT)
        {
            printf("Right range value is out of range. Please enter a value between %d and %d.\n", MIN_RANGE_LIMIT, MAX_RANGE_LIMIT);

            isValid = false;
        }

    } while (!isValid);
}

void getAndValidateEpsilon(double *epsilon)
{
    do
    {
        printf("Enter the accuracy from %.0e to %.0e (e.g., 0.0001): ", MIN_EPSILON, MAX_EPSILON);
        if (scanf("%lf", epsilon) != 1)
        {
            printf("Invalid input for accuracy. Please enter a valid number.\n");
            fflush(stdin);

            continue;
        }
        fflush(stdin);

        if (*epsilon < MIN_EPSILON || *epsilon > MAX_EPSILON)
        {
            printf("Accuracy value is out of range. Please enter a value between %.0e and %.0e.\n", MIN_EPSILON, MAX_EPSILON);
        }
    } while (*epsilon < MIN_EPSILON || *epsilon > MAX_EPSILON);
}

void getAndValidateY(int *y)
{
    do
    {
        printf("Enter the Y value from %d to %d: ", MIN_Y, MAX_Y);

        if (scanf("%d", y) != 1)
        {
            printf("Invalid input for Y. Please enter a valid number.\n");
            fflush(stdin);

            continue;
        }
        fflush(stdin);

        if (*y < MIN_Y || *y > MAX_Y)
        {
            printf("Y value is out of range. Please enter a value between %d and %d.\n", MIN_Y, MAX_Y);
        }
    } while (*y < MIN_Y || *y > MAX_Y);
}

bool askToContinue()
{
    printf("Do you want to run program again? Press 'y' to continue or any other key to exit: ");

    int key = getchar();
    fflush(stdin);

    return key == 'y';
}

double truncateNumber(double value, int decimalPlaces)
{
    double factor = pow(10.0, (double)decimalPlaces);

    return trunc(value * factor) / factor;
}

int getDecimalPlaces(double epsilon)
{
    return -log10(epsilon);
}

double solveTrigonometricFractionEquation(double x, double y)
{
    return cos(y / x) - 2.0 * sin(1.0 / x) + 1.0 / x;
}

double solveTrigonometricLogarithmEquation(double x, double y)
{
    return sin(log(x)) - cos(log(x)) + y * log(x);
}

double getTrigonometricFractionDerivative(double x, double y)
{
    return (solveTrigonometricFractionEquation(x + EPSILON_FOR_NEWTON, y) - solveTrigonometricFractionEquation(x, y)) / EPSILON_FOR_NEWTON;
}

double getTrigonometricLogarithmDerivative(double x, double y)
{
    return (solveTrigonometricLogarithmEquation(x + EPSILON_FOR_NEWTON, y) - solveTrigonometricLogarithmEquation(x, y)) / EPSILON_FOR_NEWTON;
}

double solveByHalfDividing(double (*equationFunc)(double, double), double rangeStart, double rangeEnd, double y, double epsilon)
{
    while (fabs(rangeEnd - rangeStart) > epsilon)
    {
        double mid = (rangeStart + rangeEnd) / 2.0;

        if (equationFunc(rangeStart, y) * equationFunc(mid, y) > 0)
            rangeStart = mid;
        else
            rangeEnd = mid;
    }

    return (rangeStart + rangeEnd) / 2.0;
}

double solveByNewton(double (*equationFunc)(double, double), double (*derivative)(double, double), double x0, double y, double epsilon)
{
    double x1 = 0.0;
    double delta = 0.0;

    do
    {
        delta = equationFunc(x0, y) / derivative(x0, y);
        x1 = x0 - delta;
        x0 = x1;
    } while (fabs(delta) > epsilon);

    return x1;
}

bool handleContinueWithErrorMessage(char *errorMessage)
{
    printf("%s\n", errorMessage);
    printf("\n");

    return askToContinue();
}