#include "stdafx.h"

CollisionManager::CollisionManager(float x, float y ,  float sx, float sy, String pathTag, Vector2 front, Vector2 side, Vector2 behind) {

	SetLayer(4);
	SetPosition(x, y);
	SetSize(sx, sy);
	SetShapeType(PhysicsActor::SHAPETYPE_BOX);
	SetColor(1.0f, 0.0f, 0.0f, 0.0f);
	SetDensity(0.0f);
	SetFriction(0.0f); 
	SetRestitution(0.1f);
	InitPhysics();

	_side = side;			 //Punkt lewy albo prawy
	_behind = behind;		 //Punkt za obiektem
	_front = front;			 //Punkt na przeciwko
	
	AddTags(pathTag);
}

void CollisionManager::AddTags(String pathTag) {

	std::vector<String> tags;
	std::fstream file;
	file.open(pathTag, std::ios::in);

	if( file.good() ) {
		
		String tag;

		while ( !file.eof() ) {

			getline(file, tag);
			tags.push_back(tag);

		}
		
		file.close();
	
	}	
	
	else std::cout << "Err! file : " << pathTag << " not found."  << std::endl;

	SetName(tags[0]);

	for (int i = 0; i < tags.size(); i++) {
		
		Tag(tags[i]);

	}

}


CollisionManager::~CollisionManager(void)
{
}
