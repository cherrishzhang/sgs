#include "Poker.h"
USING_NS_CC;

//Poker* Create(int index)
//{
//	Poker* ref = new Poker(index);
//	if (ref&&ref->init())
//	{
//		ref->autorelease();
//		return ref;
//	}
//	else
//	{
//		delete ref;
//		ref = nullptr;
//		return nullptr;
//	}
//}

Poker::Poker(int index):IsSelect(0),IsTopPoker(0), IsCanUsableCurr(0)
{

	CreateSpecificPoker(index);
	//���ݷ��صı�ʶ��ʼ�����Ƶ�������Ϣ
	name = "null";
	descir = "have no descir!";

	pokerPic->setAnchorPoint(Vec2::ZERO);

	//if (pokerPic!=nullptr)
	//{
	//	log("can able to create listener!");
	//	listener = EventListenerTouchOneByOne::create();
	//	listener->setSwallowTouches(false);
	//	listener->onTouchBegan = CC_CALLBACK_2(Poker::touchBegin, this);
	//	listener->onTouchMoved = CC_CALLBACK_2(Poker::touchMove, this);
	//	listener->onTouchEnded = CC_CALLBACK_2(Poker::touchEnd, this);
	//	listener->onTouchCancelled = CC_CALLBACK_2(Poker::touchCancelled, this);

	//	eventdispatcher = Director::getInstance()->getEventDispatcher();
	//	//eventdispatcher->addEventListenerWithFixedPriority(listener, 2);
	//	eventdispatcher->addEventListenerWithSceneGraphPriority(listener, pokerPic);
	//}

}


Poker::~Poker()
{

	//eventdispatcher->removeEventListener(listener);
	log("this is xigou function!");
}

//bool Poker::init()
//{
//	log("init poker!");
//	if (!Sprite::init())
//	{
//		return false;
//	}
//
//	return true;
//}

void Poker::PokerPosition(float x,float y)
{
	pokerPic->setPosition(Vec2(x,y));
}

//Sprite* Poker::getSprite()
//{
//	return pokerPic;
//}
void Poker::CreateSpecificPoker(int index)
{

	switch (index)
	{
	case 0://������
		   //��ʱӲ����
		pokerPic = Sprite::create("pic/poker_jb_00.png");
		name = "tao";//�����ض����Ƶı�ʶ
		pokerid = 0;
		break;

	case 1://����ɱ
	//	if (count==0)
	//	{
			pokerPic = Sprite::create("pic/poker_jb_01.png");
			name = "sha";//�����ض����Ƶı�ʶ
			pokerid = 1;
	//	}
	//	else
	//	{
	//		pokerPic = Sprite::create("pic/poker_jb_01.png");
	//		name = "fangyuma";//�����ض����Ƶı�ʶ
	//		pokerid = 100;
	//	}
	//	log("pokerid=%d", pokerid);
		break;
	case 2://����     /�����ƾ���/   �����滻Ϊ��

		pokerPic = Sprite::create("pic/poker_jb_02.png");
		name = "shan";//�����ض����Ƶı�ʶ
		pokerid = 2;
		break;
	case 3://�����佫��
		if (count == 0)
		{
			pokerPic = Sprite::create("pic/poker_jb_00.png");
			name = "superkongming";//�����ض����Ƶı�ʶ
		}
		else
		{
			pokerPic = Sprite::create("pic/poker_jb_01.png");
			name = "superlvmeng";//�����ض����Ƶı�ʶ
		}
		break;
	case 4://���������
		if (count == 0)
		{
			pokerPic = Sprite::create("pic/poker_id_00.png");
			name = "zhugong";//�����ض����Ƶı�ʶ
		}
		else
		{
			pokerPic = Sprite::create("pic/poker_id_01.png");
			name = "fanzei";//�����ض����Ƶı�ʶ
		}
		break;
	default:
		log(" \n-----error!------\n");
		break;

	}


}

bool Poker::touchBegin(Touch * touch, Event * event)
{
	//log("---------touchbegin----------");
	//auto vec=touch->getLocation();
	//log("UIposition is:(%f,%f)",vec.x,vec.y);
	//Vec2 point=Director::getInstance()->convertToGL(touch->getLocationInView());
	//log("Wposition is:(%f,%f)", point.x, point.y);
	auto ve = this->pokerPic->getPosition();
	log("obj 's position=(%f,%f)", ve.x, ve.y);
	//��õ�ǰ�Ƶ�λ�ÿ��Եó�������,��Ϊ���һ�������ȼ����,��ǰ�ƾ������һ�ű������� ��150-ve.x 
	Vec2 touchpoint = touch->getLocation();
	if (touchpoint.x>150&&touchpoint.x<ve.x)
	{
		if (touchpoint.y>10&&touchpoint.y<130)
		{
			log("-----------clik on poker------------");
			
			//���ݵ��λ���ж�������
			//touchpoint.x
			//if (IsTopPoker!=true)
			//{
			//	pokerPic->runAction(MoveBy::create(0.7, Vec2(0, 30)));
			//	IsTopPoker = true;

			//}
			
		}
	}


	return true;
}

void Poker::touchMove(Touch * touch, Event * event)
{
	log("-----------touchMove-----------");
}

void Poker::touchEnd(Touch * touch, Event * event)
{
	log("------------touchEnd------------");
}

void Poker::touchCancelled(Touch * touch, Event * event)
{
	log("touchCancelled");
}
