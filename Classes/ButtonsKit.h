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

//Дело в том, что планирую в своей игре сделать человечка, который обладает возможностью использовать 3 вида магии, а так же умееть драться в ближнем бою.
//У каждого вида магии есть по 3 конкретных заклинания. Суть в том, что изначально на экране есть 4 кнопки, которые позволяют выбрать текущий вид атаки. Если игрок нажимает, к примеру,
//на кнопку магии льда, то выпадает дополнительная панель с кнопками конкретных заклинаний. Нажатие каждой кнопки должно диспатчить определенное событие объекту класса Игрок, чтобы 
//тот применял какое-либо действие.
//Я модернизировал класс кнопки, снабдив его методом DoOnClick (используется boost::signals2). Есть класс CButtonsKit, который содержит 4 кнопки. Активными являются только те
//Однако, как кнопка может узнать какое конкретно событие диспатчить игроку?