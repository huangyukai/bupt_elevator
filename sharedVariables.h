#ifndef SHAREDVARIABLES
#define SHAREDVARIABLES
struct listNode
{
    char data;
    struct listNode *nextPtr;
};

typedef struct listNode LISTNODE;
typedef LISTNODE * LISTNODEPTR;

#define UP 1//���з�������
#define DOWN -1//���з�������
#define STOP 0//�����з����״ֹ̬ͣ
#define IDLE 1//״̬����
#define RUN 2//״̬����
#define A 1//����A ˳��������
#define B 2//����B
#define C 3//����C
#define D 4//����D
#define E 5//����E
#define F 6//����F

#endif
