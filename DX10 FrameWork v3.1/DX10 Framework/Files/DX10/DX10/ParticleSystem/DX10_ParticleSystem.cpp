#include "DX10_ParticleSystem.h"


DX10_ParticleSystem::DX10_ParticleSystem()
{
	// construct memner varibles 
	m_pDX10Device = 0;

	m_pInitialVB = 0;
	m_pRenderVB = 0;
	m_pStreamOutVB = 0;
	
	m_pTexureArray = 0;
	m_pRandomTexure = 0;

	m_firstRun = true;
	m_gameTime = 0.0f;
	m_timeStep = 0.0f;
	m_age = 0.0f;

	m_cameraPosition = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f);
	m_emitterPosition = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f);
	m_emitterDirection = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 0.0f);
}

DX10_ParticleSystem::~DX10_ParticleSystem()
{
	ReleaseCOM(m_pInitialVB);
	ReleaseCOM(m_pRenderVB);
	ReleaseCOM(m_pStreamOutVB);
}

bool DX10_ParticleSystem::Initialise(ID3D10Device* _pDX10Device, ID3D10Effect* _pFX, ID3D10ShaderResourceView* _texureArray, D3DXVECTOR3* _pCameraPostion, D3DXVECTOR3* _pMatView, D3DXVECTOR3* _pMatProj, UINT _maxParticles)
{
	// Check the parameters
	VALIDATE(_pDX10Device != 0);
	VALIDATE(_pFX != 0);
	VALIDATE(_texureArray != 0);

	// Initialise the member variables

	// Store the Device
	m_pDX10Device = _pDX10Device;

	// Store the Max number of particles
	m_maxParticles = _maxParticles;

	// Store the particle Texture array and create the Random Texture
	m_pTexureArray = _texureArray;
	m_pRandomTexure = CreateRandomTexture();
	VALIDATE(m_pRandomTexure != 0);

	// Create the FX variable Pointers
	VALIDATE(CreateFXVarPointers(_pFX));

	// Build the Vertex Buffers
	VALIDATE(CreateVertexBuffers());

	// Return Sucesful Initialization
	return true;
}

void DX10_ParticleSystem::Reset()
{
	m_firstRun = true;
	m_age = 0.0f;
}

void DX10_ParticleSystem::Process(float _dt, float _gameTime)
{
	// Update the game timers
	m_gameTime = _gameTime;
	m_timeStep = _dt;

	m_age += _dt;



	mfxViewProjVar->SetMatrix((float*)&(V*P));
	mfxGameTimeVar->SetFloat(m_gameTime);
	mfxTimeStepVar->SetFloat(m_timeStep);
	mfxEyePosVar->SetFloatVector((float*)&mEyePosW);
	mfxEmitPosVar->SetFloatVector((float*)&mEmitPosW);
	mfxEmitDirVar->SetFloatVector((float*)&mEmitDirW);
	mfxTexArrayVar->SetResource(mTexArrayRV);
	mfxRandomTexVar->SetResource(mRandomTexRV);

}



// Private Function

bool DX10_ParticleSystem::CreateFXVarPointers(ID3D10Effect* _pFX)
{

	m_pStreamOutTech = _pFX->GetTechniqueByName("StreamOutTech");
	m_pRenderTech = _pFX->GetTechniqueByName("DrawTech");
	
	m_pFXMatViewVar = _pFX->GetVariableByName("g_matView")->AsMatrix();
	m_pFXMatProjVar = _pFX->GetVariableByName("g_matProj")->AsMatrix();
	
	m_pFXGameTimeVar = _pFX->GetVariableByName("g_gameTime")->AsScalar();
	m_pFXTimeStepVar = _pFX->GetVariableByName("g_timeStep")->AsScalar();
	m_pFXEyePosVar = _pFX->GetVariableByName("g_EyePosW")->AsVector();
	m_pFXEmitterPosVar = _pFX->GetVariableByName("g_EmitPosW")->AsVector();
	m_pFXEmitterDirVar = _pFX->GetVariableByName("g_EmitDirW")->AsVector();
	
	m_fxTextureArrayVar = _pFX->GetVariableByName("g_TexureArray")->AsShaderResource();
	m_fxRandomTextureVar = _pFX->GetVariableByName("g_RandomTexure")->AsShaderResource();
	
	VALIDATE(m_pStreamOutTech != 0);
	VALIDATE(m_pRenderTech != 0);
	VALIDATE(m_pFXMatProjVar != 0);
	VALIDATE(m_pFXGameTimeVar != 0);
	VALIDATE(m_pFXTimeStepVar != 0);
	VALIDATE(m_pFXEyePosVar != 0);
	VALIDATE(m_pFXEmitterPosVar != 0);
	VALIDATE(m_pFXEmitterDirVar != 0);
	VALIDATE(m_fxTextureArrayVar != 0);
	VALIDATE(m_fxRandomTextureVar != 0);
	
	return true;
}

