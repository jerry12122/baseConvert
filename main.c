#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

char num[] = {'0', '1', '2', '3', '4', '5', '6','7', '8', '9', 'A', 'B', 'C', 'D','E', 'F'};
void rev(int *a, int la)
{
    int r[la];
    for (int i = 0; i < la; i++)
    {
        r[i] = a[la - 1 - i];
    }
    for (int i = 0; i < la; i++)
    {
        a[i] = r[i];
    }
}
int judge(int *a,int la,int *b,int lb)
{
    int i;
    if(la<lb)
    {
        return -1;
    }
    if(la==lb)
    {
        for(int i = 0; i < la; i++){
            if(a[i]==b[i]){
                continue;
            }
            else if(a[i]>b[i]){
                return 1;
            }
            else{
                return -1;
            }
        }
        return 0;
    }
    else{
        return 1;
    }
}
int add(int *oa, int la, int *ob, int lb, int *r)
{
    int a[100] = {0};
    int b[100] = {0};
    for(int i=0;i<la;i++){
        a[i] = oa[i];
    }
    for(int i = 0; i < lb; i++){
        b[i] = ob[i];
    }
    int s[100] = {0};
    rev(a, la);
    rev(b, lb);
    int len = la > lb ? la : lb;
    int carry = 0;
    int ls;
    for (ls = 0; ls < len; ls++)
    {
        int tmp = (a[ls] + b[ls] + carry);
        s[ls] = tmp % 10;
        carry = tmp / 10;
        
    }
    
    if (carry > 0)
    {
        s[ls] = carry;
        ls++;
    }
    rev(a, la);
    rev(b, lb);
    rev(s, ls);
    for (int i = 0; i < ls; i++)
    {
        r[i] = s[i];
    }
    return ls;
}
int sub(int *oa, int la, int *ob, int lb, int *r)
{
    int a[100] = {0};
    int b[100] = {0};
    int s[100] = {0};
    int ls;
    for (int i = 0; i < la; i++)
    {
        a[i] = oa[i];
    }
    for (int i = 0; i < lb; i++)
    {
        b[i] = ob[i];
    }
    rev(a, la);
    rev(b, lb);
    int len = la > lb ? la : lb;
    
    for (ls = 0; ls < len; ls++)
    {
        s[ls] = a[ls] - b[ls];
    }

    for (int i = 0; i < len-1; i++)
    {
        if (s[i] < 0)
        {
            s[i + 1]--; 
            s[i] += 10;
        }
    } 
    for(ls = len-1;ls>=0;ls--){
        if(s[ls]!=0){
            break;
        }
    }
    ls++;
    rev(s,ls);
    for(int i=0;i<ls;i++){
        r[i] = s[i];
    }
    return ls;
}
int mul(int *oa, int la, int *ob, int lb, int *r)
{
    int s[100] = {0};
    int a[la];
    int b[lb];
    for (int i = 0; i < la; i++)
    {
        a[i] = oa[i];
    }
    for (int i = 0; i < lb; i++)
    {
        b[i] = ob[i];
    }

    rev(a, la);
    rev(b, lb);

    for (int i = 0; i < la; i++)
    {
        for (int j = 0; j < lb; j++)
        {
            s[i + j] += a[i] * b[j];
            // printf("s[%d]:%d+=a[%d]:%d*b[%d]:%d\n",i+j,s[i+j],i,a[i],j,b[j]);
        }
    }
    rev(a, la);
    rev(b, lb);
    int i;
    int carry = 0;
    for (i = 0; i < la + lb - 1; i++)
    {
        s[i] = (s[i] + carry);
        carry = s[i] / 10;
        s[i] = s[i] % 10;
    }
    if (carry > 0)
    {
        s[i] = carry;
        i++;
    }
    rev(s, i);
    for (int j = 0; j < i; j++)
    {
        r[j] = s[j];
    }
    return i;
}
int divide(int *oa,int la,int *ob,int lb,int *q,int *r){
    int a[100] = {0};
    int b[100] = {0};
    int s[100] = {0};
    int ls = 0;

    for(int i = 0; i < la; i++){
        a[i] = oa[i];
    }
    for(int i = 0; i < lb; i++){
        b[i] = ob[i];
    }


    if(la<lb){
        q[0] = 0;
        return 0;
    }
    else{
        int len=la-lb;
        for(int i=lb;i<la;i++)
        {
            b[i]=0; 
        }
        lb=la;

        for(int j=0;j<=len;j++)
        {
            
            while(judge(a,la,b,lb-j)!=-1){
                la = sub(a, la,b,lb-j,a);
                s[j]++;
            }
            ls = j;
        }
    }
    int tmp = 0;
    rev(a, la);
    for(int i=0;i<la;i++){
        tmp+= a[i] * pow(10,i);
    }
    *r = tmp;

    ls++;
    int start;
    for(int i=0;i<ls;i++){
        if(s[i]!=0){
            start = i;
            break;
        }
    }
    ls-=start;
    for(int i=0;i<ls;i++){
        q[i] = s[i+start];
    }

    return ls;
}
int mypow(int time, int *r, int base)
{
    int base_array[2] = {0};
    int len;
    base_array[0] = base % 10;
    if (base > 9)
    {
        len = 2;
        base_array[1] = 1;
    }
    else
    {
        len = 1;
    }
    rev(base_array, len);
    if (time == 0)
    {
        r[0] = 1;
        return 1;
    }
    else if (time == 1)
    {
        for (int i = 0; i < len; i++)
        {
            r[i] = base_array[i];
        }
        return len;
    }
    else
    {
        int s[100] = {0};

        for (int i = 0; i < len; i++)
        {
            s[i] = base_array[i];
        }

        int ls = len;

        for (int i = 1; i < time; i++)
        {
            ls = mul(s, ls, base_array, len, s);
        }

        for (int i = 0; i < ls; i++)
        {
            r[i] = s[i];
        }
        return ls;
    }
}

