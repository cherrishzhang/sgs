/*
��Ϸ��ѭ��
������
*/
#pragma once
#include "PlayInfo.h"


class GameLoop
{
	
public:

	static GameLoop* GetInstance()//��ȡ��Ϸ��ѭ��Ψһ��ʵ��  _gamejudge
	{
		static GameLoop* _gamejudge;
		return _gamejudge;
	}

	/*--------���������Ϣ---*/


	void addPlayer(PlayInfo*,int);


	/*-------���������Ϣ   --------*/
	
	void setPlayPokerSlot(PlayInfo*,int type);//�޸�ָ�����playIndex ������,type ��ʾ�������� 
	void setPlayPokerState(PlayInfo*);//�޸�ָ����ҵĻغ�״̬: ���� ׼�����ж������ơ����ơ������Ѿ�����
	void setPlayHealth(PlayInfo*, int vaule);//�޸�����ֵ
	void setPlayEquip(PlayInfo*, int equipIndex);//�޸�װ����
	void setPlaySkill(PlayInfo*, std::string Oldskill,std::string Newskill);//�޸ļ���
	void setPlayBuffer(PlayInfo*, int bufferstate);//�޸�buff״̬

	/* ��ȡ�����Ϣ���� */
//	PlayInfo* getPlayInfo(int index);


private:
	static GameLoop* _gamejudge;

	GameLoop() {};
	GameLoop(const GameLoop&);
	GameLoop& operator=(const GameLoop&);

	class autoDelet
	{
		~autoDelet()
		{
			if (_gamejudge)
			{
				delete _gamejudge;
			}
		}
	};
	static autoDelet obj;
};