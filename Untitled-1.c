/*
 * @Author: your name
 * @Date: 2021-06-29 20:27:18
 * @LastEditTime: 2021-07-02 16:10:26
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \myCanvas\Untitled-1.c
 */
#include "stdio.h"
#include <stdlib.h>
// #define swap(a,b)(a=a^b,b=a^b,a=a^b)

typedef struct
{
    float dir_P;
    float dir_D;
    float error_old;

} pid;
float dir_pid(pid *p,float dz, float MBdz)
{
    float dir_error, dir;
    dir_error = dz - MBdz;
    dir = p->dir_P * dir_error + p->dir_D * (dir_error - p->error_old);
    p->error_old = dir_error;
    return dir;
}

pid *init(float pp,float pd)
{
    pid *p = malloc(sizeof(pid));
    p->dir_P=pp;
    p->dir_D=pd;
    p->error_old=0;
}
void main()
{
    pid *pp = init(3.2,1.6);
    printf("%d", dir_pid(pp,33,34));
    getchar();
}