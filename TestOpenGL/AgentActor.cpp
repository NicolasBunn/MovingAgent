#include "AgentActor.h"

AgentActor::AgentActor(const glm::vec3 color_, const bool visibleTarget)
	:position(glm::vec2(0.0f, 0.0f)), rotation(0.0f), transform(glm::mat4(1.0f)), nearestTargetActor(glm::vec2(0.0f, 0.0f)),
	acceleration(0.0f), velocity(glm::vec2(0.0f, 0.0f)), currentTime(limitWandering), color(color_), state(0), currentWayPoint(-1)
	, visibleTargetVector(visibleTarget), typeCollisionActor(0), previousState(-1), targetPoint(glm::vec2(0.0f, 0.0f)), turnTimeAvoidingWall(0.0f)
{

}

void AgentActor::InitBuffer()
{
	actor.InitBuffer();
	aim.InitBuffer();
}

void AgentActor::SetColor(const glm::vec3 color_)
{
	color = color_;
}

std::string AgentActor::GetStateLabel(const int id) const
{
	switch (id)
	{
	case 0:
		return "Idle";
		break;

	case 1:
		return "Wander";
		break;

	case 2:
		return "Go to Player";
		break;

	case 3:
		return "Pursuit";
		break;

	case 4:
		return "Follow Path";
		break;

	case 5:
		return "Flee";
		break;

	case 6:
		return "WallAvoidance";
		break;
	}
}

void  AgentActor::UpdateState(const float deltaTime, const AgentActor& target)
{
	switch (state)
	{
	case 1:
		Wander(deltaTime);
		break;

	case 2:
		//Seek(glm::vec2(0.458047867,0.106698513);
		//Seek(glm::vec2(-0.459240079, -0.179533243));
		Seek(target.position);
		break;

	case 3:
		Pursue(target);
		break;

	case 5:
		Flee(target);
		break;

	case 6:
		AvoidWall();
		break;

	}
}

void AgentActor::Update(const float deltaTime, const AgentActor& target)
{
	const float drag = 0.1f;

	UpdateState(deltaTime, target);

	transform = glm::mat4(1.0f);
	transform = glm::translate(transform, glm::vec3(position.x, position.y, 0.0f));
	transform = glm::scale(transform, glm::vec3(0.1f, 0.2f, 0.0f));
	transform = glm::rotate(transform, rotation, glm::vec3(0.0f, 0.0f, 1.0f));

	actor.transform = transform;
	aim.transform = transform;

	actorShader->SetMatrix("transform", transform);
	actorShader->SetVec3("color", color);
}

void AgentActor::Draw()
{
	glBindVertexArray(actor.vao);
	actor.Draw();

	if (visibleTargetVector)
	{
		glBindVertexArray(aim.vao);
		aim.Draw();
	}

}

void AgentActor::CreateShader(const char* vertexPath, const char* fragmentPath)
{
	actorShader = new Shader(vertexPath, fragmentPath);
}

float AgentActor::GetNewOrientation(const glm::vec2& v)
{
	if (v.length > 0)
	{
		return glm::atan(v.y, v.x);
	}

	return rotation;
}


void AgentActor::UpdatePosition(const glm::vec2& position_)
{
	position.x += position_.x;
	position.y += position_.y;

	CheckBorder();
}

void AgentActor::CheckBorder()
{
	if (position.y > 1.0f)
	{
		position.y = -0.9f;
	}
	else if (position.y < -1.0f)
	{
		position.y = 0.9f;
	}

	if (position.x > 1.0f)
	{
		position.x = -0.9f;
	}
	else if (position.x < -1.0f)
	{
		position.x = 0.9f;
	}
}

void AgentActor::UpdateAcceleration(float a)
{
	acceleration += a;
}

void AgentActor::UpdateAngle(float angle)
{
	rotation += angle;

	if (rotation > 6.3f || rotation < -6.3f)
	{
		rotation = 0.0f;
	}
}

