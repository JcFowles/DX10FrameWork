/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : Timer.h
* Description : Timer class to track time and delta ticks
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// Inclusion Guards
#pragma once
#ifndef TIMER_H
#define TIMER_H

class Timer
{
public:
	Timer();
	
	/***********************
	* GetGameTime: Retrieve the current game time
	* @author: Callan Moore
	* @return: float: Th current game time
	********************/
	float GetGameTime()const;
	
	/***********************
	* GetDeltaTime: Retrieve the current delta tick
	* @author: Callan Moore
	* @return: float: the current delta tick
	********************/
	float GetDeltaTime()const;

	/***********************
	* Reset: Reset all the timer variables
	* @author: Callan Moore
	* @return: void
	********************/
	void Reset();
	
	/***********************
	* Start: Start the clock again if it has been stopped (Un pause)
	* @author: Callan Moore
	* @return: void
	********************/
	void Start(); // Call when un paused.
	
	/***********************
	* Stop: Stop the clock from accumulating time (Pause)
	* @author: Callan Moore
	* @return: void
	********************/
	void Stop();  // Call when paused.
	
	/***********************
	* Tick: Calculate the delta tick
	* @author: Callan Moore
	* @return: void
	********************/
	void Tick();  // Call every frame.

private:
	double m_secondsPerCount;
	double m_deltaTime;

	__int64 m_baseTime;
	__int64 m_pausedTime;
	__int64 m_stopTime;
	__int64 m_prevTime;
	__int64 m_currentTime;

	bool m_stopped;
};

#endif	// TIMER_H