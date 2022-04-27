#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
char num[] = {'0', '1', '2', '3', '4', '5', '6','7', '8', '9', 'A', 'B', 'C', 'D','E', 'F'};
void print(char *input,int size){
    printf("Converted Number:");
    for(int i = size;i>=0;i--){
        printf("%c",input[i]);
    }
    printf("\n");
}

int convertToDecimal(char *input,int base,int size){
    int result = 0;
    for(int i = size; i >= 0; i--){
        for (int j = 0; j < 16; j++) 
        {
            if(input[i]==num[j]){
                result = result + j * pow(base,size-1-i);
            }
        }
    }
    return result;
}

void convertToBase2(int input,int base){
    char result[100] = {'\0'};
    int len=0;
    while(input>base){
        result[len] = num[input%base];
        input = input/base;
        len++;
    }
    result[len] = num[input];
    print(result,len);
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
    int size;
    for(size=0;input[size]!='\0';size++);
    //輸入檢查
    if(check(input,base1,size)!=0){
        printf("ERROR");
        return 0;
    }
    //轉換為10進制
    int dec;
    dec=convertToDecimal(input,base1,size);
    printf("Decimal:%d\n",dec);
    //轉換為b進制
    convertToBase2(dec,base2);
    return 0;
}