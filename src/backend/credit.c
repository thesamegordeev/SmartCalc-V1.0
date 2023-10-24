#include "SmartCalc.h"

/**
 * @brief Функция рассчитывает ежемесячный платеж по кредиту аннуитетного типа
 * Формула для расчета: A = (P * i) / (1 - (1 + i)^(-n))
 * где A - аннуитетный платеж, P - сумма, i - месячная процентная ставка
 * (годовая процентная ставка / 12), n - срок кредита в месяцах.
 * @param sum_cred Общая сумма кредита
 * @param percent Процентная ставка (годовая, 0-100%)
 * @param term Срок кредита в месяцах
 * @param result Указатель на переменную, куда будет записан результат
 * @return Код завершения - 0-ОК
 */
int mon_payment_ann(double sum_cred, double percent, int term, double *result) {
  char input[1000] = {0};
  percent = percent / (100 * 12);

  sprintf(input, "(%.14lf*%.14lf)/(1-(1+%.14lf)^(-%d))", sum_cred, percent,
          percent, term);

  int error_flag = smartcalc(input, result);
  return error_flag;
}

/**
 * @brief Функция рассчитывает переплату по кредиту аннуитетного типа
 * @param monthly_payment Ежемсячный платеж
 * @param sum_cred Общая сумма кредита
 * @param term Срок кредита в месяцах
 * @param result Указатель на переменную, куда будет записан результат
 * @return Код завершения - 0-ОК
 */
int accured_interest_ann(double monthly_payment, double sum_cred, int term,
                         double *result) {
  char input[300] = {0};
  sprintf(input, "%.14lf*%d-%.14lf", monthly_payment, term, sum_cred);

  int error_flag = smartcalc(input, result);
  return error_flag;
}

/**
 * @brief Функция рассчитывает итоговую стоимость кредита
 * @param loan_amount Общая сумма кредита
 * @param overpayment Переплата по кредиту
 * @param result Указатель на переменную, куда будет записан результат
 * @return Код завершения - 0-ОК
 */
int total_payout(double loan_amount, double overpayment, double *result) {
  char input[300] = {0};
  sprintf(input, "%.8lf+%.8lf", loan_amount, overpayment);

  int error_flag = smartcalc(input, result);
  return error_flag;
}

/**
 * @brief Функция рассчитывает ежемесячный платеж по кредиту дифферециального
 * типа Формула для расчета: A = P / n + Pо * i где A - платеж, P - сумма, n -
 * срок кредита в месяцах, Po - остаток долга, i - месячная процентная ставка
 * (годовая процентная ставка / 12).
 * @param sum_cred Общая сумма кредита
 * @param term Срок кредита в месяцах
 * @param remaining Остаток долга
 * @param percent Процентная ставка (годовая, 0-100%)
 * @param result Указатель на переменную, куда будет записан результат
 * @return Код завершения - 0-ОК
 */
int mon_payment_diff(double sum_cred, int term, double *remaining,
                     double percent, double *result) {
  char input[1000] = {0};
  percent = percent / (100 * 12);

  sprintf(input, "%.14lf/%d+%.14lf*%.14lf", sum_cred, term, *remaining,
          percent);
  int error_flag = smartcalc(input, result);

  char rem[255] = {0};
  sprintf(rem, "%.14lf-%.14lf/%d", *remaining, sum_cred, term);
  smartcalc(rem, remaining);

  return error_flag;
}

/**
 * @brief Функция рассчитывает переплату по кредиту дифференциального типа
 * @param remaining Остаток долга
 * @param percent Процентная ставка (годовая, 0-100%)
 * @param result Указатель на переменную, куда будет записан результат
 * @return Код завершения - 0-ОК
 */
int accured_interest_diff(double remaining, double percent, double *result) {
  char input[300] = {0};
  percent = percent / (100 * 12);
  double res_buff = 0;

  sprintf(input, "%.14lf*%.14lf", remaining, percent);

  int error_flag = smartcalc(input, &res_buff);
  *result += res_buff;
  return error_flag;
}

// int main() {
//   char input[255] = {0};
//   // fgets(input, 255, stdin);
//   double res = 0;
//   double rem = 47000;
//   mon_payment_diff(100000, 12, &rem, 13, &res);
//   printf("Ann mon pay %.8lf\n", res);

//   res = 0;
//   accured_interest_diff(45300.0, 21.3, &res);
//   printf("Ann acc inter %.8lf\n", res);

//   // res = 0;
//   // total_payout(100000, 45000, &res);
//   // printf("Ann total %.8lf\n", res);
// }