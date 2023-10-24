#include "SmartCalc.h"

int smartcalc(char *input, double *res) {
  int error_flag = 0;  // Будет передаваться указателем в функции с типом
  // stack, чтобы отлавливать коды ошибок и вытаскивать
  // их к фронтенду для обработки
  if (validator(input, &error_flag) == 0) {
    stack_sc *lexemes = input_parser(input);
    stack_sc *polish_notation = dijkstra(lexemes);
    stack_sc *result = calculator(polish_notation, &error_flag, 0);
    if (error_flag == 0) {
      *res = pop(&result);
      if ((*res < 1e-7 && *res > 0) || (*res > -1e-7 && *res < 0)) *res = 0;
    }
  }
  return error_flag;
}
