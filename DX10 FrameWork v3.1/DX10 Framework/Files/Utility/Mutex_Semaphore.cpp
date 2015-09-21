/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : Mutex_Semaphore.cpp
* Description : Creates a mutex for locking and unlocking critical resources
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

//This include
#include "Mutex_Semaphore.h"

Mutex_Semaphore::Mutex_Semaphore()
{
	m_iValue = 0;
}

Mutex_Semaphore::Mutex_Semaphore(int _iValue)
{
	m_iValue = _iValue;
}

Mutex_Semaphore::~Mutex_Semaphore()
{
}

void Mutex_Semaphore::Wait()
{
	// Value is the Critical section. Lock the Mutex with automatic unlocking
	std::unique_lock<std::mutex> _unqlckguard(m_Mutex);

	m_Condition.wait(_unqlckguard, [this](){return (m_iValue > 0); });
	m_iValue--;
}

void Mutex_Semaphore::Signal()
{
	std::lock_guard<std::mutex> _lckguard(m_Mutex);
	m_iValue++;
	m_Condition.notify_one();
}

bool Mutex_Semaphore::IsPositive()
{
	return (m_iValue > 0);
}