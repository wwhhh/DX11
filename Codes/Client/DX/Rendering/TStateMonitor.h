#pragma once

template <class T>
class TStateMonitor
{
public:
	TStateMonitor( T initialState );
	~TStateMonitor();

	void SetSister( TStateMonitor<T>* pSister );
	bool SameAsSister();

	void SetState( T state );
	T GetState() const;

	bool IsUpdateNeeded();
	void InitializeState();
	void ResetTracking();

private:

	// The monitoring varaibles
	bool m_bUploadNeeded;

	// The state data
	T m_InitialState;
	T m_State;

	// The sister state
	TStateMonitor<T>* m_pSister;
};

#include "TStateMonitor.inl"