#include "SmartCalc.h"
/**
 * @brief Функция создает новый элемент списка на вершине стека и записывает
 * туда переданное значение
 * @param head Указатель на верхний элемент в стеке
 * @param token Лексемма - операция или число(х), которая будет записана в поле
 * данных элемента списка
 * @param priority Приоритет операции или числа, переданного в функцию
 */
void push(stack_sc **head, double token, int priority) {
  stack_sc *tmp = calloc(1, sizeof(stack_sc));

  if (tmp == NULL) {
    exit(1);
  }

  tmp->next = *head;
  tmp->token = token;
  tmp->priority = priority;
  *head = tmp;
}

/**
 * @brief Функция удаляет последний элемент списка на вершине стека и возвращает
 * содержимое им значение
 * @return Значение поля данных (лексемма)
 */
double pop(stack_sc **head) {
  stack_sc *out;
  if (*head == NULL) {
    exit(1);
  }

  double value = 0;
  out = *head;
  *head = (*head)->next;
  value = out->token;
  free(out);
  return value;
}

/**
 * @brief Функция очищает весь стек
 * @param head Указатель на верхний элемент в стеке
 */
void free_stack(stack_sc **head) {
  while (*head != NULL) {
    pop(head);
  }
}

// /**
//  * @brief Функция печатает весь стек
//  * @param head Указатель на верхний элемент в стеке
//  */
// void printStack(const stack_sc *head) {
//   printf("stack > ");
//   while (head) {
//     if (head->is_num == 1) {
//       printf("%lf ", head->token);
//     } else {
//       printf("%c ", (char)head->token);
//     }
//     // printf("%lf ", head->token);
//     head = head->next;
//   }
//   printf("\n");
// }

/**
 * @brief Функция копирует весь стек в новый
 * @param head Указатель на верхний элемент в стеке, который нужно
 скопировать
 * @return Указатель на скопированный стек
 */
stack_sc *copy_stack(stack_sc *head) {
  stack_sc *copy = {0};
  stack_sc *reverse_copy = {0};
  while (head) {
    push(&copy, head->token, head->priority);
    copy->is_num = head->is_num;
    head = head->next;
  }

  while (copy) {
    int priority = copy->priority;
    if (copy->is_num == 1 || copy->is_num == 2) {
      // Учитывается икс или число
      int num_flag = copy->is_num;
      push(&reverse_copy, pop(&copy), priority);
      reverse_copy->is_num = num_flag;
    } else {
      push(&reverse_copy, pop(&copy), priority);
    }
  }

  return reverse_copy;
}
