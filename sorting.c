//insertion sort
// #include<stdio.h>
// int main()
// {
//     int A[100],i,n,j,key;
//     printf("Enter the no of elements you want to enter:");
//     scanf("%d",&n);
//     printf("Enter the elements:");
//     for(i=0;i<n;i++)
//     {
//         scanf("%d",&A[i]);
//     }
//     for ( i = 1; i <n; i++)
//     {
//         key=A[i];
//         j=i-1;
//         while ((key<A[j])&&(j>=0))
//         {
//             A[j+1]=A[j];
//             j=j-1;
//         }
//         A[j+1]=key;
        
//     }
//     for(i=0;i<n;i++)
//     {
//         printf(" he %d",A[i]);
//     }
//     return 0;
    

// }

//Quick sort
// #include<stdio.h>
// int partition(int A[],int p,int r)
// {
//     int pivot=A[r];
//     int i=p-1,j;
//     int temp;
//     for (j = p; j < r; j++)
//     {
//         if(A[j]<=pivot)
//         {
//             i++;
//             temp=A[j];
//             A[j]=A[i];
//             A[i]=temp;

//         }
//     }
//     i++;
//     temp=A[r];
//     A[r]=A[i];
//     A[i]=temp;
//     return i;

    
// }
// void QuickSort(int A[],int p,int r)
// {
//     int q;
//     if(p<r)
//     {
//         q=partition(A,p,r);
//         QuickSort(A,p,q-1);
//         QuickSort(A,q+1,r);
//     }
//     else
//     {
//         return;
//     }


// }
// int main()
// {
//     int A[100],r,i,p=0;
//     printf("Enter the no of elements you want to enter:");
//     scanf("%d",&r);
//     printf("Enter the elements:");
//     for(i=0;i<r;i++)
//     {
//         scanf("%d",&A[i]);
//     }
//     QuickSort(A,p,r-1);
//     for(i=0;i<r;i++)
//     {
//         printf("%d",A[i]);
//     }
// }

//Merge sort
#include<stdio.h>
void merge(int A[],int start,int mid,int end)
{
    int i=start,j=mid+1;
    int temp[100],m=0;
    while ((i<=mid)&&(j<=end))
    {
        if(A[j]<A[i])
        {
            temp[m]=A[j];
            m++;
            j++;
        }
        else
        {
            temp[m]=A[i];
            m++;
            i++;
        }
    }
    while (i<=mid)
    {
        temp[m]=A[i];
        m++;
        i++;
    }
    while (j<=end)
    {
        temp[m]=A[j];
        m++;
        j++;
    }
    for(i=0;i<m;i++)
    {
        A[start+i]=temp[i];
    }
    return;
    
    
}
void mergesort(int A[],int start,int end)
{
    int mid;
    if(start<end)
    {
        mid=start+((end-start)/2);
        mergesort(A,start,mid);
        mergesort(A,mid+1,end);
        merge(A,start,mid,end);

    }
    else
    {
        return;
    }
}

int main()
{
    int A[100],r,i,p=0;
    printf("Enter the no of elements you want to enter:");
    scanf("%d",&r);
    printf("Enter the elements:");
    for(i=0;i<r;i++)
    {
        scanf("%d",&A[i]);
    }
    mergesort(A,p,r-1);
    printf("The sorted array: ");
    for(i=0;i<r;i++)
    {
        printf("%d\t",A[i]);
    }
}
