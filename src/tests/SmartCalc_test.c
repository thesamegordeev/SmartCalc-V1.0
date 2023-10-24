#include "../backend/SmartCalc.h"

#include <check.h>
#include <math.h>
#include <stdlib.h>

#define TOLERANCE 1e-8

// =============================INPUT ERROR================================//

START_TEST(empty_input) {
  char input[10] = "";
  double result = 0;
  int error_flag = 0;
  error_flag = smartcalc(input, &result);
  ck_assert_int_eq(error_flag, INPUT_ERROR);
}
END_TEST

START_TEST(incorrect_brackets) {
  // cos(10)*sin(tan(2)
  char input[100] = {'c', 'o', 's', '(', '1', '0', ')', '*', 's',
                     'i', 'n', '(', 't', 'a', 'n', '(', '2', ')'};
  double result = 0;
  int error_flag = 0;
  error_flag = smartcalc(input, &result);
  ck_assert_int_eq(error_flag, INPUT_ERROR);
}
END_TEST

START_TEST(incorrect_x_position) {
  // x13-sin(1)x+2x
  char input[100] = {'x', '1', '3', '-', 's', 'i', 'n',
                     '(', '1', ')', 'x', '+', '2', 'x'};
  double result = 0;
  int error_flag = 0;
  error_flag = smartcalc(input, &result);
  ck_assert_int_eq(error_flag, INPUT_ERROR);
}
END_TEST

START_TEST(incorrect_dot_position) {
  // .13+12..5-4.
  char input[100] = {'.', '1', '3', '+', '1', '2',
                     '.', '.', '5', '-', '4', '.'};
  double result = 0;
  int error_flag = 0;
  error_flag = smartcalc(input, &result);
  ck_assert_int_eq(error_flag, INPUT_ERROR);
}
END_TEST

START_TEST(incorrect_operation_position) {
  // *13-*2//13-tan(/4)---tan(2)cos(3)sin(4)mod*mod
  char input[200] = {'*', '1', '3', '-', '*', '2', '/', '/', '1', '3', '-', 't',
                     'a', 'n', '(', '/', '4', ')', '-', '-', '-', 't', 'a', 'n',
                     '(', '2', ')', 'c', 'o', 's', '(', '3', ')', 's', 'i', 'n',
                     '(', '4', ')', 'm', 'o', 'd', '*', 'm', 'o', 'd'};
  double result = 0;
  int error_flag = 0;
  error_flag = smartcalc(input, &result);
  ck_assert_int_eq(error_flag, INPUT_ERROR);
}
END_TEST

START_TEST(only_brackets_position) {
  // ()-()+()*()
  char input[200] = {'(', ')', '-', '(', ')', '+', '(', ')', '*', '(', ')'};
  double result = 0;
  int error_flag = 0;
  error_flag = smartcalc(input, &result);
  ck_assert_int_eq(error_flag, INPUT_ERROR);
}
END_TEST

Suite* test_input_error(void) {
  Suite* s;
  TCase* tc_core;

  s = suite_create("test_input_error");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, empty_input);
  tcase_add_test(tc_core, incorrect_brackets);
  tcase_add_test(tc_core, incorrect_x_position);
  tcase_add_test(tc_core, incorrect_dot_position);
  tcase_add_test(tc_core, incorrect_operation_position);
  tcase_add_test(tc_core, only_brackets_position);

  suite_add_tcase(s, tc_core);

  return s;
}

// =============================MATH ERROR================================//

START_TEST(div_by_zero) {
  // 5/4+3/(2-2)
  char input[200] = {'5', '/', '4', '+', '3', '/', '(', '2', '-', '2', ')'};
  double result = 0;
  int error_flag = 0;
  error_flag = smartcalc(input, &result);
  ck_assert_int_eq(error_flag, DIV_BY_ZERO);
}
END_TEST

START_TEST(log_arg_le_zero) {
  // sin(2)+log(-1)+ln(0)+3/2
  char input[200] = {'s', 'i', 'n', '(', '2', ')', '+', 'l',
                     'o', 'g', '(', '-', '1', ')', '+', 'l',
                     'n', '(', '0', ')', '+', '3', '/', '2'};
  double result = 0;
  int error_flag = 0;
  error_flag = smartcalc(input, &result);
  ck_assert_int_eq(error_flag, LOG_ARG_LE_ZERO);
}
END_TEST

