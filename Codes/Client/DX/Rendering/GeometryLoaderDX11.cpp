#include "PCH.h"
#include "GeometryLoaderDX11.h"
#include "GeometryDX11.h"
#include "VertexElementDX11.h"
#include "Maths/Vector2f.h"
#include "Maths/Vector3f.h"
#include "Utils/Log.h"
#include "Utils/FileSystem.h"
#include "Utils/UtilString.h"
#include "MaterialGeneratorDX11.h"
#include <sstream>
#include "ms3dspec.h"


GeometryLoaderDX11::GeometryLoaderDX11( )
{
}

GeometryPtr GeometryLoaderDX11::loadMS3DFile2( std::wstring filename )
{
	// Get the file path to the models
	FileSystem fs;
	filename = fs.GetModelsFolder() + filename;

	// Temporary Milkshape structures
	unsigned short usVertexCount = 0;
	unsigned short usTriangleCount = 0;
	unsigned short usGroupCount = 0;
	unsigned short usMaterialCount = 0;
	MS3DVertex* pMS3DVertices = NULL;
	MS3DTriangle* pMS3DTriangles = NULL;
	MS3DGroup* pMS3DGroups = NULL;
	MS3DMaterial* pMS3DMaterials = NULL;

	std::ifstream fin;
	MS3DHeader header;

	// Open the file and read the MS3D header data
	fin.open( filename.c_str(),std::ios::binary );
	fin.read((char*)(&(header.id)), sizeof(header.id));
	fin.read((char*)(&(header.version)), sizeof(header.version));
	if (header.version!=3 && header.version!=4)
		return NULL;

	// Load all the vertices
	fin.read((char*)(&usVertexCount), sizeof(unsigned short));
	pMS3DVertices = new MS3DVertex[usVertexCount];
	for (int i = 0; i < usVertexCount; i++)
	{
		fin.read((char*)&(pMS3DVertices[i].flags), sizeof(unsigned char));
		fin.read((char*)&(pMS3DVertices[i].vertex[0]), sizeof(float));
		fin.read((char*)&(pMS3DVertices[i].vertex[1]), sizeof(float));
		fin.read((char*)&(pMS3DVertices[i].vertex[2]), sizeof(float));
		fin.read((char*)&(pMS3DVertices[i].boneId), sizeof(char));
		fin.read((char*)&(pMS3DVertices[i].referenceCount), sizeof(unsigned char));
	}

	// Load all the triangle indices
	fin.read((char*)(&usTriangleCount), sizeof(unsigned short));
	pMS3DTriangles = new MS3DTriangle[usTriangleCount];
	for (int i = 0; i < usTriangleCount; i++)
	{
		fin.read((char*)&(pMS3DTriangles[i].flags),sizeof(unsigned short));
		fin.read((char*)&(pMS3DTriangles[i].vertexIndices[0]), sizeof(unsigned short)); //3*sizeof(unsigned short));
		fin.read((char*)&(pMS3DTriangles[i].vertexIndices[1]), sizeof(unsigned short)); //3*sizeof(unsigned short));
		fin.read((char*)&(pMS3DTriangles[i].vertexIndices[2]), sizeof(unsigned short)); //3*sizeof(unsigned short));
		fin.read((char*)&(pMS3DTriangles[i].vertexNormals[0]), 3*sizeof(float));
		fin.read((char*)&(pMS3DTriangles[i].vertexNormals[1]), 3*sizeof(float));
		fin.read((char*)&(pMS3DTriangles[i].vertexNormals[2]), 3*sizeof(float));
		fin.read((char*)&(pMS3DTriangles[i].s), 3*sizeof(float));
		fin.read((char*)&(pMS3DTriangles[i].t), 3*sizeof(float));
		fin.read((char*)&(pMS3DTriangles[i].smoothingGroup), sizeof(unsigned char));
		fin.read((char*)&(pMS3DTriangles[i].groupIndex), sizeof(unsigned char));
	}

	// Load all the group information
	fin.read((char*)(&usGroupCount), sizeof(unsigned short));
	pMS3DGroups = new MS3DGroup[usGroupCount];
	for (int i = 0; i < usGroupCount; i++)
	{
		fin.read((char*)&(pMS3DGroups[i].flags), sizeof(unsigned char));
		fin.read((char*)&(pMS3DGroups[i].name), sizeof(char[32]));
		fin.read((char*)&(pMS3DGroups[i].numtriangles), sizeof(unsigned short));
		unsigned short triCount = pMS3DGroups[i].numtriangles;
		pMS3DGroups[i].triangleIndices = new unsigned short[triCount];
		fin.read((char*)(pMS3DGroups[i].triangleIndices), sizeof(unsigned short) * triCount);
		fin.read((char*)&(pMS3DGroups[i].materialIndex), sizeof(char));
	}

	// Load all the material information
	fin.read((char*)(&usMaterialCount),sizeof(unsigned short));
	pMS3DMaterials = new MS3DMaterial[usMaterialCount];
	for (int i = 0; i < usMaterialCount; i++)
	{
		fin.read((char*)&(pMS3DMaterials[i].name), sizeof(char[32]));
		fin.read((char*)&(pMS3DMaterials[i].ambient), 4 * sizeof(float));
		fin.read((char*)&(pMS3DMaterials[i].diffuse), 4 * sizeof(float));
		fin.read((char*)&(pMS3DMaterials[i].specular), 4 * sizeof(float));
		fin.read((char*)&(pMS3DMaterials[i].emissive), 4 * sizeof(float));
		fin.read((char*)&(pMS3DMaterials[i].shininess), sizeof(float));
		fin.read((char*)&(pMS3DMaterials[i].transparency), sizeof(float));
		fin.read((char*)&(pMS3DMaterials[i].mode), sizeof(char));
		fin.read((char*)&(pMS3DMaterials[i].texture), sizeof(char[128]));
		fin.read((char*)&(pMS3DMaterials[i].alphamap), sizeof(char[128]));
	}

	// Close the file (remaining file data unused)
	fin.close();


	// create the vertex element streams
	VertexElementDX11* pPositions = new VertexElementDX11( 3, usTriangleCount*3 );
    pPositions->m_SemanticName = VertexElementDX11::PositionSemantic;
	pPositions->m_uiSemanticIndex = 0;
	pPositions->m_Format = DXGI_FORMAT_R32G32B32_FLOAT;
	pPositions->m_uiInputSlot = 0;
	pPositions->m_uiAlignedByteOffset = 0;
	pPositions->m_InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	pPositions->m_uiInstanceDataStepRate = 0;

	VertexElementDX11* pTexcoords = new VertexElementDX11( 2, usTriangleCount*3 );
	pTexcoords->m_SemanticName = VertexElementDX11::TexCoordSemantic;
	pTexcoords->m_uiSemanticIndex = 0;
	pTexcoords->m_Format = DXGI_FORMAT_R32G32_FLOAT;
	pTexcoords->m_uiInputSlot = 0;
	pTexcoords->m_uiAlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	pTexcoords->m_InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	pTexcoords->m_uiInstanceDataStepRate = 0;

	VertexElementDX11* pNormals = new VertexElementDX11( 3, usTriangleCount*3 );
	pNormals->m_SemanticName = VertexElementDX11::NormalSemantic;
	pNormals->m_uiSemanticIndex = 0;
	pNormals->m_Format = DXGI_FORMAT_R32G32B32_FLOAT;
	pNormals->m_uiInputSlot = 0;
	pNormals->m_uiAlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	pNormals->m_InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	pNormals->m_uiInstanceDataStepRate = 0;

	Vector3f* pPos = (Vector3f*)((*pPositions)[0]);
	Vector3f* pNrm = (Vector3f*)((*pNormals)[0]);
	Vector2f* pTex = (Vector2f*)((*pTexcoords)[0]);

	GeometryPtr MeshPtr = GeometryPtr( new GeometryDX11() );

	//for ( int i = 0; i < usVertexCount; i++ )
	//{
	//	pPos[i].x() = pMS3DVertices[i].vertex[0];
	//	pPos[i].y() = pMS3DVertices[i].vertex[1];
	//	pPos[i].z() = -pMS3DVertices[i].vertex[2];
	//	pNrm[i].MakeZero();
	//}

	TriangleIndices face;

	for ( int i = 0; i < usTriangleCount; i++ )
	{

		face.i1 = 3*i+0;
		face.i2 = 3*i+2;
		face.i3 = 3*i+1;

		pPos[3*i+0].x = pMS3DVertices[pMS3DTriangles[i].vertexIndices[0]].vertex[0];
		pPos[3*i+0].y = pMS3DVertices[pMS3DTriangles[i].vertexIndices[0]].vertex[1];
		pPos[3*i+0].z = -pMS3DVertices[pMS3DTriangles[i].vertexIndices[0]].vertex[2];
		pPos[3*i+1].x = pMS3DVertices[pMS3DTriangles[i].vertexIndices[1]].vertex[0];
		pPos[3*i+1].y = pMS3DVertices[pMS3DTriangles[i].vertexIndices[1]].vertex[1];
		pPos[3*i+1].z = -pMS3DVertices[pMS3DTriangles[i].vertexIndices[1]].vertex[2];
		pPos[3*i+2].x = pMS3DVertices[pMS3DTriangles[i].vertexIndices[2]].vertex[0];
		pPos[3*i+2].y = pMS3DVertices[pMS3DTriangles[i].vertexIndices[2]].vertex[1];
		pPos[3*i+2].z = -pMS3DVertices[pMS3DTriangles[i].vertexIndices[2]].vertex[2];

		pNrm[3*i+0].x = pMS3DTriangles[i].vertexNormals[0][0];
		pNrm[3*i+0].y = pMS3DTriangles[i].vertexNormals[0][1];
		pNrm[3*i+0].z = -pMS3DTriangles[i].vertexNormals[0][2];
		pNrm[3*i+1].x = pMS3DTriangles[i].vertexNormals[1][0];
		pNrm[3*i+1].y = pMS3DTriangles[i].vertexNormals[1][1];
		pNrm[3*i+1].z = -pMS3DTriangles[i].vertexNormals[1][2];
		pNrm[3*i+2].x = pMS3DTriangles[i].vertexNormals[2][0];
		pNrm[3*i+2].y = pMS3DTriangles[i].vertexNormals[2][1];
		pNrm[3*i+2].z = -pMS3DTriangles[i].vertexNormals[2][2];

		pTex[3*i+0].x = pMS3DTriangles[i].s[0];
		pTex[3*i+0].y = pMS3DTriangles[i].t[0];
		pTex[3*i+1].x = pMS3DTriangles[i].s[1];
		pTex[3*i+1].y = pMS3DTriangles[i].t[1];
		pTex[3*i+2].x = pMS3DTriangles[i].s[2];
		pTex[3*i+2].y = pMS3DTriangles[i].t[2];

		MeshPtr->AddFace( face );
	}

	for ( int i = 0; i < usVertexCount; i++ )
	{
		pNrm[i].Normalize();
	}

	MeshPtr->AddElement( pPositions );
	MeshPtr->AddElement( pTexcoords );
	MeshPtr->AddElement( pNormals );

	// Delete temporary materials
	if (pMS3DMaterials != NULL)
	{
		delete[] pMS3DMaterials;
		pMS3DMaterials = NULL;
	}

	// Delete temporary groups and their indices
	if (pMS3DGroups != NULL)
	{
		for (int i = 0; i < usGroupCount; i++)
		{
			if (pMS3DGroups[i].triangleIndices != NULL)
			{
				delete[] pMS3DGroups[i].triangleIndices;
				pMS3DGroups[i].triangleIndices = NULL;
			}
		}
		delete[] pMS3DGroups;
		pMS3DGroups = NULL;
	}

	// Delete temporary triangles
	if (pMS3DTriangles != NULL)
	{
		delete[] pMS3DTriangles;
		pMS3DTriangles = NULL;
	}

	// Delete temporary vertices
	if (pMS3DVertices != NULL)
	{
        delete[] pMS3DVertices;
		pMS3DVertices = NULL;
	}

	//MeshPtr->GenerateVertexDeclaration();
	//MeshPtr->LoadToBuffers();

	return( MeshPtr );
}

