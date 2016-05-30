#pragma once

template <class T, class ...TArgs>
T *make_cc(TArgs&&... args)
{
	T *ret = new (std::nothrow) T;
	if (ret && ret->init(std::forward<TArgs>(args)...)) {
		ret->autorelease();
		return ret;
	}
	CC_SAFE_RELEASE(ret);
	return nullptr;
}

template <class T, class ...TArgs>
cocos2d::Scene *make_scene(TArgs&&... args)
{
	auto scene = cocos2d::Scene::create();
	auto layer = make_cc<T>(std::forward<TArgs>(args)...);
	scene->addChild(layer);

	return scene;
}

template <typename T>
class ObjectKeeper
{
public:
	ObjectKeeper(T *ptr = nullptr)
		: m_ptr(ptr)
	{
		SafeRetain();
	};

	operator bool() const
	{
		return (m_ptr != nullptr);
	};

	void Free()
	{
		if (*this)
		{
			m_ptr->release();
			m_ptr = nullptr;
		}
	};

	~ObjectKeeper()
	{
		Free();
	};

	ObjectKeeper& operator=(ObjectKeeper const& other)
	{
		if (&other != this)
		{
			Free();
			m_ptr = other.m_ptr;
			SafeRetain();
		}
		return *this;
	};

	ObjectKeeper(ObjectKeeper const& other)
		: m_ptr(nullptr)
	{
		*this = other;
	}

	operator T*() const
	{
		return m_ptr;
	}

	T* operator->() const
	{
		return m_ptr;
	}

private:
	void SafeRetain()
	{
		if (m_ptr)
		{
			m_ptr->retain();
		}
	};

	T *m_ptr;
};
