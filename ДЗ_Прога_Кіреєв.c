/*
    ДЗ з програмування
    Кіреєв Андрій Сергійович
    Варіант 10
    Нехай розглядається два підрозділи, у першому підрозділі працює m працівників,
    у другому – m1. Робота кожного підрозділу аналізується за n
    останніх років. Для кожного працівника вказана заробітна плата за відповідний рік
    (задається з клавіатури). Необхідно визначити, у скількох осіб заробіток був
    менший за середній у кожному підрозділі (реалізувати за допомогою функції).
    Відсортувати заробітну плату працівників першого підрозділу методом
    швидкого сортування (реалізувати у вигляді функції). Намалювати блок-схему.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void swap(float* array, int i, int j) {  //міняємо місцями елементи масива (власне сортування)
    float buffer = array[i];
    array[i] = array[j];
    array[j] = buffer;
}

float partition(float* array, int left, int right) {   //ділення 
    float v = array[(left + right) / 2];  //шукаємо базисний елемент - ділимо суму параметрів зарплати на 2  отримуємо середину
    int i = left; // 
    int j = right;
    while (i <= j) {
        while (array[i] < v) {  //поки лівий елемент менше середнього, ми його не рухаємо 
            i++;                //і йдемо далі по елементах вгору
        }
        while (array[j] > v) {  //така ж сама ситуація з правим елементом
            j--;
        }
        if (i >= j) {                 //якщо лівий елемент більше правого, перериваємо виконання програми 
            break;
        }
        swap(array, i++, j--);    //викликаємо функцію зміни місцями елементів (власне сортуємо)
    }
    return j;
}

void quickSort(float* array, int left, int right) {    //рекурсивна функція сортування
    if (left < right) {
        float q = partition(array, left, right);
        quickSort(array, left, q);
        quickSort(array, q + 1, right);
    }
}

struct Worker {
    char name[32];
    float* salary;
};

struct Unit {
    int count; // count of workers
    struct Worker* workers;                 //Зверніть увагу на вкладену структуру
};

int findCountMinimal(struct Unit unit, int n) {
    float average = 0;
    for (int i = 0; i < unit.count; i++) {
        for (int j = 0; j < n; ++j) {
            average += unit.workers[i].salary[j];  //адреса імені працівника ставиться у відповідність до його зарплати
        }
    }
    average /= (unit.count * n);        //пошук середьного значення для 
    int counter = 0;
    for (int i = 0; i < unit.count; i++) {
        float current = 0;
        for (int j = 0; j < n; ++j) {
            current += unit.workers[i].salary[j];
        }
        current /= n;
        if (current < average) {
            counter++;
        }
    }
    return counter;
}

void sortUnitWorkers(struct Unit unit, int n) {
    for (int i = 0; i < unit.count; i++) {
        quickSort(unit.workers[i].salary, 0, n - 1);
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int n, m, m1;                       // тут ми вказуємо типи фактичних змінних 

    printf("Enter n: ");
    scanf("%d", &n);
    printf("Enter m: ");
    scanf("%d", &m);
    printf("Enter m1: ");
    scanf("%d", &m1);

    struct Unit u1;
    u1.count = m;
    u1.workers = malloc(u1.count * sizeof(struct Worker));   //динамічне виділення пам`яті

    struct Unit u2;
    u2.count = m1;
    u2.workers = malloc(u2.count * sizeof(struct Worker));

    printf("\nEnter workers and their salary for u1");
    for (int i = 0; i < u1.count; i++) {
        printf("\nEnter worker name: ");
        scanf("%s", u1.workers[i].name);
        u1.workers[i].salary = (float*)malloc(n * sizeof(float));   //приведение типа зарплаты к float
        for (int j = 0; j < n; ++j) {
            printf("Enter salary for year %d: ", j + 1);
            float value;
            scanf("%f", &value);
            u1.workers[i].salary[j] = value;
        }
    }

    printf("\nEnter workers and their salary for u2");
    for (int i = 0; i < u2.count; i++) {
        printf("\nEnter worker name: ");
        scanf("%s", u2.workers[i].name);
        u2.workers[i].salary = (float*)malloc(n * sizeof(float));
        for (int j = 0; j < n; ++j) {
            printf("Enter salary for year %d: ", j + 1);
            float value;
            scanf("%f", &value);
            u2.workers[i].salary[j] = value;
        }
    }

    printf("\nNumber of employees with below average wages in u1: %d", findCountMinimal(u1, n));
    printf("\nNumber of employees with below average wages in u2: %d", findCountMinimal(u2, n));

    printf("\n\nWorkers of the u1 with sorted salary:");
    sortUnitWorkers(u1, n);
    for (int i = 0; i < u1.count; i++) {
        printf("\n%s", u1.workers[i].name);
        for (int j = 0; j < n; ++j) {
            printf("\n%f", u1.workers[i].salary[j]);
        }
    }

    printf("\n\nWorkers of the u2 with sorted salary:");
    sortUnitWorkers(u2, n);
    for (int i = 0; i < u2.count; i++) {
        printf("\n%s", u2.workers[i].name);
        for (int j = 0; j < n; ++j) {
            printf("\n%f", u2.workers[i].salary[j]);
        }
    }

    printf("\n");
    return 0;
}
