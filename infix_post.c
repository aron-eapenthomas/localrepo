#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include<stdlib.h>
#define MaxSize 100
static int top=-1;
static int Ans_stack[MaxSize];

static int top_op=-1;
static char op_stack[MaxSize];

static int top_Post=-1;
static char Post_stack[MaxSize];
int Post(char sy);
int precedence(char op);
int precedence(char op)
{
    if((op=='+')||(op=='-'))
    {
        return 1;
    }
    else if((op=='*')||(op=='/'))
    {
        return 2;
    }
    else if(op=='^')
    {
        return 3;
    }
    else
    {
        return 0;
    }
    
    
}
int Post(char sy)
{
    top_Post++;
    Post_stack[top_Post]=sy;
    return 0;

}
int stack_operator(char op,int prec)
{
    int current_prec=-1;
    if(top_op!=-1)
    {
        current_prec=precedence(op_stack[top_op]);
    }
    else
    {
        current_prec=0;
    }
    if (op==')')
    {
        while((top_op!=-1)&& (op_stack[top_op]!='('))
        {
            Post(op_stack[top_op]);
            Post(' ');
            top_op--;
        }
        if((top_op!=-1)&& (op_stack[top_op]=='('))
        {
            top_op--;
        }
    }
    else if(op=='(')
    {
        op_stack[++top_op]=op;    
    }
    else if((current_prec<prec)||(top_op==-1))
    {
        op_stack[++top_op]=op;    
    }
    else if(current_prec>=prec)
    {

        while (current_prec>=prec)
        {
            Post(op_stack[top_op--]);
            Post(' ');
            current_prec=precedence(op_stack[top_op]);
        }
        op_stack[++top_op]=op;    
        
    }
    return 0;
}
int Push_Ans_Stack(int num)
{
    top++;
    Ans_stack[top]=num;
    return 1;
}
int Pop_Ans_Stack()
{
    if(top!=-1)
    {
        int element =Ans_stack[top];
        top--;
        return element;
    }
    else
    {
        exit(0);
        return 0;

    }
}
int Eval_Postfix()
{
    int i,j=0,start,num,temp,ans,op1,op2;
    i=0;
    while(i<=top_Post)
    {
        if(isspace(Post_stack[i]))
        {
            i++;
        }
        else if(isdigit(Post_stack[i]))
        {
            num=0;
            while (isdigit(Post_stack[i])&&i<=top_Post)
            {
                num=num*10+(Post_stack[i]-'0');
                i++;
            }
            Push_Ans_Stack(num);
            
        }
        else
        {

                op2=Pop_Ans_Stack();
                op1=Pop_Ans_Stack();

                switch (Post_stack[i])
                {
                case '+':
                    ans=op1+op2;
                    Push_Ans_Stack(ans);
                    break;
                case '-':
                    ans=op1-op2;
                    Push_Ans_Stack(ans);
                    break;
                case '*':
                    ans=op1*op2;
                    Push_Ans_Stack(ans);
                    break;
                case '/':
                    ans=op1/op2;
                    Push_Ans_Stack(ans);
                    break;
                case '^':
                    ans=(int)pow(op1,op2);
                    Push_Ans_Stack(ans);
                    break;
                }
            i++;
        }
    }
    return 0;
    
}


int main()
{
    char exp[100];
    int length,i,j,num=0,a=0,b,prec,h;
    printf("Enter the infix expression:");
    scanf("%s",exp);
    strcat(exp, ")");
    top_op++;
    length=strlen(exp);
    op_stack[top_op]='(';

    for(i=0;i<length;i++)
    {
        if(isdigit(exp[i]))
        {
            Post(exp[i]);
        }
        else
        {
            Post(' ');
            prec=precedence(exp[i]);
            h=stack_operator(exp[i],prec);
        }
    } 
    //Number generator
    printf("The Postfix Expression :");
    for(i=0,a=0;i<=top_Post;i++)
    {
        printf("%c",Post_stack[i]);
    }
    printf("The Evaluated result:");
    i=Eval_Postfix();
    
    printf("%d",Ans_stack[top]);


    return 0;

}
