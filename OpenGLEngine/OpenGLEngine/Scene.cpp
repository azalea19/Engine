#include "Scene.h"

void Scene::render(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
  for (int i = 0; i < agents.size(); i++)
  {
    agents[i]->render(viewMatrix, projectionMatrix);
  }
}

int Scene::update(vec3 position)
{
	for (int i = 0; i < agents.size(); i++)
	{
		agents[i]->Update();
	}

	return isColliding(position);
}


int Scene::isColliding(vec3 position)
{
	Object player;
	AABoundingBox playerBox;

	bool isColliding = false;
	bool isClimbable = false;


	playerBox.min.x = position.x - 50;
	playerBox.min.y = position.y - 448;
	playerBox.min.z = position.z - 50;

	playerBox.max.x = position.x + 50;
	playerBox.max.y = position.y + 1;
	playerBox.max.z = position.z + 50;

	for (int i = 0; i < collisionObjects.size(); i++)
	{
		if (collisionObjects[i].Intersects(playerBox))
		{
			if (collisionObjects[i].climbable)
			{
				isClimbable = true;
			}
			isColliding = true;

			printf("Collision occured.\n");
		}
	}

	if (isColliding)
	{
		if (isClimbable)
		{
			return climbable;
		}
		else
			return colliding;
	}
	else
		return notColliding;
}

void Scene::addAgent(Agent* agent)
{
  agents.push_back(agent);
}

void Scene::generateCollisionObjects()
{
	for (int i = 0; i < agents.size(); i++)
	{
		
		for (int j = 0; j < agents[i]->SubObjectCount(); j++)
		{
			Object obj;
			std::vector<vec3> subVerts = agents[i]->getVerticies(j);
			
			obj.climbable = agents[i]->isClimbable(j);

			for (int f = 0; f < subVerts.size() / 3; f++)
			{
				float minX = FLT_MAX;
				float minY = FLT_MAX;
				float minZ = FLT_MAX;

				float maxX = -FLT_MAX;
				float maxY = -FLT_MAX;
				float maxZ = -FLT_MAX;

				for (int k = 0; k < 3; k++)
				{
					minX = mMin(minX, subVerts[f*3 + k].x);
					minY = mMin(minY, subVerts[f*3 + k].y);
					minZ = mMin(minZ, subVerts[f*3 + k].z);
											
					maxX = mMax(maxX, subVerts[f*3 + k].x);
					maxY = mMax(maxY, subVerts[f*3 + k].y);
					maxZ = mMax(maxZ, subVerts[f*3 + k].z);
				}
				obj.AddBox(AABoundingBox{ vec3(minX, minY, minZ), vec3(maxX, maxY, maxZ) });
			}
			obj.CalculateBoundingBox();
			collisionObjects.push_back(obj);
		}
		
	}
}

std::vector<Object> Scene::GetCollisionObjects()
{
	return collisionObjects;
}