int convertToDecimal(int *dec, char *input, int base, int size)
{
    int s[100] = {0};
    int ls = 0;
    for (int i = size - 1; i >= 0; i--)
    {
        for (int j = 0; j < 16; j++)
        {
            if (input[i] == num[j])
            {
                int p[100] = {0};
                int lp = mypow(size - 1 - i, p, base);
                int j_array[2] = {0};
                int lj;
                j_array[0] = j % 10;
                if (j > 9)
                {
                    lj = 2;
                    j_array[1] = 1;
                }
                else
                {
                    lj = 1;
                }
                rev(j_array, lj);
                int m[100] = {0};
                int lm = mul(j_array, lj, p, lp, m);
                ls = add(s, ls, m, lm, s);
            }
        }
    }
    for (int k = 0; k < ls; k++)
    {
        dec[k] = s[k];
    }
    return ls;
}
void convertToBase2(int *a,int la,int base){
    int base_array[2] = {0};
    int len;
    base_array[0] = base % 10;
    if (base > 9)
    {
        len = 2;
        base_array[1] = 1;
    }
    else
    {
        len = 1;
    }
    rev(base_array, len);

    int result[100] = {0};
    int lresult = 0;
    
    while(judge(a,la,base_array,len)!=-1){
        int t=0;
        int *r = &t;
        la = divide(a, la,base_array,len,a,r);
        result[lresult] = t;
        lresult++;
    }

    rev(a,la);
    int tmp =0;
    for(int i=0;i<la; i++){
        tmp+= a[i] * pow(10,i);
    }
    printf("%c",num[tmp]);

    for(int i=lresult-1;i>=0; i--){
        printf("%c",num[result[i]]);
    }
}


int check(char *input,int base1,int size){
    int error = size;
    for(int i=0;i<size;i++){
        for(int j=0;j<base1;j++){
            if(input[i]==num[j]){
                error--;
                break;
            }
        }
    }
    return error;
}

int main(int argc, char *argv[]){
    //輸入
    printf("---INPUT---\n");
    char input[100] = {'\0'};
    int base1,base2;
    //a進制
    printf("Number base:");
    scanf("%d",&base1);
    getchar();
    //b進制
    printf("Convert base:");
    scanf("%d",&base2);
    getchar();
    //輸入數字
    printf("Number:");
    scanf("%s", &input);
    getchar();
    //輸出
    printf("---OUTPUT---\n");
    //計算大小
    int size = strlen(input);
    //輸入檢查
    if(check(input,base1,size)!=0){
        printf("ERROR");
        return 0;
    }

    //轉換為10進制
    int dec[100];
    int ldec=convertToDecimal(dec,input,base1,size);
    printf("Decimal:");
    for(int i=0;i<ldec;i++){
        printf("%d",dec[i]);
    }
    printf("\n");
    printf("Converted:");
    //轉換為b進制
    convertToBase2(dec,ldec,base2);
    return 0;
}