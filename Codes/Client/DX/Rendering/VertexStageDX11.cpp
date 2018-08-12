#include "PCH.h"
#include "VertexStageDX11.h"
#include "VertexShaderDX11.h"
#include "RendererDX11.h"

VertexStageDX11::VertexStageDX11()
{
}

VertexStageDX11::~VertexStageDX11()
{
}

ShaderType VertexStageDX11::GetType()
{
	return( VERTEX_SHADER );
}

void VertexStageDX11::BindShaderProgram( ID3D11DeviceContext* pContext )
{
	RendererDX11* pRenderer = RendererDX11::Get();
	ShaderDX11* pShaderDX11 = pRenderer->GetShader( DesiredState.ShaderProgram.GetState() );

	ID3D11VertexShader* pShader = 0;
		
	if ( pShaderDX11 ) {
		pShader = reinterpret_cast<VertexShaderDX11*>( pShaderDX11 )->m_pVertexShader;
	}

	pContext->VSSetShader( pShader, 0, 0 );
}

void VertexStageDX11::BindConstantBuffers( ID3D11DeviceContext* pContext, int count )
{
	pContext->VSSetConstantBuffers( 
		DesiredState.ConstantBuffers.GetStartSlot(),
		DesiredState.ConstantBuffers.GetRange(),
		DesiredState.ConstantBuffers.GetFirstSlotLocation() );
}

void VertexStageDX11::BindSamplerStates( ID3D11DeviceContext* pContext, int count )
{
	pContext->VSSetSamplers( 
		DesiredState.SamplerStates.GetStartSlot(),
		DesiredState.SamplerStates.GetRange(),
		DesiredState.SamplerStates.GetFirstSlotLocation() );
}

void VertexStageDX11::BindShaderResourceViews( ID3D11DeviceContext* pContext, int count )
{
	pContext->VSSetShaderResources( 
		DesiredState.ShaderResourceViews.GetStartSlot(),
		DesiredState.ShaderResourceViews.GetRange(),
		DesiredState.ShaderResourceViews.GetFirstSlotLocation() ); 
}

void VertexStageDX11::BindUnorderedAccessViews( ID3D11DeviceContext* pContext, int count )
{
	// Do nothing - the vertex shader doesn't support UAV's!
}