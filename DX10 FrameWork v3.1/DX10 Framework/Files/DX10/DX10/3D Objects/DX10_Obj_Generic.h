/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : DX10_Obj_Generic.h
* Description : 3D Generic Object
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// Inclusion Guards
#pragma once
#ifndef __DX10_OBJ_GENERIC_H__
#define __DX10_OBJ_GENERIC_H__

// Local Includes
#include "../Meshes/DX10_Mesh.h"

class DX10_Obj_Generic
{
public:

	/***********************
	* ~CGenericObject: Default Destructor for Generic Object class
	* @author: Callan Moore
	********************/
	virtual ~DX10_Obj_Generic() {};

	/***********************
	* BaseInitialise: Initialise the Base member variables
	* @author: Callan Moore	 and Jc Fowles
	* @return: void
	********************/
	void BaseInitialise()
	{
		// Set initial position to origin point
		m_pos = { 0, 0, 0 };

		// Set initial scale
		m_scale = { 1.0f, 1.0f, 1.0f };

		// Initialise Rotations to zero
		m_rotation_Pitch = 0;
		m_rotation_Yaw = 0;
		m_rotation_Roll = 0;
		m_rotPerSecond_Pitch = 0;
		m_rotPerSecond_Yaw = 0;
		m_rotPerSecond_Roll = 0;

		// Set IDs to zero (Invalid ID)
		m_techniqueID = 0;
		m_fxID = 0;
		m_vertexLayoutID = 0;

		// Set all pointers to NULL
		m_pRenderer = 0;
	}
	
	/***********************
	* BaseProcess: Process the Generic properties
	* @author: Callan Moore
	* @parameter: _dt: The current delta tick
	* @return: void
	********************/
	void BaseProcess(float _dt)
	{
		// Calculate the new Rotation
		m_rotation_Pitch += m_rotPerSecond_Pitch * _dt;
		m_rotation_Yaw += m_rotPerSecond_Yaw * _dt;
		m_rotation_Roll += m_rotPerSecond_Roll * _dt;

		// Calculate the new world matrix
		CalcWorldMatrix();
	}
	
	/***********************
	* CalcWorldMatrix: Calculate the World Matrix 
	* @author: Callan Moore
	* @return: void
	********************/
	virtual void CalcWorldMatrix()
	{
		// Matrices to make up the World Matrix
		D3DXMATRIX matScale;
		D3DXMATRIX matRotatePitch;
		D3DXMATRIX matRotateYaw;
		D3DXMATRIX matRotateRoll;
		D3DXMATRIX matTranslation;

		// Initialise each matrix to Identity
		D3DXMatrixIdentity(&matScale);
		D3DXMatrixIdentity(&matRotatePitch);
		D3DXMatrixIdentity(&matRotateYaw);
		D3DXMatrixIdentity(&matRotateRoll);
		D3DXMatrixIdentity(&matTranslation);

		// Reset the Objects World Matrix for new Calculation
		D3DXMatrixIdentity(&m_matWorld);

		// Create Scale Transform matrix
		D3DXMatrixScaling(&matScale, m_scale.x, m_scale.y, m_scale.z);

		m_matWorld = matScale;

		// Calculate a Rotation Matrices around the Pitch, Yaw and Roll axes
		D3DXMatrixRotationX(&matRotatePitch, m_rotation_Pitch);
		D3DXMatrixRotationY(&matRotateYaw, m_rotation_Yaw);
		D3DXMatrixRotationZ(&matRotateRoll, m_rotation_Roll);

		// Calculate the Full Rotation Matrix and store in the World Matrix
		m_matWorld *= (matRotatePitch * matRotateYaw * matRotateRoll);

		// Calculate a translation Matrix based on the Objects current position in world space
		D3DXMatrixTranslation(&matTranslation, m_pos.x, m_pos.y, m_pos.z);

		// Calculate the Objects World Matrix
		m_matWorld *= matTranslation;
	}

	/***********************
	* GetPosition: Retrieve the Position of the Object
	* @author: Callan Moore
	* @return: v3float: 3D position of the Objects center
	********************/
	v3float GetPosition() { return m_pos; };

	/***********************
	* GetScale: Retrieve the Scale of the Object
	* @author: Jc Fowles
	* @return: v3float: 3D Scale of the object
	********************/
	v3float GetScale() { return m_scale; };
	
