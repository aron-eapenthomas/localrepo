#include<stdio.h>
#include<stdlib.h>
struct Node
{
    int coeff;
    int exp;
    struct Node *link;
};
struct Node* creater()
{
    struct Node *ptr;
    ptr=(struct Node *)malloc(sizeof(struct Node));
    if(ptr==NULL)
    {
        exit(0);
    }
    else
    {
        return ptr;
    }
}
int Add_polynomial(struct Node **head1,struct Node **head2,struct Node **head3);
int Add_polynomial(struct Node **head1,struct Node **head2,struct Node **head3)
{
    struct Node *ptr1=*head1;
    struct Node *ptr2=*head2;
    struct Node *ptr3=*head3;
    struct Node *temp1;
    struct Node *temp2;
    while ((ptr1!=NULL)&&(ptr2!=NULL))
    {
        if(ptr1->exp==ptr2->exp)
        {
            ptr3->coeff=ptr1->coeff+ptr2->coeff;
            ptr3->exp=ptr1->exp;
            ptr1=ptr1->link;
            ptr2=ptr2->link;
            temp1=creater();
            temp2=ptr3;
            ptr3->link=temp1;
            ptr3=ptr3->link;
        }
        else if(ptr1->exp<ptr2->exp)
        {
            ptr3->coeff=ptr2->coeff;
            ptr3->exp=ptr2->exp;
            ptr2=ptr2->link;
            temp1=creater();
            temp2=ptr3;
            ptr3->link=temp1;
            ptr3=ptr3->link;
        }
        else if(ptr1->exp>ptr2->exp)
        {
            ptr3->coeff=ptr1->coeff;
            ptr3->exp=ptr1->exp;
            ptr1=ptr1->link;
            temp1=creater();
            temp2=ptr3;
            ptr3->link=temp1;
            ptr3=ptr3->link;
        }

    }
    while (ptr1!=NULL)
    {
        ptr3->coeff=ptr1->coeff;
        ptr3->exp=ptr1->exp;
        ptr1=ptr1->link;
        temp1=creater();
        temp2=ptr3;
        ptr3->link=temp1;
        ptr3=ptr3->link;
    }
    while (ptr2!=NULL)
    {
        ptr3->coeff=ptr2->coeff;
        ptr3->exp=ptr2->exp;
        ptr2=ptr2->link;
        temp1=creater();
        temp2=ptr3;
        ptr3->link=temp1;
        ptr3=ptr3->link;
    }
    ptr3=temp2;
    ptr3->link=NULL;
    return 1;
    
    
}
int multi_polynomial(struct Node **head1,struct Node **head2,struct Node **head3,int m,int n)
{
    int i,j,max,sum;
    struct Node *ptr1=*head1;
    struct Node *ptr2=*head2;
    struct Node *ptr3=*head3;
    struct Node *head4=creater();
    struct Node *ptr4=head4;
    struct Node *temp1;
    struct Node *temp2;
    int multi_value,multi_exp;
    for ( i = 0; i < m; i++)
    {
        for ( j = 0; j < n; j++)
        {
            multi_value=ptr1->coeff*ptr2->coeff;
            multi_exp=ptr1->exp+ptr2->exp;
            ptr4->coeff=multi_value;
            ptr4->exp=multi_exp;
            ptr2=ptr2->link;
            if((i==m-1)&&(j==n-1))
            {
                ptr4->link=NULL;
            }
            else
            {
                temp1=creater();
                temp2=ptr4;
                ptr4->link=temp1;
                ptr4=ptr4->link;
            }
        }
        ptr1=ptr1->link;
        ptr2=*head2;
        
    }
    // finding the maximum exponent
    max=0;
    temp2=head4;
    while (temp2!=NULL)
    {
        if(temp2->exp>max)
        {
            max=temp2->exp;
        }
        temp2=temp2->link;
    }
    ptr3=*head3;
    for ( i = max; i >= 0; i--)
    {
        temp2=head4;
        sum=0;
        while (temp2!=NULL)
        {
            if(temp2->exp==i)
            {
                sum=sum+temp2->coeff;
            }
            temp2=temp2->link;
        }
        ptr3->coeff=sum;
        ptr3->exp=i;
        if(i!=0)
        {    
            ptr3->link=creater();
            ptr3=ptr3->link;
        }
        else
        {
            ptr3->link=NULL;
        }

    }
    
    return 1;
    
    
}
int display(struct Node *head3)
{
    struct Node *ptr;
    if(head3==NULL)
    {
        printf("Linked list is empty");
    }
    else
    {
        ptr=head3;
        while (ptr!=NULL)
        {
            printf("Coefficient = %d ",ptr->coeff);
            printf("Exponent = %d \n",ptr->exp);
            ptr=ptr->link;
        }
        
    }
    return 0;
}

