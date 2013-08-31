/***********************************************************
	文件名称： 电梯图形化界面
	作 者： 黄昱恺
	版 本： 1.0
	说 明： 电梯图形化界面所需要调用的全部函数
	修改记录:
***********************************************************/
#include <stdio.h>
#include "egg.h"
#pragma comment(lib,"winmm.lib")//发出语音提示所需的lib
#include "sharedVariables.h"

//电梯按钮的图片地址定义
#define BUTTON_INSIDE_ON_1 "img\\button1_pressed.bmp"
#define BUTTON_INSIDE_ON_2 "img\\button2_pressed.bmp"
#define BUTTON_INSIDE_ON_3 "img\\button3_pressed.bmp"
#define BUTTON_INSIDE_ON_4 "img\\button4_pressed.bmp"
#define BUTTON_INSIDE_ON_5 "img\\button5_pressed.bmp"
#define BUTTON_INSIDE_ON_6 "img\\button6_pressed.bmp"
#define BUTTON_INSIDE_ON_7 "img\\button7_pressed.bmp"
#define BUTTON_INSIDE_ON_8 "img\\button8_pressed.bmp"
#define BUTTON_INSIDE_ON_9 "img\\button9_pressed.bmp"
#define BUTTON_OUTSIDE_UP_ON "img\\button_arrow_up_pressed.bmp"
#define BUTTON_OUTSIDE_DOWN_ON "img\\button_arrow_down_pressed.bmp"
#define BUTTON_INSIDE_OFF_1 "img\\button1_released.bmp"
#define BUTTON_INSIDE_OFF_2 "img\\button2_released.bmp"
#define BUTTON_INSIDE_OFF_3 "img\\button3_released.bmp"
#define BUTTON_INSIDE_OFF_4 "img\\button4_released.bmp"
#define BUTTON_INSIDE_OFF_5 "img\\button5_released.bmp"
#define BUTTON_INSIDE_OFF_6 "img\\button6_released.bmp"
#define BUTTON_INSIDE_OFF_7 "img\\button7_released.bmp"
#define BUTTON_INSIDE_OFF_8 "img\\button8_released.bmp"
#define BUTTON_INSIDE_OFF_9 "img\\button9_released.bmp"
#define BUTTON_OUTSIDE_UP_OFF "img\\button_arrow_up_released.bmp"
#define BUTTON_OUTSIDE_DOWN_OFF "img\\button_arrow_down_released.bmp"
//各按钮的大小定义
#define INSIDE_BUTTON_LENGTH 67
#define INSIDE_BUTTON_HEIGHT 67
#define OUTSIDE_BUTTON_LENGTH 30
#define OUTSIDE_BUTTON_HEIGHT 30
#define ELEVATOR_GO 73
#define ELEVATOR_OPEN 73
#define ELEVATOR_HEIGHT 73

