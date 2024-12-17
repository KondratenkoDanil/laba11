#include <iostream>
#include <cmath> // Для sqrt, якщо знадобиться
using namespace std;

int main() {
    const double A = 15;     // Коєфіцієнт при x^2
    const double B = 32;     // Коєфіцієнт при x
    const double C = 40;     // Константа
    int x = 0;               // Аргумент x
    double y = 0;            // Значення функції

    // Початковий цикл для пошуку цілого x
    __asm {
        finit                  // Очищення регістрів FPU
        ml :
        fld x                  // Завантажуємо x
            fmul st, st            // Обчислюємо x^2
            fmul dword ptr[A]      // Множимо на 15
            fld x                  // Завантажуємо x знову
            fmul dword ptr[B]      // Множимо на 32
            fadd                   // Додаємо результат до попереднього
            fadd dword ptr[C]      // Додаємо 40
            fsqrt                  // Обчислюємо квадратний корінь
            fstp y                 // Зберігаємо результат у змінну y

            // Перевірка, чи y > 30
            fld y
            fcomp dword ptr[limit] // Порівняння з 30
            fstsw ax
            sahf
            jae end_loop           // Якщо y >= 30, вихід з циклу

            inc x                  // Збільшуємо x
            jmp ml                 // Повертаємось до початку циклу

            end_loop :
    }

    cout << "Найменше ціле значення x, при якому y > 30: " << x << endl;
    return 0;
}

const double limit = 30; // Граничне значення для порівняння
