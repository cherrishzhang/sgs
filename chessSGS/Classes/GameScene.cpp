#include "GameScene.h"
#include "GameLoop.h"
#include "GameUI.h"
#include "GameOverLayer.h"
#pragma execution_character_set("utf-8")
bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	log("---gamescene----");
	//std::vector<PlayInfo*>_playerCollection;
	auto play01 = new PlayInfo(0);
	_playerCollection.push_back(play01);
	auto play02 = new PlayInfo(1);
	_playerCollection.push_back(play02);
	auto mainlayer = GameUI::create();
	_mainLayer = mainlayer;
	mainlayer->initRoleInfo(play01);
	mainlayer->initFoeInfo(play02);
	this->addChild(mainlayer);

	rifflePoker();//�����ƶ�
	currentPlayer = 0;
	feedbackType = 0;
	isOverFeedback = false;
	barprect = 100.0f;
	scheduleUpdate();

	return true;
	
}
void GameScene::update(float delta)
{

	if (IsGameOver)
	{
		log("game is over!");
		CreateOverLayer();
		
	}
	UpdatePlayState();
	_mainLayer->UpdateRoleInfo(_playerCollection[0]);
	_mainLayer->UpdatFoeInfo(_playerCollection[1]);
	_mainLayer->Updategiveupheap();
		switch (PlayState)
		{
		case 0:
			_mainLayer->CurrenState->setString("׼���׶�");
			
			PlayState++;
			break;
		case 1:
			_mainLayer->CurrenState->setString("�ж��׶�");
			
			
			PlayState++; 
			break;
		case 2:
			_mainLayer->CurrenState->setString("���ƽ׶�");
			if (currentPlayer==0)
			{
				if (_mainLayer->isAddPoker==true)
				{
					auto poker01 = CurrentplayAddPoker(currentPlayer);//��������ӵ����Ƶ�poker�����ͱ��
					auto poker02 = CurrentplayAddPoker(currentPlayer);
					_mainLayer->addPoker(poker01, poker02);//����������Ƶ����� ��Ч��
					_mainLayer->isAddPoker = false;
					_mainLayer->DrawnDarkAllPoker();
				}	
				if (_mainLayer->buttonmenu->isVisible())
				{
					//do  nothing
				
				}
				else
				{
					_mainLayer->buttonmenu->setVisible(true);
					_mainLayer->menuButtonOK->setEnabled(false);
				
				//	MenuItemImage* obj = static_cast<MenuItemImage*>(_mainLayer->buttonmenu->getChildren().at(0));
				//	obj->setEnabled(false);
					
				}
			}
			else
			{
				//log("------------the robot -------------");
				//_playerCollection[1]->losePlayHealth();//�����˵����ƽ׶� ��ʧȥһ������
				//Ϊ���������2������
				auto poker01 = CurrentplayAddPoker(currentPlayer);//��������ӵ����Ƶ�poker�����ͱ��
				auto poker02 = CurrentplayAddPoker(currentPlayer);

				int num = _playerCollection[0]->_playPokerSlot.size();
				_mainLayer->_showFoePokerNums->setString(std::to_string(num));
		

				_mainLayer->FoeIsUsePoker = true;
			}
			PlayState++;
			_mainLayer->isEndUsePokeState = false;
			
			break;
		case 3:
			_mainLayer->CurrenState->setString("���ƽ׶�");
			if (_mainLayer->isEndUsePokeState !=true)
			{
			
				//log("-------now is usepoker state!-------------");
			//����ʱ  ��gameui ���е���ʱ������ʱ�������
				if (_mainLayer->isCountDown==false)//�Ƿ����ڼ�ʱ
				{
					//log("-------now is countdown!-------------");
					_mainLayer->CountDown(5.0,0);
				}	
				if(currentPlayer==1)//�� ����ǵ��Եĳ��ƻغ�
				{
					
					//���Գ���
					if (_mainLayer->FoeIsUsePoker)
					{
						if (_mainLayer->timebar->getPercent() < barprect)
						{
							//log("timebar=%f", _mainLayer->timebar->getPercent());
							if (_mainLayer->timebar->getPercent() < 95)
							{
								if (_playerCollection[1]->UsableTaoPoker)
								{
									log("eat tao!");
									FoeUsePoker(0);
								}
							}
							if (_mainLayer->timebar->getPercent() < 50)
							{
								if (_playerCollection[1]->UsableShaPokerCounts > 0)
								{
									log("sha target 1!");
									FoeUsePoker(1);
								}

							}
						}
					}
					
				}
				else
				{
					
					SignUsablePoker();
					if (_mainLayer->showpokerslot.empty()!=true)//���Ʋ�Ϊ��
					{
						UsePoker();
					}
				}

			}
			else
			{
				PlayState++;
				_mainLayer->isCountDown = false;
				_mainLayer->isUsePoker = false;
				for (auto&w : _mainLayer->showpokerslot)
				{
					//log("render current handpoker color");
					w->pokerPic->setColor(_mainLayer->color);
				}
				_playerCollection[currentPlayer]->UsableShaPokerCounts = 1;
				_mainLayer->isEndGiveUpPokeState = false;
			}
			
			break;
		case 4:
			_mainLayer->CurrenState->setString("���ƽ׶�");
			
			if (currentPlayer==0)
			{
				//log("size=%d", _playerCollection[0]->_playPokerSlot.size());
				//log("_rolePokerUpper=%d", _playerCollection[0]->_rolePokerUpper);
				auto intx = _playerCollection[0]->_playPokerSlot.size() - _playerCollection[0]->GetPokerUpper();
				if (_playerCollection[0]->_playPokerSlot.size() >_playerCollection[0]->GetPokerUpper())
				{
					log("--------------��Ҫ����------------");
					if (!_mainLayer->isEndGiveUpPokeState)
					{
						/*���ƽ׶ο��Ե�����е���----����������Ϊ����ʹ��*/
						for (auto &w : _mainLayer->showpokerslot)
						{
							w->IsCanUsableCurr = true;
						}

						_mainLayer->menuButtonOK->setEnabled(true);
						if (_mainLayer->isCountDown == false)//�Ƿ����ڼ�ʱ
						{
							//log("-------now is countdown!-------------");
						//	_mainLayer->SwapTimeBar();
							_mainLayer->timebar->setPercent(100);
							_mainLayer->CountDown(5.0f, 1);
							
						}
					
						if (_mainLayer->isUsePoker)//��������ȷ����ť
						{
							//��ȡ��ǰѡ���������
							int count = 0;//���õ�����
							std::vector<Poker*>tempPoker;
							std::vector<int>tempPokerIndex;
							for (int i = 0; i < _mainLayer->showpokerslot.size(); i++)
							{
								if (_mainLayer->showpokerslot[i]->IsSelect)
								{
									count++;
									tempPoker.push_back(_mainLayer->showpokerslot[i]);
									tempPokerIndex.push_back(i);
								}
							}
							if (count<=intx)
							{
								/*������ǰѡ�е���*/
								do 
								{
									auto w = tempPoker[count - 1];
								
									auto m = tempPokerIndex[count - 1];
									w->pokerPic->runAction(Sequence::create(MoveTo::create(1, Vec2(360, 260)), CallFunc::create([&, w]() {
										_mainLayer->giveupPokerHeap.push_back(w);
										log("������ǰѡ������!");
									}), nullptr));

									auto _pokerbegin = _playerCollection[0]->_playPokerSlot.begin() + m;
									_playerCollection[0]->_playPokerSlot.erase(_pokerbegin);
									auto itbegin = _mainLayer->showpokerslot.begin() + m;
									_mainLayer->showpokerslot.erase(itbegin);
									_mainLayer->DrawShowPokerSlot();
									count--;
								} while (count>0);
								

							}
							else
							{
								//����ʧ��
							}
							_mainLayer->isUsePoker = false;
						}
					}
					else
					{
						CurrentplayGiveupPoker(currentPlayer);
					}
				}
				else
				{
					_mainLayer->isEndGiveUpPokeState = true;
					if (_mainLayer->isCountDown==true)
					{
						//unschedule(schedule_selector(GameUI::setTimeBarwithtimeIngiveup));  ��֪��Ϊʲôȡ������
						_mainLayer->timebar->setPercent(0);
						_mainLayer->setTimeBarwithtimeIngiveup(0);
					}

					//_mainLayer->timebar->setPercent(100);
					//_mainLayer->timebar->setVisible(false);
					_mainLayer->menuButtonOK->setEnabled(false);
				}
				

			//	log("------------PlayeState=%d", PlayState);
			}
			else
			{
				CurrentplayGiveupPoker(currentPlayer);
				//_playerCollection[0]->losePlayHealth();//��� ʧȥһ������
				//log("----------On! i'm lose a heat! i'm olny %d------------", _playerCollection[0]->GetPlayerHealth());
			}
			if (PlayState<=4)
			{
				if (currentPlayer==0&&!_mainLayer->isEndGiveUpPokeState)
				{
					log("-----------���ڽ������ƽ׶�---------");
				}
				else
				{
					PlayState = 0;
					_mainLayer->isCountDown = false;
					UpdateCurrentPlayer();//�ֵ���һ�����
				}

			//	log("------------PlayeState=%d", PlayState);
			}
			break;
		case 5:
			
			GameOver();
			break;
		case 6://����غ�,�غ�����Ӧ
			SignUsablePoker();
			UsePoker();
			for (int i=0;i< _mainLayer->showpokerslot.size();i++)//�鿴�Ƿ���ѡ����
			{
				if (_mainLayer->showpokerslot[i]->IsSelect)
				{
					_mainLayer->menuButtonOK->setEnabled(true);//�� �򼤻ť
					break;
				}	
				else
				{
					_mainLayer->menuButtonOK->setEnabled(false);
				}
			}
			
			/*�ж��Ƿ�������Ӧ����Ӧ*/
			switch (feedbackType)
			{
			case 0://Ҫ����		
				if (isOverFeedback)
				{
						//�����Ӧ


						//
						_mainLayer->isExtraUsePoker = false;
						_mainLayer->timebar->setPercent(100.0f);
						_mainLayer->timebar->setVisible(false);
						_mainLayer->buttonmenu->setVisible(false);
						_mainLayer->SwapTimeBar();
						_mainLayer->timebar->setVisible(true);

						_mainLayer->FoeIsUsePoker = true;
						isOverFeedback = false;
				}
				else
				{




					if (!_mainLayer->isExtraUsePoker)
					{
						_playerCollection[0]->losePlayHealth();
					}
				}
			


				break;
			case 1://Ҫ��ɱɱ
				break;
			case 2://Ҫ����и�ɻ�
				break;
			default:
				break;
			}
			if (!_mainLayer->isExtraUsePoker)
			{
				PlayState = 3;
			}
			break;
		default:
			log("have an error!");
			break;
		}



	//count++;
	//if (count >= 1200)
	//{
	//	UpdateCurrentPlayer();
	//}
}