//电梯初始化时用到的图片定义
#define I1	 "img\\initialize\\1.bmp"
#define I2	 "img\\initialize\\2.bmp"
#define I3	 "img\\initialize\\3.bmp"
#define I4	 "img\\initialize\\4.bmp"
#define I5	 "img\\initialize\\5.bmp"
#define I6	 "img\\initialize\\6.bmp"
#define I7	 "img\\initialize\\7.bmp"
#define I8	 "img\\initialize\\8.bmp"
#define I9	 "img\\initialize\\9.bmp"
#define I10	 "img\\initialize\\10.bmp"
#define I11	 "img\\initialize\\11.bmp"
#define I12	 "img\\initialize\\12.bmp"
#define I13	 "img\\initialize\\13.bmp"
#define I14	 "img\\initialize\\14.bmp"
#define I15	 "img\\initialize\\15.bmp"
#define I16	 "img\\initialize\\16.bmp"
#define I17	 "img\\initialize\\17.bmp"
#define I18	 "img\\initialize\\18.bmp"
#define I19	 "img\\initialize\\19.bmp"
#define I20	 "img\\initialize\\20.bmp"
#define I21	 "img\\initialize\\21.bmp"
#define I22	 "img\\initialize\\22.bmp"
#define I23	 "img\\initialize\\23.bmp"
#define I24	 "img\\initialize\\24.bmp"
#define I25	 "img\\initialize\\25.bmp"
#define I26	 "img\\initialize\\26.bmp"
#define I27	 "img\\initialize\\27.bmp"
#define I28	 "img\\initialize\\28.bmp"
#define I29	 "img\\initialize\\29.bmp"
#define I30	 "img\\initialize\\30.bmp"
#define I31	 "img\\initialize\\31.bmp"
#define I32	 "img\\initialize\\32.bmp"
#define I33	 "img\\initialize\\33.bmp"
#define I34	 "img\\initialize\\34.bmp"
#define I35	 "img\\initialize\\35.bmp"
#define I36	 "img\\initialize\\36.bmp"
#define I37	 "img\\initialize\\37.bmp"
#define I38	 "img\\initialize\\38.bmp"
#define I39	 "img\\initialize\\39.bmp"
#define I40	 "img\\initialize\\40.bmp"
#define I41	 "img\\initialize\\41.bmp"
#define I42	 "img\\initialize\\42.bmp"
#define I43	 "img\\initialize\\43.bmp"
#define I44	 "img\\initialize\\44.bmp"
#define I45	 "img\\initialize\\45.bmp"
#define I46	 "img\\initialize\\46.bmp"
#define I47	 "img\\initialize\\47.bmp"
#define I48	 "img\\initialize\\48.bmp"
#define I49	 "img\\initialize\\49.bmp"
#define I50	 "img\\initialize\\50.bmp"
#define I51	 "img\\initialize\\51.bmp"
#define I52	 "img\\initialize\\52.bmp"
#define I53	 "img\\initialize\\53.bmp"
#define I54	 "img\\initialize\\54.bmp"
#define I55	 "img\\initialize\\55.bmp"
#define I56	 "img\\initialize\\56.bmp"
#define I57	 "img\\initialize\\57.bmp"
#define I58	 "img\\initialize\\58.bmp"
#define I59	 "img\\initialize\\59.bmp"
#define I60	 "img\\initialize\\60.bmp"
#define I61	 "img\\initialize\\61.bmp"
#define I62	 "img\\initialize\\62.bmp"
#define I63	 "img\\initialize\\63.bmp"
#define I64	 "img\\initialize\\64.bmp"
#define I65	 "img\\initialize\\65.bmp"
#define I66	 "img\\initialize\\66.bmp"
#define I67	 "img\\initialize\\67.bmp"
#define I68	 "img\\initialize\\68.bmp"
#define I69	 "img\\initialize\\69.bmp"
#define I70	 "img\\initialize\\70.bmp"
#define I71	 "img\\initialize\\71.bmp"
#define I72	 "img\\initialize\\72.bmp"
#define I73	 "img\\initialize\\73.bmp"
#define I74	 "img\\initialize\\74.bmp"
#define I75	 "img\\initialize\\75.bmp"
#define I76	 "img\\initialize\\76.bmp"
#define I77	 "img\\initialize\\77.bmp"
#define I78	 "img\\initialize\\78.bmp"
#define I79	 "img\\initialize\\79.bmp"
#define I80	 "img\\initialize\\80.bmp"
#define I81	 "img\\initialize\\81.bmp"
#define I82	 "img\\initialize\\82.bmp"
#define I83	 "img\\initialize\\83.bmp"
#define I84	 "img\\initialize\\84.bmp"
#define I85	 "img\\initialize\\85.bmp"
#define I86	 "img\\initialize\\86.bmp"
#define I87	 "img\\initialize\\87.bmp"
#define I88	 "img\\initialize\\88.bmp"
#define I89	 "img\\initialize\\89.bmp"
#define I90	 "img\\initialize\\90.bmp"
#define I91	 "img\\initialize\\91.bmp"
#define I92	 "img\\initialize\\92.bmp"
#define I93	 "img\\initialize\\93.bmp"
#define I94	 "img\\initialize\\94.bmp"
#define I95	 "img\\initialize\\95.bmp"

//电梯开门动画用到的图片定义
#define L1	"img\\lift\\1.bmp"
#define L2	"img\\lift\\2.bmp"
#define L3	"img\\lift\\3.bmp"
#define L4	"img\\lift\\4.bmp"
#define L5	"img\\lift\\5.bmp"
#define L6	"img\\lift\\6.bmp"
#define L7	"img\\lift\\7.bmp"
#define L8	"img\\lift\\8.bmp"
#define L9	"img\\lift\\9.bmp"
#define L10	"img\\lift\\10.bmp"
#define L11	"img\\lift\\11.bmp"
#define L12	"img\\lift\\12.bmp"
#define L13	"img\\lift\\13.bmp"
#define L14	"img\\lift\\14.bmp"
#define L15	"img\\lift\\15.bmp"
#define L16	"img\\lift\\16.bmp"
#define L17	"img\\lift\\17.bmp"
#define L18	"img\\lift\\18.bmp"
#define L19	"img\\lift\\19.bmp"
#define L20	"img\\lift\\20.bmp"
#define L21	"img\\lift\\21.bmp"
#define L22	"img\\lift\\22.bmp"
#define L23	"img\\lift\\23.bmp"
#define L24	"img\\lift\\24.bmp"
#define L25	"img\\lift\\25.bmp"
#define L26	"img\\lift\\26.bmp"
#define L27	"img\\lift\\27.bmp"
//电梯楼层显示的图片定义
#define F1	"img\\Screen_1.bmp"
#define F2	"img\\Screen_2.bmp"
#define F3	"img\\Screen_3.bmp"
#define F4	"img\\Screen_4.bmp"
#define F5	"img\\Screen_5.bmp"
#define F6	"img\\Screen_6.bmp"
#define F7	"img\\Screen_7.bmp"
#define F8	"img\\Screen_8.bmp"
#define F9	"img\\Screen_9.bmp"
//电梯向上运行时指示灯动画图片定义
#define MP1	"img\\up\\1.bmp"
#define MP2	"img\\up\\2.bmp"
#define MP3	"img\\up\\3.bmp"
#define MP4	"img\\up\\4.bmp"
#define MP5	"img\\up\\5.bmp"
#define MP6	"img\\up\\6.bmp"
#define MP7	"img\\up\\7.bmp"
#define MP8	"img\\up\\8.bmp"
#define MP9	"img\\up\\9.bmp"
#define MP10	"img\\up\\10.bmp"
#define MP11	"img\\up\\11.bmp"
#define MP12	"img\\up\\12.bmp"
#define MP13	"img\\up\\13.bmp"
#define MP14	"img\\up\\14.bmp"
#define MP15	"img\\up\\15.bmp"
#define MP16	"img\\up\\16.bmp"
#define MP17	"img\\up\\17.bmp"
#define MP18	"img\\up\\18.bmp"
#define MP19	"img\\up\\19.bmp"
#define MP20	"img\\up\\20.bmp"
#define MP21	"img\\up\\21.bmp"
#define MP22	"img\\up\\22.bmp"
#define MP23	"img\\up\\23.bmp"
#define MP24	"img\\up\\24.bmp"
#define MP25	"img\\up\\25.bmp"
#define MP26	"img\\up\\26.bmp"
#define MP27	"img\\up\\27.bmp"
#define MP28	"img\\up\\28.bmp"
#define MP29	"img\\up\\29.bmp"
#define MP30	"img\\up\\30.bmp"
#define MP31	"img\\up\\31.bmp"
#define MP32	"img\\up\\32.bmp"
#define MP33	"img\\up\\33.bmp"
#define MP34	"img\\up\\34.bmp"
#define MP35	"img\\up\\35.bmp"

