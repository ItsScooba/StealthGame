#pragma once



#include <vector>
#include <map>
#include <string>
#include <memory>

#include <glm\glm.hpp>

#include "MaterialParameters.h"





typedef std::pair< glm::vec3, glm::vec3 > socket_transform;








class AnimationPose
{
public:


	AnimationPose();
	~AnimationPose();


public:


	std::vector < std::shared_ptr< BaseMaterialParameter > > material_parameters;
	std::map< std::string, socket_transform > socket_transforms;


};