int GeometryLoaderDX11::FindAdjacentIndex( int edgeStart, int edgeEnd, int triV, int* pRaw, int rawLen)
{
	for(int f = 0; f < rawLen; f+=3)
	{
		int esIdx = -1;
		for( int i = 0; i < 3; ++i ) { if(pRaw[f+i]==edgeStart) esIdx = i; }

		int eeIdx = -1;
		for( int i = 0; i < 3; ++i ) { if(pRaw[f+i]==edgeEnd) eeIdx = i; }

		if((-1!=esIdx)&&(-1!=eeIdx))
		{
			int oIdx = -1;
			for(int i = 0; i < 3; ++i) { if((i!=esIdx) && (i!=eeIdx)) oIdx = i; }

			if(pRaw[f+oIdx]!=triV)
				return pRaw[f + oIdx];
		}
	}

	return edgeStart;
}

GeometryLoaderDX11::PlyElementDesc GeometryLoaderDX11::ParsePLYElementHeader(std::string headerLine, std::ifstream& input)
{
	GeometryLoaderDX11::PlyElementDesc desc;
	std::string txt;

	// Parse the header line
	// "element <name> <count>"
	int split = headerLine.find_first_of(' ', 8);
	desc.name = headerLine.substr(8, split - 8);
		
	split = headerLine.rfind( ' ' );
	std::istringstream elemCount(headerLine.substr(split, headerLine.length() - split));
	elemCount >> desc.elementCount;

	// Parse any attached properties
	while(input.is_open() && !input.eof())
	{
		std::getline( input, txt );

		if(0 == txt.compare(0, 13, "property list"))
		{
			// Parse this property list declaration
			desc.dataFormat.push_back(ParsePLYElementPropertyList(txt.substr(14, txt.length() - 14)));
		}
		else if(0 == txt.compare(0, 8, "property"))
		{
			// Parse this property declaration
			desc.dataFormat.push_back(ParsePLYElementProperty(txt.substr(9, txt.length() - 9)));
		}
		else
		{
			// At this point we'll also have read a line too far so
			// need to "unread" it to avoid breaking remaining parsing.
			input.putback('\n');
			for(int i = -1 + txt.length(); i >= 0; i--)
				input.putback(txt.at(i));
			// (there must be a better way, no?!?)
			break;
		}
	}

	return desc;
}