//电梯向下运行时指示灯动画图片定义
#define MD1	"img\\down\\1.bmp"
#define MD2	"img\\down\\2.bmp"
#define MD3	"img\\down\\3.bmp"
#define MD4	"img\\down\\4.bmp"
#define MD5	"img\\down\\5.bmp"
#define MD6	"img\\down\\6.bmp"
#define MD7	"img\\down\\7.bmp"
#define MD8	"img\\down\\8.bmp"
#define MD9	"img\\down\\9.bmp"
#define MD10	"img\\down\\10.bmp"
#define MD11	"img\\down\\11.bmp"
#define MD12	"img\\down\\12.bmp"
#define MD13	"img\\down\\13.bmp"
#define MD14	"img\\down\\14.bmp"
#define MD15	"img\\down\\15.bmp"
#define MD16	"img\\down\\16.bmp"
#define MD17	"img\\down\\17.bmp"
#define MD18	"img\\down\\18.bmp"
#define MD19	"img\\down\\19.bmp"
#define MD20	"img\\down\\20.bmp"
#define MD21	"img\\down\\21.bmp"
#define MD22	"img\\down\\22.bmp"
#define MD23	"img\\down\\23.bmp"
#define MD24	"img\\down\\24.bmp"
#define MD25	"img\\down\\25.bmp"
#define MD26	"img\\down\\26.bmp"
#define MD27	"img\\down\\27.bmp"
#define MD28	"img\\down\\28.bmp"
#define MD29	"img\\down\\29.bmp"
#define MD30	"img\\down\\30.bmp"
#define MD31	"img\\down\\31.bmp"
#define MD32	"img\\down\\32.bmp"
#define MD33	"img\\down\\33.bmp"
#define MD34	"img\\down\\34.bmp"
#define MD35	"img\\down\\35.bmp"

