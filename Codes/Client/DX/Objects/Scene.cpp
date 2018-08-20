#include "PCH.h"
#include "Scene.h"
#include "SceneGraph.h"

Scene::Scene()
{
    m_pRoot = new Node3D();
}

Scene::~Scene()
{
    for (auto pActor : m_vActors) {
        SAFE_DELETE(pActor);
    }

    delete m_pRoot;
}

Node3D* Scene::GetRoot()
{
    return(m_pRoot);
}

void Scene::Update(float time)
{
    m_pRoot->Update(time);
}

void Scene::Render(RendererDX11* pRenderer)
{
    // 渲染所在位置!  每一个相机渲染各自的视图
    for (auto pCamera : m_vCameras)
    {
        Parameters.InitRenderParams();
        pCamera->RenderFrame(pRenderer);
    }
}

void Scene::PreRender(RendererDX11* pRenderer, VIEWTYPE type)
{
    m_pRoot->PreRender(pRenderer, type);
}

void Scene::AddCamera(Camera* camera)
{
    m_vCameras.push_back(camera);
    camera->SetScene(this);
    AddActor(camera);
}

Camera* Scene::GetCamera(unsigned int index)
{
    assert(index < m_vCameras.size());
    return(m_vCameras[index]);
}

unsigned int Scene::GetCameraCount()
{
    return(m_vCameras.size());
}

void Scene::AddActor(Actor* actor)
{
    // 将 actor 与 rootNode 连接起来
    m_pRoot->AttachChild(actor->GetNode());
    // 加入场景 actors 中
    m_vActors.push_back(actor);
}

void Scene::RemoveActor(Actor* pActor)
{
    // 遍历从场景中移除
    auto it = m_vActors.begin();

    while (it != m_vActors.end()) {
        if (*it == pActor)
            it = m_vActors.erase(it);
        else
            it++;
    }

    // 获取父节点，并从父类中移除
    Node3D* pParent = static_cast<Node3D*>(pActor->GetNode()->GetParent());
    if (pParent) pParent->DetachChild(pActor->GetNode());
}

void Scene::AddLight(Light* light)
{
    AddActor(light);
    m_vLights.push_back(light);
}

Light* Scene::GetLight(unsigned int index)
{
    if (m_vLights.size() > index)
    {
        return m_vLights[index];
    }

    return 0;
}

unsigned int Scene::GetLightCount()
{
    return(m_vLights.size());
}