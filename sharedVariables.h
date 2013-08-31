#ifndef SHAREDVARIABLES
#define SHAREDVARIABLES
struct listNode
{
    char data;
    struct listNode *nextPtr;
};

typedef struct listNode LISTNODE;
typedef LISTNODE * LISTNODEPTR;

#define UP 1//运行方向向上
#define DOWN -1//运行方向向下
#define STOP 0//无运行方向或状态停止
#define IDLE 1//状态空闲
#define RUN 2//状态运行
#define A 1//策略A 顺便服务策略
#define B 2//策略B
#define C 3//策略C
#define D 4//策略D
#define E 5//策略E
#define F 6//策略F

#endif
