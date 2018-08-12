#pragma once

#include "Actor.h"
#include "SpatialController.h"
#include "Rendering/ParameterContainer.h"
#include "Events/IEventListener.h"

class Scene;

class Camera : public Actor, public IEventListener
{
public:
	Camera();
	virtual ~Camera();

	void SetOverlayView( Task* pTask );
	void SetScene( Scene* pScene );

	Task* GetOverlayView();
	Scene* GetScene();

	void RenderFrame( RendererDX11* pRenderer );

	void SetProjectionParams( float zn, float zf, float aspect, float fov );
	void SetOrthographicParams( float zn, float zf, float width, float height );

	void SetClipPlanes( float zn, float zf );
	void SetAspectRatio( float aspect );
	void SetFieldOfView( float fov );

	float GetNearClipPlane();
	float GetFarClipPlane();
	float GetAspectRatio();
	float GetFieldOfView();

	SpatialController<Node3D>& Spatial();
	const Matrix4f& ProjMatrix() const;
    const Matrix4f& ViewMatrix();

    virtual bool HandleEvent( EventPtr pEvent );
    virtual std::wstring GetName();

	ParameterContainer Parameters;

protected:

	void ApplyProjectionParams();
	void ApplyOrthographicParams();

	Task* m_pOverlayView;
	Scene* m_pScene;

	float m_fNear;
	float m_fFar;
	float m_fAspect;
	float m_fFov;

	float m_fWidth;
	float m_fHeight;

    Matrix4f m_ProjMatrix;
    Matrix4f m_ViewMatrix;
	VectorParameterWriterDX11* m_pViewPositionWriter;
	SpatialController<Node3D>*	m_pSpatialController;
};