GeometryLoaderDX11::PlyElementPropertyDeclaration GeometryLoaderDX11::ParsePLYElementProperty(std::string desc)
{
	// <type> <name>
	GeometryLoaderDX11::PlyElementPropertyDeclaration decl;
	decl.isList = false;

	int split = desc.find(' ');

	decl.type = desc.substr(0, split);
	decl.name = desc.substr(split + 1, desc.length() - (split + 1));

	return decl;
}

GeometryLoaderDX11::PlyElementPropertyDeclaration GeometryLoaderDX11::ParsePLYElementPropertyList(std::string desc)
{
	// <length_type> <element_type> <name>
	GeometryLoaderDX11::PlyElementPropertyDeclaration decl;
	decl.isList = true;

	int split = desc.find(' ');
	decl.listLengthType = desc.substr(0, split);

	decl.type = desc.substr(split + 1, desc.rfind(' ') - (split + 1));

	split = desc.rfind(' ') + 1;
	decl.name = desc.substr(split, desc.length() - split);

	return decl;
}

std::vector<void**> GeometryLoaderDX11::ReadPLYElementData(std::ifstream& input, const GeometryLoaderDX11::PlyElementDesc& desc)
{
	std::vector<void**> raw;

	for(int i = 0; i < desc.elementCount; ++i)
	{
		std::string txt;
		std::getline(input, txt);

		raw.push_back(ParsePLYElementData(txt, desc.dataFormat));
	}

	return raw;
}

