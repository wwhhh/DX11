#include "PCH.h"
#include "Renderable.h"

Renderable::Renderable() :
    iPass(GEOMETRY),
    Executor(nullptr),
    Material(nullptr)
{
}

Renderable::~Renderable()
{
    Executor = nullptr;
    Material = nullptr;
}

void Renderable::SetMaterial(MaterialPtr pMaterial)
{
    Material = pMaterial;

    // ��ѯ���е� vertex shader ���� executor Ԥ�ȴ�������

    if (Material != nullptr && Executor != nullptr)
    {
        std::vector<int> idlist;
        Material->GetAllVertexShaderIDs(idlist);

        for (auto ID : idlist) {
            Executor->GenerateInputLayout(ID);
        }
    }
}

MaterialPtr Renderable::GetMaterial()
{
    return(Material);
}

void Renderable::SetGeometry(ExecutorPtr pExecutor)
{
    Executor = pExecutor;

    // ��ѯ���е� vertex shader ���� executor Ԥ�ȴ�������

    if (Material != nullptr && Executor != nullptr)
    {
        std::vector<int> idlist;
        Material->GetAllVertexShaderIDs(idlist);

        for (auto ID : idlist) {
            Executor->GenerateInputLayout(ID);
        }
    }
}

ExecutorPtr Renderable::GetGeometry()
{
    return(Executor);
}