GameScene::~GameScene()
{
	
}

//����������ҵ�״̬,��Ҫ���������Ƿ�����
void GameScene::UpdatePlayState()
{
	for (auto &w:_playerCollection)
	{
		if (w->GetPlayerHealth()<=0)
		{
			w->SetPlayState();//�������״̬Ϊ ����  
			PlayState = 5;//�����������������Ϸflag����
		}
	}
	//���µ�ǰ�غ����״̬
	auto player = _playerCollection[currentPlayer];//��ȡ��ǰ�غ������Ϣָ��
	if (player->GetPlayMaxHealth()>player->GetPlayerHealth())//���������Ѫ
	{
		log("�������=%d", player->GetPlayMaxHealth());
		log("��ǰ����=%d", player->GetPlayerHealth());
		player->UsableTaoPoker = true;//����ʹ���� 
		
	}
	else
	{
		player->UsableTaoPoker = false; 
		
	}

}
//���������ʹ�õ���,���ݵ�ǰ�غ�������
void GameScene::SignUsablePoker()
{
	if (PlayState == 3||PlayState==6)//����ǳ��ƽ׶λ��߶���׶�
	{
		auto currplaypokerslot = _mainLayer->showpokerslot;
		auto playindex = _playerCollection[currentPlayer];
		for (auto &w: currplaypokerslot)
		{
			switch (w->pokerid)
			{
			case 0://��
				if (playindex->UsableTaoPoker)//�����ʹ����
				{

					//�����Ʊ��
					w->pokerPic->setColor(_mainLayer->color);
					w->IsCanUsableCurr = true;
				}
				else
				{
					w->pokerPic->setColor(Color3B(30, 100, 100));
					w->IsCanUsableCurr = false;
				}
				break;
			case 1://ɱ
				//log("should sign SHA poker");
				if (playindex->UsableShaPokerCounts>0)//���������ɱ
				{
					
					//��ɱ�Ʊ��
					w->pokerPic->setColor(_mainLayer->color);
					w->IsCanUsableCurr = true;
				}
				else
				{
					w->pokerPic->setColor(Color3B(30, 100, 100));
					w->IsCanUsableCurr = false;
				}
				break;
			case 2://�� 
					//�������Ʊ��
				if (_mainLayer->isExtraUsePoker)
				{
					w->pokerPic->setColor(_mainLayer->color);
					w->IsCanUsableCurr = true;
				}
				
				break;
			default:
				break;
			}
		}
	}
	else
	{
		log("need to develop");
	}

}