void** GeometryLoaderDX11::ParsePLYElementData(std::string text, const std::vector<PlyElementPropertyDeclaration>& desc)
{
	void** parsed;

	parsed = new void*[desc.size()];

	std::vector<std::string> tokens;
	std::istringstream is (text);
	std::string tmps;
    while (is.good()) {
        is >> tmps;
		tokens.push_back(tmps);
    }


	unsigned int e = 0;
	for(std::vector<std::string>::iterator it = tokens.begin(); it != tokens.end(); ++it)
	{
		if( e >= desc.size())
			break;

		if(desc[e].isList)
		{
			// Read this as length
			int arrLen = 0;

			arrLen = ExtractDataVal<int>(*it);

			// Size up the type
			if(0 == desc[e].type.compare("char"))
			{
				parsed[e] = ExtractDataPtrArray<char>(arrLen, it);
			}
			else if(0 == desc[e].type.compare("uchar"))
			{
				parsed[e] = ExtractDataPtrArray<unsigned char>(arrLen, it);
			}
			else if(0 == desc[e].type.compare("short"))
			{
				parsed[e] = ExtractDataPtrArray<short>(arrLen, it);
			}
			else if(0 == desc[e].type.compare("ushort"))
			{
				parsed[e] = ExtractDataPtrArray<unsigned short>(arrLen, it);
			}
			else if(0 == desc[e].type.compare("int"))
			{
				parsed[e] = ExtractDataPtrArray<int>(arrLen, it);
			}
			else if(0 == desc[e].type.compare("uint"))
			{
				parsed[e] = ExtractDataPtrArray<unsigned int>(arrLen, it);
			}
			else if(0 == desc[e].type.compare("float"))
			{
				parsed[e] = ExtractDataPtrArray<float>(arrLen, it);
			}
			else if(0 == desc[e].type.compare("double"))
			{
				parsed[e] = ExtractDataPtrArray<double>(arrLen, it);
			}
			else
			{
				// wtf?
			}
		}
		else
		{
			if(0 == desc[e].type.compare("char"))
			{
				parsed[e] = ExtractDataPtr<char>(*it);
			}
			else if(0 == desc[e].type.compare("uchar"))
			{
				parsed[e] = ExtractDataPtr<unsigned char>(*it);
			}
			else if(0 == desc[e].type.compare("short"))
			{
				parsed[e] = ExtractDataPtr<short>(*it);
			}
			else if(0 == desc[e].type.compare("ushort"))
			{
				parsed[e] = ExtractDataPtr<unsigned short>(*it);
			}
			else if(0 == desc[e].type.compare("int"))
			{
				parsed[e] = ExtractDataPtr<int>(*it);
			}
			else if(0 == desc[e].type.compare("uint"))
			{
				parsed[e] = ExtractDataPtr<unsigned int>(*it);
			}
			else if(0 == desc[e].type.compare("float"))
			{
				parsed[e] = ExtractDataPtr<float>(*it);
			}
			else if(0 == desc[e].type.compare("double"))
			{
				parsed[e] = ExtractDataPtr<double>(*it);
			}
			else
			{
				// wtf?
			}
		}

		++e;
	}

	return parsed;
}

