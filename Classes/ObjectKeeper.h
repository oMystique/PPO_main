#pragma once

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
