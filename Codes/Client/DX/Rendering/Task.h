#pragma once

#include "RendererDX11.h"
#include "PipelineManagerDX11.h"
#include "IParameterManager.h"

class Task
{

public:
	Task( );
	virtual ~Task( );

	// 更新绘制的方法，提供一个时间参数
    // 动画在此处更新
    // 绘制方法需要设置渲染状态和绘制图形
	virtual void Update( float fTime ) = 0;
	virtual void QueuePreTasks( RendererDX11* pRenderer ) = 0;
	virtual void ExecuteTask( PipelineManagerDX11* pPipelineManager, IParameterManager* pParamManager ) = 0;

	// 渲染视图需要设置所有用到的渲染参数
	// SetUsageParams 是用来设置需要被使用的 render view 的输出的语义名
	virtual void SetRenderParams( IParameterManager* pParamManager ) = 0;
	virtual void SetUsageParams( IParameterManager* pParamManager ) = 0;

	virtual std::wstring GetName( ) = 0;
};