START_TEST(afunc_arg_out_of_range) {
  // asin(2)-acos(-3)
  char input[200] = {'a', 's', 'i', 'n', '(', '2', ')', '-',
                     'a', 'c', 'o', 's', '(', '-', '3', ')'};
  double result = 0;
  int error_flag = 0;
  error_flag = smartcalc(input, &result);
  ck_assert_int_eq(error_flag, AFUNC_ARG_OUT_OF_RANGE);
}
END_TEST

START_TEST(sqrt_arg_less_zero) {
  // sqrt(1)+sqrt(2)+sqrt(-4)
  char input[200] = {'s', 'q', 'r', 't', '(', '1', ')', '+',
                     's', 'q', 'r', 't', '(', '2', ')', '+',
                     's', 'q', 'r', 't', '(', '-', '4', ')'};
  double result = 0;
  int error_flag = 0;
  error_flag = smartcalc(input, &result);
  ck_assert_int_eq(error_flag, SQRT_ARG_L_ZERO);
}
END_TEST

Suite* test_math_error(void) {
  Suite* s;
  TCase* tc_core;

  s = suite_create("test_math_error");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, div_by_zero);
  tcase_add_test(tc_core, log_arg_le_zero);
  tcase_add_test(tc_core, afunc_arg_out_of_range);
  tcase_add_test(tc_core, sqrt_arg_less_zero);
  suite_add_tcase(s, tc_core);

  return s;
}

// =============================TEST NORMAL================================//

START_TEST(afuncs_normal) {
  // asin(0.35)-acos(1)+atan(5)/acos(0.1)
  char input[200] = {'a', 's', 'i', 'n', '(', '0', '.', '3', '5',
                     ')', '-', 'a', 'c', 'o', 's', '(', '1', ')',
                     '+', 'a', 't', 'a', 'n', '(', '5', ')', '/',
                     'a', 'c', 'o', 's', '(', '0', '.', '1', ')'};
  double result = 0;
  smartcalc(input, &result);
  ck_assert_double_eq_tol(result, asin(0.35) - acos(1) + atan(5) / acos(0.1),
                          TOLERANCE);
}
END_TEST

START_TEST(trigonometry_normal) {
  // sin(3)/cos(1)+tan(cos(-1))
  char input[200] = {'s', 'i', 'n', '(', '3', ')', '/', 'c', 'o',
                     's', '(', '1', ')', '+', 't', 'a', 'n', '(',
                     'c', 'o', 's', '(', '-', '1', ')', ')'};
  double result = 0;
  smartcalc(input, &result);

  ck_assert_double_eq_tol(result, sin(3) / cos(1) + tan(cos(-1)), TOLERANCE);
}
END_TEST

START_TEST(log_normal) {
  // log(1*ln(5))-ln(3.14*0.1)/log(2.14525)
  char input[200] = {'l', 'o', 'g', '(', '1', '*', 'l', 'n', '(', '5',
                     ')', ')', '-', 'l', 'n', '(', '3', '.', '1', '4',
                     '*', '0', '.', '1', ')', '/', 'l', 'o', 'g', '(',
                     '2', '.', '1', '4', '5', '2', '5', ')'};
  double result = 0;
  smartcalc(input, &result);

  ck_assert_double_eq_tol(
      result, log10(1 * log(5)) - log(3.14 * 0.1) / log10(2.14525), TOLERANCE);
}
END_TEST

START_TEST(sqrt_normal) {
  // sqrt(3*ln(5)+4)-sqrt(sqrt(27))
  char input[200] = {'s', 'q', 'r', 't', '(', '3', '*', 'l', 'n', '(',
                     '5', ')', '+', '4', ')', '-', 's', 'q', 'r', 't',
                     '(', 's', 'q', 'r', 't', '(', '2', '7', ')', ')'};
  double result = 0;
  smartcalc(input, &result);

  ck_assert_double_eq_tol(result, sqrt(3 * log(5) + 4) - sqrt(sqrt(27)),
                          TOLERANCE);
}
END_TEST

START_TEST(unar_operations_normal) {
  // -3.654+(+12-(+4))-(12+(-4))
  char input[200] = {'-', '3', '.', '6', '5', '4', '+', '(', '+',
                     '1', '2', '-', '(', '+', '4', ')', ')', '-',
                     '(', '1', '2', '+', '(', '-', '4', ')', ')'};
  double result = 0;
  smartcalc(input, &result);

  ck_assert_double_eq_tol(result, -3.654 + (+12 - (+4)) - (12 + (-4)),
                          TOLERANCE);
}
END_TEST