int main()
{
    int i=0,m,n,op,t;
    struct Node *head1,*head2,*ptr,*temp,*head3=NULL;
    printf("Enter the no of terms in the first polynomial:");
    scanf("%d",&m);
    printf("Enter the no of terms in the second polynomial:");
    scanf("%d",&n);
    //  without Minimizing the use of else in the loop
    //First polynomial
    printf("For the first polynomial\n");
    head1=creater();
    ptr=head1;
    for(i=0;i<m;i++)
    {
        printf("Enter the %d coeffient:",i+1);
        scanf("%d",&ptr->coeff);
        printf("Enter its corresponding exponent:");
        scanf("%d",&ptr->exp);
        if(i!=m-1)
        {
            temp=creater();
            ptr->link=temp;
            ptr=ptr->link;
        }
        else
        {
            ptr->link=NULL;
        }

    }
    //Second polynomial
    printf("For the second polynomial\n");
    head2=creater();
    ptr=head2;
    for(i=0;i<n;i++)
    {
        printf("Enter the %d coeffient:",i+1);
        scanf("%d",&ptr->coeff);
        printf("Enter its corresponding exponent:");
        scanf("%d",&ptr->exp);
        if(i!=n-1)
        {
            temp=creater();
            ptr->link=temp;
            ptr=ptr->link;
        }
        else
        {
            ptr->link=NULL;
        }

    }
    //Minimizing else use in the for loop
    // head1=creater();
    // printf("Enter the %d coeffient:",i+1);
    // scanf("%d",&head1->coeff);
    // printf("Enter its corresponding exponent:");
    // scanf("%d",&head1->exp);
    // ptr=creater();
    // head1->link=ptr;
    // for(i=1;i<m;i++)
    // {
    //     printf("Enter the %d coeffient:",i+1);
    //     scanf("%d",&ptr->coeff);
    //     printf("Enter its corresponding:");
    //     scanf("%d",&ptr->exp);
    //     if(i!=m-1)
    //     {
    //         temp=creater();
    //         ptr->link=temp;
    //         ptr=ptr->link;
    //     }
    //     else
    //     {
    //         ptr->link=NULL;
    //     }

    // }
    // printf("For the first polynomial\n");
    // if(head1==NULL)
    // {
    //     printf("Linked list is empty");
    // }
    // else
    // {
    //     ptr=head1;
    //     while (ptr!=NULL)
    //     {
    //         printf("Coefficient = %d ",ptr->coeff);
    //         printf("Exponent = %d \n",ptr->exp);
    //         ptr=ptr->link;
    //     }
        
    // }
    // printf("For the second polynomial\n");
    // if(head2==NULL)
    // {
    //     printf("Linked list is empty");
    // }
    // else
    // {
    //     ptr=head2;
    //     while (ptr!=NULL)
    //     {
    //         printf("Coefficient = %d ",ptr->coeff);
    //         printf("Exponent = %d \n",ptr->exp);
    //         ptr=ptr->link;
    //     }
        
    // }
    while (1)
    {
        printf("Press 1 for addition \n 2 for Multiplication \n 3 for exit\n");
        printf("Enter your choice: ");
        scanf("%d",&op);
        if(op==1)
        {
            head3=creater();
            t=Add_polynomial(&head1,&head2,&head3);
            printf("The Resultant Polynomial after Addition:\n");
            t=display(head3);
        }
        else if(op==2)
        {
            head3=creater();
            t=multi_polynomial(&head1,&head2,&head3,m,n);
            printf("The Resultant Polynomial after multiplication:\n");
            t=display(head3);
        }
        else
        {
            break;
        }
    }
    return 0;
}