void GameScene::rifflePoker()
{
	//������ƶ�,�½��ƶ�
	if (!_pokerHeap.empty())
	{
		_pokerHeap.clear();//�������Ԫ��
		log("have clear all met");
	}
	
	//�ݶ� һ��20���� 
	/*
	������ 0�� 1ɱ   2����������5��12ɱ3����
	*/
	_pokerHeap={ 0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2 };
	int x = 19;
	do 
	{
		//�������2���±��ֵ
		auto index1 = random(0, 19);
		auto index2 = random(0, 19);
		if (index1!=index2)
		{
			auto temp = _pokerHeap[index1];
			_pokerHeap[index1] = _pokerHeap[index2];
			_pokerHeap[index2] = temp;
			x--;
		}

	} while (x>0);
	log("����½��ƶ�");
}

void GameScene::UpdateCurrentPlayer()//�غϸ���
{
	count = 1;
	
	if (currentPlayer==0)
	{
		_mainLayer->buttonmenu->setVisible(false);
		
		currentPlayer++;
		_mainLayer->SwapTimeBar();
	}
	else
	{
		currentPlayer = 0;

		barprect = 100.0f;
		_mainLayer->SwapTimeBar();
	}
	_mainLayer->isAddPoker = true;
}

void GameScene::GameOver()
{
	//��Ϸ��������
	if (PlayState==5)
	{
		IsGameOver = true;
	}

}

