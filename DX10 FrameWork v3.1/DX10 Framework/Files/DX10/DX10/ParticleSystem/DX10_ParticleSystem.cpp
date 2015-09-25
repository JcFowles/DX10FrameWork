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

	m_pMatView = 0;
	m_pMatProj = 0;
	m_pCameraPosition = 0;

	m_emitterPosition = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f);
	m_emitterDirection = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 0.0f);
}

DX10_ParticleSystem::~DX10_ParticleSystem()
{
	ReleaseCOM(m_pInitialVB);
	ReleaseCOM(m_pRenderVB);
	ReleaseCOM(m_pStreamOutVB);

	ReleaseCOM(m_pEffect);

}

bool DX10_ParticleSystem::Initialise(ID3D10Device* _pDX10Device, ID3D10Effect* _pFX, ID3D10ShaderResourceView* _texureArray, ID3D10ShaderResourceView* _randomtexure, D3DXVECTOR3* _pCameraPostion, D3DXMATRIX* _pMatView, D3DXMATRIX* _pMatProj, UINT _maxParticles)
{
	// Check the parameters
	VALIDATE(_pDX10Device != 0);
	VALIDATE(_pFX != 0);
	VALIDATE(_texureArray != 0);
	VALIDATE(_randomtexure != 0);

	// Initialise the member variables

	// Store the Device
	m_pDX10Device = _pDX10Device;

	// Store the Effect 
	m_pEffect = _pFX;

	// Store camera properties
	m_pMatView = _pMatView;
	m_pMatProj = _pMatProj;

	m_pCameraPosition = _pCameraPostion;

	// Store the Max number of particles
	m_maxParticles = _maxParticles;

	// Store the particle Texture array and create the Random Texture
	m_pTexureArray = _texureArray;
	m_pRandomTexure = _randomtexure;

	// Create the FX variable Pointers
	VALIDATE(CreateFXVarPointers(m_pEffect));

	// Build the Vertex Buffers
	VALIDATE(CreateVertexBuffers());

	// Create the input layout for the particle .FX file
	VALIDATE(CreateInputLayout());

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
}

void DX10_ParticleSystem::Render()
{
	// Reset draw states in case they're different
	float blendFactors[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	m_pDX10Device->OMSetDepthStencilState(0, 0);
	m_pDX10Device->OMSetBlendState(0, blendFactors, 0xFFFFFFFF);

	// Set shader variables
	m_pFXMatViewVar->SetMatrix((float*)m_pMatView);
	m_pFXMatProjVar->SetMatrix((float*)m_pMatProj);
	m_pFXGameTimeVar->SetFloat(m_gameTime);
	m_pFXTimeStepVar->SetFloat(m_timeStep);
	D3DXVECTOR4 cameraPos = D3DXVECTOR4(m_pCameraPosition->x, m_pCameraPosition->y, m_pCameraPosition->z, 1.0f);
	m_pFXCameraPosVar->SetFloatVector((float*)&cameraPos);
	m_pFXEmitterPosVar->SetFloatVector((float*)&m_emitterPosition);
	m_pFXEmitterDirVar->SetFloatVector((float*)&m_emitterDirection);
	
	m_fxTextureArrayVar->SetResource(m_pTexureArray);
	m_fxRandomTextureVar->SetResource(m_pRandomTexure);

	// Set IA stage
	m_pDX10Device->IASetInputLayout(m_pInputLayout);
	m_pDX10Device->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_POINTLIST);

	UINT stride = sizeof(ParticleVertex);
	UINT offset = 0;

	// On the first pass, use the initial Vertex Buffer.
	// Otherwise, use  the Vertex Buffer that contains the current particle list.
	if (m_firstRun == true)
	{
		m_pDX10Device->IASetVertexBuffers(0, 1, &m_pInitialVB, &stride, &offset);
	}
	else
	{
		m_pDX10Device->IASetVertexBuffers(0, 1, &m_pRenderVB, &stride, &offset);
	}

	// Update the current particle list using stream-out only technique.
	m_pDX10Device->SOSetTargets(1, &m_pStreamOutVB, &offset);

	D3D10_TECHNIQUE_DESC techDesc;
	m_pStreamOutTech->GetDesc(&techDesc);
	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		m_pStreamOutTech->GetPassByIndex(p)->Apply(0);

		if (m_firstRun)
		{
			m_pDX10Device->Draw(1, 0);
			m_firstRun = false;
		}
		else
		{
			m_pDX10Device->DrawAuto();
		}
	}

	// After streaming-out we need to Unbind the Vertex Buffer
	ID3D10Buffer* bufferArray[1] = { 0 };
	m_pDX10Device->SOSetTargets(1, bufferArray, &offset);

	// swap the  updated stream Out vertex buffer with the Render Buffer 
	// to Draw the Updated Vertex Buffer
	std::swap(m_pRenderVB, m_pStreamOutVB);

	// Draw the updated particle system we just streamed-out.
	m_pDX10Device->IASetVertexBuffers(0, 1, &m_pRenderVB, &stride, &offset);

	m_pRenderTech->GetDesc(&techDesc);
	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		m_pRenderTech->GetPassByIndex(p)->Apply(0);

		m_pDX10Device->DrawAuto();
	}
}

