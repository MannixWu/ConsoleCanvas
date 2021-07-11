#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

#define WIDTH 60
#define HEIGHT 60
#define FRAME 70
#define TRUE 1
#define FALSE 0
// #define max(a, b) ((a) > (b) ? (a) : (b))
// #define min(a, b) ((a) < (b) ? (a) : (b))
#define PI 3.1415
#define LOG(num)(printf("%d\n",num))

int canvas[HEIGHT][WIDTH];
char canvasStr[(HEIGHT + 2) * (WIDTH + 2) * 2 + HEIGHT];
char GetCh(int data);
char ch[] = {' ', '`', '.', '^', ',', ':', '~', '"', '<', '!', 'c', 't', '+', '{', 'i', '7', '?', 'u', '3', '0', 'p', 'w', '4', 'A', '8', 'D', 'X', '%', '#', 'H', 'W', 'M'};
char num[] = {0, 5, 7, 9, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45, 47, 49, 51, 53, 55, 59, 61, 63, 66, 68, 70};

//绘制函数

void showCanvas();
void consoleClear();
void drawPoint(int x, int y, int color);
void clearCanvas(int color);
void drawRect(int x1, int y1, int x2, int y2, int color);
void drawLine(int x1, int y1, int x2, int y2, int color);
void drawTria(int x1, int y1, int x2, int y2, int x3, int y3, int color);

//数学函数

int between(int num, int minNum, int maxNum);
int distance(int x1, int y1, int x2, int y2);
double round(double num);
void swap(int *a, int *b);

//Life Game
int map1[HEIGHT][WIDTH];
int map2[HEIGHT][WIDTH];
int getCellCount();
int getCell();
int main()
{
  for (int y = 0; y < HEIGHT; y++)
  {
    for (int x = 0; x < WIDTH; x++)
    {
      map1[y][x] = 0;
      map2[y][x] = 0;
    }
  }
  //===============预设===============//
  //随机地图
  srand((unsigned)time(NULL));
  for (int y = 0; y < HEIGHT; y++)
  {
    for (int x = 0; x < WIDTH; x++)
    {
      map1[y][x] = (rand()%3==0)?70:0;
    }
  }
  //滑翔伞
  // map1[3][3] = 70;
  // map1[3][4] = 70;
  // map1[3][5] = 70;
  // map1[2][5] = 70;
  // map1[1][4] = 70;
  //---------------预设---------------//
  //程序内容
  while (TRUE){
    //遍历地图每个细胞
    for (int y = 0; y < HEIGHT; y++)
    {
      for (int x = 0; x < WIDTH; x++)
      {
        //对每个细胞计算周边邻居
        int cellCount = getCellCount(x, y);
        //细胞为存活状态
        if (map1[y][x] == 70)
        {
          if (cellCount == 2 || cellCount == 3)
          {
            map2[y][x] = 70;
          }
          else
          {
            map2[y][x] -= 5;
            if(map2[y][x]<0){
              map2[y][x]=0;
            }
          }
        }
        //细胞为死亡状态
        else
        {
          if (cellCount == 3)
          {
            map2[y][x] = 70;
          }
          else{
            map2[y][x] -= 5;
            if(map2[y][x]<0){
              map2[y][x]=0;
            }
          }
        }
      }
    }
    //输出本次地图，并且把新结果当下一次的地图
    for (int y = 0; y < HEIGHT; y++)
    {
      for (int x = 0; x < WIDTH; x++)
      {
        drawPoint(x,y,map1[y][x]);
        map1[y][x] = map2[y][x];
      }
    }
    Sleep(10);
    showCanvas();
  }
  //避免程序自己退出
  system("pause");
  return 0;
}
//获取当前位置细胞邻居数量
int getCellCount(int x, int y)
{
  int sum = 0;

  for (int yy = -1; yy <= 1; yy++)
  {
    for (int xx = -1; xx <= 1; xx++)
    {
      if (!(xx==0&&yy==0))
      {
        int cx = xx + x;
        int cy = yy + y;
        while (cx < 0)
        {
          cx += WIDTH;
        }
        while (cx >= WIDTH)
        {
          cx -= WIDTH;
        }
        while (cy < 0)
        {
          cy += HEIGHT;
        }
        while (cy >= HEIGHT)
        {
          cy -= HEIGHT;
        }
        if(map1[cy][cx]==70){
          sum++ ;
        }
      }
    }
  }
  return sum;
}
/***************************************************************************
 * @brief        绘制线段
 * @param     x1    点1横坐标
 * @param     y1    点1纵坐标
 * @param     x2    点2横坐标
 * @param     y2    点2纵坐标
 * @param     color     绘制的内容
 * @return      void
 * @example:  drawLine(3,4,9,6,1);//以(3,4)和(9,6)两点为端点用1绘制线段
 ***************************************************************************/
