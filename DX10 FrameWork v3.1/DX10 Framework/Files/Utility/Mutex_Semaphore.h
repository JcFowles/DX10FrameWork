/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : Mutex_Semaphore.h
* Description : Creates a mutex for locking and unlocking critical resources
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

#pragma once

#ifndef __MYSEMAPHORE_H__
#define __MYSEMAPHORE_H__

//Library includes
#include <condition_variable>
#include <mutex>


class Mutex_Semaphore
{
public:

	/***********************
	* Mutex_Semaphore: Default Constructor for the Mutex_Semaphore Class
	* @author: Callan Moore
	********************/
	Mutex_Semaphore();

	/***********************
	* Mutex_Semaphore: Constructor taking in a value for the Mutex_Semaphore Class
	* @author: Callan Moore
	********************/
	Mutex_Semaphore(int _iValue);

	/***********************
	* ~CMySemaphore: Default Destructor for the MySemaphore Class
	* @author: Callan Moore
	********************/
	~Mutex_Semaphore();

	/***********************
	* Wait: Atomic operation that waits for the semaphore value to be positive and then decrements it by one.
	* @author: Callan Moore
	* @return: void
	********************/
	void Wait();


	/***********************
	* Signal: Atomic operation that increments the semaphore value by one. Which when positive, wakes up a waiting Semaphore
	* @author: Callan Moore
	* @return: void
	********************/
	void Signal();

	/***********************
	* IsPositive: Checks if the Value is positive
	* @author: Callan Moore
	* @return: bool: Returns whether the Value is positive
	********************/
	bool Mutex_Semaphore::IsPositive();

private:
	int m_iValue;
	std::condition_variable m_Condition; 
	std::mutex m_Mutex;
};

#endif // __MYSEMAPHORE_H__