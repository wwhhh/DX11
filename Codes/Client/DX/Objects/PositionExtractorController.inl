
template <typename T>
PositionExtractorController<T>::PositionExtractorController() :
	m_pWriter( nullptr )
{
}

template <typename T>
PositionExtractorController<T>::~PositionExtractorController()
{
}

template <typename T>
void PositionExtractorController<T>::Update( float fTime )
{
	// If there is an entity and a writer set, then 
	// set in this controller.

	if ( nullptr != IController<T>::m_pEntity && nullptr != m_pWriter )
	{
		Vector3f WorldPosition = IController<T>::m_pEntity->Transform.LocalPointToWorldSpace(IController<T>::m_pEntity->Transform.Position() );
		m_pWriter->SetValue( Vector4f( WorldPosition, 1.0f ) );
	}
}

template <typename T>
void PositionExtractorController<T>::SetParameterWriter( VectorParameterWriterDX11* pWriter )
{
	m_pWriter = pWriter;
}