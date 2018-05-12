/*
�����Ϣ��,�洢���������Ϣ�ṩ��GameUI��ʾ,�Լ���Ϸ�߼��ཻ��.
*/
#pragma once
#include <string>
#include <vector>
#include "Poker.h"
class PlayInfo
{


public:
	PlayInfo();
	PlayInfo(int owner);
	//PlayInfo(const PlayInfo&);
	//PlayInfo& operator=(const PlayInfo&);
	~PlayInfo();

public:
	//����������
	bool SetPlayerIdentity();

	void SetPlaySkill();

	void losePlayHealth();//ʧȥһ������
	void recovePlayHealth();//�ָ�һ������


	int GetPlayerIdentity() //��ȡ������
	{
		return _playeridentity;
	}
	int GetPlayerHealth()
	{
		return _roleCurrHealth;
	}
	int GetPlayMaxHealth()
	{
		return _roleHealth;
	}
	int GetRoleSex()//��ȡ��ɫ�Ա�
	{
		return _roleSex;
	}
	int GetPokerUpper();//���ؽ�ɫ��������
	
	void SetPlayState();//�޸����״̬,��Ҫ�����޸�����


	std::vector<int> _playPokerSlot;//������Ʋ�

	/*�������״�����*/
	int UsableShaPokerCounts;//�ܹ�ʹ�õ�ɱ������
	bool UsableWinebuffer;//�Ƿ�õ�����buffer,ɱ�˺���һ��buffer
	bool UsableAttackOther;//�ܹ������������
	bool UsableTaoPoker;//�ܷ�ʹ������
	/*�����Ϸ״̬���*/
	int AttackRange;//��������

	
	/*  */
	
private:
	std::string _playerName;//����ǳ�
	int owner;//������,0������� 1�������
	int _playeridentity;//������ ---ͨ������ƻ�ȡ
	int _rolePokerUpper;//��������
	std::string _playerRole;//��ҽ�ɫ  ----ͨ���佫�ƻ�ȡ
	int _roleHealth;//��ɫ����ֵ
	int _roleCurrHealth;//��ǰ����ֵ
	bool _roleDeath;//�������
	int _roleSex;//��ɫ�Ա�
	std::vector<std::string> _roleSkill;//��ɫ������



	

	/*�߼�����*/
	//int* equip;//װ����,0������װ��,�������������ߡ����������������ĸ�Ԫ��
	std::vector<int> buffstate;//buffer״̬: ��,����

};
