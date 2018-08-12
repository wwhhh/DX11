#pragma once

class TriangleIndices
{
public:
	TriangleIndices();
	TriangleIndices( unsigned int P1, unsigned int P2, unsigned int P3 );
	~TriangleIndices();

	void swap12( );
	void swap23( );
	void swap31( );

	unsigned int i1;
	unsigned int i2;
	unsigned int i3;
};