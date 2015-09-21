/*
* Bachelor of Software Engineering
* Media Design School 
* Auckland
* New Zealand 
* 
* (c) 2005 - 2015 Media Design School 
* 
* File Name : DX10_Camera_Debug.h
* Description : Debug Camera used to move freely around the world
* Author : Jc Fowles 
* Mail : Jc.Fowles@mediadesign.school.nz 
*/

#pragma once
#ifndef __DEBUG_CAMERA_H__
#define __DEBUG_CAMERA_H__

//Local includes
#include "../DX10_Renderer.h"

class DX10_Camera_Debug
{
	//member functions
public:

	//****Creation/Deletion****

	/***********************
	* DX10_Camera_Debug: Constructor of the DX10_Camera_Debug object
	* @author: Jc Fowles
	* @return:
	********************/
	DX10_Camera_Debug();

	/***********************
	* DX10_Camera_Debug: Destructor of the DX10_Camera_Debug object
	* @author: Jc Fowles
	* @return:
	********************/
	~DX10_Camera_Debug();

	//Generic Functions

	/***********************
	* SetPostionVec: Set the Position vector
	* @author: Jc Fowles
	* @return: bool: Successful Initialization or not
	********************/
	bool Initialise(DX10_Renderer* _pRender);

	/***********************
	* process: Process the camera
	* @author: Jc Fowles
	* @return: void
	********************/
	void Process();
		
	//****Getters****
	
	//View Stuff

	/***********************
	* GetViewMatrix: Get the View matrix
	* @author: Jc Fowles
	* @return: D3DXMATRIX*: Returns the the View Matrix
	********************/
	D3DXMATRIX* GetViewMatrix(){ return &m_matView; };

	/***********************
	* GetPosition: Get the Position of the camera
	* @author: Jc Fowles
	* @return: v3float: Returns the the Position vector of the camera
	********************/
	v3float GetPosition(){ return m_position; };
	
	/***********************
	* GetTarget: Get the target of the camera
	* @author: Jc Fowles
	* @return: v3float: Returns the the target vector of the camera
	********************/
	v3float GetTarget(){ return m_target; };

	/***********************
	* GetUp: Get the Up vector of the camera
	* @author: Jc Fowles
	* @return: v3float: Returns the the up vector of the camera
	********************/
	v3float GetUp(){ return m_up; };

	/***********************
	* GetLook: Get the Look vector of the camera
	* @author: Jc Fowles
	* @return: v3float: Returns the the target vector of the camera
	********************/
	v3float GetLook() { return m_look; };

	//Projection Stuff
	

	//Limitations

	/***********************
	* GetMaxVelocity: Get the Camera's Max allowed velocity
	* @author: Jc Fowles
	* @return: float: Returns the Camera's Max allowed velocity
	********************/
	float GetMaxVelocity(){	return m_maxVelocity;	};
	
	/***********************
	* GetMaxPitch: Return The maximum allow pitch rotation
	* @author: Jc Fowles
	* @return: float: Returns The maximum allow pitch rotation
	********************/
	float GetMaxPitch(){return m_maxPitch;};
		
	//****Setters****

	//View
	
	/***********************
	* SetViewProperties: Set the Position, LookAt/target and Up vector for the view matrix
	* @author: Jc Fowles
	* @parameter: _Pos: The position vector to set the camera to
	* @parameter: _target: The Look At (Target) vector to set the camera to
	* @parameter: _up: The Up vector to set the camera to
	* @return: void
	********************/
	void SetViewProperties(v3float _Pos, v3float _target, v3float _up);
	
	/***********************
	* SetPostionVec: Set the Position vector
	* @author: Jc Fowles
	* @parameter: _Pos: The position vector to set the camera to
	* @return: void
	********************/
	void SetPostionVec(v3float _Pos){ m_position = _Pos; };
	