template<typename T> T* GeometryLoaderDX11::ExtractDataPtr(std::string input)
{
	T* t = new T;

	std::istringstream iss(input);

	iss >> *t;

	return t;
}

template<typename T> T GeometryLoaderDX11::ExtractDataVal(std::string input)
{
	T t;

	std::istringstream iss(input);

	iss >> t;

	return t;
}

template<typename T> GeometryLoaderDX11::PlyDataArray<T>* GeometryLoaderDX11::ExtractDataPtrArray(int length, std::vector<std::string>::iterator iterator)
{
	PlyDataArray<T>* t = new PlyDataArray<T>;
	t->length = length;
	t->data = new T[length];

	for(int i = 0; i < length; ++i)
	{
		std::istringstream iss(*(++iterator));
		iss >> t->data[i];
	}

	return t;
}



int GeometryLoaderDX11::FindPlyElementIndex(std::vector<PlyElementDesc> elems, std::string name)
{
	for(unsigned int idx = 0; idx < elems.size(); ++idx)
		if(0 == elems.at(idx).name.compare(name))
			return idx;

	return -1;
}

int GeometryLoaderDX11::FindPlyElementPropertyIndex(std::vector<PlyElementPropertyDeclaration> elems, std::string name)
{
	for(unsigned int idx = 0; idx < elems.size(); ++idx)
		if(0 == elems.at(idx).name.compare(name))
			return idx;

	return -1;
}