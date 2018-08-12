#include "PCH.h"
#include "DXGIOutput.h"

DXGIOutput::DXGIOutput( Microsoft::WRL::ComPtr<IDXGIOutput> pOutput )
{
	m_pOutput = pOutput;
}

DXGIOutput::~DXGIOutput()
{
}