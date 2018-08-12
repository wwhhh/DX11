#pragma once

#include "PCH.h"

class FileLoader 
{
public:
	FileLoader();
	~FileLoader();

	bool Open( const std::wstring& filename );
	bool Close( );

	char* GetDataPtr();
	unsigned int GetDataSize();

protected:
	char*			m_pData;
	unsigned int	m_uiSize;

};