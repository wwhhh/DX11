#pragma once

struct LineIndices
{
	LineIndices();
	LineIndices( unsigned int I1, unsigned int I2 );
	~LineIndices();

	LineIndices& operator= ( const LineIndices& Line );

	void swap12( );

	unsigned int i1;
	unsigned int i2;
};