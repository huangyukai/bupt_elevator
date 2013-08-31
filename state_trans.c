/***********************************************************
	文件名称： 电梯的状态控制
	作 者： 黄昱恺
	版 本： 3.0
	说 明： 根据自动机模型和control()计算出的电梯目标楼层和运行方向决定此刻电梯的状态
	修改记录： 1、修复到9层后不运行的bug            修改人：黄昱恺
			   2、修复电梯停靠后由于Sleep造成的错误 修改人：黄昱恺
			   3、全面去除Sleep                     修改人：黄昱恺
***********************************************************/

#include <windows.h>
#include <time.h>
#include "list.h"
#include "egg.h"
#include "control.h"
#include "sharedVariables.h"
#include "graphical_interface.h"
//外部变量引用
extern HEGG background, elevator, button, head, string;
extern HANDLE hMutex;
extern int buttonUp[10];
extern int buttonDown[10];
extern int buttonNumber[10];
extern int currentFloor;
extern int nextFloor;
extern int moveDirection;
extern int state;
extern int velocity;
extern int stopTime;
extern int Profile;
extern int profileChange;
extern int previousProfile;
extern double totalTime[7];
extern double eachNumber[7];
extern int Go;
extern int openbutton;
extern double restTime;
extern int ignore;
extern LISTNODEPTR headPtr;
extern LISTNODEPTR lastPtr;
extern LISTNODEPTR currentPtr;
extern LISTNODEPTR tempPtr;
extern char listUp[10];
extern char listDown[10];
extern char listNumber[10];
extern int waitTime;
extern int profileCfindnextfloor;
extern int profileEFfindnextfloor;
//进入不同状态的标示
int startIDLE = 1;
int startRun = 1;
int startRUN = 1;
int startSTOP = 1;
int startRUNEF = 1 ;
//时间统计变量
double a, b, c;
double as, bs, cs;
double ar, br, cr;
double directa, directb, directc;
double staticStart, staticStop;