void drawLine(int x1, int y1, int x2, int y2, int color)
{
#if 0
    int distance = (int)sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
    for (int i = 0; i < distance; i++)
    {
        drawPoint(x1 + (x2 - x1) * i / distance, y1 + (y2 - y1) * i / distance, color);
    }
#else
  //优化后的算法
  if (fabs(x1 - x2) > fabs(y1 - y2))
  {
    if (x1 > x2)
    {
      swap(&x1, &x2);
      swap(&y1, &y2);
    }
    for (double x = x1; x <= x2; x++)
    {
      double y = round((double)((y2 - y1) * (x - x1)) / (x2 - x1) + y1);
      drawPoint((int)x, (int)y, color);
    }
  }
  else
  {
    if (y1 > y2)
    {
      swap(&x1, &x2);
      swap(&y1, &y2);
    }
    for (double y = y1; y <= y2; y++)
    {
      double x = round((double)((x2 - x1) * (y - y1)) / (y2 - y1) + x1);
      drawPoint((int)x, (int)y, color);
    }
  }
#endif
}

/***************************************************************************
 * @brief        绘制三角形
 * @param     x1    点1横坐标
 * @param     y1    点1纵坐标
 * @param     x2    点2横坐标
 * @param     y2    点2纵坐标
 * @param     x3    点3横坐标
 * @param     y3    点3纵坐标
 * @param     color     绘制的内容
 * @return     void
 * @example  drawTria(45, 5, 5, 6, 40, 5, 1);//以(3,4)和(9,6)两点为端点用1绘制线段
 ***************************************************************************/
void drawTria(int x1, int y1, int x2, int y2, int x3, int y3, int color)
{
  if (y3 < y2)
  {
    swap(&x2, &x3);
    swap(&y2, &y3);
  }
  if (y2 < y1)
  {
    swap(&x1, &x2);
    swap(&y1, &y2);
  }
  if (y3 < y2)
  {
    swap(&x2, &x3);
    swap(&y2, &y3);
  }
  drawLine(x1, y1, x2, y2, color);
  drawLine(x3, y3, x2, y2, color);
  drawLine(x1, y1, x3, y3, color);
  for (double y = y1; y <= y3; y++)
  {
    int xl, xr;
    if (y < y2)
    {
      //上半
      xl = (x2 - x1) * (y - y1) / (y2 - y1) + x1;
    }
    else
    {
      xl = (x2 - x3) * (y - y3) / (y2 - y3) + x3;
    }
    xr = (x3 - x1) * (y - y1) / (y3 - y1) + x1;
    if (xl > xr)
    {
      swap(&xl, &xr);
    }
    for (int x = xl; x <= xr; x++)
    {
      drawPoint(x, y, color);
    }
  }
}

/**************************************************************************************
 * @brief:         在指定坐标绘制点
 * @param       {int} x   坐标x
 * @param       {int} y   坐标y
 * @param       {int} color   绘制的内容
 * @return       void
 **************************************************************************************/
void drawPoint(int x, int y, int color)
{
  if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
  {
    canvas[y][x] = color;
  }
}

/**************************************************************************************
 * @brief:         在两指定坐标矩形范围内填充内容
 * @param       {int} x1  点1 x坐标
 * @param       {int} y1  点1 y坐标
 * @param       {int} x2  点2 x坐标
 * @param       {int} y2  点2 y坐标
 * @param       {int} color   绘制的内容
 * @return        void
 **************************************************************************************/
void drawRect(int x1, int y1, int x2, int y2, int color)
{

  x1 = between(x1, 0, WIDTH - 1);
  y1 = between(y1, 0, HEIGHT - 1);
  x2 = between(x2, 0, WIDTH - 1);
  y2 = between(y2, 0, HEIGHT - 1);
  if (x1 > x2)
  {
    swap(&x1, &x2);
  }
  if (y1 > y2)
  {
    swap(&y1, &y2);
  }
  for (int y = y1; y <= y2; y++)
  {
    for (int x = x1; x <= x2; x++)
    {
      drawPoint(x, y, color);
    }
  }
}

/**************************************************************************************
 * @brief                : 清空控制台
 * @param               void
 * @return               void
 * @example          : consoleClear()；
 **************************************************************************************/
void consoleClear()
{
  system("cls");
}

/**************************************************************************************
 * @brief               :   把画布用指定内容清空
 * @param                {int} color    要清空的内容
 * @return                void
 * @example         :   clearCanvas(0);//把画布清空为0
 **************************************************************************************/
