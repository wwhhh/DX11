#include "PCH.h"
#include "Camera.h"
//#include "Scene.h"
#include "ViewPortDX11.h"

Camera::Camera() :
	m_pCameraView( nullptr ),
	m_pOverlayView( nullptr ),
	m_pScene( nullptr ),
	m_fNear( 0.1f ),
	m_fFar( 100.0f ),
	m_fAspect( 1280.0f / 800.0f ),
	m_fFov( static_cast<float>( MATHS_PI ) / 4.0f ),
	m_fWidth( 1280.0f ),
	m_fHeight( 800.0f ),
	m_ProjMatrix(),
	m_pViewPositionWriter( nullptr ),
	m_pSpatialController( nullptr )
{
	// 空间控制器
	m_pSpatialController = new SpatialController<Node3D>();
	GetNode()->Controllers.Attach( m_pSpatialController );

    m_ProjMatrix.MakeIdentity();

	m_pViewPositionWriter = Parameters.SetVectorParameter( L"ViewPosition", Vector4f( 0.0f, 0.0f, 0.0f, 0.0f ) );
}

Camera::~Camera()
{
	SAFE_DELETE( m_pOverlayView );
}

void Camera::RenderFrame( RendererDX11* pRenderer )
{
	if ( m_pOverlayView )
		pRenderer->QueueTask( m_pOverlayView );

    if (m_pCameraView)
    {
        Vector3f p = GetBody()->Transform.LocalPointToWorldSpace(Vector3f(0.0f, 0.0f, 0.0f));
        m_pViewPositionWriter->SetValue(Vector4f(p.x, p.y, p.z, 1.0f));

        Parameters.InitRenderParams();

        //m_pCameraView->SetViewMatrix(m_ViewMatrix);

        // 设置场景节点
        if (m_pScene) {
            m_pCameraView->SetScene(m_pScene);
        }

        // 加入渲染队列
        m_pCameraView->QueuePreTasks(pRenderer);
        // 处理渲染队列
        pRenderer->ProcessTaskQueue();
    }
}

void Camera::SetCameraView(SceneRenderTask* pTask)
{
    m_pCameraView = pTask;
    m_pCameraView->SetEntity(m_pBody);
}

void Camera::SetOverlayView( Task* pTask )
{
	m_pOverlayView = pTask;
}

void Camera::SetScene( Scene* pScene )
{
	m_pScene = pScene;
}

Task* Camera::GetOverlayView()
{
	return( m_pOverlayView );
}

Scene* Camera::GetScene()
{
	return( m_pScene );
}

void Camera::SetProjectionParams( float zn, float zf, float aspect, float fov )
{
	m_fNear = zn;
	m_fFar = zf;
	m_fAspect = aspect;
	m_fFov = fov;

	ApplyProjectionParams();
}

void Camera::SetOrthographicParams( float zn, float zf, float width, float height )
{
	m_fNear = zn;
	m_fFar = zf;
	m_fWidth = width;
	m_fHeight = height;

	ApplyOrthographicParams();
}

void Camera::SetClipPlanes( float zn, float zf )
{
	m_fNear = zn;
	m_fFar = zf;

	ApplyProjectionParams();
}

void Camera::SetAspectRatio( float aspect )
{
	m_fAspect = aspect;

	ApplyProjectionParams();
}

void Camera::SetFieldOfView( float fov )
{
	m_fFov = fov;

	ApplyProjectionParams();
}

float Camera::GetNearClipPlane()
{
	return( m_fNear );
}

float Camera::GetFarClipPlane()
{
	return( m_fFar );
}

float Camera::GetAspectRatio()
{
	return( m_fAspect );
}

float Camera::GetFieldOfView()
{
	return( m_fFov );
}

void Camera::ApplyProjectionParams()
{
	m_ProjMatrix = Matrix4f::PerspectiveFovLHMatrix( m_fFov, m_fAspect, m_fNear, m_fFar );
 
    if (m_pCameraView)
        m_pCameraView->SetProjMatrix(m_ProjMatrix);
}

void Camera::ApplyOrthographicParams()
{
	m_ProjMatrix = Matrix4f::OrthographicLHMatrix( m_fNear, m_fFar, m_fWidth, m_fHeight );

    if (m_pCameraView)
        m_pCameraView->SetProjMatrix(m_ProjMatrix);
}

const Matrix4f& Camera::ProjMatrix() const
{
    return( m_ProjMatrix );
}

const Matrix4f& Camera::ViewMatrix()
{
    float cosY, cosP, cosR;
    float sinY, sinP, sinR;

    Vector3f rotation = Spatial().GetRotation();

    cosP = cosf(rotation.x);
    sinP = sinf(rotation.x);
    cosY = cosf(rotation.y);
    sinY = sinf(rotation.y);
    cosR = cosf(rotation.z);
    sinR = sinf(rotation.z);

    Vector3f Fwd;
    Fwd.x = sinY * cosR;
    Fwd.y = sinP;
    Fwd.z = cosP * cosY;
    
    Vector3f Eye;
    Vector3f At;
    Vector3f Up;

    Eye = Spatial().GetTranslation();
    At = Spatial().GetTranslation() + Fwd;
    Up = Vector3f(0.0f, 1.0f, 0.0f);

    m_ViewMatrix = (Matrix4f::LookAtLHMatrix(Eye, At, Up));
    
    //return m_ViewMatrix;

    return Spatial().GetEntity()->Transform.GetView();
}

SpatialController<Node3D>& Camera::Spatial()
{
	return( *m_pSpatialController );
}

bool Camera::HandleEvent( EventPtr pEvent )
{
    eEVENT e = pEvent->GetEventType();
	
    return false;
}

std::wstring Camera::GetName()
{
    return( L"Camera" );
}