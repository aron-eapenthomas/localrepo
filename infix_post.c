#include<stdio.h>
#include<string.h>
#include<ctype.h>
#define MaxSize 100
static int top=-1,top_op=-1,top_Post=-1,Ans_stack[MaxSize];
static char Post_stack[MaxSize],op_stack[MaxSize];
int Post(char sy);
int precedence(char op);
int precedence(char op)
{
    if((op=='+')||(op=='-'))
    {
        return 3;
    }
    else if((op=='*')||(op=='/'))
    {
        return 4;
    }
    else if(op=='^')
    {
        return 5;
    }
    else if(op=='(')
    {
        // if(top_op==-1)
        // {
        //     return 0;
        // }
        // else
        // {
        //     return 8;
        // }
        return 0;
    }
    else if (op==')')
    {
        return 10;
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
    int current_prec=precedence(op_stack[top_op]);
    if (op==')')
    {
        while(op_stack[top_op]!='(')
        {
            // printf("HI %c \n",op_stack[top_op--]);
            Post(op_stack[top_op]);
            Post(' ');
            top_op--;
            // break;
        }
        if(op_stack[top_op]=='(')
        {
            top_op--;
        }
    }
    else if(op=='(')
    {
        op_stack[++top_op]=op;    
    }
    else if(current_prec<prec)
    {
        op_stack[++top_op]=op;    
    }
    else if(current_prec>=prec)
    {
        Post(op_stack[top_op]);
        op_stack[top_op]=op;    
    }
    return 0;
}
int Push_Ans_Stack(int num)
{
    Ans_stack[top]=num;
    top++;
    return 1;
}
int Pop_Ans_Stack()
{
    int element =Ans_stack[top];
    top--;
    return 1;
}
int Eval_Postfix()
{
    int i,j,start,num,temp;
    i=0;
    while(i<=top_Post)
    {
        if(Post_stack[i]==' ')
        {
            if(!isdigit(Post_stack[i+1]))
            {
                i=i+2;
            }
            else
            {
                j=i;
                num=0;
                for(start=j;start<i;start++)
                {
                    num=num*10+(Post_stack[start]-'0');
                    printf("%d",num);
                }
                Push_Ans_Stack(num);   
                i++;             
            }
        }
        else
        {
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
    length=strlen(exp);
    length++;
    exp[length-1]=')';
    // exp[length]='\0';
    top_op++;
    op_stack[top_op]='(';
    // op_stack[top_op+1]='\0';

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
    // op_stack[++top_op]=')';
    // for ( i = 0; i <=top_op; i++)
    // {
    //     // if((op_stack[i]!=')')||(op_stack[i]!='('))
    //     // {
    //         // }
        
    //     Post(op_stack[i]);
    // }   
    //Number generator
    printf("The Postfix Expression");
    for(i=0,a=0;i<=top_Post;i++)
    {
        printf("%c",Post_stack[i]);
    }
    printf("The Evaluated result:%");
    i=Eval_Postfix();
    for(i=0;i<=top;i++)
    {
        printf("%d",Ans_stack[i]);
    }


    return 0;

}