START_TEST(default_operations_normal) {
  // 7.4324*3.12/2-(12+7^(3*0.12)*(14.6-0)/2.001)mod9
  char input[200] = {'7', '.', '4', '3', '2', '4', '*', '3', '.', '1',
                     '2', '/', '2', '-', '(', '1', '2', '+', '7', '^',
                     '(', '3', '*', '0', '.', '1', '2', ')', '*', '(',
                     '1', '4', '.', '6', '-', '0', ')', '/', '2', '.',
                     '0', '0', '1', ')', 'm', 'o', 'd', '9'};
  double result = 0;
  smartcalc(input, &result);

  ck_assert_double_eq_tol(
      result,
      7.4324 * 3.12 / 2 -
          fmod((12 + pow(7, (3 * 0.12)) * (14.6 - 0) / 2.001), 9),
      TOLERANCE);
}
END_TEST

START_TEST(x_normal) {
  // xmod15+9-4*x/(x+3)
  char input[200] = {'x', 'm', 'o', 'd', '1', '5', '+', '9', '-',
                     '4', '*', 'x', '/', '(', 'x', '+', '3', ')'};
  double result = 0;
  smartcalc(input, &result);
  // По умолчанию х = 0
  ck_assert_double_eq_tol(result, fmod(0, 15) + 9 - 4 * 0 / (0 + 3), TOLERANCE);
}
END_TEST

START_TEST(stack) {
  // xmod15+9-4*x/(x+3)
  char input[200] = {'x', 'm', 'o', 'd', '1', '5', '+', '9', '-',
                     '4', '*', 'x', '/', '(', 'x', '+', '3', ')'};
  stack_sc* lexemes = input_parser(input);
  stack_sc* cpy = copy_stack(lexemes);
  free_stack(&lexemes);
  free_stack(&cpy);
}
END_TEST

Suite* test_normal(void) {
  Suite* s;
  TCase* tc_core;

  s = suite_create("test_normal");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, afuncs_normal);
  tcase_add_test(tc_core, trigonometry_normal);
  tcase_add_test(tc_core, log_normal);
  tcase_add_test(tc_core, sqrt_normal);
  tcase_add_test(tc_core, unar_operations_normal);
  tcase_add_test(tc_core, default_operations_normal);
  tcase_add_test(tc_core, x_normal);
  tcase_add_test(tc_core, stack);

  suite_add_tcase(s, tc_core);

  return s;
}

// =============================TEST CREDIT================================//

START_TEST(monthly_payment_ann) {
  double result = 0;
  mon_payment_ann(100000, 12, 24, &result);
  ck_assert_double_eq_tol(result, 4707.3472223, 1e-2);
}
END_TEST

START_TEST(accur_interest_ann) {
  double result = 0;
  accured_interest_ann(30000, 100000, 5, &result);
  ck_assert_double_eq_tol(result, 50000, 1e-2);
}
END_TEST

START_TEST(monthly_payment_diff) {
  double result = 0;
  double rem = 47000;
  mon_payment_diff(100000, 12, &rem, 13, &result);
  ck_assert_double_eq_tol(result, 8842.5, 1e-2);
}
END_TEST

START_TEST(accur_interest_diff) {
  double result = 0;
  accured_interest_diff(45300.0, 21.3, &result);
  ck_assert_double_eq_tol(result, 804.075, 1e-2);
}
END_TEST

START_TEST(total) {
  double result = 0;
  total_payout(100000, 45000, &result);
  ck_assert_double_eq_tol(result, 145000, 1e-2);
}
END_TEST

Suite* test_credit(void) {
  Suite* s;
  TCase* tc_core;

  s = suite_create("test_credit");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, monthly_payment_ann);
  tcase_add_test(tc_core, accur_interest_ann);
  tcase_add_test(tc_core, monthly_payment_diff);
  tcase_add_test(tc_core, accur_interest_diff);
  tcase_add_test(tc_core, total);

  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int no_failed = 0;
  Suite* s[] = {test_input_error(), test_math_error(), test_normal(),
                test_credit()};
  SRunner* runner;

  for (int i = 0; i < 4; i++) {
    runner = srunner_create(s[i]);
    srunner_run_all(runner, CK_NORMAL);
    no_failed = srunner_ntests_failed(runner);
    srunner_free(runner);
  }

  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}