struct coordinates
{
    int x;
    int y;
};
struct coordinates elevatorpoint[10] = {{0, 0}, {50, 682}, {50, 609}, {50, 536}, {50, 463}, {50, 390}, {50, 317}, {50, 244}, {50, 171}, {50, 98}};
struct coordinates elevator_outside_button_up[10] = {{0, 0}, {274, 700}, {274, 613}, {274, 541}, {274, 468}, {274, 395}, {274, 322}, {274, 249}, {274, 176}, {0, 0}};
struct coordinates elevator_outside_button_down[10] = {{0, 0}, {0, 0}, {274, 647}, {274, 575}, {274, 501}, {274, 429}, {274, 356}, {274, 283}, {274, 210}, {274, 129}};
struct coordinates elevator_inside_button[10] = {{0, 0}, {384, 660}, {384, 577}, {384, 494}, {384, 411}, {384, 328}, {466, 494}, {466, 411}, {466, 328}, {466, 245}};
struct coordinates elevator_go = {466, 162};
struct coordinates elevator_open = {384, 162};
struct coordinates elevator_floor = {446, 49};
struct coordinates elevator_arrow = {367, 55};
char *initialize_animation[95] = {	I1,	I2,	I3,	I4,	I5,	I6,	I7,	I8,	I9,	I10,	I11,	I12,	I13,	I14,	I15,	I16,	I17,	I18,	I19,	I20,	I21,	I22,	I23,	I24,	I25,	I26,	I27,	I28,	I29,	I30,	I31,	I32,	I33,	I34,	I35,	I36,	I37,	I38,	I39,	I40,	I41,	I42,	I43,	I44,	I45,	I46,	I47,	I48,	I49,	I50,	I51,	I52,	I53,	I54,	I55,	I56,	I57,	I58,	I59,	I60,	I61,	I62,	I63,	I64,	I65,	I66,	I67,	I68,	I69,	I70,	I71,	I72,	I73,	I74,	I75,	I76,	I77,	I78,	I79,	I80,	I81,	I82,	I83,	I84,	I85,	I86,	I87,	I88,	I89,	I90,	I91,	I92,	I93,	I94,	I95};
char *liftpicture[27] = {	L1,	L2,	L3,	L4,	L5,	L6,	L7,	L8,	L9,	L10,	L11,	L12,	L13,	L14,	L15,	L16,	L17,	L18,	L19,	L20,	L21,	L22,	L23,	L24,	L25,	L26,	L27};
char *showfloor[9] = {F1,	F2,	F3,	F4,	F5,	F6,	F7,	F8,	F9};
char *showmove_up[35] = {MP1,	MP2,	MP3,	MP4,	MP5,	MP6,	MP7,	MP8,	MP9,	MP10,	MP11,	MP12,	MP13,	MP14,	MP15,	MP16,	MP17,	MP18,	MP19,	MP20,	MP21,	MP22,	MP23,	MP24,	MP25,	MP26,	MP27,	MP28,	MP29,	MP30,	MP31,	MP32,	MP33,	MP34,	MP35};
char *showmove_down[35] = {MD1,	MD2,	MD3,	MD4,	MD5,	MD6,	MD7,	MD8,	MD9,	MD10,	MD11,	MD12,	MD13,	MD14,	MD15,	MD16,	MD17,	MD18,	MD19,	MD20,	MD21,	MD22,	MD23,	MD24,	MD25,	MD26,	MD27,	MD28,	MD29,	MD30,	MD31,	MD32,	MD33,	MD34,	MD35};
extern HEGG background, elevator, button, head, string, initial;
extern int currentFloor;
extern int moveDirection;
extern HANDLE hMutex;
extern int openbutton;
extern int profileCfindnextfloor;
extern int Profile;
extern int profileEFfindnextfloor;
int showmove_i = 0;
int showdirect = 0;

/***********************************************************
	函数名称：showDirection_run(int is_showDirection_stop_call)
	函数功能： 电梯运行过程中指示灯动画
	入口参数： is_showDirection_stop_call判断是否为showDirection_stop函数调用
	出口参数： 无
	备 注：
***********************************************************/
void showDirection_run(int is_showDirection_stop_call)
{

    if (showmove_i == 35)//35张图片循环
    {
        showmove_i = 0;
    }

    WaitForSingleObject(hMutex, INFINITE);//声明互斥对象
    SetActiveEgg(button);//在button的egg上操作
    MovePen(elevator_arrow.x, elevator_arrow.y);

    //画箭头
    if (is_showDirection_stop_call == 1)
    {
        if (showdirect == UP)
        {
            DrawBitmap(showmove_up[showmove_i]);

        }

        if (showdirect == DOWN)
        {
            DrawBitmap(showmove_down[showmove_i]);
        }
    }
    else
    {

        if (moveDirection == UP)
        {

            MovePen(elevator_arrow.x, elevator_arrow.y);
            DrawBitmap(showmove_up[showmove_i]);

            showdirect = UP;

        }

        if (moveDirection == DOWN)
        {

            MovePen(elevator_arrow.x, elevator_arrow.y);
            DrawBitmap(showmove_down[showmove_i]);

            showdirect = DOWN;
        }

    }

    showmove_i++;
    ReleaseMutex(hMutex);//释放互斥对象


}

/***********************************************************
	函数名称：showDirection_stop()
	函数功能： 电梯禁止时指示灯动画
	入口参数： 无
	出口参数： 无
	备 注：
***********************************************************/
void showDirection_stop()
{
    for (; showmove_i != 1;)//时电梯刚开始停靠显示完之前的指示灯动画
    {
        showDirection_run(1);
        Sleep(3);
    }

    WaitForSingleObject(hMutex, INFINITE);//声明互斥对象
    SetActiveEgg(button);//在button的egg上操作
    MovePen(elevator_arrow.x, elevator_arrow.y);

    if (moveDirection == UP)
    {
        DrawBitmap(showmove_up[0]);
    }

    if (moveDirection == DOWN)
    {
        DrawBitmap(showmove_down[0]);
    }

    if (moveDirection == STOP)
    {
        DrawBitmap("img\\arrow.bmp");
    }

    ReleaseMutex(hMutex);//释放互斥对象
}

