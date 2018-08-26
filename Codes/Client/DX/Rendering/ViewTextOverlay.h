#pragma once

#include "Task.h"
#include "SpriteFontLoaderDX11.h"
#include "SpriteRendererDX11.h"

class Entity3D;

struct TextEntry
{
	std::wstring text;
	Matrix4f xform;
	Vector4f color;
	TextEntry() {};
	TextEntry( std::wstring& text, Matrix4f& xform, Vector4f& color )
	{
		this->text = text;
		this->xform = xform;
		this->color = color;
	};
};

class ViewTextOverlay : public Task
{
public:
	ViewTextOverlay( RendererDX11& Renderer, ResourcePtr RenderTarget );
	virtual ~ViewTextOverlay();

	virtual void Update( float fTime );
	virtual void QueuePreTasks( RendererDX11* pRenderer );
	virtual void ExecuteTask( PipelineManagerDX11* pPipelineManager, IParameterManager* pParamManager );
	virtual void Resize( UINT width, UINT height );

	virtual void SetRenderParams( IParameterManager* pParamManager );
	virtual void SetUsageParams( IParameterManager* pParamManager );

	void WriteText( std::wstring& text, Matrix4f& xform, Vector4f& color );

	virtual std::wstring GetName();

protected:
	Vector4f				m_vColor;
	int						m_iViewport;

	ResourcePtr				m_RenderTarget;

	SpriteFontPtr			m_pSpriteFont;
	SpriteRendererDX11*		m_pSpriteRenderer;
	
	std::vector<TextEntry>	m_TextEntries;
};