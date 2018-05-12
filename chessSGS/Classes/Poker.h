/*
�˿�����

*/
#pragma once
#include "cocos2d.h"
USING_NS_CC;
class Poker//:public cocos2d::Sprite
{
	
public:
	
	Poker(int );
	~Poker();
//	static Poker* Create(int index);
//	bool init();
	//Sprite* getSprite();
	void PokerPosition(float x, float y);
	cocos2d:: Sprite* pokerPic;//�˿��ƾ���

	bool IsCanUse;//�Ƿ��ܹ�ʹ��,�� ��Ѫ �� �Ͳ���ʹ�� ��־Ϊ��
	bool IsSelect;//�Ƿ�ѡ��
	bool IsTopPoker;//�Ƿ���̧

	bool IsCanUsableCurr;//��ǰ�Ƿ��ܹ�ʹ��
	int pokerid;//ÿ�࿨��Ψһ��ʶ Ŀǰ��0 ɱ1 ��2


private:
	int count;//�˿��Ƶ��� 1-13 
	int flowerColor;//��ɫ1-4 �ں�÷��
	
	int typeIndex;//��������  ������0 װ����1 ������2 �佫��3 �����4
	
	std::string  name;//��������,���ظ�
	std::string descir;//����˵��


private:
	EventListenerTouchOneByOne* listener;
	EventDispatcher*eventdispatcher;//�¼�������
private:
	//��������
	void CreateSpecificPoker(int);//�����ض�����

	bool touchBegin(Touch*touch, Event*event);
	void touchMove(Touch*touch, Event*event);
	void touchEnd(Touch*touch, Event*event);
	void touchCancelled(Touch*touch, Event*event);
};