/***********************************************************
	函数名称：showFloor()
	函数功能： 显示电梯楼层
	入口参数： 无
	出口参数： 无
	备 注：
***********************************************************/
void showFloor(void)
{
    WaitForSingleObject(hMutex, INFINITE);//声明互斥对象
    SetActiveEgg(button);//在button的egg上操作
    MovePen(elevator_floor.x, elevator_floor.y);
    DrawBitmap(showfloor[currentFloor - 1]);
    ReleaseMutex(hMutex);//释放互斥对象
}

/***********************************************************
	函数名称：lightOn(char input)
	函数功能： 点亮按钮电梯
	入口参数： input字符型 对应键盘输入的代表电梯按钮的字符
	出口参数： 无
	备 注：
***********************************************************/
void lightOn(char input)
{

    WaitForSingleObject(hMutex, INFINITE);//声明互斥对象

    switch (input)
    {


        case 'G'
                :
            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_go.x, elevator_go.y);
            DrawBitmap("img\\button_closed_pressed.bmp");

            break;

        case 'O'
                :

            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_open.x, elevator_open.y);
            DrawBitmap("img\\button_open_pressed.bmp");

            break;

        case 'q'
                :

            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_outside_button_up[1].x, elevator_outside_button_up[1].y);
            DrawBitmap(BUTTON_OUTSIDE_UP_ON);

            break;

        case 'w'
                :


            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_outside_button_up[2].x, elevator_outside_button_up[2].y);
            DrawBitmap(BUTTON_OUTSIDE_UP_ON);

            break;

        case 'e'
                :


            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_outside_button_up[3].x, elevator_outside_button_up[3].y);
            DrawBitmap(BUTTON_OUTSIDE_UP_ON);


            break;

        case 'r'
                :


            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_outside_button_up[4].x, elevator_outside_button_up[4].y);
            DrawBitmap(BUTTON_OUTSIDE_UP_ON);


            break;

        case 't'
                :

            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_outside_button_up[5].x, elevator_outside_button_up[5].y);
            DrawBitmap(BUTTON_OUTSIDE_UP_ON);
            break;

        case 'y'
                :

            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_outside_button_up[6].x, elevator_outside_button_up[6].y);
            DrawBitmap(BUTTON_OUTSIDE_UP_ON);
            break;

        case 'u'
                :

            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_outside_button_up[7].x, elevator_outside_button_up[7].y);
            DrawBitmap(BUTTON_OUTSIDE_UP_ON);
            break;

        case 'i'
                :

            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_outside_button_up[8].x, elevator_outside_button_up[8].y);
            DrawBitmap(BUTTON_OUTSIDE_UP_ON);

            break;

            //电梯向下按钮的请求
        case 'a'
                :



            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_outside_button_down[2].x, elevator_outside_button_down[2].y);
            DrawBitmap(BUTTON_OUTSIDE_DOWN_ON);
            break;

        case 's'
                :

            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_outside_button_down[3].x, elevator_outside_button_down[3].y);
            DrawBitmap(BUTTON_OUTSIDE_DOWN_ON);
            break;

        case 'd'
                :

            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_outside_button_down[4].x, elevator_outside_button_down[4].y);
            DrawBitmap(BUTTON_OUTSIDE_DOWN_ON);
            break;

        case 'f'
                :

            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_outside_button_down[5].x, elevator_outside_button_down[5].y);
            DrawBitmap(BUTTON_OUTSIDE_DOWN_ON);
            break;

        case 'g'
                :

            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_outside_button_down[6].x, elevator_outside_button_down[6].y);
            DrawBitmap(BUTTON_OUTSIDE_DOWN_ON);
            break;

        case 'h'
                :

            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_outside_button_down[7].x, elevator_outside_button_down[7].y);
            DrawBitmap(BUTTON_OUTSIDE_DOWN_ON);
            break;

        case 'j'
                :

            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_outside_button_down[8].x, elevator_outside_button_down[8].y);
            DrawBitmap(BUTTON_OUTSIDE_DOWN_ON);
            break;

        case 'k'
                :

            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_outside_button_down[9].x, elevator_outside_button_down[9].y);
            DrawBitmap(BUTTON_OUTSIDE_DOWN_ON);
            break;

            //电梯内部按钮请求
        case '1'
                :



            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_inside_button[1].x, elevator_inside_button[1].y);
            DrawBitmap(BUTTON_INSIDE_ON_1);
            break;

        case '2'
                :

            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_inside_button[2].x, elevator_inside_button[2].y);
            DrawBitmap(BUTTON_INSIDE_ON_2);
            break;

        case '3'
                :

            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_inside_button[3].x, elevator_inside_button[3].y);
            DrawBitmap(BUTTON_INSIDE_ON_3);
            break;

        case '4'
                :

            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_inside_button[4].x, elevator_inside_button[4].y);
            DrawBitmap(BUTTON_INSIDE_ON_4);
            break;

        case '5'
                :
            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_inside_button[5].x, elevator_inside_button[5].y);
            DrawBitmap(BUTTON_INSIDE_ON_5);
            break;

        case '6'
                :

            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_inside_button[6].x, elevator_inside_button[6].y);
            DrawBitmap(BUTTON_INSIDE_ON_6);
            break;

        case '7'
                :

            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_inside_button[7].x, elevator_inside_button[7].y);
            DrawBitmap(BUTTON_INSIDE_ON_7);


            break;

        case '8'
                :

            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_inside_button[8].x, elevator_inside_button[8].y);
            DrawBitmap(BUTTON_INSIDE_ON_8);

            break;

        case '9'
                :

            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_inside_button[9].x, elevator_inside_button[9].y);
            DrawBitmap(BUTTON_INSIDE_ON_9);
            break;

    }

    ReleaseMutex(hMutex);//释放互斥对象

}

