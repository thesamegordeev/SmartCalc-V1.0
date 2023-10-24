#include "SmartCalc.h"

/**
 * @brief Функция первично проверяет корректность ввода данных
 * @param input Указатель на массив чаров (строку), введенную пользователем
 * @return 0 - OK, 1 - ошибка синтаксическая
 */
int validator(char *input, int *error_flag) {
  int result = 0;
  result += strlen(input) == 0;
  is_x_in_input(input);  // X -> x
  result += is_brackers_correct(input);
  result += is_x_correct_position(input);
  result += is_dot_correct_position(input);
  result += is_op_correct_position(input);
  result += is_only_brackets(input);
  result += only_one_dot_in_digit(input);
  result += missed_operation(input);
  if (result != 0) *error_flag = 1;
  return result;
}

/**
 * @brief Функция определяет наличие X в строке и заменяет на х, который
 * распознается парсером
 * @param input Указатель на строку, введенную пользователем
 * @return 0 - х в строке нет, 1 - х в строке находится
 */
int is_x_in_input(char *input) {
  int input_len = strlen(input);
  int is_x = 0;
  for (int i = 0; i < input_len; i++) {
    if (input[i] == 'X' || input[i] == 'x') {
      input[i] = 'x';
      is_x = 1;
    }
  }
  return is_x;
}

/**
 * @brief Функция проверяет корректность ввода X
 * @param input Указатель на строку, введенную пользователем
 * @return 0 - OK, != 0 - ошибка
 */
int is_x_correct_position(char *input) {
  int input_len = strlen(input);
  int flag = 0;
  for (int i = 0; i < input_len; i++) {
    if (i > 0 && i < input_len - 1 &&
        input[i] == 'x') {  // Если х не находится на крайних позициях
      flag += isdigit(input[i - 1]) || input[i - 1] == 'x';
      flag += isdigit(input[i + 1]) || input[i + 1] == 'x';
    } else if (i == 0 && input[i] == 'x') {  // Если х находится в начале строки
      flag += isdigit(input[i + 1]) || input[i + 1] == 'x';
    } else if (i == input_len - 1 &&
               input[i] == 'x') {  // Если х находится в конце строки
      flag += isdigit(input[i - 1]) || input[i - 1] == 'x';
    }
  }
  return flag;
}

/**
 * @brief Функция проверяет корректность ввода скобок
 * @param input Указатель на строку, введенную пользователем
 * @return 0 - OK, != 0 - ошибка
 */
int is_brackers_correct(char *input) {
  int flag = 0;
  int input_len = strlen(input);
  for (int pos = 0; pos < input_len && flag >= 0; pos++) {
    if (input[pos] == '(') {
      flag++;
    } else if (input[pos] == ')') {
      flag--;
    }
  }
  return flag;
}

/**
 * @brief Функция проверяет корректность ввода точек
 * @param input Указатель на строку, введенную пользователем
 * @return 0 - OK, != 0 - ошибка
 */
int is_dot_correct_position(char *input) {
  int input_len = strlen(input);
  int flag = 0;
  for (int i = 0; i < input_len; i++) {
    // Если точка находится не между цифрами или точка стоит на самом первом
    // или на самом последнем месте, значит некорректный ввод
    if ((input[i] == '.' && i > 0 && i < input_len - 1 &&
         (isdigit(input[i - 1]) == 0 || isdigit(input[i + 1]) == 0)) ||
        (input[i] == '.' && (i == 0 || i == input_len - 1))) {
      flag++;
    }
  }
  return flag;
}

/**
 * @brief Функция проверяет корректность ввода операций
 * @param input Указатель на строку, введенную пользователем
 * @return 0 - OK, != 0 - ошибка
 */
