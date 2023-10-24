#include "SmartCalc.h"

/**
 * @brief Функция парсит проверенную на корректность строку на лексеммы
 * @param input Входная строка, которую функция будет парсить
 * @return Односвязный список из лексемм, записанных в порядке их следования, с
 * учтенным приоритетом и флагом на число или икс
 */
stack_sc *input_parser(char *input) {
  stack_sc *parse = {0};
  int len_input = strlen(input);
  int unar_minus_flag = 0;
  for (int i = 0; i < len_input; i++) {
    // Если токен - цифра
    if (isdigit(input[i])) {
      char buff[255] = {0};
      for (int j = 0;
           j < 255 && (isdigit(input[i]) || input[i] == '.') && i < len_input;
           j++, i++) {
        buff[j] = input[i];
      }
      double num = 0;
      sscanf(buff, "%lf", &num);
      if (unar_minus_flag == 1) {
        num *= -1;
        unar_minus_flag = 0;
      }
      push(&parse, num, 0);
      parse->is_num = 1;
    }
    if (input[i] == '+' || input[i] == '-' || input[i] == '*' ||
        input[i] == '/' || input[i] == '^' || input[i] == '-' ||
        input[i] == ')' || input[i] == '(') {
      push(&parse, input[i], check_priority(input[i]));
    }
    if (input[i] == 'X' || input[i] == 'x') {
      push(&parse, input[i], check_priority(input[i]));
      parse->is_num = 2;
    }
    if (input[i] == '~') {
      unar_minus_flag = 1;
    }
    if (input[i] == 'm' && input[i + 1] == 'o' && input[i + 2] == 'd') {
      push(&parse, 'm', check_priority(input[i]));
      i += 2;
    }
    if (input[i] == 'c' && input[i + 1] == 'o' && input[i + 2] == 's') {
      push(&parse, 'c', check_priority(input[i]));
      i += 2;
    }
    if (input[i] == 't' && input[i + 1] == 'a' && input[i + 2] == 'n') {
      push(&parse, 't', check_priority(input[i]));
      i += 2;
    }
    if (i < len_input - 3 && input[i] == 's' && input[i + 1] == 'i' &&
        input[i + 2] == 'n') {
      push(&parse, 's', check_priority(input[i]));
      i += 2;
    }
    if (i < len_input - 4 && input[i] == 's' && input[i + 1] == 'q' &&
        input[i + 2] == 'r' && input[i + 3] == 't') {
      push(&parse, 'q', check_priority(input[i]));
      i += 3;
    }
    if (input[i] == 'a' && input[i + 1] == 's' && input[i + 2] == 'i' &&
        input[i + 3] == 'n') {
      push(&parse, 'n', check_priority(input[i]));
      i += 3;
    }
    if (input[i] == 'a' && input[i + 1] == 'c' && input[i + 2] == 'o' &&
        input[i + 3] == 's') {
      push(&parse, 'o', check_priority(input[i]));
      i += 3;
    }
    if (input[i] == 'a' && input[i + 1] == 't' && input[i + 2] == 'a' &&
        input[i + 3] == 'n') {
      push(&parse, 'a', check_priority(input[i]));
      i += 3;
    }
    if (input[i] == 'l' && input[i + 1] == 'o' && input[i + 2] == 'g') {
      push(&parse, 'g', check_priority(input[i]));
      i += 2;
    }
    if (input[i] == 'l' && input[i + 1] == 'n') {
      push(&parse, 'l', check_priority(input[i]));
      i++;
    }
  }
  stack_sc *reverse_parse = {0};
  while (parse) {
    int priority = parse->priority;
    if (parse->is_num == 1) {
      push(&reverse_parse, pop(&parse), priority);
      reverse_parse->is_num = 1;
    } else if (parse->is_num == 2) {
      push(&reverse_parse, pop(&parse), priority);
      reverse_parse->is_num = 2;
    } else {
      push(&reverse_parse, pop(&parse), priority);
    }
  }

  return reverse_parse;
}

/**
 * @brief Функция определяет приоритет операции
 * @param token Операция, приоритет которой будет проверен
 * @return Целое число - приоритет операции
 */
int check_priority(char token) {
  int priority = 0;
  switch (token) {
    case 'x':
      priority = 0;
      break;
    case ')':
      priority = 0;
      break;
    case '(':
      priority = 0;
      break;
    case '+':
      priority = 1;
      break;
    case '-':
      priority = 1;
      break;
    // case '~':
    //   priority = 1;
    //   break;
    // case '#':
    //   priority = 1;
    //   break;
    case '*':
      priority = 2;
      break;
    case '/':
      priority = 2;
      break;
    case 'm':
      priority = 2;
      break;
    case '^':
      priority = 3;
      break;
    default:
      priority = 4;
      break;
  }
  return priority;
}
