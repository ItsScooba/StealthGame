#pragma once








#include "I_System.h"

#include "AI_Component.h"









//System used for updating and maintaining any AI Components and the objects they control.
class AI_System : public I_System
{
public:



	AI_System();
	~AI_System();

	bool Initialize();
	void Shutdown();

	void Update( const float& deltaTime );



private:


	void OnEntitySpawned( std::shared_ptr< I_Event > spawnEvent );
	void OnEntityDestroyed( std::shared_ptr< I_Event > destroyEvent );


private:


	std::vector< std::shared_ptr< AI_Component > > m_aiComponents;


};