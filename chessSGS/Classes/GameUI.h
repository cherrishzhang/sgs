#pragma once
/*
����Ϸ����UI

*/

#include "cocos2d.h"
#include "ui/CocosGUI.h"


USING_NS_CC;
class PlayInfo;
class Poker;
typedef enum 
{
	thandPoker_Tag  //����
	,tgiveupPoker_Tag //���ƶѵ���
	,tSkill_Tag //����
	,tEquip_Tag //װ��


}SpriteTags;
class GameUI:public cocos2d::Layer
{
	//friend class GameScene;
public:
	bool init();

	virtual void onEnter();
	virtual void onExit();

	void menuReOpen(Ref*pSender);//�ؿ�
	void menuExit(Ref*pSender);//�˳���Ϸ
	void menuaddpoker(Ref*pSender);
	void menuusepoker(Ref*pSender);
	void menugiveuppoker(Ref*pSender);
	//���ƽ���
	void menuOkPoker(Ref*pSender);//ȷ��
	void menuCancelPoker(Ref*pSender);//ȡ��

	void update(float delta);
	/* ������� ��ʾ */
	void addPoker( int ,int);
	/* ���ʹ����(�����غ�����) ��ʾ */
	void usePoker(int num=1);
	/* ������� ��ʾ */
	void giveupPoker( );
	/* ����������� ��ʾ*/
	void giveupPoke_Robot(int );
	void fun1(Ref*);
	/*���ƶѵĸ���*/
	void Updategiveupheap();

	CREATE_FUNC(GameUI);

	//��ʼ����ɫ��Ϣ
	void initRoleInfo(PlayInfo* player);
	//���½�ɫ��Ϣ(��ʾ)
	void UpdateRoleInfo(PlayInfo*player);

	//��ʼ��������Ϣ
	void initFoeInfo(PlayInfo* player);
	//���¶�����Ϣ(��ʾ)
	void UpdatFoeInfo(PlayInfo*player);

	Color3B color;
	Label*CurrenState;
	MenuItemImage* menuButtonOK;//ȷ��
	MenuItemImage* menuButtonCancel;//ȡ��
	Menu*buttonmenu;//ȷ��/ȡ�� ����˵�

	int SelectPokerCounts;//��ѡ���Ƶ�����  Ĭ��Ϊ1,��һ�γ�һ���ƣ����Ǽ��ܵ�����Ӱ���������
	
	bool isAddPoker;
	bool isUsePoker;//�Ƿ�����ȷ����ť������
	void CountDown(float dt=5.0f,int index=0);//����ʱ����ʵ����ʱ����
	void setTimeBarwithtime(float );
	void setTimeBarwithtimeIngiveup(float);
	bool isCountDown;//�Ƿ��ڶ��� ��������CountDown 
	bool isEndUsePokeState;//�Ƿ�������ƽ׶�

	bool isUpdateGiveupHeap;//�Ƿ�������ƶ�,�ͷ����е��ڴ�

	void SwapTimeBar();//������ǰ�غϵ�ʱ�����ָ��,�ǰ�غϽ��ж�����Loadingbar ָ��ָ��play��ʱ�����ָ��
	
	void UpdateShowPokerSlot(PlayInfo*);//�������Ʋ�,�ⲿ����
	void DrawShowPokerSlot();//�������Ʋ۵���
	void addgiveupheap(Poker*);//����Ƶ����ƶ�



	void TopPoler(Poker*);//����ѡ�е���,����������������̧ ��ʾ��ѡ��
	void DownPoker(Poker*);//�ջ���̧��ʾ����,ʹ��ع�ԭλ

	void DrawnDarkAllPoker();//�������������ɫ�䰵

	void AdjustPoker();//���Ƶ���:��������λ��,����

	std::vector<Poker*>showpokerslot;//�����Ҫ��ʾ�����Ʋ�
	bool isSortPokers;//�Ƿ���������

	std::deque<Poker*>giveupPokerHeap;//���ƶ�
	bool isEndGiveUpPokeState;//�Ƿ���������ƽ׶�
	/*��ҳ��Ʋ����������*/
	bool isSelectShaPoker;//�Ƿ�ѡ����ɱ

	bool isExtraUsePoker;//�Ƿ����ڶ������ƽ׶�
	bool FoeIsUsePoker;//�����Ƿ�����
	Label*_showFoePokerNums;
	ui::LoadingBar* timebar;
	ui::LoadingBar* timebarRobot;
private:
	//std::deque<Poker*>SelectPokers;//ѡ���Ƶļ���
	std::vector<int>showIntslot;
	
	Sprite*bg;//����ͼƬ
	Sprite*equipment;//װ����ͼƬ
	Sprite*pokerSlot;//���Ʋ۱���ͼƬ
	Sprite*rolePicInfo;//��ɫuiͼƬ��Ϣ
	//Vector<Sprite*>roleHealthInfo;

	Sprite*foeInfoShow;
	

	

	Label* timelabel;
	
	Label*_showOurPokerNums;

	
	int _lastpokerpoint;//���Ʋ����һ���Ƶ�λ��
	int _lastheappoint;//���ƶ������Ƶ�λ��

	EventDispatcher*eventdispatcher;

	bool onTouchBegan(Touch*touch, Event*event); 
	void onTouchMoved(Touch*touch, Event*event);
	void onTouchEnded(Touch*touch, Event*event);
	void onTouchCancelled(Touch*touch, Event*event);


	void isSelectPoker();//�ж��Ƿ�ѡ����
};

