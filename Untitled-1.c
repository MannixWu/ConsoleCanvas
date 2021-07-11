/*
 * @Author: your name
 * @Date: 2021-06-29 20:27:18
 * @LastEditTime: 2021-07-10 13:17:08
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \myCanvas\Untitled-1.c
 */
#include <stdio.h>
#include <Windows.h>

#define WIDTH 3
#define HEIGHT 3

void p(int **p){
    for(int i = 0;i<4;i++){
        printf("pa:\t%d",*(p+i));
    }
}
int getCell(int *p, int x, int y)
{
  while (x < 0)
  {
    x += WIDTH;
  }
  while (x >= WIDTH)
  {
    x -= WIDTH;
  }
  while (y < 0)
  {
    y += HEIGHT;
  }
  while (y >= HEIGHT)
  {
    y -= HEIGHT;
  }
  return *(p+x+y*HEIGHT);
}
int main(){
    int a[HEIGHT][WIDTH]={{1,2,3},{4,5,6},{7,8,9}};
    int b[HEIGHT][WIDTH]={{5,6},{7,8}};
    printf("%d",(getCell(a,5,0)));
    system("pause");
    return 0;
}