int is_op_correct_position(char *input) {
  int input_len = strlen(input);
  int flag = 0;
  for (int i = 0; i < input_len; i++) {
    if (input[i] != '.' && !isdigit(input[i]) && input[i] != 'x') {
      flag += non_unary_ops(input, i, input_len);
      flag += unary_ops(input, i, input_len);
      flag += check_mod(input, i, input_len);
    }
    if (input[i] == 's' || input[i] == 'a' || input[i] == 't' ||
        input[i] == 'l' || input[i] == 'c' || input[i] == '(') {
      flag += check_func_args(input, i, input_len);
    }
  }
  return flag;
}

/**
 * @brief Функция проверяет корректность ввода бинарных операций
 * @param input Указатель на строку, введенную пользователем
 * @param i Итератор, указывающий нынешнее местоположение во входной строке
 * @param input_len Длина строки
 * @return 0 - OK, != 0 - ошибка
 */
int non_unary_ops(char *input, int i, int input_len) {
  char operators[] = {'*', '/', '^'};
  int flag = 0;

  for (int j = 0; j < 3; j++) {
    // Если нынешний токен - оператор, и при этом не находится на крайней
    // позиции, то проверяем окружающие его лексеммы на число, бинарные знаки
    // или x
    if (input[i] == operators[j] && (i != 0 && i != input_len - 1)) {
      // Если окружающие токены - скобки, то флаг учтет это
      flag +=
          (!isdigit(input[i - 1]) && input[i - 1] != 'x' &&
           input[i - 1] != 'c' && input[i - 1] != 't' && input[i - 1] != 'l' &&
           input[i - 1] != 'a' && input[i - 1] != 's' && input[i - 1] != ')') +
          (!isdigit(input[i + 1]) && input[i + 1] != 'x' &&
           input[i + 1] != 'c' && input[i + 1] != 't' && input[i + 1] != 'l' &&
           input[i + 1] != 'a' && input[i + 1] != 's' && input[i + 1] != '(' &&
           input[i + 1] != '-' && input[i + 1] != '+');
    } else if (input[i] == operators[j] && (i == 0 || i == input_len - 1)) {
      flag++;
    }
  }
  return flag;
}

/**
 * @brief Функция проверяет корректность ввода унарных операций
 * @param input Указатель на строку, введенную пользователем
 * @param i Итератор, указывающий нынешнее местоположение во входной строке
 * @param input_len Длина строки
 * @return 0 - OK, != 0 - ошибка
 */
int unary_ops(char *input, int i, int input_len) {
  char unar_operators[] = {'-', '+'};
  char unar_operators_for_change[] = {'~', '#'};
  int flag = 0;
  // В этом цикле проверяются лексеммы операций, которые могут быть
  // унарными, если это подтвердится, то '-' заменится на '~', а '+' на '#'
  // для дальнейшего парсинга
  for (int j = 0; j < 2; j++) {
    // Если нынешний токен - оператор, и при этом не находится на крайней
    // правой позиции, то проверяем лексемму справа на число, унарные знаки
    // или x
    if (input[i] == unar_operators[j] && i != input_len - 1) {
      // Если окружающие токены - скобки, то флаг учтет это
      flag += !isdigit(input[i + 1]) && input[i + 1] != 'x' &&
              input[i + 1] != '(' && input[i + 1] != '-' &&
              input[i + 1] != 'c' && input[i + 1] != 't' &&
              input[i + 1] != 'l' && input[i + 1] != 'a' &&
              input[i + 1] != 's' && input[i + 1] != '+';
    } else if (input[i] == unar_operators[j] && i == input_len - 1) {
      flag++;
    }
    // Тут происходит замена унарных знаков
    if (input[i] == unar_operators[j] &&
        (i == 0 ||
         (!isdigit(input[i - 1]) && input[i - 1] != 'x' &&
          input[i - 1] != 'c' && input[i - 1] != 't' && input[i - 1] != 'l' &&
          input[i - 1] != 'a' && input[i - 1] != 's' && input[i - 1] != ')'))) {
      input[i] = unar_operators_for_change[j];
    }
  }
  return flag;
}

