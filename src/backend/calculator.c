#include "SmartCalc.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/**
 * @brief Функция подсчитывает результат, используя алгоритм подсчета ОПН
 * @param polish_notation Указатель на стек, содержащий выражение в виде ОПН
 * @param error_flag Указатель на индикатор ошибки, который обрабатывается на
 * всех уровнях работы программы
 * @param x_val Значение Х, имеет смысл только при подсчете функций для
 * построения графика, будет подставлено вместо Х при подсчете
 * @return Односвязный список, содержащий в себе один элемент - ответ, если не
 * было вычислительных ошибок, указатель на NULL в ином случае
 */
stack_sc *calculator(stack_sc *polish_notation, int *error_flag, double x_val) {
  stack_sc *operations = {0};
  while (polish_notation) {
    if (polish_notation->is_num == 1) {
      int priority = polish_notation->priority;
      push(&operations, pop(&polish_notation), priority);
      operations->is_num = 1;
    } else if (polish_notation->is_num == 2) {
      int priority = polish_notation->priority;
      pop(&polish_notation);
      push(&operations, x_val, priority);
      operations->is_num = 2;
    } else if (polish_notation->priority != 4) {
      char op = pop(&polish_notation);
      double num_2 = pop(&operations);
      double num_1 = pop(&operations);
      if (detection_errors(num_2, op, error_flag) == 0) {
        double result = make_calc(num_1, num_2, op);
        push(&operations, result, 0);
        operations->is_num = 1;
      } else {
        if (operations) free_stack(&operations);
        if (polish_notation) free_stack(&polish_notation);
      }
    } else {
      char op = pop(&polish_notation);
      double num = pop(&operations);
      if (detection_errors(num, op, error_flag) == 0) {
        double result = make_calc_pref(num, op);
        push(&operations, result, 0);
        operations->is_num = 1;
      } else {
        if (operations) free_stack(&operations);
        if (polish_notation) free_stack(&polish_notation);
      }
    }
  }
  return operations;
}

/**
 * @brief Функция совершает постфиксные операции (+, -, *...)
 * @param num_1 Первое число для совершения операции
 * @param num_2 Второе число для совершения операции
 * @param op Знак операции
 * @return Число с плавающей точкой - результат операции
 */
double make_calc(double num_1, double num_2, char op) {
  double result = 0;
  switch (op) {
    case '+':
      result = num_1 + num_2;
      break;
    case '-':
      result = num_1 - num_2;
      break;
    case '*':
      result = num_1 * num_2;
      break;
    case '/':
      result = num_1 / num_2;
      break;
    case '^':
      result = pow(num_1, num_2);
      break;
    case 'm':
      result = fmod(num_1, num_2);
      break;
  }
  return result;
}

/**
 * @brief Функция совершает префиксные операции (sin, cos, tan...)
 * @param num Число для совершения операции
 * @param op Знак операции
 * @return Число с плавающей точкой - результат операции
 */
double make_calc_pref(double num, char op) {
  double result = 0;
  switch (op) {
    case 's':
      result = sin(num);
      break;
    case 'q':
      result = sqrt(num);  // >= 0
      break;
    case 'n':
      result = asin(num);  // [-1; 1]
      break;
    case 'o':
      result = acos(num);  // [-1; 1]
      break;
    case 'a':
      result = atan(num);
      break;
    case 'l':
      result = log(num);  // > 0
      break;
    case 'g':
      result = log10(num);  // > 0
      break;
    case 't':
      result = tan(num);  // != +-PI/2
      break;
    case 'c':
      result = cos(num);
      break;
  }
  return result;
}

/**
 * @brief Функция обнаруживает ошибки вычисления в операциях
 * @param num Число для совершения операции
 * @param op Знак операции
 * @param error_flag Указатель на номер ошибки
 * @return Результат операции
 */
int detection_errors(double num, char op, int *error_flag) {
  int flag = 0;

  if ((op == '/' || op == 'm') && num == 0) {
    *error_flag = DIV_BY_ZERO;
    flag++;
  } else if ((op == 'l' || op == 'g') && num <= 0.0) {
    *error_flag = LOG_ARG_LE_ZERO;
    flag++;
  } else if ((op == 'o' || op == 'n') && (num < -1.0 || num > 1.0)) {
    *error_flag = AFUNC_ARG_OUT_OF_RANGE;
    flag++;
  } else if (op == 'q' && num < 0) {
    *error_flag = SQRT_ARG_L_ZERO;
    flag++;
  }

  return flag;
}