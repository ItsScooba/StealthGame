#pragma once



#include <string>
#include <memory>

#include "GUI_Widget.h"

#include "Mesh.h"










//Class used to represent 
class Cursor : public GUI_Widget
{
public:


	Cursor();
	~Cursor();

	void Tick();

	bool SetTexture( std::string cursorTextureID );
	void OnDraw();


private:


	int m_cursorPositionX, m_cursorPositionY;
	std::shared_ptr< Mesh > m_mesh;


public:


	const int& GetPositionX() { return m_cursorPositionX; }
	const int& GetPositionY() { return m_cursorPositionY; }


};