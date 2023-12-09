#include <stdio.h>
#include <stdlib.h> /* для atof() */
#include <ctype.h>

#define MAXOP 100 /* макс. размер операнда или оператора */
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

char buf[BUFSIZE]; /* буфер для ungetch */
int bufp = 0; /* след, свободная позиция в буфере */

int getch(void) /* взять (возможно возвращенный) символ */ {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* вернуть символ на ввод */
{
    if (bufp >= BUFSIZE)
        printf ("ungetch: слишком много символов\n");
    else
        buf[bufp++] = c;
}

/* getop: получает следующий оператор или операнд */
int getop(char s[])
{
    int i, c;
    while ((s[0] = c = getch()) == ' ' || c == '\t' );
    s[1] = '\0';
    if (!isdigit(c) && c != '.')
        return c; /* не число */
    i = 0;
    if (isdigit(c)) /* накапливаем целую часть */
        while (isdigit(s[++i] = c = getch()));
    if (c == '.') /* накапливаем дробную часть */
        while (isdigit(s[++i] = c = getch()));
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
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