/***********************************************************
	函数名称： state_trans()
	函数功能： 控制电梯的状态
	入口参数： 无
	出口参数： 无
	备 注： 使用到的全局变量
			buttonUp,buttonDown,buttonNumber,currentFloor,state,nextFloor,moveDirection
			其中nextFloor，moveDirection为只读 不可修改
			使用自动机模型 电梯运行速度2秒每层 电梯停靠时间为4秒
***********************************************************/
void state_trans()
{
    static int reopen = 0;//电梯关门时按下开门键的标示

    switch (state) //根据状态和事件，进行相应的处理
    {
        case
                IDLE: //电梯空闲状态
            if (openbutton == 1)
            {
                state = STOP;//电梯按下开门按钮进入停靠状态
            }

            if (moveDirection != STOP) //由control函数发现有不同层响应呼叫 电梯进入运行状态
            {
                state = RUN;//电梯进入运行状态
                startIDLE = 1;
            }
            else
                if (currentFloor == nextFloor) //由control函数发现有同层响应呼叫 电梯进入停靠状态
                {
                    state = STOP;
                    startIDLE = 1;
                }
                else
                {
                    if (Profile == C)
                    {
                        if (startIDLE == 1)
                        {
                            a = clock();
                            startIDLE = 0;
                        }
                        else
                        {
                            b = clock();
                            c = (double) (b - a) / CLOCKS_PER_SEC;

                            if (c > waitTime) //等待waitTime秒
                            {
                                if (currentFloor != 1)
                                {
                                    nextFloor = -1;
                                    moveDirection = DOWN;
                                    state = RUN;
                                    startIDLE = 1;
                                }

                            }
                        }
                    }
                    else
                    {
                        moveDirection = STOP;
                    }
                }

            break;

        case
                RUN://电梯运行状态
            if (currentFloor == ignore)//安全运行结束
            {
                ignore = 0;
            }

            if (nextFloor == -1 || profileCfindnextfloor == 1)
            {

                if (currentFloor != 1) //未到目标楼层
                {

                    if (startRUN == 1)//计时器开始计时
                    {
                        directa = ar = clock();
                        startRUN = 0;
                    }
                    else
                    {
                        directb = br = clock();
                        cr = (double) (br - ar) / CLOCKS_PER_SEC;
                        directc = (double) (directb - directa) / CLOCKS_PER_SEC;
                        elevatorMove((double)cr / velocity);//电梯运行动画

                        if (directc >= 0.05)
                        {
                            directa = clock();
                            showDirection_run(0);//指示灯动画
                        }

                        if (cr > velocity)//时间到velocity秒
                        {
                            currentFloor--;
                            profileCfindnextfloor = 0;
                            showFloor();
                            elevatorMove(0);
                            startRUN = 1;
                        }

                    }

                }

                if (currentFloor == 1) //电梯到达目标楼层
                {
                    nextFloor = 0;
                    state = IDLE;
                    moveDirection = STOP;
                    showDirection_stop();
                }

            }
            else//profileCfindnextfloor==0
            {

                if (startRun == 1)
                {
                    staticStart = clock();//统计计时
                    startRun = 0;
                }

                if (currentFloor != nextFloor || profileEFfindnextfloor == 1) //未到目标楼层
                {
                    if (startRUN == 1)
                    {
                        directa = ar = clock();
                        startRUN = 0;
                        profileEFfindnextfloor = 0;
                    }
                    else
                    {

                        if (profileEFfindnextfloor == 1)
                        {
                            static double temptime1, temptime = 0;

                            if (startRUNEF == 1)
                            {
                                br = clock();
                                temptime = (double) (br - ar) / CLOCKS_PER_SEC;
                                temptime1 = temptime;
                                ar = clock();
                                startRUNEF = 0;
                            }
                            else
                            {

                                directb = br = clock();
                                cr = (double) (br - ar) / CLOCKS_PER_SEC;
                                directc = (double) (directb - directa) / CLOCKS_PER_SEC;


                                temptime = temptime1 - cr;

                                if (temptime > 0)
                                {

                                    elevatorMove((double)(velocity - temptime) / velocity);

                                }

                                if (directc >= 0.05)
                                {
                                    directa = clock();
                                    showDirection_run(0);//指示灯动画
                                }

                                if (temptime < 0)
                                {

                                    showFloor();//显示当前楼层

                                    profileEFfindnextfloor = 0;
                                    elevatorMove(0);//电梯运行动画
                                    startRUNEF = 1;
                                    startRUN = 1;
                                    temptime = 0;
                                }


                            }


                        }

                        else

                        {
                            directb = br = clock();

                            cr = (double) (br - ar) / CLOCKS_PER_SEC;
                            directc = (double) (directb - directa) / CLOCKS_PER_SEC;

                            if (profileEFfindnextfloor == 0)
                            {
                                elevatorMove((double)cr / velocity);//电梯运行动画
                            }

                            if (directc >= 0.05)
                            {
                                directa = clock();
                                showDirection_run(0);//指示灯动画
                            }

                            if (cr > velocity)
                            {
                                currentFloor += moveDirection;
                                showFloor();//显示当前楼层

                                if (profileEFfindnextfloor == 0)
                                {
                                    elevatorMove(0);//电梯运行动画
                                }

                                startRUN = 1;
                            }
                        }


                    }
                }




                if ((currentFloor == nextFloor) && (profileEFfindnextfloor == 0)) //电梯到达目标楼层
                {
                    if (moveDirection == UP) //关闭相应的按钮 电梯进入停靠状态
                    {
                        if (Profile == B)//B策略单独处理
                        {
                            if (headPtr != NULL)
                            {
                                closeButton();
                                eachNumber[previousProfile]++;
                                deleteNode(headPtr->data);
                            }
                        }

                        else//关闭按钮
                        {
                            if((buttonUp[currentFloor] == 0) && (buttonNumber[currentFloor] == 0))
                            {
                                buttonDown[currentFloor] = 0;
                                deleteNode(listDown[currentFloor]);
                                lightOff(listDown[currentFloor]);

                                eachNumber[previousProfile]++;
                            }
                            else//关闭按钮
                            {
                                buttonUp[currentFloor] = 0;
                                buttonNumber[currentFloor] = 0;
                                lightOff(listUp[currentFloor]);
                                lightOff(listNumber[currentFloor]);

                                if (headPtr != NULL)
                                {
                                    eachNumber[previousProfile]++;
                                    deleteNode(listUp[currentFloor]);

                                    deleteNode(listNumber[currentFloor]);
                                }


                            }
                        }

                        state = STOP;
                        startRun = 1;
                        staticStop = clock();
                        totalTime[previousProfile] += (double) (staticStop - staticStart) / CLOCKS_PER_SEC;//统计时间

                    }

                    if (moveDirection == DOWN) //关闭相应的按钮 电梯进入停靠状态

                    {
                        if (Profile == B)//B策略需单独处理
                        {
                            if (headPtr != NULL)
                            {
                                closeButton();
                                deleteNode(headPtr->data);


                                eachNumber[previousProfile]++;
                            }
                        }
                        else//关闭按钮
                        {
                            if ((buttonDown[currentFloor] == 0) && (buttonNumber[currentFloor] == 0))
                            {
                                buttonUp[currentFloor] = 0;
                                lightOff(listUp[currentFloor]);
                                deleteNode(listUp[currentFloor]);

                                eachNumber[previousProfile]++;
                            }
                            else//关闭按钮
                            {

                                buttonDown[currentFloor] = 0;
                                buttonNumber[currentFloor] = 0;
                                lightOff(listDown[currentFloor]);
                                lightOff(listNumber[currentFloor]);

                                if (headPtr != NULL)
                                {
                                    eachNumber[previousProfile]++;
                                    deleteNode(listDown[currentFloor]);
                                    deleteNode(listNumber[currentFloor]);
                                }
                            }
                        }

                        state = STOP;//进入停靠
                        startRun = 1;
                        staticStop = clock();

                        totalTime[previousProfile] += (double) (staticStop - staticStart) / CLOCKS_PER_SEC;//统计时间

                    }

                    if (moveDirection == STOP) //如果电梯无运行方向 电梯进入停靠状态
                    {
                        state = STOP;
                        startRun = 1;
                        staticStop = clock();
                        //时间统计
                        totalTime[previousProfile] += (double) (staticStop - staticStart) / CLOCKS_PER_SEC;//统计时间
                    }
                }

            }

            break;

        case
                STOP: //电梯停靠状态

            if (startSTOP == 1)//刚开始停靠
            {
                DWORD ThreadIDa = 1, ThreadIDb = 2;
                HANDLE hReada, hReadb;
                as = clock();//计时器初始化

                if (reopen == 1)//判断是否开门
                {
                    reopen = 0;
                }
                else
                {
                    //开门动画,指示灯动画并且播放语音
                    hReada = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)arriveSound, NULL, 0, &ThreadIDa);
                    hReadb = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)showDirection_stop, NULL, 0, &ThreadIDb);
                    openDoor();

                    startSTOP = 0;
                }

            }
            else
            {

                if (openbutton == 1)//长按开门键则不关门
                {
                    as = clock();
                    restTime = stopTime;
                }
                else
                {
                    showDirection_stop();
                    bs = clock();
                    cs = (double) (bs - as) / CLOCKS_PER_SEC;
                    restTime = stopTime - cs;

                    if (cs > stopTime || Go == 1)//Go指令判断
                    {
                        startSTOP = 1;

                    }

                }

            }

            if (startSTOP == 1)
            {

                if (nextFloor == 0) //如果无目标楼层 电梯进入空闲状态
                {
                    if (closeDoor() == 1)
                    {
                        state = STOP;
                        startSTOP = 1;
                        reopen = 1;
                        break;
                    }

                    moveDirection = STOP;
                    state = IDLE;

                    if (Profile == B)
                    {
                        showDirection_stop();
                    }

                }
                else//有目标楼层则电梯进入运行状态
                {
                    if (closeDoor())
                    {
                        state = STOP;
                        startSTOP = 1;
                        reopen = 1;
                        break;
                    }

                    state = RUN;
                    control();
                    gosound();

                }

            }

            break;

    }//end of switch
}