/***********************************************************
	函数名称：lightOff(char input)
	函数功能： 熄灭按钮电梯
	入口参数： input字符型 对应键盘输入的代表电梯按钮的字符
	出口参数： 无
	备 注：
***********************************************************/
void lightOff(char input)
{
    WaitForSingleObject(hMutex, INFINITE);//声明互斥对象
    SetActiveEgg(button);//在button的egg上操作

    //根据要熄灭的按钮执行相应操作
    switch (input)
    {
        case 'G'
                :

            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_go.x, elevator_go.y);
            DrawBitmap("img\\button_closed_released.bmp");
            break;

        case 'O'
                :
            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_open.x, elevator_open.y);
            DrawBitmap("img\\button_open_released.bmp");
            break;

        case 'q'
                :
            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_outside_button_up[1].x, elevator_outside_button_up[1].y);
            DrawBitmap(BUTTON_OUTSIDE_UP_OFF);
            break;

        case 'w'
                :
            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_outside_button_up[2].x, elevator_outside_button_up[2].y);
            DrawBitmap(BUTTON_OUTSIDE_UP_OFF);
            break;

        case 'e'
                :
            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_outside_button_up[3].x, elevator_outside_button_up[3].y);
            DrawBitmap(BUTTON_OUTSIDE_UP_OFF);
            break;

        case 'r'
                :
            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_outside_button_up[4].x, elevator_outside_button_up[4].y);
            DrawBitmap(BUTTON_OUTSIDE_UP_OFF);
            break;

        case 't'
                :
            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_outside_button_up[5].x, elevator_outside_button_up[5].y);
            DrawBitmap(BUTTON_OUTSIDE_UP_OFF);
            break;

        case 'y'
                :
            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_outside_button_up[6].x, elevator_outside_button_up[6].y);
            DrawBitmap(BUTTON_OUTSIDE_UP_OFF);
            break;

        case 'u'
                :
            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_outside_button_up[7].x, elevator_outside_button_up[7].y);
            DrawBitmap(BUTTON_OUTSIDE_UP_OFF);
            break;

        case 'i'
                :
            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_outside_button_up[8].x, elevator_outside_button_up[8].y);
            DrawBitmap(BUTTON_OUTSIDE_UP_OFF);
            break;

            //电梯向下按钮的请求
        case 'a'
                :
            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_outside_button_down[2].x, elevator_outside_button_down[2].y);
            DrawBitmap(BUTTON_OUTSIDE_DOWN_OFF);
            break;

        case 's'
                :
            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_outside_button_down[3].x, elevator_outside_button_down[3].y);
            DrawBitmap(BUTTON_OUTSIDE_DOWN_OFF);
            break;

        case 'd'
                :
            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_outside_button_down[4].x, elevator_outside_button_down[4].y);
            DrawBitmap(BUTTON_OUTSIDE_DOWN_OFF);
            break;

        case 'f'
                :
            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_outside_button_down[5].x, elevator_outside_button_down[5].y);
            DrawBitmap(BUTTON_OUTSIDE_DOWN_OFF);
            break;

        case 'g'
                :
            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_outside_button_down[6].x, elevator_outside_button_down[6].y);
            DrawBitmap(BUTTON_OUTSIDE_DOWN_OFF);
            break;

        case 'h'
                :
            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_outside_button_down[7].x, elevator_outside_button_down[7].y);
            DrawBitmap(BUTTON_OUTSIDE_DOWN_OFF);
            break;

        case 'j'
                :
            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_outside_button_down[8].x, elevator_outside_button_down[8].y);
            DrawBitmap(BUTTON_OUTSIDE_DOWN_OFF);
            break;

        case 'k'
                :
            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_outside_button_down[9].x, elevator_outside_button_down[9].y);
            DrawBitmap(BUTTON_OUTSIDE_DOWN_OFF);
            break;

            //电梯内部按钮请求
        case '1'
                :
            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_inside_button[1].x, elevator_inside_button[1].y);
            DrawBitmap(BUTTON_INSIDE_OFF_1);
            break;

        case '2'
                :
            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_inside_button[2].x, elevator_inside_button[2].y);
            DrawBitmap(BUTTON_INSIDE_OFF_2);
            break;

        case '3'
                :
            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_inside_button[3].x, elevator_inside_button[3].y);
            DrawBitmap(BUTTON_INSIDE_OFF_3);
            break;

        case '4'
                :
            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_inside_button[4].x, elevator_inside_button[4].y);
            DrawBitmap(BUTTON_INSIDE_OFF_4);
            break;

        case '5'
                :
            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_inside_button[5].x, elevator_inside_button[5].y);
            DrawBitmap(BUTTON_INSIDE_OFF_5);
            break;

        case '6'
                :
            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_inside_button[6].x, elevator_inside_button[6].y);
            DrawBitmap(BUTTON_INSIDE_OFF_6);
            break;

        case '7'
                :
            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_inside_button[7].x, elevator_inside_button[7].y);
            DrawBitmap(BUTTON_INSIDE_OFF_7);
            break;

        case '8'
                :
            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_inside_button[8].x, elevator_inside_button[8].y);
            DrawBitmap(BUTTON_INSIDE_OFF_8);
            break;

        case '9'
                :
            SetActiveEgg(button);//在button的egg上操作
            MovePen(elevator_inside_button[9].x, elevator_inside_button[9].y);
            DrawBitmap(BUTTON_INSIDE_OFF_9);
            break;

    }

    ReleaseMutex(hMutex);//释放互斥对象

}