void AgentActor::Wander(const float dt)
{
	if (currentTime <= 0.0f)
	{
		currentTime = limitWandering;
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> dis(0, 6.3);
		targetRotationWanders = dis(gen);
	}
	else
	{
		float distance = 10.0f;
		if (typeCollisionActor == 1)
		{
			distance = glm::distance(position, entityCollision.start);
		}
		if (distance < 0.2f)
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<> dis(0, 6.3);
			rotation = dis(gen);
			typeCollisionActor = 0;
			return;
		}
		else
		{
			float diffRotation = rotation - targetRotationWanders;
			if (glm::abs(diffRotation) > 1.0f)
			{
				if (diffRotation < 0)
				{
					rotation += 0.01f;
				}
				else
				{
					rotation -= 0.01f;
				}
			}
			else
			{
				position.x += 0.0005f *  glm::cos(rotation);
				position.y += 0.0005f *  glm::sin(rotation);

				CheckBorder();
			}
		}
	}
	currentTime -= dt;
}

void AgentActor::Align(const AgentActor& target)
{
	glm::vec2 vel = target.position - position;
	vel = glm::normalize(vel);

	float newOrientation = GetNewOrientation(vel);

	if (rotation <= newOrientation)
	{
		rotation += 0.005f;
	}
}

//A ameliorer
void AgentActor::Pursue(const AgentActor& target)
{
	const float ancitipationFactor = 0.4f;

	glm::vec2 anticipate = target.position;
	anticipate.x += ancitipationFactor * glm::cos(target.rotation);
	anticipate.y += ancitipationFactor * glm::sin(target.rotation);

	float distance = glm::distance(target.position, position);
	if (distance <= ancitipationFactor)
	{
		Seek(target.position);
	}
	else
	{
		Seek(anticipate);
	}
}

void AgentActor::AvoidWall()
{
	glm::vec2 pt1 = glm::vec2(100.0f, 100.0f);
	glm::vec2 pt2 = glm::vec2(0.0f, 0.0f);
	nearestTargetActor = pt1;
	typeCollisionActor = 0;

	Collision::LineCollision targetVector = GetTargetVector();

	if (Collision::Intersect2DLine(entityCollision, targetVector, pt1, pt2) == 1)
	{
		UpdateAngle(0.005f);
	}
	else
	{
		if (turnTimeAvoidingWall > 0)
		{
			UpdateAngle(0.005f);
			turnTimeAvoidingWall -= 0.01f;
		}
		else
		{
			
			int testCollision = 0;
			if (targetPoint.x == 0.0f && targetPoint.y == 0.0f)
			{
				targetPoint.x = (0.25) * position.x + 0.75 * GetTargetVector().direction.x;
				targetPoint.y = (0.25) * position.y + 0.75 * GetTargetVector().direction.y;
			}
			Seek(targetPoint);
		}
	}
}

void AgentActor::Seek(const glm::vec2 target)
{
	if (typeCollisionActor == 1)
	{
		previousState = state;
		state = 6;
		targetPoint = glm::vec2(0.0f, 0.0f);
		turnTimeAvoidingWall = 1.0f;
		return;
	}

	float distance = glm::distance(target, position);

	if (distance > 0.1f)
	{
		glm::vec2 vel = target - position;
		vel = glm::normalize(vel);

		position.x += 0.001f * vel.x;
		position.y += 0.001f * vel.y;

		float newOrientation = GetNewOrientation(vel);
		float diff = newOrientation - rotation;

		if (glm::abs(diff) > 0.01f)
		{
			if (rotation < newOrientation)
			{
				rotation += 0.01f;
			}
			else
			{
				rotation -= 0.01f;
			}
		}
	}
	else
	{
		if (state == 6)
		{
			state = previousState;
		}
	}
}

void AgentActor::Flee(const AgentActor& target)
{
	float distance = glm::distance(target.position, position);

	if (distance < 0.5f)
	{
		glm::vec2 vel = target.position - position;
		vel = glm::normalize(vel);

		position.x -= 0.001f * vel.x;
		position.y -= 0.001f * vel.y;

		float newOrientation = GetNewOrientation(vel);
		rotation = newOrientation;

		CheckBorder();
	}
}

void AgentActor::Separate(const AgentActor& target)
{
	const float decayCoeffictient = 0.0001f;
	const float threshold = 0.5f;

	glm::vec2 direction = target.position - position;
	float distance = glm::distance(target.position, position);

	if (distance < threshold)
	{
		float strength = decayCoeffictient / (distance * distance);
		direction = glm::normalize(direction);

		position.x -= 0.001f * direction.x;
		position.y -= 0.001f * direction.y;

		CheckBorder();
	}
}

