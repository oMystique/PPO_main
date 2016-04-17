#pragma once
#include "SneakyInput\SneakyButtonSkinnedBase.h"
#include "ObjectKeeper.h"
#include <vector>

class CPlayer;

class CButtonsKit: public cocos2d::Layer
{
public:
	static cocos2d::Layer* create(cocos2d::Size const &visibleSize);
	void insertButton(ObjectKeeper<SneakyButton> const &button);
	void initButtons(cocos2d::Size const &visibleSize);
	void update(float dt);
	std::vector<ObjectKeeper<SneakyButton>> m_buttons;
};

//���� � ���, ��� �������� � ����� ���� ������� ���������, ������� �������� ������������ ������������ 3 ���� �����, � ��� �� ������ ������� � ������� ���.
//� ������� ���� ����� ���� �� 3 ���������� ����������. ���� � ���, ��� ���������� �� ������ ���� 4 ������, ������� ��������� ������� ������� ��� �����. ���� ����� ��������, � �������,
//�� ������ ����� ����, �� �������� �������������� ������ � �������� ���������� ����������. ������� ������ ������ ������ ���������� ������������ ������� ������� ������ �����, ����� 
//��� �������� �����-���� ��������.
//� �������������� ����� ������, ������� ��� ������� DoOnClick (������������ boost::signals2). ���� ����� CButtonsKit, ������� �������� 4 ������. ��������� �������� ������ ��
//������, ��� ������ ����� ������ ����� ��������� ������� ���������� ������?