#ifndef _DOUBLELIST_H_
#define _DOUBLELIST_H_

#include "common.h"

/**************************************************************************
 *                            ���ݽṹ��                                   *
 **************************************************************************/

//���ṹ��
typedef struct D_Node
{
	elemType iData;
	struct D_Node *pNext;
	struct D_Node *pPrev;
}List_Node;


//����ṹ��
typedef struct D_LIST
{
	elemType iCount;            //����Ԫ�ظ���
    struct D_Node *pHead;      //ͷ���
	struct D_Node *pCur;      //��ǰ�ڵ�
}List_t;


/**************************************************************************
 *                        ȫ�ֺ���ԭ��                                     *
 **************************************************************************/

//��ʼ��
WORD DoubleListInit(List_t *pDL);

//ͷ�巨
WORD DoubleListHead(List_t *pDL, int iInSize, void (*InputElem)(elemType *), WORD (*EqualElem)(elemType *, elemType *));

//β�巨
WORD DoubleListLast(List_t *pDL, int iInSize, void (*InputElem)(elemType *), WORD (*EqualElem)(elemType *, elemType *));

//ɾ��
WORD DoubleListDelete(List_t *pDL, int iPosition, elemType *peOutValue);

//�������ֵ
WORD DoubleListInsert(List_t *pDL, int iPosition, elemType *peInValue, WORD (*EqualElem)(elemType *, elemType *));

//����ĳ��ֵ
WORD DoubleListValueFind(List_t *pDL, elemType *peInValue, int *piOutPosition, WORD (*EqualElem)(elemType *, elemType *));

//������ĳ���
WORD DoubleListLength(List_t *pDL);

//�ж������Ƿ�Ϊ��
WORD DoubleListEmpty(List_t *pDL);

//�������
WORD DoubleListClear(List_t *pDL);

//��������
WORD DoubleListDisplay(List_t *pDL, void(*OutPut)(elemType *));
 
#endif