void AgentActor::FollowPath(const glm::vec3* pathPoint, const int nbPoint)
{
	if (currentWayPoint == -1)
	{
		currentWayPoint = SelectNearestPoint(pathPoint, nbPoint);
	}
	else
	{
		float distance = glm::distance(position, glm::vec2(pathPoint[currentWayPoint].x, pathPoint[currentWayPoint].y));
		if (distance < 0.1f)
		{
			if (currentWayPoint < nbPoint)
			{
				currentWayPoint++;
			}
		}
		else
		{
			Seek(pathPoint[currentWayPoint]);
		}
	}
}

int AgentActor::SelectNearestPoint(const glm::vec3* pathPoint, const int nbpoint)
{
	float distance = 10;
	int selectId = -1;

	for (int i = 0; i < nbpoint; i++)
	{
		float computeDistance = glm::distance(position, glm::vec2(pathPoint[i].x, pathPoint[i].y));

		if (computeDistance < distance)
		{
			distance = computeDistance;
			selectId = i;
		}
	}

	return selectId;
}

Collision::LineCollision AgentActor::GetTargetVector() const
{
	Collision::LineCollision l;
	glm::vec4 a = glm::vec4(aim.vertices[0], aim.vertices[1], aim.vertices[2], 1.0f);
	glm::vec4 b = glm::vec4(aim.vertices[3], aim.vertices[4], aim.vertices[5], 1.0f);

	a = transform * a;
	b = transform * b;

	l.start = glm::vec3(a.x, a.y, a.z);
	l.direction = glm::vec3(b.x, b.y, b.z);

	return l;
}

Collision::LineCollision* AgentActor::GetEntityCollision() const
{
	Collision::LineCollision* l = new Collision::LineCollision[3];

	glm::vec4 a = glm::vec4(actor.vertices[0], actor.vertices[1], actor.vertices[2], 1.0f);
	glm::vec4 b = glm::vec4(actor.vertices[3], actor.vertices[4], actor.vertices[5], 1.0f);
	glm::vec4 c = glm::vec4(actor.vertices[6], actor.vertices[7], actor.vertices[8], 1.0f);

	a = transform * a;
	b = transform * b;
	c = transform * c;

	Collision::LineCollision l1;
	Collision::LineCollision l2;
	Collision::LineCollision l3;

	glm::vec3 vec3A = glm::vec3(a.x, a.y, a.z);
	glm::vec3 vec3B = glm::vec3(b.x, b.y, b.z);
	glm::vec3 vec3C = glm::vec3(c.x, c.y, c.z);

	l1.start = vec3A;
	l1.direction = vec3B;

	l2.start = vec3B;
	l2.direction = vec3C;

	l3.start = vec3A;
	l3.direction = vec3C;

	l[0] = l1;
	l[1] = l2;
	l[2] = l3;

	return l;
}

void AgentActor::UpdateNearestCollision(const glm::vec2 targetPosition, const int type, const Collision::LineCollision& entity)
{
	float distanceCurrent = glm::distance(position, nearestTargetActor);
	float distanceNewTarget = glm::distance(position, targetPosition);

	if (distanceCurrent > distanceNewTarget)
	{
		nearestTargetActor = targetPosition;
		typeCollisionActor = type;
		entityCollision = entity;
	}
}

void AgentActor::CheckCollision(Collision::LineCollision* entity, const int type)
{
	nearestTargetActor = glm::vec2(100, 100);
	glm::vec2 pt1 = glm::vec2(100.0f, 100.0f);
	glm::vec2 pt2 = glm::vec2(0.0f, 0.0f);
	if (Collision::IntersectQuadLine(entity, GetTargetVector(), pt1, pt2) == 1)
	{
		float distance = glm::distance(position, pt1);
		if (distance < 0.3f)
		{
			UpdateNearestCollision(pt1, type, *entity);
		}
		Collision::IntersectQuadLine(entity, GetTargetVector(), pt1, pt2);
	}
}

