/***********************************************************
	�ļ����ƣ� ���ݳ�ʼ��
	�� �ߣ� ������
	�� ���� 4.0
	˵ ���� ��ʼ�����ݲ����Ͱ�Ȩ����
	�޸ļ�¼:���Ӽ�ʱ �޸���:������
***********************************************************/
#include<stdio.h>
#include<windows.h>
#include <stdlib.h>
#include "sharedVariables.h"

extern int velocity;
extern int stopTime;
extern int waitTime;
extern int initialization;
extern int Profile;//���ݿ��Ʋ��� Ĭ��Ϊ����A(˳��������)
extern int blockedFloor;
extern int previousProfile;
int ok = 0;//�ж������Ƿ����
/***********************************************************
	�������ƣ� initialize()
	�������ܣ� ��ʼ�����ݲ����Ͱ�Ȩ����
	��ڲ����� ��
	���ڲ����� ��
	�� ע��
***********************************************************/
void initialize(void)
{
    int i;
    char temp;
    printf("\t                                                \\\\\\|///\n");
    printf("\t                                              \\\\\  - -  //\n");
    printf("\t                                               (  @ @  )\n");
    printf("\t����������������������������������������������oOOo-(_)-oOOo����\n");
    printf("\t��                        ����ϵͳ                           ��\n");
    printf("\t��                  �鳤��������                             ��\n");
    printf("\t��                  ��Ա������ͥ����꿭                     ��\n");
    printf("\t��                  ��Ȩ���С�����ؾ�                Oooo   ��\n");
    printf("\t���������������������������������������������� oooO��-(   )����\n");
    printf("\t                                               (   )   ) /\n");
    printf("\t                                                \\ (   (_/\n");
    printf("\t                                                 \\_)\n");


    //���ݳ�ʼ��������
    printf("\n\t���ݳ�ʼ�������ã�\n\n");
    printf("\t    ���������ÿ����һ����Ҫ��ʱ�䣨��λ�룩����������5:  ");
    scanf("%d", &velocity);

    for (; velocity <= 0;)
    {
        printf("\t    ʱ��Ϊ��ֵ�����������룺");
        scanf("%d", &velocity);
    }

    printf("\t    ���������ͣ��ʱ�䣨��λ�룩����������5:  ");
    scanf("%d", &stopTime);

    for (; stopTime <= 0;)
    {
        printf("\t    ʱ��Ϊ��ֵ�����������룺");
        scanf("%d", &stopTime);
    }

    printf("\t    ��������ݳ�ʼ���ԣ�A��B��C��D��:  ");

    //�ж����������Ƿ�Ϸ�
    for (; ok == 0;)
    {

        fflush(stdin);
        scanf("%c", &temp);

        switch(temp)
        {
            case 'A'
                    :
                Profile = A;
                previousProfile = Profile;
                ok = 1;
                break;

            case 'B'
                    :
                Profile = B;
                previousProfile = Profile;
                ok = 1;
                break;

            case 'C'
                    :
                Profile = C;
                previousProfile = Profile;
                ok = 1;
                break;

            case 'D'
                    :
                Profile = D;
                previousProfile = Profile;
                ok = 1;
                break;

            default
                    :
                printf("\t    ����������������룺");
        }


    }
	fflush(stdin);
    if (Profile == C)
    {
        printf("\t    ��������ݿ��ж�ú�ص�һ�㣨��λ�룩����������10:  ");
        scanf("%d", &waitTime);

        for (; waitTime <= 0;)
        {
            printf("\t    ʱ��Ϊ��ֵ�����������룺");
            scanf("%d", &waitTime);
        }
    }

    if (Profile == D)
    {
        printf("\t    ���������ε��ݶ��㵽�ڼ�������󣨵�λ�룩����������5:  ");
        scanf("%d", &blockedFloor);

        for (; blockedFloor <= 1 || blockedFloor > 9;)
        {
            printf("\t    ¥�����벻���ϡ����������룺");
            scanf("%d", &blockedFloor);
        }

    }



    //�����ʼ���ݺ�,������ݽ���
    for (i = 1; i <= 2; i++)
    {
        printf("\n");
    }

    printf("\t����ϵͳ���ڳ�ʼ��");

    for (i = 1; i <= 2; i++)
    {
        printf("\n");
    }

    for (i = 1; i <= 14; i++)
    {
        printf(" ");
    }

    for (i = 1; i <= 50; i++)
    {
        printf("\|");
        Sleep(10);
    }

    initialization = 0;//��ʼ�����
}