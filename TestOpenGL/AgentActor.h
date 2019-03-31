#pragma once

#include <random>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Triangle.h"
#include "Line.h"
#include "Collision.h"

class AgentActor
{
public:
	AgentActor(const glm::vec3 color_ = glm::vec3(0.0f, 0.0f, 0.0f), const bool visibleTarget = false);

	const float limitWandering = 0.5f;

	void InitBuffer();
	void Update(const float deltaTime, const AgentActor& target);
	void Draw();

	void UpdatePosition(const glm::vec2& position_);
	void UpdateAngle(float angle);
	void UpdateAcceleration(float a);
	void UpdateNearestCollision(const glm::vec2 targetPosition, const int type, const Collision::LineCollision& entity);

	void CreateShader(const char* vertexPath, const char* fragmentPath);

	float GetNewOrientation(const glm::vec2& v);

	void Align(const AgentActor& target);
	void Seek(const glm::vec2 target);
	void Flee(const AgentActor& target);
	void Wander(const float dt);
	void Pursue(const AgentActor& target);
	void FollowPath(const glm::vec3* pathPoint, const int nbPoint);
	void Separate(const AgentActor& target);
	void CheckBorder();
	void AvoidWall();

	void SetColor(const glm::vec3 color_);
	void UpdateState(const float deltaTime, const AgentActor& target);
	int  SelectNearestPoint(const glm::vec3* pathPoint, const int nbpoint);

	Collision::LineCollision GetTargetVector() const;
	Collision::LineCollision* GetEntityCollision() const;

	std::string GetStateLabel(const int id) const;

	void CheckCollision(Collision::LineCollision* entity, const int type);

	Triangle actor;
	Line aim;
	Shader* actorShader;

	glm::vec3 color;

	glm::mat4 transform;

	glm::vec2 position;
	glm::vec2 velocity;
	glm::vec2 targetPoint;
	glm::vec2 nearestTargetActor;

	float currentTime;
	float rotation;
	float acceleration;
	float targetRotationWanders;
	float turnTimeAvoidingWall;

	int state;
	int currentWayPoint;
	int typeCollisionActor;
	int previousState;

	bool visibleTargetVector;

	Collision::LineCollision entityCollision;
};















