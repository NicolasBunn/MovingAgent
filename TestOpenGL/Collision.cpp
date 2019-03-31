#include "Collision.h"

int Collision::IntersectQuadLine(LineCollision l[2], LineCollision&& l2, glm::vec2& pt, glm::vec2& pt1)
{
	int result = -1;

	pt = glm::vec2(100.0f, 100.0f);

	for (int i = 0; i < 2; i++)
	{
		glm::vec2 point1 = glm::vec2(0.0f, 0.0f);
		glm::vec2 point2 = glm::vec2(0.0f, 0.0f);
		int r = Intersect2DLine(l[i], l2, point1, point2);

		if (r == 1)
		{
			float distBestPoint = glm::distance(glm::vec2(l2.start.x, l2.start.y), pt);
			float distPoint1 = glm::distance(glm::vec2(l2.start.x, l2.start.y), point1);

			if (distBestPoint > distPoint1)
			{
				pt = point1;
			}

			result = 1;
		}
	}

	return result;
}

int Collision::IntersectTriangleLine(LineCollision l[3], LineCollision&& l2, glm::vec2& pt)
{
	int result = -1;

	pt = glm::vec2(100.0f, 100.0f);

	for (int i = 0; i < 3; i++)
	{
		glm::vec2 point1 = glm::vec2(0.0f, 0.0f);
		glm::vec2 point2 = glm::vec2(0.0f, 0.0f);
		int r = Intersect2DLine(l[i], l2, point1, point2);

		if (r == 1)
		{
			float distBestPoint = glm::distance(glm::vec2(l2.start.x, l2.start.y), pt);
			float distPoint1 = glm::distance(glm::vec2(l2.start.x, l2.start.y), point1);

			if (distBestPoint > distPoint1)
			{
				pt = point1;
			}

			result = 1;
		}
	}

	return result;
}

int Collision::Intersect2DLine(LineCollision& l1, LineCollision& l2, glm::vec2& pt0, glm::vec2& pt1)
{
	glm::vec2 u = l1.direction - l1.start;
	glm::vec2 v = l2.direction - l2.start;
	glm::vec2 w = l1.start - l2.start;

	float d = perp(u, v);

	if (glm::abs(d) < 0.001f)
	{
		if (perp(u, w) != 0 || perp(v, w) != 0)
		{
			return 0;
		}

		float du = glm::dot(u, u);
		float dv = glm::dot(v, v);
		if (du == 0 && dv == 0)
		{
			if (l1.start != l2.start)
			{
				return 0;
			}
			pt0.x = l1.start.x;
			pt0.y = l1.start.y;
			
			return 1;
		}
		if (du == 0)
		{
			if (inSegment(l1.start, l2) == 0)
			{
				return 0;
			}
			pt0.x = l1.start.x;
			pt0.y = l1.start.y;
			return 1;
		}
		if (dv == 0)
		{
			if (inSegment(l2.start, l1) == 0)
			{
				return 0;
			}
			pt0.x = l2.start.x;
			pt0.y = l2.start.y;
			return 1;
		}

		float t0, t1;
		glm::vec2 w2 = l1.direction - l2.start;

		if (v.x != 0)
		{
			t0 = w.x / v.x;
			t1 = w2.x / v.x;
		}
		else
		{
			t0 = w.y / v.y;
			t1 = w2.y / v.y;
		}
		if (t0 > t1) {                   // must have t0 smaller than t1
			float t = t0; t0 = t1; t1 = t;    // swap if not
		}

		if (t0 > 1 || t1 < 0) {
			return 0;      // NO overlap
		}
		t0 = t0 < 0 ? 0 : t0;               // clip to min 0
		t1 = t1 > 1 ? 1 : t1;

		if (t0 == t1)
		{
			pt0.x = l2.start.x + t0 * v.x;
			pt0.y = l2.start.y + t0 * v.y;
			return 1;
		}

		pt0.x = l2.start.x + t0 * v.x;
		pt0.y = l2.start.y + t0 * v.y;

		pt1.x = l2.start.x + t1 * v.x;
		pt1.y = l2.start.y + t1 * v.y;

		return 2;

	}

	float sI = perp(v, w) / d;
	if (sI < 0 || sI > 1)
	{
		return 0;
	}

	float tI = perp(u, w) / d;
	if (tI < 0 || tI > 1)
	{
		return 0;
	}

	pt0.x = l1.start.x + sI * u.x;
	pt0.y = l1.start.y + sI * u.y;

	return 1;
}

int Collision::Intersect3DRayTriangle(LineCollision&& l, TriangleCollision&& tr, glm::vec3* pt)
{
	/*glm::vec3 u, v, n;
	glm::vec3 dir, w0, w;
	float r, a, b;

	u = tr.b - tr.a;
	v = tr.c - tr.a;
	n = glm::cross(u, v);
	if (n == glm::vec3(0.0f, 0.0f, 0.0f))
	{
		return -1;
	}

	dir = l.direction - l.start;
	w0 = l.start - tr.a;
	a = -glm::dot(n, w0);
	b = glm::dot(n, dir);
	if (glm::abs(b) < 0.001f)
	{
		if (a == 0)
		{
			return 2;
		}
		else
		{
			return 0;
		}
	}

	r = a / b;
	if (r < 0.0)
	{
		return 0;
	}

	pt->x = l.start.x + r * dir.x;
	pt->y = l.start.y + r * dir.y;
	pt->z = l.start.z + r * dir.z;

	float uu, uv, vv, wu, wv, d;

	uu = glm::dot(u, u);
	uv = glm::dot(u, v);
	vv = glm::dot(v, v);
	w.x = pt->x - tr.a.x;
	w.y = pt->y - tr.a.y;
	w.z = pt->z - tr.a.z;
	wu = glm::dot(w, u);
	wv = glm::dot(w, v);

	float d1 = uv * uv - uu * vv;

	float s, t;
	s = (uv * wv - vv * wu) / d1;
	if (s < 0.0 || s > 1.0)
	{
		return 0;
	}
	t = (uv * wu - uu * wv) / d1;
	if (t < 0.0 || (s + t) > 1.0)
	{
		return 0;
	}*/

	return 1;
}

int Collision::inSegment(glm::vec2 p, LineCollision l)
{
	if (l.start.x != l.direction.x)
	{
		if (l.start.x <= p.x && p.x <= l.direction.x)
		{
			return 1;
		}

		if (l.start.x >= p.x && p.x >= l.direction.x)
		{
			return 1;
		}
	}
	else
	{
		if (l.start.y <= p.y && p.y <= l.direction.y)
		{
			return 1;
		}

		if (l.start.y >= p.y && p.y >= l.direction.y)
		{
			return 1;
		}
	}

	return 0;
}

float Collision::perp(glm::vec2 u, glm::vec2 v)
{
	return (u.x * v.y - u.y * v.x);
}