/***********************************************************
	文件名称： 链表操作所需函数
	作 者： 黄昱恺
	版 本： 2.1
	说 明： 链表操作所要的函数
	修改记录:
***********************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "sharedVariables.h"
//全局变量调用
extern int buttonUp[10];
extern int buttonDown[10];
extern int buttonNumber[10];
extern int currentFloor;
extern int nextFloor;
extern int moveDirection;
extern int Profile;
extern int profileChange;
LISTNODEPTR headPtr = NULL;
LISTNODEPTR lastPtr = NULL;
LISTNODEPTR currentPtr = NULL;
LISTNODEPTR tempPtr;
/***********************************************************
	函数名称： createList()
	函数功能： 创建链表至已有链表尾部
	入口参数： 无
	出口参数： 无
	备 注：
***********************************************************/
void createList(char request)
{
    currentPtr = malloc(sizeof(LISTNODE)); //分配结点内存

    if (currentPtr != NULL)
    {
        //插入结点
        currentPtr->data = request;

        if (headPtr == NULL)  //若currentPtr是头结点
        {
            headPtr = currentPtr;
            lastPtr = currentPtr;
        }
        else
        {
            lastPtr->nextPtr = currentPtr; //将结点连上链表尾结点
            lastPtr = currentPtr; //使lastPtr指向当前链表的最后一个结点
        }

        lastPtr->nextPtr = NULL;
    }
}

/***********************************************************
	函数名称： closeButton()
	函数功能： 关闭按钮
	入口参数： 无
	出口参数： 无
	备 注：
***********************************************************/
void closeButton()
{
    switch(headPtr->data)//根据输入关闭不同的按钮
    {
            //电梯向上按钮的请求
        case 'q'
                :
            buttonUp[1] = 0;
            lightOff(headPtr->data);
            break;

        case 'w'
                :
            buttonUp[2] = 0;
            lightOff(headPtr->data);
            break;

        case 'e'
                :
            buttonUp[3] = 0;
            lightOff(headPtr->data);
            break;

        case 'r'
                :
            buttonUp[4] = 0;
            lightOff(headPtr->data);
            break;

        case 't'
                :
            buttonUp[5] = 0;
            lightOff(headPtr->data);
            break;

        case 'y'
                :
            buttonUp[6] = 0;
            lightOff(headPtr->data);
            break;

        case 'u'
                :
            buttonUp[7] = 0;
            lightOff(headPtr->data);
            break;

        case 'i'
                :
            buttonUp[8] = 0;
            lightOff(headPtr->data);
            break;

            //电梯向下按钮的请求
        case 'a'
                :
            {
                buttonDown[2] = 0;
                lightOff(headPtr->data);
            }
            break;

        case 's'
                :
            {
                buttonDown[3] = 0;
                lightOff(headPtr->data);
            }
            break;

        case 'd'
                :
            {
                buttonDown[4] = 0;
                lightOff(headPtr->data);
            }
            break;

        case 'f'
                :
            {
                buttonDown[5] = 0;
                lightOff(headPtr->data);
            }
            break;

        case 'g'
                :
            {
                buttonDown[6] = 0;
                lightOff(headPtr->data);
            }
            break;

        case 'h'
                :
            {
                buttonDown[7] = 0;
                lightOff(headPtr->data);
            }
            break;

        case 'j'
                :
            {
                buttonDown[8] = 0;
                lightOff(headPtr->data);
            }
            break;

        case 'k'
                :
            {
                buttonDown[9] = 0;
                lightOff(headPtr->data);
            }
            break;

            //电梯内部按钮请求
        case '1'
                :
            {
                buttonNumber[1] = 0;
                lightOff(headPtr->data);
            }
            break;

        case '2'
                :
            {
                buttonNumber[2] = 0;
                lightOff(headPtr->data);
            }
            break;

        case '3'
                :
            {
                buttonNumber[3] = 0;
                lightOff(headPtr->data);
            }
            break;

        case '4'
                :
            {
                buttonNumber[4] = 0;
                lightOff(headPtr->data);
            }
            break;

        case '5'
                :
            {
                buttonNumber[5] = 0;
                lightOff(headPtr->data);
            }
            break;

        case '6'
                :
            {
                buttonNumber[6] = 0;
                lightOff(headPtr->data);
            }
            break;

        case '7'
                :
            buttonNumber[7] = 0;

            lightOff(headPtr->data);
            break;

        case '8'
                :
            buttonNumber[8] = 0;
            lightOff(headPtr->data);
            break;

        case '9'
                :
            buttonNumber[9] = 0;
            lightOff(headPtr->data);
            break;
    }

}

/***********************************************************
	函数名称： deleteNode(char value)
	函数功能： 删除指定链表
	入口参数： value字符型 对应键盘输入的代表电梯按钮的字符
	出口参数： 无
	备 注：
***********************************************************/
void deleteNode(char value)
{
    LISTNODEPTR previousPtr, currentPtr;

    for(;;)
    {
        previousPtr = NULL;
        currentPtr = headPtr; //将头结点地址赋给currentPtr

        //查找待删除结点，若找到，则由currentPt指向该结点
        while (currentPtr != NULL &&  currentPtr->data != value)
        {
            previousPtr = currentPtr;
            currentPtr = currentPtr->nextPtr;
        }


        if (currentPtr != NULL)
        {
            //如果找到要删除的结点
            if ( previousPtr == NULL) //删除的是头结点
            {
                headPtr = currentPtr->nextPtr;    //更新头结点
            }
            else//删除的是中间结点或者尾结点
            {
                previousPtr->nextPtr = currentPtr->nextPtr;
            }

            free(currentPtr); //释放结点内存

        }
        else
        {
            break;
        }

    }
}

/***********************************************************
	函数名称： checkFloor(char ch)
	函数功能： 判断指令对应的楼层
	入口参数： ch字符型 对应键盘输入的代表电梯按钮的字符
	出口参数： 无
	备 注：
***********************************************************/
int checkFloor(char ch)
{
    switch(ch)//判断按钮对应的是几楼
    {
        case '1'
                :
        case 'q'
                :
            return 1;
            break;

        case '2'
                :
        case 'w'
                :
        case 'a'
                :
            return 2;
            break;

        case '3'
                :
        case 'e'
                :
        case 's'
                :
            return 3;
            break;

        case '4'
                :
        case 'r'
                :
        case 'd'
                :
            return 4;
            break;

        case '5'
                :
        case 't'
                :
        case 'f'
                :
            return 5;
            break;

        case '6'
                :
        case 'y'
                :
        case 'g'
                :
            return 6;
            break;

        case '7'
                :
        case 'u'
                :
        case 'h'
                :
            return 7;
            break;

        case '8'
                :
        case 'i'
                :
        case 'j'
                :
            return 8;
            break;

        case '9'
                :
        case 'k'
                :
            return 9;
            break;

        default
                :
            return 99;
            break;
    }
}
