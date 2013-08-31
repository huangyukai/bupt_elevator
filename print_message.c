/***********************************************************
�ļ����ƣ����
�� �ߣ� ������
�� ���� 1.0
˵ ���� ����������в���
����״̬����ǰ¥�㡢Ŀ��¥�㡢�������а�ť״̬
�޸ļ�¼��
***********************************************************/
#include <stdio.h>
#include <windows.h>
#include "initialize.h"
#include "sharedVariables.h"

extern int currentFloor;
extern int nextFloor;
extern int moveDirection;
extern int state;
extern int buttonUp[10];
extern int buttonDown[10];
extern int buttonNumber[10];
extern int Profile;//���ݿ��Ʋ��� Ĭ��Ϊ����A(˳��������)
extern double totalTime[5];
extern double eachNumber[5];
extern double averageTime[5];
extern double restTime;
extern int ignore;
/***********************************************************
	�������ƣ� buttonstation()
	�������ܣ� �ж����а�ťĿǰ��״̬�����״̬
	��ڲ����� ��
	���ڲ����� ��
	�� ע��
***********************************************************/
void buttonstation(void)
{
    int i;
    printf("��ť״̬\n");

    //listPrint();
    for (i = 1; i <= 9; i++)
    {

        printf("	��%d��", i);

        if (buttonUp[i] == 1)
        {
            printf("���ϵ�  ��  ", i);
        }
        else
        {
            printf("���ϵ���    ", i);
        }

        if (buttonDown[i] == 1)
        {
            printf("���µ�  ��  ", i);
        }
        else
        {
            printf("���µ���    ", i);
        }

        if (buttonNumber[i] == 1)
        {
            printf("�ڲ���  ��  ", i);
        }
        else
        {
            printf("�ڲ�����    ", i);
        }

        printf("\n");
    }
}

/***********************************************************
	�������ƣ�print_message()
	�������ܣ� ������ݵ����в�������ʾ�û������ʽ
	��ڲ����� ��
	���ڲ����� ��
	�� ע��
***********************************************************/
void print_message(void)
{
    int i;

    initialize();


    while(1)
    {

        Sleep(700);
        system("cls");

        printf("����״̬");

        switch(Profile)
        {
            case
                    A:
                printf("������ʹ�ò���ΪA��:\n");
                break;

            case
                    B:
                printf("������ʹ�ò���ΪB��:\n");
                break;

            case
                    C:
                printf("������ʹ�ò���ΪC��:\n");
                break;

            case
                    D:
                printf("������ʹ�ò���ΪD��:\n");
                break;
        }




        if (state == IDLE)


        {
            printf("	���ݿ���\n	�Źر�\n");
        }

        if (state == RUN)
        {
            if (nextFloor < 0)
            {
                printf("	���ݳ�ʱ������ʹ�ã����ڻص�1��\n	�Źر�\n");
            }

            if(moveDirection == UP && nextFloor >= 0)
            {
                printf("	�������������˶�\n	�Źر�\n");
            }

            if(moveDirection == DOWN && nextFloor >= 0)

            {
                printf("	�������������˶�\n	�Źر�\n");
            }
        }
        else
        {
            if (state == STOP)
            {
                printf("	����ͣ��������     ͣ��ʱ��ʣ�ࣺ%.2f��\n	�Ŵ�\n", restTime);
            }
        }

        printf("	�������ڵ�%d��\n", currentFloor);

        if ((nextFloor != 0) && (nextFloor != currentFloor) && (nextFloor > 0))
        {
            printf("	��������Ŀ��Ϊ��%d��\n", nextFloor);
        }
        else
        {
            printf("\n");
        }


        buttonstation();
        printf("\n");
        printf("ͳ�����ݣ�ƽ��ÿ����Ӧ�ĺ�ʱ��:\n");

        for (i = A; i <= D; i++)
        {
            switch(i)
            {
                case
                        A:
                    printf("	A����:");
                    break;

                case
                        B:
                    printf("B����:");
                    break;

                case
                        C:
                    printf("C����:");
                    break;

                case
                        D:
                    printf("D����:");
                    break;
            }

            if (eachNumber[i] > 0.5)
            {




                printf("%5.2f��   ", totalTime[i] / eachNumber[i]);
            }
            else
            {
                printf("ͳ����    ");
            }

        }

        printf("\n");


        printf("\n��Ӽ����������������Ƶ������У�(���������س�)    ��������G����Go��ť\n");
        printf("��������q w e r t y u i�ֱ�����1 2 3 4 5 6 7 8�������Ϻ���\n");
        printf("��������a s d f g h j k�ֱ�����2 3 4 5 6 7 8 9�������º���\n");
        printf("��������1 2 3 4 5 6 7 8 9�ֱ��������ڲ��е�1 2 3 4 5 6 7 8 9�����\n");
        printf("��������A B C D������A B C D���Լ��л�\n");
    }


}
