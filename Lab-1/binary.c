#include <stdio.h>
#include <math.h>
//it returns kati size ko array banaune
int declareSize(int decimal)
{
    int i=0;
    while(decimal>0)
    {
        decimal /= 2;
        i++;
    }
    return i;
}

void showArray(int *array, int maxSize)
{
    if(array[maxSize])
    {
        for(int i=maxSize; i>=0; i--)
        {
            printf("%d", array[i]);
        }
        printf("\n");
    }

    else
    {
         for(int i=maxSize-1; i>=0; i--)
        {
            printf("%d", array[i]);
        }
        printf("\n");
    }
}

void decimalToBinary(int decimal, int *binary, int maxSize)
{
    for(int i=0; i<=maxSize; i++)
    {
        binary[i]=0;
    }

    int i=0;
    while(decimal>0)
    {
        binary[i]=decimal % 2;
        decimal /= 2;
        i++;
    }
    showArray(binary,maxSize);
}

void binaryAddition(int *binary1, int *binary2, int *sum, int maxSize)
{
    int carry=0;
    for(int i=0; i<=maxSize; i++)
    {
        sum[i]=0;
    }

    for(int i=0; i<maxSize; i++)
    {
        sum[i]=binary1[i]^binary2[i]^carry;
        carry=(binary1[i]&binary2[i]) | (binary1[i]&carry) | (binary2[i]&carry) | (binary1[i]&binary2[i]&carry);
    }
    if(carry)
    {
        sum[maxSize]=1;
    }
    else
    {
        sum[maxSize]=0;
    }
    
    
}

void _1sComplement(int decimal, int *smallarr, int maxSize)
{
    printf("1's Complement of %d: ", decimal);
    for(int i=0; i<maxSize; i++)
    {
        smallarr[i]=!smallarr[i];
    }
    showArray(smallarr, maxSize);
}

void _2sComplement(int decimal, int *smallarr, int *sum,int maxSize)
{
    printf("2's Complement of %d: ", decimal);
    int add1[maxSize];

    //initialization
    for(int i=0; i<=maxSize; i++)
    {
        add1[i]=0;
    }
    add1[0]=1;

    binaryAddition(smallarr,add1,sum,maxSize);
    for(int i=0; i<=maxSize; i++)
    {
        smallarr[i]=sum[i];
    }
}

void subBinary(int *smallarr, int *bigarr, int *sum, int maxSize)
{
    binaryAddition(smallarr,bigarr,sum, maxSize);
    if(sum[maxSize]==1)
    {
        sum[maxSize]=0;
    }
    showArray(sum,maxSize);
}

void converIntoDecimal(int *arr, int maxSize)
{
    int x=0;
    int j=0;

    for(int i=0; i<=maxSize; i++)
    {
        x +=arr[i]*(pow(2, j));
        j++;
    }
    printf("%d", x);
    printf("\n");
}

int main()
{
    //decimal 1
    int decimal1;
    printf("Enter 1st Decimal: ");
    scanf("%d", &decimal1);

    //decimal 2
    int decimal2;
    printf("Enter 2nd Decimal: ");
    scanf("%d", &decimal2);

    //size of 2 decimals and comparing which is greater
    int size1=declareSize(decimal1);
    int size2=declareSize(decimal2);
    int maxSize=(size1>size2) ? size1 : size2;

    //declaration of two array to store binary
    int binary1[maxSize];
    int binary2[maxSize];

    printf("\n");
    printf("Binary of %d: ",decimal1);
    decimalToBinary(decimal1, binary1, maxSize);
    printf("Binary of %d: ",decimal2);
    decimalToBinary(decimal2, binary2, maxSize);

    //binaryaddition
    printf("\n");
    int sum[maxSize];
    printf("Binary addition: ");
    binaryAddition(binary1,binary2,sum,maxSize);
    showArray(sum,maxSize);

    //value of binary addition in decimal
    printf("\n");
    printf("Value of binary addition in Decimal: ");
    converIntoDecimal(sum,maxSize);

    //1's complement of smaller number
    // int smallerArray[maxSize];
    int smallerDecimale= (decimal1>decimal2) ? decimal2 : decimal1;
    int biggerDecimale= (decimal1>decimal2) ? decimal1 : decimal2;
    int *smallerArray = ((decimal1>decimal2) ? binary2 : binary1);
    int *biggerArray = ((decimal1>decimal2) ? binary1 : binary2);
    printf("\n");
    _1sComplement(smallerDecimale, smallerArray, maxSize);

    //2's complement
    _2sComplement(smallerDecimale, smallerArray, sum, maxSize);
    showArray(sum,maxSize);

    //2scomplement binasy substraction
    printf("\n");
    printf("Addition of 2's complement of '%d' & binary '%d': ",smallerDecimale,biggerDecimale);
    subBinary(smallerArray, biggerArray, sum, maxSize);
    printf("\n");
    if(decimal1>decimal2)
    {
        printf("Substraction (%d-%d): ",decimal1, decimal2);
    }

    else
    {
        printf("Substraction (%d-%d): -", decimal1, decimal2);
    }
    
    //converting into decimal
    converIntoDecimal(sum,maxSize);
    return 0;
}