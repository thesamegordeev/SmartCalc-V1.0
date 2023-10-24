#include <ctype.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_ERROR 1
#define DIV_BY_ZERO 2
#define LOG_ARG_LE_ZERO 3
#define AFUNC_ARG_OUT_OF_RANGE 4
#define SQRT_ARG_L_ZERO 5

int smartcalc(char *input, double *res);

/*
INPUT CHECK
*/

int validator(char *input, int *error_flag);
int is_brackers_correct(char *input);
int is_x_in_input(char *input);
int is_x_correct_position(char *input);
int is_dot_correct_position(char *input);
int is_op_correct_position(char *input);
int unary_ops(char *input, int i, int input_len);
int non_unary_ops(char *input, int i, int input_len);
int check_mod(char *input, int i, int input_len);
int check_func_args(char *input, int i, int input_len);
int is_only_brackets(char *input);
int only_one_dot_in_digit(char *input);
int missed_operation(char *input);

/*
OPERATIONS WITH X
*/

int is_x_in_input(char *input);

/*
STACK
*/

/**
 * @brief Структура стека на односвязном списке для парсинга, польской нотации и
 * подсчета результата
 * @param token Хранит данные
 * @param priority Хранит в себе приоритет лексеммы для корректного
 * преобразования в ОПН
 * @param is_num Хранит в себе флаг, является элемент числом, Х или операцией,
 * для обработки ввода и ОПН
 * @param next Указатель на следующий элемент стека
 */
typedef struct stack_sc {
  double token;
  int priority;
  int is_num;
  struct stack_sc *next;
} stack_sc;

typedef struct freq {
  int frq;  // 0 - None, 1 - Once a month, 2 - Every quarter, 3 - Every 6 month,
            // 4 - Every year
  double sum;
} freq;

double pop(stack_sc **head);
void push(stack_sc **head, double token, int priority);
void free_stack(stack_sc **head);
void printStack(const stack_sc *head);
stack_sc *copy_stack(stack_sc *head);

/*
PARSER
*/

stack_sc *input_parser(char *input);
int check_priority(char token);

/*
Reverse Polish Notation interpreter
*/

stack_sc *dijkstra(stack_sc *lexemes);

/*
Calculation
*/

stack_sc *calculator(stack_sc *polish_notation, int *error_flag, double x_val);
double make_calc(double num_1, double num_2, char op);
double make_calc_pref(double num, char op);
int detection_errors(double num, char op, int *error_flag);

/*
Credit Calc
*/

int mon_payment_ann(double sum_cred, double percent, int term, double *result);
int accured_interest_ann(double monthly_payment, double sum_cred, int term,
                         double *result);

int mon_payment_diff(double sum_cred, int term, double *remaining,
                     double percent, double *result);
int accured_interest_diff(double remaining, double percent, double *result);
int total_payout(double loan_amount, double overpayment, double *result);