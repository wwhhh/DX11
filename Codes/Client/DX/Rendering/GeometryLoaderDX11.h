#pragma once

#include "GeometryDX11.h"
#include <string>

class GeometryLoaderDX11
{
public:	
	static GeometryPtr loadMS3DFile2( std::wstring filename );		

private:
	GeometryLoaderDX11();

	struct PlyElementPropertyDeclaration
	{
		std::string name;
		bool isList;
		std::string type;
		std::string listLengthType;
	};

	struct PlyElementDesc
	{
		std::string name;
		int elementCount;
		std::vector< PlyElementPropertyDeclaration > dataFormat;
		std::vector< void** > data;
	};

	template<typename T>
	struct PlyDataArray
	{
		unsigned int length;
		T* data;
	};

	static int FindAdjacentIndex( int edgeStart, int edgeEnd, int triV, int* pRaw, int rawLen);
	static PlyElementDesc ParsePLYElementHeader(std::string headerLine, std::ifstream& input);
	static PlyElementPropertyDeclaration ParsePLYElementProperty(std::string desc);
	static PlyElementPropertyDeclaration ParsePLYElementPropertyList(std::string desc);
	static std::vector<void**> ReadPLYElementData(std::ifstream& input, const PlyElementDesc& desc);
	static void** ParsePLYElementData(std::string text, const std::vector<PlyElementPropertyDeclaration>& desc);
	template<typename T> static T* ExtractDataPtr(std::string input);
	template<typename T> static T ExtractDataVal(std::string input);
	template<typename T> static PlyDataArray<T>* ExtractDataPtrArray(int length, std::vector<std::string>::iterator iterator);
	static int FindPlyElementIndex(std::vector<PlyElementDesc> elems, std::string name);
	static int FindPlyElementPropertyIndex(std::vector<PlyElementPropertyDeclaration> elems, std::string name);
};