bool DX10_ParticleSystem::CreateVertexBuffers()
{
	// Create the buffer to start the particle system.

	D3D10_BUFFER_DESC vertexBufferDesc;
	vertexBufferDesc.Usage = D3D10_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(ParticleVertex) * 1;
	vertexBufferDesc.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;

	// The initial particle emitter has type 0 and age 0.
	// The rest of the particle attributes do not apply to an emitter.
	ParticleVertex initialParticle;
	ZeroMemory(&initialParticle, sizeof(ParticleVertex));
	initialParticle.age = 0.0f;
	initialParticle.type = 0;

	D3D10_SUBRESOURCE_DATA initialVertexData;
	initialVertexData.pSysMem = &initialParticle;

	// Create the initial buffer holding the emitter
	VALIDATEHR(m_pDX10Device->CreateBuffer(&vertexBufferDesc, &initialVertexData, &m_pInitialVB));

	// Create the ping-pong(Swapping) buffers for stream-out and Rendering.
	vertexBufferDesc.ByteWidth = sizeof(ParticleVertex) * m_maxParticles;
	vertexBufferDesc.BindFlags = D3D10_BIND_VERTEX_BUFFER | D3D10_BIND_STREAM_OUTPUT;

	VALIDATEHR(m_pDX10Device->CreateBuffer(&vertexBufferDesc, 0, &m_pRenderVB));
	VALIDATEHR(m_pDX10Device->CreateBuffer(&vertexBufferDesc, 0, &m_pStreamOutVB));

	// return Succesfull creation
	return true;
}

bool DX10_ParticleSystem::CreateRandomTexture()
{
	// Create the random data.
	D3DXVECTOR4 randomValues[1024];
	for (int i = 0; i < 1024; ++i)
	{
		randomValues[i].x = RandomFloat(-1.0f, 1.0f);
		randomValues[i].y = RandomFloat(-1.0f, 1.0f);
		randomValues[i].z = RandomFloat(-1.0f, 1.0f);
		randomValues[i].w = RandomFloat(-1.0f, 1.0f);
	}

	D3D10_SUBRESOURCE_DATA initialData;
	initialData.pSysMem = randomValues;
	initialData.SysMemPitch = 1024 * sizeof(D3DXVECTOR4);
	initialData.SysMemSlicePitch = 1024 * sizeof(D3DXVECTOR4);

	// Create the texture.
	D3D10_TEXTURE1D_DESC textureDesc;
	textureDesc.Width = 1024;
	textureDesc.MipLevels = 1;
	textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	textureDesc.Usage = D3D10_USAGE_IMMUTABLE;
	textureDesc.BindFlags = D3D10_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;
	textureDesc.ArraySize = 1;

	ID3D10Texture1D* randomTex = 0;
	VALIDATEHR(m_pDX10Device->CreateTexture1D(&textureDesc, &initialData, &randomTex));
	
	// Create the resource view.
	D3D10_SHADER_RESOURCE_VIEW_DESC viewDesc;
	viewDesc.Format = textureDesc.Format;
	viewDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE1D;
	viewDesc.Texture1D.MipLevels = textureDesc.MipLevels;
	viewDesc.Texture1D.MostDetailedMip = 0;

	VALIDATEHR(m_pDX10Device->CreateShaderResourceView(randomTex, &viewDesc, &m_pRandomTexure));

	ReleaseCOM(randomTex);

	// return Succesfull creation
	return true;
}