	/***********************
	* GetRotationPitch: Retrieve the Objects current rotation around the X axis
	* @author: Callan Moore
	* @return: float: Rotation in radians
	********************/
	float GetRotationPitch() { return m_rotation_Pitch; };
	
	/***********************
	* GetRotationYaw: Retrieve the Objects current rotation around the Y axis
	* @author: Callan Moore
	* @return: float: Rotation in radians
	********************/
	float GetRotationYaw() { return m_rotation_Yaw; };
	
	/***********************
	* GetRotationRoll: Retrieve the Objects current rotation around the Z axis
	* @author: Callan Moore
	* @return: float: Rotation in radians
	********************/
	float GetRotationRoll() { return m_rotation_Roll; };
	
	/***********************
	* GetRotPerFramePitch: Retrieve the Rotation per frame around the X axis
	* @author: Callan Moore
	* @return: float: The rotation that occurs each frame in radians
	********************/
	float GetRotPerFramePitch() { return m_rotPerSecond_Pitch; };
	
	/***********************
	* GetRotPerFrameYaw: Retrieve the Rotation per frame around the X axis
	* @author: Callan Moore
	* @return: float: The rotation that occurs each frame in radians
	********************/
	float GetRotPerFrameYaw() { return m_rotPerSecond_Yaw; };
	
	/***********************
	* GetRotPerFrameRoll: Retrieve the Rotation per frame around the X axis
	* @author: Callan Moore
	* @return: float: The rotation that occurs each frame in radians
	********************/
	float GetRotPerFrameRoll() { return m_rotPerSecond_Roll; };
	
	/***********************
	* SetPosition: Set the Position of the object
	* @author: Callan Moore
	* @parameter: _pos: 3D position in world space for the center of the object
	* @return: void 
	********************/
	void SetPosition(v3float _pos) { m_pos = _pos; };

	/***********************
	* SetScale: Set the Scale of the object
	* @author: Jc Fowles
	* @parameter: _scale: 3D scale of the object
	* @return: void
	********************/
	void SetScale(v3float _scale) { m_scale = _scale; };
	
	/***********************
	* SetRotationPitch: Set the rotation around the X axis
	* @author: Callan Moore
	* @parameter: _rotX: Rotation in radians
	* @return: void
	********************/
	void SetRotationPitch(float _rotX) { m_rotation_Pitch = _rotX; };
	
	/***********************
	* SetRotationYaw: Set the rotation around the Y axis
	* @author: Callan Moore
	* @parameter: _rotY: Rotation in radians
	* @return: void
	********************/
	void SetRotationYaw(float _rotY) { m_rotation_Yaw = _rotY; };
	
	/***********************
	* SetRotationRoll: Set the rotation around the Z axis
	* @author: Callan Moore
	* @parameter: _rotZ: Rotation in radians
	* @return: void
	********************/
	void SetRotationRoll(float _rotZ) { m_rotation_Roll = _rotZ; };
	
	/***********************
	* SetRotPerSecondPitch: Set the rotation increment that will occur each Second around the X axis
	* @author: Callan Moore
	* @parameter: _rotX: Rotation in radians
	* @return: void
	********************/
	void SetRotPerSecondPitch(float _rotX) { m_rotation_Pitch = _rotX; };
	
	/***********************
	* SetRotPerSecondYaw: Set the rotation increment that will occur each Second around the X axis
	* @author: Callan Moore
	* @parameter: _rotY: Rotation in radians
	* @return: void
	********************/
	void SetRotPerSecondYaw(float _rotY) { m_rotation_Yaw = _rotY; };
	
	/***********************
	* SetRotPerSecondRoll: Set the rotation increment that will occur each Second around the X axis
	* @author: Callan Moore
	* @parameter: _rotZ: Rotation in radians
	* @return: void
	********************/
	void SetRotPerSecondRoll(float _rotZ) { m_rotation_Roll = _rotZ; };
	

protected:
	DX10_Renderer* m_pRenderer;
	DX10_Mesh* m_pMesh;
	D3DXCOLOR m_color;

	float m_dt;

	v3float m_pos;
	v3float m_scale;
	float m_rotation_Pitch;
	float m_rotation_Yaw;
	float m_rotation_Roll;
	float m_rotPerSecond_Pitch;
	float m_rotPerSecond_Yaw;
	float m_rotPerSecond_Roll;
	
	UINT m_fxID;
	UINT m_techniqueID;
	UINT m_vertexLayoutID;

	D3DXMATRIX m_matWorld;
};

#endif	// __DX10_OBJ_GENERIC_H__

