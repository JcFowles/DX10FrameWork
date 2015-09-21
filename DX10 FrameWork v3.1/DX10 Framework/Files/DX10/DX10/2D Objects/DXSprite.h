//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2015 Media Design School
//
// File Name	:	DXSprite.h
// Description	:	This wraps all the Sprite functions and variables
// Author		:	Juran Griffith
// Mail			:	juran.griffith@mediadesignschool.com
//

#pragma once
#ifndef __DX_SPRITE_H__
#define __DX_SPRITE_H__

// Library Includes
//#include <iostream>     // std::cout
#include <fstream>      // std::ifstream

// Local Includes
#include "../DX10_Utilities.h"
#include "../DX10_Renderer.h"
#include "../Shaders/DX10_Shader_Sprite.h"

class DXSprite
{
	// Functions
	public:
		/*******************
		-> Default constructor.
		@author:	Juran Griffith.
		@parameter:	None.
		@return:	...
		********************/
		DXSprite();

		/*******************
		-> Default destructor.
		@author:	Juran Griffith.
		@parameter:	None.
		@return:	...
		********************/
		~DXSprite();

		/*******************
		-> Intializes the object
		@author:	Juran Griffith.
		@parameter: _pHWnd				- The handler to the window.
		@parameter: _pDX10_Renderer		- The renderer for this application
		@parameter: _pShader			- The shader object to use for rendering the sprite.
		@parameter: _filename			- The filename of the texture (include the filepath here too if needed).
		@parameter: _imageWidth			- The image width.
		@parameter: _imageHeight		- The image height.
		@parameter: _sliceWidth			- How many slices along the width of the image to do to split the image up into sections. (For sprite sheets etc...)
		@parameter: _sliceHeight		- How many slices along the height of the image to do to split the image up into sections. (For sprite sheets etc...)
		@return:	bool		- Returns true if the intialization succeeds otherwise the error on why it failed.
		********************/
		bool Initialize(HWND* _pHWnd, DX10_Renderer* _pDX10_Renderer, DX10_Shader_Sprite* _pShader, std::string _filename, UINT _imageWidth, UINT _imageHeight, UINT _sliceWidth = 1, UINT _sliceHeight = 1);

		/*******************
		-> Prepares the object for drawing.
		@author:	Juran Griffith.
		@parameter:	_positionX	- The x screen position to draw the object.
		@parameter:	_positionY	- The y screen position to draw the object.
		@return:	void.
		********************/
		void SetPosition(float _positionX, float _positionY);

		/*******************
		-> Gets the number of indexes for the 2D image.
		@author:	Juran Griffith.
		@parameter:	None.
		@return:	int		- The number of indexes for the 2D image
		********************/
		int GetIndexCount();

		/*******************
		-> Gets the number of slices in the image for rendering different parts of the image.
		@author:	Juran Griffith.
		@parameter:	None.
		@return:	int		- The number of indexes for the 2D image
		********************/
		int GetSliceWidth();

		/*******************
		-> Gets the number of slices in the image for rendering different parts of the image.
		@author:	Juran Griffith.
		@parameter:	None.
		@return:	int		- The number of indices for the 2D image
		********************/
		int GetSliceHeight();

		/*******************
		-> Gets the width of the image
		@author:	Juran Griffith.
		@parameter:	None.
		@return:	UINT		- The width of the image.
		********************/
		UINT GetWidth();

		/*******************
		-> Gets the height of the image
		@author:	Juran Griffith.
		@parameter:	None.
		@return:	UINT		- The height of the image.
		********************/
		UINT GetHeight();

		/*******************
		-> Gets the texture for this object so that it can be used for rendering by shaders.
		@author:	Juran Griffith.
		@parameter:	None.
		@return:	ID3D10ShaderResourceView*		- Returns a pointer to the texture resource.
		********************/
		ID3D10ShaderResourceView* GetTexture();

		/*******************
		-> Sets the uv to point to different section of the image based on the amount of splicing done.
		@author:	Juran Griffith.
		@parameter: _index	- The image index to render.
		@return:	void.
		********************/
		void SetImageIndex(UINT _index);

		/*******************
		-> Sets the size of the image
		@author:	Juran Griffith.
		@parameter:	_width	- The width of the image.
		@parameter:	_height	- The height of the image.
		@return:	void.
		********************/
		void SetSize(float _width, float _height);

		/*******************
		-> Prepare the vertex and index buffers on the gpu to be drawn by the shader.
		@author:	Juran Griffith.
		@parameter:	None.
		@return:	void.
		********************/
		void Render();
	protected:
	private:
		/*******************
		-> This builds the vertex and index buffer that will be used to draw the 2D image
		@author:	Juran Griffith.
		@parameter:	None.
		@return:	bool		- Returns true if the intialization succeeds otherwise the error on why it failed.
		********************/
		bool InitializeBuffers();

		/*******************
		-> Update the contents of the dynamic vertex buffer to re-position the 2D image image on the screen if need be
		@author:	Juran Griffith.
		@parameter:	_positionX	- The x screen position to draw the object.
		@parameter:	_positionY	- The y screen position to draw the object.
		@return:	void.
		********************/
		bool UpdateBuffers(float _positionX, float _positionY);

		/*******************
		-> Gets the PNG width and height of the image and updates this sprites width and height variables.
		@author:	Juran Griffith.
		@parameter:	None.
		@return:	bool	- True if the file can be read and the variables are updated.
		********************/
		bool GetPngSize();

	// Variables
	public:
	protected:
	private:
		UINT					m_vertexCount;
		UINT					m_indexCount;

		std::string				m_strFilename;

		float					m_previousPosX;
		float					m_previousPosY;

		int						m_screenWidth;
		int						m_screenHeight;
		UINT					m_imageWidth;
		UINT					m_imageHeight;

		// Sprite sheet variables
		std::vector<POINT>		m_imageIndexList;
		int						m_index;
		int						m_indexPrev;
		int						m_sliceWidth;
		int						m_sliceHeight;
		float					m_offsetScreenWidth;
		float					m_offsetScreenHeight;
		float					m_offsetImageWidth;
		float					m_offsetImageHeight;
		float					m_offsetU;
		float					m_offsetV;

		DX10_Renderer*			m_pDX10_Renderer;
		ID3D10ShaderResourceView*	m_pTex;
		DX10_Buffer*			m_pBuff;
		DX10_Shader_Sprite*		m_pShader;
};

#endif