int GameScene::GetOutPokerFromHeap()//���ƶѳ���
{
	if (_pokerHeap.size()<=0)
	{
		//��Ҫһ�����ƶ�
		rifflePoker();
	}
	log("�ƶѻ���%d",_pokerHeap.size());
	auto it = _pokerHeap.end();
	auto temp = *(--it);//�ƶ����һ����,�������������
	_pokerHeap.pop_back();
	return temp;
}

int GameScene::CurrentplayAddPoker(int index)
{
	auto temp = GetOutPokerFromHeap();
	if (_playerCollection.empty()!=true)
	{

		_playerCollection[index]->_playPokerSlot.push_back(temp);//��������
		log("��ǰ���:%d ӵ�� %d ������", index,_playerCollection[index]->_playPokerSlot.size());
	
	}
	return temp;
}

void GameScene::CurrentplayGiveupPoker(int playindex)
{
	if (_playerCollection.empty() != true)
	{
		auto upper = _playerCollection[playindex]->GetPokerUpper();
		if (_playerCollection[playindex]->_playPokerSlot.size() > upper)//�ж������Ƿ���
		{
			//do give up ��ʱ����������
			auto dis = _playerCollection[playindex]->_playPokerSlot.size() - upper;//��Ҫ����������

			do 
			{
				//����Index ִ��gameUI�Ķ����� ����
				if (playindex==0)
				{
					_mainLayer->giveupPoker();
				}
				else
				{
					auto it=_playerCollection[playindex]->_playPokerSlot.end();
					log(" -----------callfunction  give up robot-------");
					_mainLayer->giveupPoke_Robot(*(--it));
				}
				_playerCollection[playindex]->_playPokerSlot.pop_back();
				dis--;
			} while (dis>0);
			

		}
		//log("-------have no give up poker!--------");
	}
	
}

void GameScene::UsePoker()//ǰ�����Ѿ����� 
{
	int count = 0;
	std::vector<Poker*>tempPoker;
	std::vector<int>tempPokerIndex;
	for (int i=0;i<_mainLayer->showpokerslot.size();i++)
	{
		if (_mainLayer->showpokerslot[i]->IsSelect)
		{
			count++;
			tempPoker.push_back(_mainLayer->showpokerslot[i]);
			tempPokerIndex.push_back(i);
		}
	}
	if (count>_mainLayer->SelectPokerCounts)
	{
		//������Ч,��Ҫȡ��һЩ�Ƶ�ѡ��
	}
	else
	{
		
		switch (count)
		{
		case 1:
		{
			
			switch (tempPoker[0]->pokerid)
			{
			case 0://��
				_mainLayer->menuButtonOK->setEnabled(true);//�ҿ��Ե����Ȼ�����������
				UseTaoPoker(tempPoker[0], tempPokerIndex[0]);
				break;
			case 1://ɱ
			
				
				_mainLayer->isSelectShaPoker = true;
				UseShaPoker(tempPoker[0], tempPokerIndex[0]);
				
				break;
			case 2://��
				
				UseShanPoker(tempPoker[0], tempPokerIndex[0]);
				break;
			default:
				break;
			}
		}
			break;
		default:
			break;
		}
	}

}



