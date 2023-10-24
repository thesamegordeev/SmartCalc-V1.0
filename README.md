# SmartCalc v1.0

Реализация SmartCalc v1.0.


## Contents

1. [Chapter I](#chapter-i) \
    1.1. [Introduction](#introduction)
2. [Chapter II](#chapter-ii) \
    2.1. [Information](#information)
3. [Chapter III](#chapter-iii) \
    3.1. [Part 1](#part-1-реализация-smartcalc-v10)  
    3.2. [Part 2](#part-2-дополнительно-кредитный-калькулятор)  
    3.3. [Part 3](#part-3-дополнительно-депозитный-калькулятор)  

## Chapter I

## Introduction

В данном проекте Вам предстоит реализовать на языке программирования Си с использованием структурного подхода расширенную версию обычного калькулятора, который можно найти в стандартных приложениях каждой операционной системы. Помимо базовых арифметических операций, как плюс-минус и умножить-поделить, Вам необходимо дополнить калькулятор возможностью вычисления арифметических выражений с учетом приоритетов, а так же некоторыми математическими функциями (синус, косинус, логарифм и т.д.). Помимо вычисления выражений калькулятор так же должен поддерживать использование переменной _x_ и построение графика соответствующей функции. В качестве дополнительных улучшений можно будет рассмотреть кредитный и депозитный калькулятор.


## Chapter II

## Information

### Историческая справка

История развития такого вычислительного механизма как калькулятор начинается в ХVII веке, а первые прообразы этого аппарата существовали в VI столетии до нашей эры. Само слово "калькулятор" происходит от латинского "calculo", что в переводе означает "считаю", "подсчитываю". Но более детальное изучение этимологии этого понятия показывает, что изначально следует говорить о слове "calculus", которое переводится как "камешек". Ведь изначально именно камешки использовались как атрибут для счета.

Историю вычислительных машин, в том числе и калькуляторов, традиционно начинают с суммирующей машины Паскаля, созданной в 1643 году Блезом Паскалем, и арифмометра Лейбница, изобретённого в 1673 году немецким математиком Готфридом Вильгельмом Лейбницем.

Суммирующая машина представляла собой ящик со связанными между собой шестеренками, которые поворачивались специальными колесиками, каждому из которых соответствовал один десятичный разряд. Когда одним из колесиков совершался десятый оборот, происходил сдвиг следующей шестеренки на одну позицию, увеличивавший разряд числа. Ответ после проведения математических действий отображался в окошках над колесиками.

Через 20 лет Лейбниц создал свой вариант калькулятора, принцип работы которого был таким же как и у суммирующей машины Паскаля - шестеренки и колесики. Однако в калькулятор Лейбница были добавлены движущая часть, которая стала прообразом подвижных кареток будущих настольных калькуляторов, и рукоятка, крутившая ступенчатое колесо, которое в дальнейшем было заменено на цилиндр. Данные добавления позволили существенно ускорить повторяющиеся операции - умножение и деление. Использование калькулятора Лейбница хоть и незначительно упростило процесс вычисления, но дало толчок другим изобретателям - движущая часть и цилиндр калькулятора Лейбница использовались в вычислительных машинах до середины XX века.

Затем в 1957 компанией Casio был выпущен один из первых серийных калькуляторов 14-А. Он выполнял четыре действия арифметики над 14-разрядными десятичными числами. Конструкция использовала реле, весила 140 кг и была выполнена в виде стола с тумбой-вычислительным блоком, клавиатурой и дисплеем, при работе потребляла 300 Вт. Однако, калькуляторы быстро развивались и усложнялись, как и прочие вычислительные машины. В 1965 году компания Wang Laboratories выпустила калькулятор Wang LOCI-2, который мог вычислять логарифмы, Casio представила первый калькулятор со встроенной памятью "Casio 001" (размеры 37x48x25 см, вес 17 кг), а Olivetti выпустила "Programma 101" - первый калькулятор, который мог сохранять программу и многократно выполнять вычисления по ней.

Малогабаритные настольные и карманные калькуляторы начали выпускаться с 1970 года, после появления интегральных микросхем, резко сокративших размеры, массу и энергопотребление электронных приборов. В 1970 году Sharp и Canon начали продажи калькуляторов, которые можно было держать в руке (весом порядка 800 г). В 1971 появился первый действительно карманный (131x77x37 мм) калькулятор 901B фирмы Bomwar. Он выполнял 4 арифметические операции, имел дисплей на светодиодах и стоил 240 долларов. В 1973 году в продаже появился калькулятор Sharp EL-805, в котором впервые был использован ЖК-дисплей. А уже в 1979 Hewlett Packard выпустила первый калькулятор с алфавитно-цифровым индикатором, программируемый, с возможностью подключения дополнительных модулей - RAM, ROM, устройства чтения штрих-кодов, кассеты с магнитной лентой, флоппи-дисков, принтеров и др.

### Польская прямая и обратная нотации

Несмотря на безусловное удобство работы с классической формой записи выражений при ручном счёте, при написании программ запросы чаще всего формируются в формате `что делать -> с какими данными совершать операции`. Так, примерно в 1920 Польский логик Ян Лукасевич изобрел префиксную нотацию (в последствии также называемую польской нотацией или прямой польской нотацией) с целью упрощения пропозиционной логики.

Рассмотрим способы написания выражений:

Выражение, написанное в классической (инфиксной) нотации:

>2 / (3 + 2) * 5

Выражение, написанное в польской (префиксной) нотации:

>\* (/ 2 (+ 3 2)) 5

Как правило скобки между операциями с одинаковым приоритетом опускаются и итоговая запись выглядит следующим образом:

>\* / 2 (+ 3 2) 5

Польская нотация получила широкое распространение в области вычислительных систем, в частности она используется во многих стековых языках, таких как PostScript, и долгое время являлась основой для многих вычислительных машин (калькуляторов).

В середине 1950-х австралийским философом и специалистом в области теории вычислительных машин Чарльзом Хэмблином была разработана обратная польская нотация (ОПН). Работа Хэмблина была представлена на конференции в июне 1957, и издана в 1957 и 1962.

Первыми компьютерами, поддерживающими обратную польскую нотацию, были KDF9 от English Electric Company, анонсированные в 1960 и выпущенные в 1963, и американский Burroughs B5000, анонсированный в 1961, выпущен в том же 1963. 

Компания Friden перенесла ОПН в настольные калькуляторы, выпустив в июне 1964 модель EC-130. А в 1968 инженеры Hewlett-Packard разработали настольный калькулятор 9100A с поддержкой ОПН. Этот калькулятор сделал обратную польскую нотацию популярной среди учёных и инженеров, даже несмотря на то, что в ранней рекламе 9100A ОПН не упоминалась. В 1972 калькулятор HP-35 с поддержкой ОПН стал первым научным карманным калькулятором.

ОПН применялась в советском инженерном калькуляторе Б3-19М (совместная разработка с ГДР), выпущенном в 1976 году. Все выпускаемые в СССР вплоть до конца 1980-х годов программируемые микрокалькуляторы, за исключением «Электроника МК-85» и «Электроника МК-90», использовали ОПН — она проще реализовывалась и позволяла при программировании обходиться меньшим числом команд, в сравнении с обычной алгебраической нотацией (количество программной памяти в моделях того времени всегда было критическим ресурсом). ОПН использовалась в российских программируемых калькуляторах «Электроника МК-152» и «Электроника МК-161», обеспечивая их совместимость с программами, написанными для советских калькуляторов. 

Обратная польская нотация имела все преимущества прародителя, позволяя сократить объём выражений благодаря отсутствию необходимости в скобках. Это позволяло сократить число команд при написании компьютерных программ. Благодаря этому свойству, обратную польскую нотацию также иногда называют обратной бесскобочной записью.

Пример выражения, написанного в обратной польской (бесскобочной) нотации:

> 2 3 2 + / 5 *

### Алгоритм Дейкстры

Эдсгер Дейкстра изобрёл алгоритм для преобразования выражений (в том числе функций) из инфиксной в обратную польскую нотацию. Алгоритм получил название «сортировочная станция», за сходство его операций с происходящим на железнодорожных сортировочных станциях. 

>Перед рассмотрением самого алгоритма сделаем небольшую ремарку и введём понятие лексемы. Лексемой будет называться простейшая единица морфологического разбора выражения. Так, разбитое на лексемы выражение 2 / (3 + 2) * 5 (пробелы добавлены для более удобного восприятия и не несут семантического смысла), будет выглядеть следующим образом: [2], [/], [(], [3], [+], [2], [)], [*], [5], где [2, 3, 5] - числовые лексемы, [/, (, +, ), *] - лексемы-операции.

Алгоритм сортировочной станции основан на стеке. В преобразовании участвуют две текстовых переменных: входная и выходная строки. В процессе преобразования используется стек, хранящий ещё не добавленные к выходной строке операции. Преобразующая программа последовательно считывает лексемы из входной строки, выполняя на каждом шаге некоторые действия, зависящие от того, какая лексема была считана.

#### Реализация алгоритма

Пока в исходной строке есть необработанные лексемы, считываем очередную:

Если лексема:
- Число - добавляем в строку вывода.
- Функция или открывающая скобка - помещаем в стек.
- Разделитель аргументов функции (например, запятая):         
    - Перекладываем операторы из стека в выходную очередь пока лексемой на вершине стека не станет открывающая скобка. Если в стеке не окажется открывающей скобки - в выражении допущена ошибка.
- Оператор (O1):
    - Пока присутствует на вершине стека лексема-оператор (O2) чей приоритет выше приоритета O1, либо при равенстве приоритетов O1 является левоассоциативным:
        - Перекладываем O2 из стека в выходную очередь.
    - Помещаем O1 в стек.
- Закрывающая скобка:
    - Пока лексема на вершине стека не станет открывающей скобкой, перекладываем лексемы-операторы из стека в выходную очередь.
    - Удаляем из стека открывающую скобку.
    - Если лексема на вершине стека — функция, перекладываем её в выходную очередь.
    - Если стек закончился до того, как была встречена открывающая скобка - в выражении содержится ошибка.

Если во входной строке больше не осталось лексем:
- Пока есть операторы в стеке:
    - Если на вершине стека скобка - в выражении допущена ошибка.
    - Перекладываем оператор из стека в выходную очередь.

Конец.


## Chapter III

## Part 1. Реализация SmartCalc v1.0

Необходимо реализовать программу SmartCalc v1.0:

- Программа должна быть разработана на языке Си стандарта C11 с использованием компилятора gcc. Допустимо использование дополнительных библиотек и модулей QT
- Код программы должен находиться в папке src 
- Сборка программы должна быть настроена с помощью Makefile со стандартным набором целей для GNU-программ: all, install, uninstall, clean, dvi, dist, test, gcov_report. Установка должна вестись в любой другой произвольный каталог
- Программа должна быть разработана в соответствии с принципами структурного программирования
- При написании кода необходимо придерживаться Google Style
- Должно быть обеспечено покрытие unit-тестами модулей, связанных с вычислением выражений, с помощью библиотеки Check
- Реализация с графическим пользовательским интерфейсом, на базе любой GUI-библиотеки с API для C89/C99/C11 
<br/>Для Linux: GTK+, CEF, Qt
<br/>Для Mac: GTK+, Nuklear, raygui, microui, libagar, libui, IUP, LCUI, CEF, Qt
- На вход программы могут подаваться как целые числа, так и вещественные числа, записанные через точку. По желанию можно обрабатывать ввод чисел в экспоненциальной записи
- Вычисление должно производиться после полного ввода вычисляемого выражения и нажатия на символ `=`
- Вычисление произвольных скобочных арифметических выражений в инфиксной нотации
- Вычисление произвольных скобочных арифметических выражений в инфиксной нотации с подстановкой значения переменной _x_ в виде числа
- Построение графика функции, заданной с помощью выражения в инфиксной нотации с переменной _x_  (с координатными осями, отметкой используемого масштаба и сеткой с адаптивным шагом)
    - Не требуется предоставлять пользователю возможность менять масштаб
- Область определения и область значения функций ограничиваются по крайней мере числами от -1000000 до 1000000
    - Для построения графиков функции необходимо дополнительно указывать отображаемые область определения и область значения
- Проверяемая точность дробной части - минимум 7 знаков после запятой
- У пользователя должна быть возможность ввода до 255 символов
- Скобочные арифметические выражения в инфиксной нотации должны поддерживать следующие арифметические операции и математические функции:
    - **Арифметические операторы**:

        | Название оператора | Инфиксная нотация <br /> (Классическая) | Префиксная нотация <br /> (Польская нотация) |  Постфиксная нотация <br /> (Обратная польская нотация) |
        | ------ | ------ | ------ | ------ |
        | Скобки | (a + b) | (+ a b) | a b + |
        | Сложение | a + b | + a b | a b + |
        | Вычитание | a - b | - a b | a b - |
        | Умножение | a * b | * a b | a b * |
        | Деление | a / b | / a b | a b \ |
        | Возведение в степень | a ^ b | ^ a b | a b ^ |
        | Остаток от деления | a mod b | mod a b | a b mod |
        | Унарный плюс | +a | +a | a+ |
        | Унарный минус | -a | -a | a- |

        >Обратите внимание, что оператор умножения содержит обязательный знак `*`. Обработка выражения с опущенным знаком `*` является необязательной и остается на усмотрение разработчика

    - **Функции**:
  
        | Описание функции | Функция |   
        | ---------------- | ------- |  
        | Вычисляет косинус | cos(x) |   
        | Вычисляет синус | sin(x) |  
        | Вычисляет тангенс | tan(x) |  
        | Вычисляет арккосинус | acos(x) | 
        | Вычисляет арксинус | asin(x) | 
        | Вычисляет арктангенс | atan(x) |
        | Вычисляет квадратный корень | sqrt(x) |
        | Вычисляет натуральный логарифм | ln(x) | 
        | Вычисляет десятичный логарифм | log(x) |

## Part 2. Дополнительно. Кредитный калькулятор

Предусмотреть специальный режим "кредитный калькулятор" (за образец можно взять сайты banki.ru и calcus.ru):
 - Вход: общая сумма кредита, срок, процентная ставка, тип (аннуитетный, дифференцированный)
 - Выход: ежемесячный платеж, переплата по кредиту, общая выплата

## Part 3. Дополнительно. Депозитный калькулятор

Предусмотреть специальный режим "калькулятор доходности вкладов" (за образец можно взять сайты banki.ru и calcus.ru):
 - Вход: сумма вклада, срок размещения, процентная ставка, налоговая ставка, периодичность выплат, капитализация процентов, список пополнений, список частичных снятий
 - Выход: начисленные проценты, сумма налога, сумма на вкладе к концу срока
