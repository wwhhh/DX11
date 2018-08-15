#pragma once

#include "RendererDX11.h"
#include "PipelineManagerDX11.h"
#include "IParameterManager.h"

class Task
{

public:
	Task( );
	virtual ~Task( );

	// ���»��Ƶķ������ṩһ��ʱ�����
    // �����ڴ˴�����
    // ���Ʒ�����Ҫ������Ⱦ״̬�ͻ���ͼ��
	virtual void Update( float fTime ) = 0;
	virtual void QueuePreTasks( RendererDX11* pRenderer ) = 0;
	virtual void ExecuteTask( PipelineManagerDX11* pPipelineManager, IParameterManager* pParamManager ) = 0;

	// ��Ⱦ��ͼ��Ҫ���������õ�����Ⱦ����
	// SetUsageParams ������������Ҫ��ʹ�õ� render view �������������
	virtual void SetRenderParams( IParameterManager* pParamManager ) = 0;
	virtual void SetUsageParams( IParameterManager* pParamManager ) = 0;

	virtual std::wstring GetName( ) = 0;
};