/*
 * @Author: your name
 * @Date: 2021-06-29 20:27:18
 * @LastEditTime: 2021-06-30 21:02:10
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \myCanvas\Untitled-1.c
 */
#include "stdio.h"
// #define swap(a,b)(a=a^b,b=a^b,a=a^b)
#define swap(a,b)(a=a+b,b=a-b,a=a-b)
int fun(int num){
    int sum=0;
    while(num){
        if(num%2){
            sum++;
        }
        num/=2;
    }
    return sum;
}
/* #define fun(num)(\
    int sum=0;\
    while(num){\
        if(num%2){\
            sum++;\
        }\
        num/=2;\
    }\
    return sum;\
    )
 */
void main()
{
    int a=7;
    printf("%d",3>2);
    getchar();
}