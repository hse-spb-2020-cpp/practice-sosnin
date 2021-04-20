#ifndef CALC_LIB
#define CALC_LIB

#define CALC_MAX_ARITY 3

#ifdef __cplusplus
extern "C" {
#endif

enum calc_error {
    CALC_ERROR_OK,
    CALC_ERROR_BAD_NUMBER,
    CALC_ERROR_UNKNOWN_FUNCTION,
    CALC_ERROR_EXPECTED_OPEN_PAREN,
    CALC_ERROR_EXPECTED_COMMA,
    CALC_ERROR_EXPECTED_CLOSE_PAREN,
    CALC_ERROR_UNEXPECTED_CHAR,
    CALC_ERROR_EXTRA_INPUT
};

typedef struct calc_function {
    const char *name;
    int arity;
    union {
        double (*func0)(void);
        double (*func1)(double);
        double (*func2)(double, double);
        double (*func3)(double, double, double);
    };
} calc_function;

#define CALC_FUNCTIONS_SENTINEL \
    {                           \
        NULL, 0, {              \
            NULL                \
        }                       \
    }

typedef union calc_result_s {
    double value;
    int error_position;
} calc_result;

int calc_evaluate(const char *expr,
                  calc_result *res,
                  const calc_function *functions
#ifdef __cplusplus
                  = nullptr
#endif
);

#ifdef __cplusplus
}
#endif

#endif  // CALC_LIB
