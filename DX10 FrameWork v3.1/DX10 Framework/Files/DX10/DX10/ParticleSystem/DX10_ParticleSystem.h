/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : ParticleSystem.h
* Description : Code Used for creating, updating and drawing a particle system
* Author :	Jc Fowles
* Mail :	Jc.Fowles@mediadesign.school.nz
*/

// Inclusion Guards
#pragma once
#ifndef __DX10_PARTICLE_SYSTEM_H__
#define __DX10_PARTICLE_SYSTEM_H__

// Library Includes

// Local Includes
#include "../../../Utility/Utilities.h"
#include "../Cameras/DX10_Camera_Debug.h"
#include "../DX10_Utilities.h"
#include "../DX10_Renderer.h"


// Struct for the particle Vertex
struct ParticleVertex
{
	D3DXVECTOR3 initialPos;
	D3DXVECTOR3 initialVel;
	D3DXVECTOR2 size;
	float age;
	unsigned int type;
};


class DX10_ParticleSystem
{
	// Member functions
public:
	DX10_ParticleSystem();
	~DX10_ParticleSystem();

	bool Initialise(ID3D10Device* _pDX10Device, ID3D10Effect* _pFX,
		ID3D10ShaderResourceView* _texureArray, UINT _maxParticles);

	void Reset();
	// TO DO JC: Change to a base camera
	void SetUpPerFrame(DX10_Camera_Debug* _pCamera);
	void Process(float _dt, float _gameTime);
	void Render();

	void SetEyePos(const v3float& _eyePosW);
	void SetEmitPos(const v3float& _emitPosW);
	void SetEmitDir(const v3float& _emitDirW);

	// Time elapsed since the system was reset.
	float GetAge()const { return m_age; };

protected:
private:

	DX10_ParticleSystem(const DX10_ParticleSystem& rhs);
	DX10_ParticleSystem& operator=(const DX10_ParticleSystem& rhs);

	/***********************
	* CreateFXVarPointers: Create the pointers to the FX memory on the graphics card
	* @author: Jc Fowles
	* @parameter: _pFX : Pointer to the .fx file to get the variables from
	* @return: bool: Successful or not
	********************/
	bool CreateFXVarPointers(ID3D10Effect* _pFX);

	bool CreateVertexBuffers();

	bool CreateRandomTexture();

	// Member Variables
public:
protected:
private:

	UINT m_maxParticles;
	bool m_firstRun;

	float m_gameTime;
	float m_timeStep;
	float m_age;

	D3DXVECTOR4 m_cameraPosition;
	D3DXVECTOR4 m_emitterPosition;
	D3DXVECTOR4 m_emitterDirection;

	ID3D10Device* m_pDX10Device;
	
	ID3D10Buffer* m_pInitialVB;
	ID3D10Buffer* m_pRenderVB;
	ID3D10Buffer* m_pStreamOutVB;
	
	ID3D10ShaderResourceView* m_pTexureArray;
	ID3D10ShaderResourceView* m_pRandomTexure;
	
	ID3D10EffectTechnique* m_pStreamOutTech;
	ID3D10EffectTechnique* m_pRenderTech;

	ID3D10EffectMatrixVariable* m_pFXMatViewVar;
	ID3D10EffectMatrixVariable* m_pFXMatProjVar;
	ID3D10EffectScalarVariable* m_pFXGameTimeVar;
	ID3D10EffectScalarVariable* m_pFXTimeStepVar;
	ID3D10EffectVectorVariable* m_pFXEyePosVar;
	ID3D10EffectVectorVariable* m_pFXEmitterPosVar;
	ID3D10EffectVectorVariable* m_pFXEmitterDirVar;

	ID3D10EffectShaderResourceVariable* m_fxTextureArrayVar;
	ID3D10EffectShaderResourceVariable* m_fxRandomTextureVar;

};

#endif; //__DX10_PARTICLE_SYSTEM_H__