/***********************************************************
	函数名称：elevatorMove(double rate)
	函数功能： 电梯运行动画
	入口参数： rate为电梯运行在楼层之间的百分比
	出口参数： 无
	备 注：
***********************************************************/
void elevatorMove(double rate)
{
    WaitForSingleObject(hMutex, INFINITE);//声明互斥对象

    if (profileCfindnextfloor == 1)//c策略的在回到一层时有相应的特殊处理
    {
        //电梯的移动
        SetActiveEgg(elevator);//在elevator的egg上操作
        MoveEgg(elevatorpoint[currentFloor].x + 54, (int)(elevatorpoint[currentFloor].y - (double) (((double)DOWN * rate)*ELEVATOR_HEIGHT) ) - 41);
        //缆线的移动
        SetActiveEgg(string);//在string的egg上操作
        MoveEgg(0, (elevatorpoint[currentFloor].y - (double) (((double)DOWN * rate)*ELEVATOR_HEIGHT) ) - elevatorpoint[1].y);
    }
    else
    {

        if (profileEFfindnextfloor == 1)
        {
            SetActiveEgg(elevator);//在elevator的egg上操作
            MoveEgg(elevatorpoint[currentFloor - moveDirection].x + 54, (int)(elevatorpoint[currentFloor - moveDirection].y - (double) (((double)moveDirection * rate)*ELEVATOR_HEIGHT) ) - 41);
            //缆线的移动
            SetActiveEgg(string);//在string的egg上操作
            MoveEgg(0, (elevatorpoint[currentFloor - moveDirection].y - (double) (((double)moveDirection * rate)*ELEVATOR_HEIGHT) ) - elevatorpoint[1].y);
        }
        else
        {


            //电梯的移动
            SetActiveEgg(elevator);//在elevator的egg上操作
            MoveEgg(elevatorpoint[currentFloor].x + 54, (int)(elevatorpoint[currentFloor].y - (double) (((double)moveDirection * rate)*ELEVATOR_HEIGHT) ) - 41);
            //缆线的移动
            SetActiveEgg(string);//在string的egg上操作
            MoveEgg(0, (elevatorpoint[currentFloor].y - (double) (((double)moveDirection * rate)*ELEVATOR_HEIGHT) ) - elevatorpoint[1].y);
        }

    }

    ReleaseMutex(hMutex);//释放互斥对象
}


