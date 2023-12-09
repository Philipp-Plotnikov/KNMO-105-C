#include <stdio.h>
#include <stdlib.h> /* для atof() */
#include <ctype.h>

#define MAXOP 3 /* макс. размер операнда или оператора */
#define NUMBER '0' /* признак числа */
#define MAXVAL 100 /* максимальная глубина стека */
#define BUFSIZE 100

int sp = 0; /* следующая свободная позиция в стеке */
double val[MAXVAL]; /* стек */

void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("ошибка: стек полон, %g не помещается\n", f);
}

double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf( "ошибка: стек пуст\n");
        return 0.0;
    }
}

/* getop: получает следующий оператор или операнд */
int getop(char s[])
{   
    if (MAXOP < 1) {
        printf( "Error: reach the MAXOP\n");
        exit (1);
    } 
    int i, c;
    while ((s[0] = c = getchar()) == ' ' || c == '\t');
    s[1] = '\0';
    if (!isdigit(c) && c != '.')
        return c; /* не число */
    i = 0;
    if (isdigit(c)) /* накапливаем целую часть */
        while (isdigit(s[++i] = c = getchar())) {
            if (MAXOP < i + 1) {
                printf( "Error: reach the MAXOP\n");
                exit (1);
            } 
        }
    if (c == '.') /* накапливаем дробную часть */
        while (isdigit(s[++i] = c = getchar())) {
            if (MAXOP < i + 1) {
                printf( "Error: reach the MAXOP\n");
                exit (1);
            } 
        }
    s[i] = '\0';
    return NUMBER;
}

/* калькулятор с обратной польской записью */
int main ()
{
    int type;
    double op2;
    char s[MAXOP];
    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push (atof(s));
                break;
            case '+':
                push (pop() + pop());
                break;
            case '*':
                push (pop() * pop());
                break;
            case '-':
                op2 = pop();
                push (pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push (pop() / op2);
                else
                    printf("ошибка: деление на нуль\n");
                break;
            case '\n' :
                printf("\t%.8g\n", pop());
                break;
            default:
                printf("ошибка: неизвестная операция %s\n", s);
                break;
        }
    }
    return 0;
}