// Set Emitter

void DX10_ParticleSystem::SetEmitterPosition(const v3float& _emitterPosition)
{
	m_emitterPosition = D3DXVECTOR4(_emitterPosition.x, _emitterPosition.y, _emitterPosition.z, 1.0f);
}

void DX10_ParticleSystem::setEmitterDirection(const v3float& _emitterDirection)
{
	m_emitterDirection = D3DXVECTOR4(_emitterDirection.x, _emitterDirection.y, _emitterDirection.z, 0.0f);
}

// Private Function

bool DX10_ParticleSystem::CreateFXVarPointers(ID3D10Effect* _pFX)
{

	m_pStreamOutTech = _pFX->GetTechniqueByName("StreamOutTech");
	m_pRenderTech = _pFX->GetTechniqueByName("DrawTech");
	
	m_pFXGameTimeVar = _pFX->GetVariableByName("g_gameTime")->AsScalar();
	m_pFXTimeStepVar = _pFX->GetVariableByName("g_timeStep")->AsScalar();

	m_pFXMatViewVar = _pFX->GetVariableByName("g_matView")->AsMatrix();
	m_pFXMatProjVar = _pFX->GetVariableByName("g_matProj")->AsMatrix();
	m_pFXCameraPosVar = _pFX->GetVariableByName("g_EyePosW")->AsVector();

	m_pFXEmitterPosVar = _pFX->GetVariableByName("g_EmitPosW")->AsVector();
	m_pFXEmitterDirVar = _pFX->GetVariableByName("g_EmitDirW")->AsVector();
	
	m_fxTextureArrayVar = _pFX->GetVariableByName("g_TexureArray")->AsShaderResource();
	m_fxRandomTextureVar = _pFX->GetVariableByName("g_RandomTexure")->AsShaderResource();
	
	VALIDATE(m_pStreamOutTech != 0);
	VALIDATE(m_pRenderTech != 0);
	VALIDATE(m_pFXGameTimeVar != 0);
	VALIDATE(m_pFXTimeStepVar != 0);
	VALIDATE(m_pFXMatProjVar != 0);
	VALIDATE(m_pFXCameraPosVar != 0);
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

bool DX10_ParticleSystem::CreateInputLayout()
{
	
	D3D10_INPUT_ELEMENT_DESC particleDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "VELOCITY", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "SIZE", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "AGE", 0, DXGI_FORMAT_R32_FLOAT, 0, 32, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "TYPE", 0, DXGI_FORMAT_R32_UINT, 0, 36, D3D10_INPUT_PER_VERTEX_DATA, 0 },
	};

	D3D10_PASS_DESC passDesc;
	m_pStreamOutTech->GetPassByIndex(0)->GetDesc(&passDesc);

	// Create the input layout for the particles
	VALIDATEHR(m_pDX10Device->CreateInputLayout(particleDesc, 5, passDesc.pIAInputSignature,
		passDesc.IAInputSignatureSize, &m_pInputLayout));

	// Return succesfull Creation
	return true;
}
