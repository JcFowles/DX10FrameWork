/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : GenUtilities.h
* Description : General Utilitis used by the application
* Author :	Jc Fowles
* Mail :	Jc.Fowles@mediadesign.school.nz
*/

#pragma once
#ifndef __GEN_UTILS_H__
#define __GEN_UTILS_H__

// Library Inlcudes 
#include <cstdlib>
#include <vector>
#include <string>
#include <cassert>
#include <math.h>


// Defines 

// Success Check
#define VALIDATE(a) if (!a) return (false)

// Pointer Deletion
#define ReleasePointer(x) { if (x){ delete x; x = 0; } }



#endif //__GEN_UTILS_H__