void clearCanvas(int color)
{
  for (int y = 0; y < HEIGHT; y++)
  {
    for (int x = 0; x < WIDTH; x++)
    {
      canvas[y][x] = color;
    }
  }
}

/**************************************************************************************
 * @brief               :   把画布内容输出到控制台
 * @param                void
 * @return                void
 * @example         :   showCanvas();
 **************************************************************************************/
void showCanvas()
{
#if 0
    //上边框
    for (int x = 0; x < WIDTH + 2; x++)
    {
        printf("@@");
    }
    printf("\n");

    for (int y = 0; y < HEIGHT; y++)
    {
        //左边框
        printf("@@");
        //画布内容
        for (int x = 0; x < WIDTH; x++)
        {
            printf("%c%c", GetCh(canvas[y][x]), GetCh(canvas[y][x]));
        }
        //右边框
        printf("@@");
        printf("\n");
    }
    //下边框
    for (int x = 0; x < WIDTH + 2; x++)
    {
        printf("@@");
    }
    printf("\n");
#else
  //consoleClear();
  int i = 0;
  //上边框
  for (int x = 0; x < WIDTH + 2; x++)
  {
    //printf("@@");
    canvasStr[i++] = '@';
    canvasStr[i++] = '@';
  }
  //printf("\n");
  canvasStr[i++] = '\n';

  for (int y = 0; y < HEIGHT; y++)
  {
    //左边框
    //printf("@@");
    canvasStr[i++] = '@';
    canvasStr[i++] = '@';
    //画布内容
    for (int x = 0; x < WIDTH; x++)
    {
      //printf("%c%c", GetCh(canvas[y][x]), GetCh(canvas[y][x]));
      canvasStr[i++] = GetCh(canvas[y][x]);
      canvasStr[i++] = GetCh(canvas[y][x]);
    }
    //右边框
    //printf("@@");
    canvasStr[i++] = '@';
    canvasStr[i++] = '@';
    //printf("\n");
    canvasStr[i++] = '\n';
  }
  //下边框
  for (int x = 0; x < WIDTH + 2; x++)
  {
    //printf("@@");
    canvasStr[i++] = '@';
    canvasStr[i++] = '@';
  }
  //printf("\n");
  canvasStr[i++] = '\n';
  printf("%s", canvasStr);
  HANDLE houtput = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD loc;
  loc.X = 0;
  loc.Y = 0;
  SetConsoleCursorPosition(houtput, loc);
#endif
}

/**************************************************************************************
 * @brief               :  根据灰度计算需要的字符
 * @param               {int} data     灰度值（0~70）
 * @return                {char}          最接近该灰度的字符
 * @note                  版权声明：本文为CSDN博主「DeRoy」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
 * @note                  原文链接：https://blog.csdn.net/qq_44519484/article/details/104983090
 **************************************************************************************/
char GetCh(int data)
{
  //快速查找
  //data=between(data,1,69);
  int left = 0, right = 31, index; //num的最大元素下标是31
  while (left < right)
  {
    index = (left + right) / 2;
    if (num[index] == data)
      return ch[index]; //找到数字 直接返回对应的字符
    else if (num[index] > data)
      right = index - 1; //往左找
    else
      left = index + 1;
  }
  //退出的条件  left>=right
  return ch[left]; //return ch[right]也可以
}

/**************************************************************************************
 * @brief               :   将一个数限定在某一范围内
 * @param                {int} num  被限定的数
 * @param                {int} minNum   最小值
 * @param                {int} maxNum   最大值
 * @return                {int} 限定后的值
 **************************************************************************************/
int between(int num, int minNum, int maxNum)
{
  return max(min(num, maxNum), minNum);
}

/**************************************************************************************
 * @brief               :   计算两点的距离
 * @param                {int} x1   点1 x坐标
 * @param                {int} y1   点1 y坐标
 * @param                {int} x2   点2 x坐标
 * @param                {int} y2   点2 y坐标
 * @return                {int}  两点的距离
 * @example         :  distance(12,21,56,76);
 **************************************************************************************/
int distance(int x1, int y1, int x2, int y2)
{
  return (int)sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

/**************************************************************************************
 * @brief               :   交换两个变量的值
 * @param                {int} *a   变量a的指针
 * @param                {int} *b   变量b的指针
 * @return                 void
 * @example         :   swap( &a, &b);
 **************************************************************************************/
void swap(int *a, int *b)
{
  *a = *a ^ *b;
  *b = *a ^ *b;
  *a = *a ^ *b;
}

/**
 * @description: 四舍五入
 * @param {double} 输入的数
 * @return {*}  取整的结果
 */
double round(double num)
{
  return floor(num + 0.5);
}
