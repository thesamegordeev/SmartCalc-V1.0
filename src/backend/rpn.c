#include "SmartCalc.h"

/**
 * @brief Функция преобразует распарсенный список лексемм к виду ОПН
 * @param lexemes Указатель на стек, содержащий лексеммы
 * @return Односвязный список из лексемм, записанных в виде ОПН, с
 * учтенным приоритетом и флагом на число или икс
 */
stack_sc *dijkstra(stack_sc *lexemes) {
  stack_sc *result = {0};
  stack_sc *operations = {0};

  while (lexemes) {
    // if (lexemes->is_num == 1 || lexemes->token == 'x' ||
    //     lexemes->token == 'X') {

    // Если число или х
    if (lexemes->is_num == 1 || lexemes->is_num == 2) {
      int priority = lexemes->priority;
      int is_num = lexemes->is_num;
      push(&result, pop(&lexemes), priority);
      // if (result->token != 'x' && result->token != 'X') {
      //   result->is_num = 1;
      // } else {
      result->is_num = is_num;
      //}
      // 2 будет индикатором что лексемма это икс
    } else if (lexemes->priority == 4) {
      // Если префиксная функция (синус косинус итд)
      int priority = lexemes->priority;
      push(&operations, pop(&lexemes), priority);
    } else if (lexemes->token == '(') {
      // Если найдена открывающая скобка
      int priority = lexemes->priority;
      push(&operations, pop(&lexemes), priority);
    } else if (lexemes->token == ')') {
      // Если нашлась закрывающая скобка
      while (operations && operations->token != '(') {
        int priority = operations->priority;
        push(&result, pop(&operations), priority);
      }
      pop(&operations);
      pop(&lexemes);
    } else if (operations && (lexemes->priority <= operations->priority)) {
      // Если приоритет операции в стеке меньше приоритета рассматриваемой
      // операции
      while (operations && (lexemes->priority <= operations->priority)) {
        // Перекладываем все операции с большим приоритетом в выход
        int priority = operations->priority;
        push(&result, pop(&operations), priority);
      }
      // Пушим в вспомогательный стек
      int priority = lexemes->priority;
      push(&operations, pop(&lexemes), priority);
    } else {
      // Во всех остальных случаях
      int priority = lexemes->priority;
      push(&operations, pop(&lexemes), priority);
    }
  }

  // Все оставшиеся операции выталкиваем в выход
  while (operations) {
    int priority = operations->priority;
    push(&result, pop(&operations), priority);
  }

  stack_sc *reverse_result = {0};
  // Здесь стек переворачивается, чтобы привести к виду оригинальной ОПН
  while (result) {
    int priority = result->priority;
    // Учитывается икс или число
    int num_flag = result->is_num;
    push(&reverse_result, pop(&result), priority);
    reverse_result->is_num = num_flag;
  }
  return reverse_result;
}