/*
��Ϸ����
*/
#pragma once
#include "cocos2d.h"
class GameUI;
class GameOverLayer;
class PlayInfo;
class Poker;
class GameScene:public cocos2d::Scene
{

public:
	bool init();
	CREATE_FUNC(GameScene);
	void update(float delta);

	~GameScene();



	void UpdatePlayState();//����������ҵ�״̬,�ж���Ϸ����,��Ҫ���������Ƿ�����


	void SignUsablePoker();//������õ���
private:
	void rifflePoker();//����ϴ��,����һ�����ƶ�
	void UpdateCurrentPlayer();//���µ�ǰ���
	void GameOver();
	int GetOutPokerFromHeap();//���ƶѳ����
	int CurrentplayAddPoker(int);//��ǰ����������
	void CurrentplayGiveupPoker(int);//��ǰ��Ҷ�������
	//void Delay();

	/* ���Ʒ����ж� */
	void UsePoker();//����ѡ�е���ִ�в�ͬ�ķ���
	
	void UseAnPokerThenUp(Poker*,int);//ʹ��һ���ƺ�������ƶ�
	void CreateOverLayer();


	GameUI* _mainLayer;
	GameOverLayer* _overLayer;

	
	std::vector<int> _pokerHeap;
	std::vector<PlayInfo*>_playerCollection;

	int count;//ˢ��һ֡������һ����20*60=1200֡ ���Զ�����UpdateCurrentPlayer����
    bool IsGameOver;//��Ϸ�Ƿ����
	int currentPlayer;//��ǰ�غ����
	bool IsOverState;//�׶��Ƿ����
	int PlayState;//��ǰ�����Ϸ״̬,����: 0׼����1�ж���2���ơ�3���ơ�4���� 5�Ѿ�����

	

	/*��Ч��*/
	void UseTaoPoker(Poker*,int);//��
	void UseShaPoker(Poker*,int);//ɱ
	void UseShanPoker(Poker*,int);//����
	
	void PokerEffect(int);//������Ч

	void extraUsePoker(int target);//����ĳ��ƻغ�:�غ�����Ӧ��"���ƽ׶�"
	int feedbackType;//��Ӧ����,��Ӧɱ-���� ���� �赶 ��Ӧ��-ɱ ��  �ȵȣ���ʱֻ����Ӧ�� 0
	bool isOverFeedback;//�Ƿ������Ӧ
	void FoeUsePoker(int);//���Եĳ���ѡ��

	
	float barprect;//����ʱ���ᵱǰ����
};