void GameScene::CreateOverLayer()
{

	_overLayer = GameOverLayer::create();

	addChild(_overLayer, 10);

}

void GameScene::UseAnPokerThenUp(Poker *obj, int index)
{
	if (_mainLayer->isExtraUsePoker)
	{
		//����ǻغ������
		auto it_scene = _playerCollection[0]->_playPokerSlot.begin() + index;
		log("what's wrong!---------");
		_playerCollection[0]->_playPokerSlot.erase(it_scene);
	}
	else
	{
		auto it_scene = _playerCollection[currentPlayer]->_playPokerSlot.begin() + index;
		log("what's wrong!---------");
		_playerCollection[currentPlayer]->_playPokerSlot.erase(it_scene);
	}
	

	auto sp = obj->pokerPic;
	auto f = CallFunc::create([&, obj]() {
		log("���ƶѴ�С=%d",_mainLayer->giveupPokerHeap.size());
		_mainLayer->giveupPokerHeap.push_back(obj);
		log("���ƶѴ�С=%d", _mainLayer->giveupPokerHeap.size());
	
	});

	sp->setTag(tgiveupPoker_Tag);
	obj->pokerPic->runAction(Sequence::create(MoveTo::create(1, Vec2(360, 260)), f, nullptr));
	auto it_UI = _mainLayer->showpokerslot.begin() + index;
	_mainLayer->showpokerslot.erase(it_UI);

	//��������
	_mainLayer->DrawShowPokerSlot();
	log("�������Ʋ�");
}

/*�Ƶ�Ч��*/
void GameScene::UseTaoPoker(Poker*obj,int index)
{
	if (_mainLayer->isUsePoker)//��������ȷ��,��ô�ͳ���,ʹ��������
	{
		//Ч����
		PokerEffect(0);
		_playerCollection[currentPlayer]->recovePlayHealth();//�ָ�һ��Ѫ
		_mainLayer->isUsePoker = false;
		log("��ǰ���=%d", currentPlayer);

		UseAnPokerThenUp(obj, index);
		
	}
	log("-----------\length:=%d\n------------",_mainLayer->showpokerslot.size());
}
void GameScene::UseShaPoker(Poker*obj, int index)
{


	if (_mainLayer->isUsePoker)//��������ȷ��,��ô�ͳ���,ʹ��������
	{
		//Ч���� ʹĿ�����(����)���� "�غ�����Ӧ�׶�" :��������һغ��ڵ�"���ƽ׶�"
		
		PokerEffect(1);
		extraUsePoker(1);//1�����(���ǵ���)��Ӧ

		_playerCollection[currentPlayer]->UsableShaPokerCounts--;//ɱ��ʹ�ô���-1
		_mainLayer->isUsePoker = false;
	
		UseAnPokerThenUp(obj, index);
	}

}
void  GameScene::UseShanPoker(Poker*obj, int index)
{
	if (_mainLayer->isUsePoker)//��������ȷ��,��ô�ͳ���,ʹ��������
	{
		//Ч����
		PokerEffect(2);
		isOverFeedback = true;
		_mainLayer->isUsePoker = false;

		UseAnPokerThenUp(obj, index);
	}
	log("-----------\n--use Shan --\n------------");
}

void GameScene::PokerEffect(int typeindex)
{
	Sprite*sp;
	switch (typeindex)
	{
	case 0:
		sp = Sprite::create("pic/tao_eff.png");
		break;
	case 1:
		sp = Sprite::create("pic/sha_eff.png");
		break;
	case 2:
		sp = Sprite::create("pic/shan_eff.png");
		break;
	default:
		break;
	}

		
		sp->setAnchorPoint(Vec2::ZERO);
		sp->setPosition(500, 200);
		addChild(sp, 14,1001);

		sp->runAction(Sequence::create(DelayTime::create(1.0f), CallFunc::create([&]() {this->removeChildByTag(1001);
		//log("----------remove ------------");
		}), nullptr));
		

}

