/*
Calculator infix to postfix and evaluate expression */
#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <math.h> 

#define MAX_OP 6
#define MAX_ITEM 100

typedef struct stk
{
    char *item[MAX_ITEM];
    int top;
} STACK;
STACK S;

char op[MAX_OP]={'(','+','-','*','/','^'};
char prio[MAX_OP]={0, 1, 1, 2, 2, 3};
int in_item, max_len, post_item;
bool error = false;

int ReadExpression(char *, char **);
void in_to_post(char **, char **);
void push(char *);
void pop(char **);
int priority(char *);
double in_evaluate(char **);
void evaluate(char **, char *, char *);
void ftoa(double, char *);

void main()
{
    char salir[MAX_ITEM];
    int repetir = 1;
    char expression[MAX_ITEM];
    int i;

 
    do{
           S.top = -1;

    printf("Ingrese expresion infija con una longitud maxima de %d: \n",MAX_ITEM);
    cin >> expression;
    max_len = (int)strlen(expression)+1;
    if(max_len < 100) max_len = 100;
    if (max_len > MAX_ITEM)
    {
        printf("La expresion es muy larga el limite maximo es: %d",MAX_ITEM);
        _getch();
        return;
    }

    char **infix = new char*[max_len];
    in_item = ReadExpression(expression,infix);


    printf("\nInfija: \n");
    for(i=0;i<in_item;i++)
        printf("%s ",infix[i]);


    char **postfix = new char*[in_item];


    in_to_post(infix,postfix);

    printf("\n\nPostfija: \n");
    for(i=0;i<post_item;i++)
        printf("%s ",postfix[i]);


    printf("\n\nRespuesta = %.2f\n",in_evaluate(postfix));


    for(i=0;i<in_item;i++)
        delete [] infix[i];
    delete [] infix;


   printf("\n\t Quiere seguir?  [S/N]: ");
   gets(salir);
   if (!(strcmp(salir, "S") == 0 || strcmp(salir, "s") == 0)) {
			repetir = 0;
		}

    } while(repetir);


    system("pause");

	
}

int ReadExpression(char *in, char *infix[])       
{
    int i, j, k;

    i = j = k = 0;
    if(in[0] == '+' || in[0] == '-') {
        infix[k] = new char[max_len];
        infix[k][0] = '0';
        infix[k++][1] = '\0';
    }
    while(in[i] != '\0')
    {
        infix[k] = new char[max_len];
        if(!isdigit(in[i]))
        {
            strncpy(infix[k],&in[i],1);
            infix[k++][1] = '\0';
            if(in[i] != '\0')
                i++;
            if(in[i-1] == '(' && in[i] == '-') {
                infix[k] = new char[max_len];
                infix[k][0] = '0';
                infix[k++][1] = '\0';
            }
        }
        else
        {
            j = i++;
            while((isdigit(in[i]) || in[i] == '.') && in[i] != '\0')
                i++;
            strncpy(infix[k],&in[j],i-j);
            infix[k++][i-j] = '\0';
        }
    }
    return k;
}

void in_to_post(char *infix[], char *postfix[])       
{
    int i, j;
    char *element;

    i = j = 0;
    for(i=0;i<in_item;i++)
    {
        if(atof(infix[i]) != 0 || infix[i][0] == '0')
            postfix[j++] = infix[i];
        else if(strcmp(infix[i],"(") == 0)
            push(infix[i]);
        else if(strcmp(infix[i],")") == 0)
            while (S.top >= 0)
            {
                pop(&element);
                if(strcmp(element,"(") == 0)
                    break;
                postfix[j++] = element;
            }
        else if(!isdigit(*infix[i]))
        {
            while(S.top >= 0)
            {
                element = S.item[S.top];
                if(priority(infix[i]) <= priority(element))
                {
                    pop(&element);
                    postfix[j++] = element;
                }
                else
                    break;
            }
            push(infix[i]);
        }
    }
    while(S.top >= 0)
    {
        pop(&element);
        postfix[j++] = element;
    }
    post_item = j;
}

void push(char *x)              
{
    if(S.top < MAX_ITEM-1)
    {
        S.top++;
        S.item[S.top] = x;
    }
}
void pop(char **x)
{
    if(S.top >= 0)
    {
        *x = S.item[S.top];
        S.top--;
    }
}

int priority(char *c)
{
    int i;
    for(i=0;i<MAX_OP;i++)
        if(strncmp(&op[i],c,1) == 0)
            return(prio[i]);
    return(-1);
}

double in_evaluate(char *postfix[])
{
    char *op1, *op2, *result;

    for(int i=0;i<post_item;i++)
    {
        if(atof(postfix[i]) != 0 || postfix[i][0] == '0')
            push(postfix[i]);
        else if(!isdigit(*postfix[i]))
        {
            pop(&op2);
            pop(&op1);
            evaluate(&postfix[i],op1,op2);
            if (error == true)
                return 0;
            push(postfix[i]);
        }
    }
    pop(&result);
    return(atof(result));
}
void evaluate(char **optr, char *op1, char *op2)
{
    double a, b, c;

    a = atof(op1);
    b = atof(op2);

    if(strcmp(*optr,"+") == 0)
        c = a + b;
    else if(strcmp(*optr,"-") == 0)
        c = a - b;
    else if(strcmp(*optr,"*") == 0)
        c = a * b;
    else if(strcmp(*optr,"/") == 0)
        if (b != 0.0)
            c = a / b;
        else {
            printf("\n\nSyntax Error\n");
            error = true;
        }
    else if(strcmp(*optr,"^") == 0) {
        if (b >= 0)
            c = pow(a,b);
        else if(ceil(b) == b)
            c = pow(a,b);
        else {
            printf("\n\nSyntax Error\n");
            error = true;
        }
    }
    else {
        printf("\n\nSyntax Error\n");
        error = true;
    }

    ftoa(c,*optr);
}
void ftoa(double f, char *s)    
{
    int i;
    char s2[15];

    if(f < 0)
    {
        s[0] = '-';
        f = -f;
        itoa((int)f,s2,10);
        strcat(s,s2);
    }
    else
        itoa((int)f,s,10);
    strcat(s,".");

    for(i=0;i<15;i++)
    {
        f -= (int)f;
        f *= 10;
        *(s2+i) = char(f+'0');
    }
    s2[i] = '\0';
    strcat(s,s2);
}