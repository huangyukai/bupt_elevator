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
#include "egg.h"
#include "graphical_interface.h"

extern int velocity;
extern int stopTime;
extern int waitTime;
extern int Profile;
extern int blockedFloor;
extern int previousProfile;

int ok = 0;//�ж������Ƿ����
char ShowConsole;
extern HEGG background, elevator, button;

/***********************************************************
	�������ƣ� initialize()
	�������ܣ� ��ʼ�����ݲ����Ͱ�Ȩ����
	��ڲ����� ��
	���ڲ����� ��
	�� ע��
***********************************************************/
void initialize(void)
{
    //�������
    int i;
    char temp;
    DWORD ThreadID3 = 3;
    HANDLE hRead2;

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

    //�ж����������Ƿ�Ϸ�
    for (; velocity <= 0;)
    {
        printf("\t    ʱ��Ϊ��ֵ�����������룺");
        scanf("%d", &velocity);
    }

    printf("\t    ���������ͣ��ʱ�䣨��λ�룩����������5:  ");
    scanf("%d", &stopTime);

    //�ж����������Ƿ�Ϸ�
    for (; stopTime <= 0;)
    {
        printf("\t    ʱ��Ϊ��ֵ�����������룺");
        scanf("%d", &stopTime);
    }

    printf("\t    ��ѡ����ݳ�ʼ����\n\t        A:˳��������\n\t        B:�����ȷ������\n\t        C:һ����ݲ���\n\t        D:�긣���ݲ���\n\t        E:�����Ӧ����\n\t        F:���ƽ���ȴ�ʱ�����\n\t    ������������ͣ�");

    //�ж����������Ƿ�Ϸ�
    for (; ok == 0;)
    {
        fflush(stdin);
        scanf("%c", &temp);

        //ѡ�����
        switch(temp)
        {
            case 'A'
                    :
                Profile = A;
                previousProfile = Profile;//ǰһ���ԵĲ�����ʼ��
                ok = 1;//�������ݷ��ϸ�ʽҪ��
                break;

            case 'B'
                    :
                Profile = B;
                previousProfile = Profile;//ǰһ���ԵĲ�����ʼ��
                ok = 1;//�������ݷ��ϸ�ʽҪ��
                break;

            case 'C'
                    :
                Profile = C;
                previousProfile = Profile;//ǰһ���ԵĲ�����ʼ��
                ok = 1;//�������ݷ��ϸ�ʽҪ��
                break;

            case 'D'
                    :
                Profile = D;
                previousProfile = Profile;//ǰһ���ԵĲ�����ʼ��
                ok = 1;//�������ݷ��ϸ�ʽҪ��
                break;

            case 'E'
                    :

                Profile = E;
                previousProfile = Profile;//ǰһ���ԵĲ�����ʼ��
                ok = 1;//�������ݷ��ϸ�ʽҪ��
                break;

            case 'F'
                    :

                Profile = F;
                previousProfile = Profile;//ǰһ���ԵĲ�����ʼ��
                ok = 1;//�������ݷ��ϸ�ʽҪ��
                break;

            default
                    :
                printf("\t    ����������������룺");
        }


    }

    //����ΪC��Dʱ������ʼ������
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

    //��ʾ�Ƿ�����DOS����
    printf("\t    �Ƿ���ʾDOS����̨\n\t    ����ʾ����Y����������N������ͼ�ν��水�Ҽ���ʱ����������������N:  ");
    fflush(stdin);
    scanf("%c", &ShowConsole);
    fflush(stdin);

    //�ж����������Ƿ�Ϸ�
    for (; ShowConsole != 'N' && ShowConsole != 'Y';)
    {
        printf("\t    ����������������룺");
        fflush(stdin);
        scanf("%c", &ShowConsole);
    }

    //ϵͳ��������ʾ
    MessageBox(NULL, TEXT("  ������ϵͳͼ�ν���ֱ���Ϊ1024*768\n  ���ϵͳ�ֱ��ʹ��Ϳ��ܵ��µ��ݽ�����ʾ����ȫ\n  ��������²�����ʾ����ȫ����������ϵͳ��������ʹ��"), TEXT("ʹ�û���ע��"), MB_ICONINFORMATION);

    if (ShowConsole == 'N')
    {
        EggStart(1024, 768);
        ShowConsoleWindow(0);//����DOS����
    }
    else
    {
        EggStart(1024, 768);
    }


    //��ʼ��ʼ��,���Ȼ�ñ����ľ��
    background = GetActiveEgg();
    //ͼ�ν����ʼ���½�һ���߳�
    hRead2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)initializeanimation, NULL, 0, &ThreadID3);

    //�����ʼ���ݺ�,������ݽ���
    for (i = 1; i <= 2; i++)
    {
        printf("\n");
    }

    //DOS�����ʼ��
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
        Sleep(45);
    }


}