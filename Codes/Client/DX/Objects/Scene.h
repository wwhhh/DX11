#pragma once

#include "Camera.h"
#include "Node3D.h"
#include "Entity3D.h"

class Scene {
public:
    Scene();
    virtual ~Scene();

    virtual void Update(float time);
    virtual void PreRender(RendererDX11* pRenderer, VIEWTYPE type);
    virtual void Render(RendererDX11* Renderer);

    void AddCamera(Camera* camera);
    Camera* GetCamera(unsigned int index);
    unsigned int GetCameraCount();

    void AddActor(Actor* actor);
    void RemoveActor(Actor* actor);

    Node3D* GetRoot();

public:
    ParameterContainer Parameters;

protected:
    Node3D * m_pRoot;
    std::vector< Camera* > m_vCameras;
    std::vector< Actor* > m_vActors;
};