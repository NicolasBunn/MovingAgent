#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Collision
{
	public:
		struct LineCollision
		{
			glm::vec2 start;
			glm::vec2 direction;
		};

		struct TriangleCollision
		{
			glm::vec3 a;
			glm::vec3 b;
			glm::vec3 c;
		};

		static int IntersectQuadLine(LineCollision l[2], LineCollision&& l2, glm::vec2& pt, glm::vec2& pt1);
		static int IntersectTriangleLine(LineCollision l[3], LineCollision&& l2, glm::vec2& pt);
		static int Intersect2DLine(LineCollision& l1, LineCollision& l2, glm::vec2& pt0,glm::vec2& pt1);
		static int Intersect3DRayTriangle(LineCollision&& l, TriangleCollision&& tr, glm::vec3* pt);

		static int inSegment(glm::vec2 p, LineCollision l);
		static float perp(glm::vec2 u, glm::vec2 v);

};