#include <iostream>
#include <stack>
using namespace std;
//структура описывающая любое число или операцию
struct Leksema {
    char type; // 0 для чисел, "+" для операций сложения, "-" для операций вычитания и так далее...
    double value; // для работы с разными числами
};

//математическая функция которая произволит расчеты и при возникновении ошибки возвращает false
bool Maths(stack <Leksema>& Stack_number, stack <Leksema>& Stack_operation, Leksema& item) {
    double a, b, result;
    a = Stack_number.top().value;
    Stack_number.pop();

    switch (Stack_operation.top().type) {
    case '+':
        b = Stack_number.top().value;
        Stack_number.pop();
        result = a + b;
        item.type = '0';
        item.value = result;
        Stack_number.push(item);
        Stack_operation.pop();
        break;
    case '-':
        b = Stack_number.top().value;
        Stack_number.pop();
        result = b - a;
        item.type = '0';
        item.value = result;
        Stack_number.push(item);
        Stack_operation.pop();
        break;
    case '*':
        b = Stack_number.top().value;
        Stack_number.pop();
        result = a * b;
        item.type = '0';
        item.value = result;
        Stack_number.push(item);
        Stack_operation.pop();
        break;
    case '/':
        b = Stack_number.top().value;
        if (a == 0) {
            cerr << "\n ошибка на ноль нельзя делать балбес \n";
            return false;
        }
        else {
            Stack_number.pop();
            result = b / a;
            item.type = '0';
            item.value = result;
            Stack_number.push(item);
            Stack_operation.pop();
            break;
        }
    default: 
        cerr << "мой калькулятор пока не знает такой операции но скоро будут добавлены новые фичи)";
        return false;
        break;
    }

    return true;
}


//функция которая возвращает приоритет операции
int getRang(char Ch) {
    if (Ch == '+' || Ch == '-') return 1;
    if (Ch == '*' || Ch == '/') return 2;

    return 0;
}


int main()
{   
    setlocale(LC_ALL, "rus");
    //получение элементов введенных с клавиатуры
    char Ch;
    double value;
    //для проверки что первое число отрицательное
    bool flag = 1;

    //стэк для введенных чисел
    stack<Leksema> Stack_number;
    //стэк для операций
    stack<Leksema> Stack_operation;

    Leksema item;

    //бесконечный цикл
    while (true) {
        //запись переменной в оперативную память
        Ch = cin.peek();

        if (Ch == '\n' || Ch == EOF) break;

        //если прочитано число 
        if ((Ch >= '0') && (Ch <= '9') || (Ch == '-' && flag == 1)) {
            cin >> value;
            item.type = '0';
            item.value = value;
            Stack_number.push(item);
            flag = 0;
            //для перехода к следующей итерации
            continue;
        }
        //если прочитана какая либо операция
        if (Ch == '+' || (Ch == '-' && flag == 0) || Ch == '*' || Ch == '/') {
            if (Stack_operation.size() == 0) { // если стек с операциями пуст
                item.type = Ch;
                item.value = 0;
                Stack_operation.push(item);
                //для перехода к следующему символу
                cin.ignore();
                //для перехода к следующей итерации
                continue;
            }
            // если стек с операвцуиями НЕ пустб но приоритет текущей опериции выше верхней в стеке с операциями
            if ((Stack_operation.size() != 0) && (getRang(Ch) > getRang(Stack_operation.top().type))) {
                item.type = Ch;
                item.value = 0;
                Stack_operation.push(item);
                //для перехода к следующему символу
                cin.ignore();
                //для перехода к следующей итерации
                continue;
            }
            // если стек с операвцуиями НЕ пустб но приоритет текущей опериции ниже либо равен верхней в стеке с операциями
            if ((Stack_operation.size() != 0) && (getRang(Ch) <= getRang(Stack_operation.top().type))) {
                if (!Maths(Stack_number, Stack_operation, item)) {
                    system("pause");
                    return 0;
                }
                continue;
            }
            
        }
    }
    //для выполнениния N операций
    while (Stack_operation.size() != 0) {
        if (!Maths(Stack_number, Stack_operation, item)) {
            system("pause");
            return 0;
        }
        else {// если все хорошо
            continue;
        }
    }
    cout << "ответ : " << Stack_number.top().value;
    return 0;
}

//------------------------------------------------------------------------------------------------//
// 
//1. Алгоритм начинается с бесконечного цикла while, который продолжает работу до тех пор, пока не будет введен символ новой строки или конец файла.

//2. На каждой итерации цикла программа читает по одному символу из входного потока.

//3. Если прочитанный символ является цифрой(от '0' до '9'), программа понимает, что это число.
// Тогда программа читает дальше символы, чтобы сформировать полное число, 
// затем это число добавляется в стек `Stack_number` в структуру `Leksema` как объект типа "число" с указанием значения этого числа.

//4. Если прочитанный символ является операцией(+, -, *, / ), программа проверяет стек `Stack_operation`:
//- Если стек операций пустой, операция добавляется в стек для будущего выполнения.
//- Если стек операций не пустой, программа сравнивает приоритет текущей операции с операцией на вершине стека.
// Если приоритет текущей операции выше, чем операции на вершине стека, то текущая операция добавляется в стек для будущего выполнения.
//- Если приоритет текущей операции ниже или равен операции на вершине стека, 
// то программа выполняет операцию на вершине стека с помощью функции `Maths` (если это возможно) и затем добавляет текущую операцию в стек.
//
//5. После того, как все числа и операции прочитаны и добавлены в соответствующие стеки,
//  программа выполняет из стека `Stack_operation` все оставшиеся операции поочередно с числами из стека `Stack_number`, используя функцию `Maths`.
//
//6. Наконец, программа выводит результат вычислений, который находится в вершине стека `Stack_number`.
// 
//------------------------------------------------------------------------------------------------//