	/***********************
	* SetTargetVec: Set the Look At vector
	* @author: Jc Fowles
	* @parameter: _target: The Look At (Target) vector to set the camera to
	* @return: void
	********************/
	void SetTargetVec(v3float _target){ m_target = _target; };
	
	/***********************
	* SetUpVec: Set the Look At vector
	* @author: Jc Fowles
	* @parameter: _up: The Up vector to set the camera to
	* @return: void
	********************/
	void SetUpVec(v3float _up) { m_up = _up; };
	
	/***********************
	* SetMaxVelocity: Set max velocity
	* @author: Jc Fowles
	* @Parameter: float maxVelocity: value to set max velocity to
	* @return: void: 
	********************/
	void DX10_Camera_Debug::SetMaxVelocity(float maxVelocity) { m_maxVelocity = maxVelocity; }
	
	/***********************
	* SetMaxPitch: Set what the max pitch is allowed
	* @author: Jc Fowles
	* @Parameter: float maxPitch:Value to set max pitch to
	* @return: void: 
	********************/
	void DX10_Camera_Debug::SetMaxPitch(float maxPitch)     { m_maxPitch = maxPitch; }

	/***********************
	* SetSpeed: Set the speed
	* @author: Jc Fowles
	* @Parameter: float _fSpeed: Value to set speed to 
	* @return: void: 
	********************/
	void DX10_Camera_Debug::SetMoveSpeed(float _fSpeed)			{ m_moveSpeed = _fSpeed; }

	/***********************
	* SetSpeed: Set the speed
	* @author: Jc Fowles
	* @Parameter: float _fSpeed: Value to set speed to
	* @return: void:
	********************/
	void DX10_Camera_Debug::SetTurnSpeed(float _fSpeed)			{ m_turnSpeed = _fSpeed; }
	
	
	//****Functionality****
	
	//Rotations
	
	/***********************
	* Pitch: Rotate camera on the X-Axis
	* @author: Jc Fowles
	* @parameter: _fDeg: The amount in degree you would like to rotate
	* @return: void
	********************/
	void Pitch(float _fDeg);	//X-Axis

	/***********************
	* Pitch: Rotate camera on the Y-Axis
	* @author: Jc Fowles
	* @parameter: _fDeg: The amount in degree you would like to rotate
	* @return: void
	********************/
	void Yaw(float _fDeg);		//Y-Axis


	/***********************
	* Pitch: Rotate camera on the Z-Axis
	* @author: Jc Fowles
	* @parameter: _fDeg: The amount in degree you would like to rotate
	* @return: void
	********************/
	void Roll(float _fDeg);		//Z-Axis

	//Movements
	
	/***********************
	* Strafe: Move the camera on the X-Axis
	* @author: Jc Fowles
	* @parameter: _fDistance: The Distance you would like to move
	* @return: void
	********************/
	void Strafe(float _fDistance);	//X-Axis
	
	/***********************
	* Fly: Move the camera on the Y-Axis
	* @author: Jc Fowles
	* @parameter: _fDistance: The Distance you would like to move
	* @return: void
	********************/
	void Fly(float _fDistance);		//Y-Axis
	
	/***********************
	* Move: Move the camera on the Z-Axis
	* @author: Jc Fowles
	* @parameter: _fDistance: The Distance you would like to move in units per velocity
	* @return: void
	********************/
	void Move(float _fDistance);	//Z-Axis
	
	

	
	//Member variables
private:
	
	// Matrices
	D3DXMATRIX  m_matView;
		
	// Camera Axis
	v3float m_right;		//Camera Right(X-Axis)
	v3float m_up;		//Camera Up(Y-Axis)
	v3float m_look;		//Camera Look(Z-Axis)

	// Camera Properties
	v3float m_position;
	v3float m_target;		
	v3float m_velocity;

	// Rotation Limitations
	float m_maxPitch;
	float m_maxVelocity;
	
	// Movement Speed
	float m_moveSpeed;
	float m_turnSpeed;

	DX10_Renderer* m_pRenderer;
		
};

#endif //__DEBUG_CAMERA_H__