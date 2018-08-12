#pragma once

#include "Node3D.h"
#include "Entity3D.h"

class Actor
{
public:
	Actor();
	virtual ~Actor();

	Node3D* GetNode() const;
	Node3D* GetNode();
	Entity3D* GetBody() const;
	Entity3D* GetBody();


	void AddElement( Entity3D* pElement );
	void RemoveElement( Entity3D* pElement );
	void AddElement( Node3D* pElement );
	void RemoveElement( Node3D* pElement );

	//void AddSubtree( Node3D* pNode );
	//void RemoveSubtree( Node3D* pNode );

protected:
	Node3D*					m_pRoot;
	Entity3D*				m_pBody;

	std::vector<Entity3D*>	m_EntityElements;
	std::vector<Node3D*>	m_NodeElements;
};