/**
 * @brief Функция проверяет инпут на остутствие операций (не должно быть
 * cos(3)sin(4))
 * @param input Указатель на строку, введенную пользователем
 * @return 0 - OK, != 0 - ошибка
 */
int missed_operation(char *input) {
  int flag = 0;
  int input_len = strlen(input);
  char operations[] = {'+', '-', '*', '/', '^', 'm', ')'};
  int operations_len = strlen(operations);
  for (int i = 0; i < input_len; i++) {
    if (i < input_len - 2 && input[i] == ')') {
      int match_counter = 0;
      for (int j = 0; j < operations_len; j++) {
        if (input[i + 1] != operations[j]) match_counter++;
      }
      flag += match_counter == 7;
    }
  }
  return flag;
}

/**
 * @brief Функция проверяет корректность ввода функции mod
 * @param input Указатель на строку, введенную пользователем
 * @param i Итератор, указывающий нынешнее местоположение во входной строке
 * @param input_len Длина строки
 * @return 0 - OK, != 0 - ошибка
 */
int check_mod(char *input, int i, int input_len) {
  // В этом условии будет проверяться корректность ввода mod
  int flag = 0;
  if (input[i] == 'm' && i != 0 && i != input_len - 3) {
    flag +=
        (!isdigit(input[i - 1]) && input[i - 1] != 'x' && input[i - 1] != ')' &&
         input[i - 1] != 'c' && input[i - 1] != 't' && input[i - 1] != 'l' &&
         input[i - 1] != 'a' && input[i - 1] != 's') +
        (!isdigit(input[i + 3]) && input[i + 3] != 'x' && input[i + 3] != '(' &&
         input[i + 3] != 'c' && input[i + 3] != 't' && input[i + 3] != 'l' &&
         input[i + 3] != 'a' && input[i + 3] != 's');
  } else if (input[i] == 'm' && (i == 0 || i == input_len - 3)) {
    flag++;
  }
  return flag;
}

/**
 * @brief Функция проверяет, не пустые ли скобки при математической функции
 * @param input Указатель на строку, введенную пользователем
 * @param i Итератор, указывающий нынешнее местоположение во входной строке
 * @param input_len Длина строки
 * @return 0 - OK, != 0 - ошибка
 */
int check_func_args(char *input, int i, int input_len) {
  while (input[i] != '(' && i < input_len) i++;
  return i >= input_len - 1 || input[i + 1] == ')';
}

/**
 * @brief Функция проверяет, что помимо скобок и операций в выражении есть
 * числа или х, не должно быть ()+()/()
 * @param input Указатель на строку, введенную пользователем
 * @param i Итератор, указывающий нынешнее местоположение во входной строке
 * @param input_len Длина строки
 * @return 0 - OK, != 0 - ошибка
 */
int is_only_brackets(char *input) {
  int input_len = strlen(input);
  int flag = input_len;
  for (int i = 0; i < input_len; i++) {
    if (isdigit(input[i]) || input[i] == 'x') flag--;
  }
  return flag == input_len;
}

/**
 * @brief Функция для проверки наличия только одной точки в числе, то есть не
 * должно быть 123.456.789
 * @param input Указатель на строку, введенную пользователем
 * @param i Итератор, указывающий нынешнее местоположение во входной строке
 * @param input_len Длина строки
 * @return 0 - OK, != 0 - ошибка
 */
int only_one_dot_in_digit(char *input) {
  int input_len = strlen(input);
  int dot_flag = 0;
  int flag = 0;
  for (int i = 0; i < input_len; i++) {
    dot_flag = 0;
    if (isdigit(input[i])) {
      while (i < input_len && (isdigit(input[i]) || input[i] == '.')) {
        i++;
        if (input[i] == '.') dot_flag++;
      }
    }
    if (dot_flag > 1) flag++;
  }
  return flag;
}
