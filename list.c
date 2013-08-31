/***********************************************************
	�ļ����ƣ� ����������躯��
	�� �ߣ� ������
	�� ���� 2.1
	˵ ���� ���������Ҫ�ĺ���
	�޸ļ�¼:
***********************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "sharedVariables.h"
//ȫ�ֱ�������
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
	�������ƣ� createList()
	�������ܣ� ������������������β��
	��ڲ����� ��
	���ڲ����� ��
	�� ע��
***********************************************************/
void createList(char request)
{
    currentPtr = malloc(sizeof(LISTNODE)); //�������ڴ�

    if (currentPtr != NULL)
    {
        //������
        currentPtr->data = request;

        if (headPtr == NULL)  //��currentPtr��ͷ���
        {
            headPtr = currentPtr;
            lastPtr = currentPtr;
        }
        else
        {
            lastPtr->nextPtr = currentPtr; //�������������β���
            lastPtr = currentPtr; //ʹlastPtrָ��ǰ��������һ�����
        }

        lastPtr->nextPtr = NULL;
    }
}

/***********************************************************
	�������ƣ� closeButton()
	�������ܣ� �رհ�ť
	��ڲ����� ��
	���ڲ����� ��
	�� ע��
***********************************************************/
void closeButton()
{
    switch(headPtr->data)//��������رղ�ͬ�İ�ť
    {
            //�������ϰ�ť������
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

            //�������°�ť������
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

            //�����ڲ���ť����
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
	�������ƣ� deleteNode(char value)
	�������ܣ� ɾ��ָ������
	��ڲ����� value�ַ��� ��Ӧ��������Ĵ�����ݰ�ť���ַ�
	���ڲ����� ��
	�� ע��
***********************************************************/
void deleteNode(char value)
{
    LISTNODEPTR previousPtr, currentPtr;

    for(;;)
    {
        previousPtr = NULL;
        currentPtr = headPtr; //��ͷ����ַ����currentPtr

        //���Ҵ�ɾ����㣬���ҵ�������currentPtָ��ý��
        while (currentPtr != NULL &&  currentPtr->data != value)
        {
            previousPtr = currentPtr;
            currentPtr = currentPtr->nextPtr;
        }


        if (currentPtr != NULL)
        {
            //����ҵ�Ҫɾ���Ľ��
            if ( previousPtr == NULL) //ɾ������ͷ���
            {
                headPtr = currentPtr->nextPtr;    //����ͷ���
            }
            else//ɾ�������м������β���
            {
                previousPtr->nextPtr = currentPtr->nextPtr;
            }

            free(currentPtr); //�ͷŽ���ڴ�

        }
        else
        {
            break;
        }

    }
}

/***********************************************************
	�������ƣ� checkFloor(char ch)
	�������ܣ� �ж�ָ���Ӧ��¥��
	��ڲ����� ch�ַ��� ��Ӧ��������Ĵ�����ݰ�ť���ַ�
	���ڲ����� ��
	�� ע��
***********************************************************/
int checkFloor(char ch)
{
    switch(ch)//�жϰ�ť��Ӧ���Ǽ�¥
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