void GameScene::extraUsePoker(int target)
{
	if (target==0)//���Ŀ�������
	{
		//
		if (_playerCollection[0]->_playPokerSlot.empty()==true)
		{
			_playerCollection[0]->losePlayHealth();//��� ʧȥһ������
			
		}
		else
		{
			if (_mainLayer->isExtraUsePoker == false)
			{
				_mainLayer->timebar->setVisible(false);//���ص��ԵĽ�����
				_mainLayer->SwapTimeBar();//����������ָ��
				_mainLayer->timebar->setVisible(true);//��ʾ��ҵĽ����� ,��ǰtimebarָ��ָ����ҵ�
				_mainLayer->buttonmenu->setVisible(true);
				_mainLayer->menuButtonOK->setEnabled(false);

				PlayState = 6;
			}
	
			_mainLayer->isExtraUsePoker = true;
		}

	}
	else
	{

		auto temp = _playerCollection[target]->_playPokerSlot;
		
		if (temp.end()!=std::find(temp.begin(),temp.end(),2))
		{
			//�������
			auto itindex = std::find(_playerCollection[target]->_playPokerSlot.begin(), _playerCollection[target]->_playPokerSlot.end(), 2);
			log("���һ����1");
			_playerCollection[1]->_playPokerSlot.erase(itindex);
			log("���һ����2");
			_mainLayer->giveupPoke_Robot(2);
			log("���һ����3");
		}
		else
		{
			//log("Foecurrenthealth=%d",_playerCollection[target]->GetPlayerHealth());
			_playerCollection[target]->losePlayHealth();//ʧȥһ������
			//log("Foecurrenthealth=%d", _playerCollection[target]->GetPlayerHealth());
		}
		log("------- extraUsePoker------");
	}
}

void GameScene::FoeUsePoker(int index)
{
	auto temp = _playerCollection[1]->_playPokerSlot;//��ȡ����
	int taoindex = -1;
	int shaindex = -1;
	int shanindex = -1;
	bool havetao = false;
	bool havesha = false;
	bool haveshan = false;
	for (int k = 0; k < temp.size(); k++)
	{
		if (temp[k] == 0)//����ҵ���һ���� ��
		{
			havetao = true;
			taoindex =k;
		}
		if (temp[k] == 1)//����ҵ���һ��ɱ ��
		{
			havesha = true;
			shaindex = k;
		}
		if (temp[k] == 2)//����ҵ���һ���� ��
		{
			haveshan = true;
			shanindex = k;
		}
	}
	switch (index)
	{
	case  0:
		//���Ȳ�������״̬
		if (_playerCollection[1]->UsableTaoPoker&&havetao)//����ܳ���,˵��״̬���������һ�Ҫ����
		{
			
			//������

			PokerEffect(0);

		//	log("---------pokersize()=%d", _playerCollection[1]->_playPokerSlot.size());
			auto it = _playerCollection[1]->_playPokerSlot.begin() + taoindex;
			_playerCollection[1]->_playPokerSlot.erase(it);
			_playerCollection[currentPlayer]->recovePlayHealth();//�ָ�һ��Ѫ
			_playerCollection[1]->UsableTaoPoker = false;
			_mainLayer->giveupPoke_Robot(0);//�Ե�����˵,���Ƽ���һ���Ƶ����ƶѣ�������ʾ����һ����
			
			

			barprect = _mainLayer->timebar->getPercent();//����֮�󴢴����
			barprect = barprect - 15.0;
			
			
		}
		break;
	case 1:
		if (_playerCollection[1]->UsableShaPokerCounts>0 && havesha)//�����ɱ��ʹ�ô���������ɱ�Ļ�
		{
			auto temp1 = _playerCollection[1]->_playPokerSlot;
			//��ɱ
			
			auto it = _playerCollection[1]->_playPokerSlot.begin() + shaindex;
			_playerCollection[1]->_playPokerSlot.erase(it);



			_mainLayer->giveupPoke_Robot(1);
			PokerEffect(1);
			
			extraUsePoker(0);//1�����(���ǵ���)��Ӧ
			_mainLayer->FoeIsUsePoker = false;//���ܳ���,����ȴ�Ŀ�������Ӧ����FoeIsUsePoker = true;
			
			_playerCollection[currentPlayer]->UsableShaPokerCounts--;//ɱ��ʹ�ô���-1
			

			barprect = _mainLayer->timebar->getPercent();//����֮�󴢴����
			barprect = barprect - 10.0;
		}
		break;
	default:
		break;
	}
	
	
	
}