/***********************************************************
	函数名称：initializeanimation(void)
	函数功能： 电梯动画初始化
	入口参数： 无
	出口参数： 无
	备 注：
***********************************************************/
void initializeanimation(void)
{
    int i;
    button = LayEgg();
    string = LayEgg();
    elevator = LayEgg();
    head = LayEgg();
    initial = LayEgg();

    SetActiveEgg(initial);
    MovePen(0, 0);
    DrawBitmap("img\\initialize\\0.bmp");

    for(i = 0; i <= 94; i++)
    {
        WaitForSingleObject(hMutex, INFINITE);//声明互斥对象
        SetActiveEgg(initial);
        MovePen(272, 232);
        DrawBitmap(initialize_animation[i]);

        if (i == 10)
        {
            SetActiveEgg(background);
            MovePen(0, 0);
            DrawBitmap("img\\background.bmp");//画背景
        }

        if (i == 20)
        {
            SetActiveEgg(string);//在string的egg上操作
            MovePen(140, 54);
            //画缆线
            DrawBitmap("img\\lift\\string.bmp");
            MovePen(169, 54);
            DrawBitmap("img\\lift\\string.bmp");
        }

        if (i == 30)
        {
            //画电梯
            SetActiveEgg(elevator);//在elevator的egg上操作
            MoveEgg(elevatorpoint[1].x + 54, elevatorpoint[1].y - 41);
            MovePen(0, 0);
            DrawBitmap(L1);
        }

        if (i == 40)
        {
            SetActiveEgg(head);
            MovePen(0, 0);
            DrawBitmap("img\\lift\\head.bmp");

        }

        if (i == 50)
        {
            SetActiveEgg(button);

            switch(Profile)
            {
                case
                        B:
                    MovePen(687, 226);
                    DrawBitmap("img\\showb.bmp");
                    break;

                case
                        C:
                    MovePen(687, 226);
                    DrawBitmap("img\\showc.bmp");
                    break;

                case
                        D:
                    MovePen(687, 226);
                    DrawBitmap("img\\showd.bmp");
                    break;

                case
                        E:
                    MovePen(687, 226);
                    DrawBitmap("img\\showe.bmp");
                    break;

                case
                        F:
                    MovePen(687, 226);
                    DrawBitmap("img\\showf.bmp");
                    break;


            }

        }

        if (i == 60)
        {
            SetActiveEgg(button);

            switch(Profile)
            {
                case
                        B:
                    MovePen(672, 512);
                    DrawBitmap("img\\B.bmp");
                    break;

                case
                        C:
                    MovePen(672, 512);
                    DrawBitmap("img\\C.bmp");
                    break;

                case
                        D:
                    MovePen(672, 512);
                    DrawBitmap("img\\D.bmp");
                    break;

                case
                        E:
                    MovePen(672, 512);
                    DrawBitmap("img\\E.bmp");
                    break;

                case
                        F:
                    MovePen(672, 512);
                    DrawBitmap("img\\F.bmp");
                    break;
            }

        }


        ReleaseMutex(hMutex);//释放互斥对象

        if (i < 40)
        {
            Sleep(37);
        }
        else
        {
            Sleep(8);
        }

    }

    EatEgg(initial);//初始化结束,删除此蛋
    return;

}



/***********************************************************
	函数名称：openDoor(void)
	函数功能： 开门
	入口参数： 无
	出口参数： 无
	备 注：
***********************************************************/
void openDoor(void)
{
    int i;


    for (i = 0; i <= 26; i++)
    {
        WaitForSingleObject(hMutex, INFINITE);//声明互斥对象
        SetActiveEgg(elevator);//在elevator的egg上操作
        MovePen(0, 0);
        DrawBitmap(liftpicture[i]);

        ReleaseMutex(hMutex);//释放互斥对象
        Sleep(25);

    }

}

/***********************************************************
	函数名称：closeDoor(void)
	函数功能： 关门
	入口参数： 无
	出口参数： 无
	备 注：
***********************************************************/
int closeDoor(void)
{

    int i, startback = 0;


    for (i = 26; i >= 0; i--)
    {
        if (openbutton == 1)
        {
            startback = 1;
            break;
        }

        WaitForSingleObject(hMutex, INFINITE);//声明互斥对象
        SetActiveEgg(elevator);//在elevator的egg上操作
        MovePen(0, 0);
        DrawBitmap(liftpicture[i]);
        ReleaseMutex(hMutex);//释放互斥对象
        Sleep(25);

    }

    if (startback == 1)//关门时按下开门键的处理
    {
        startback = 0;

        for (; i <= 26; i++)
        {
            WaitForSingleObject(hMutex, INFINITE);//声明互斥对象
            SetActiveEgg(elevator);//在elevator的egg上操作
            MovePen(0, 0);
            DrawBitmap(liftpicture[i]);
            ReleaseMutex(hMutex);//释放互斥对象
            Sleep(25);

        }

        return 1;
    }
    else
    {
        return 0;
    }

}

/***********************************************************
	函数名称：arriveSound(void)
	函数功能： 播放到站语音
	入口参数： 无
	出口参数： 无
	备 注：
***********************************************************/
void arriveSound(void)
{
    switch(currentFloor)
    {
        case
                1:
            sndPlaySound ("sound\\1.wav", SND_ASYNC);
            break;

        case
                2:
            sndPlaySound ("sound\\2.wav", SND_ASYNC);
            break;

        case
                3:
            sndPlaySound ("sound\\3.wav", SND_ASYNC);
            break;

        case
                4:
            sndPlaySound ("sound\\4.wav", SND_ASYNC);
            break;

        case
                5:
            sndPlaySound ("sound\\5.wav", SND_ASYNC);
            break;

        case
                6:
            sndPlaySound ("sound\\6.wav", SND_ASYNC);
            break;

        case
                7:
            sndPlaySound ("sound\\7.wav", SND_ASYNC);
            break;

        case
                8:
            sndPlaySound ("sound\\8.wav", SND_ASYNC);
            break;

        case
                9:
            sndPlaySound ("sound\\9.wav", SND_ASYNC);
            break;
    }


}

/***********************************************************
	函数名称：arriveSound(void)
	函数功能： 播放运行语音
	入口参数： 无
	出口参数： 无
	备 注：
***********************************************************/
void gosound()
{
    switch(moveDirection)
    {
        case
                1:
            sndPlaySound ("sound\\up.wav", SND_ASYNC);
            break;

        case
                - 1:
            sndPlaySound ("sound\\down.wav", SND_ASYNC);
            break;
    }
}