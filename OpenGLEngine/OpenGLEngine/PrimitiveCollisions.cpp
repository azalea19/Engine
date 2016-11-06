#include "PrimitiveCollisions.h"
#include "MMath.h"


struct Plane
{
	vec3 normal;
	float distance;
};

struct LineSegment1D
{
	float start;
	float end;
};

bool Intersects(LineSegment1D const & a, LineSegment1D const & b);

LineSegment1D getProjection1D(const mSphere sphere, vec3 normal)
{
	LineSegment1D myLine;
	float centreProjection;

	centreProjection = glm::dot(sphere.centre, normal);
	myLine.start = centreProjection - sphere.radius;
	myLine.end = centreProjection + sphere.radius;

	return myLine;
}

LineSegment1D getProjection1D(const vec3* corners, vec3 normal, int numCorners)
{
	LineSegment1D myLine;

	myLine.start = FLT_MAX;
	myLine.end = -FLT_MAX;

	for (int i = 0; i < numCorners; i++)
	{
		float scalarProduct = glm::dot(corners[i], normal);
		myLine.start = mMin(myLine.start, scalarProduct);
		myLine.end = mMax(myLine.end, scalarProduct);
	}

	return myLine;
}

bool SeperatingAxisTest(const vec3* object1Corners, int num1Corners, const vec3* object2Corners, int num2Corners, const vec3* normals, int numNormals)
{
	for (int i = 0; i < numNormals; i++)
	{
		LineSegment1D shadow1 = getProjection1D(object1Corners, normals[i], num1Corners);
		LineSegment1D shadow2 = getProjection1D(object2Corners, normals[i], num2Corners);

		if (!Intersects(shadow1, shadow2))
		{
			return false;
		}
	}
	return true;
}

void getmTriangleNormals(vec3* normals, mTriangle tri)
{
	vec3 direction1;
	vec3 direction2;
	vec3 direction3;
	vec3 faceNormal;

	vec3 a = tri.corners[0];
	vec3 b = tri.corners[1];
	vec3 c = tri.corners[2];

	direction1 = a - b;
	direction2 = b - c;
	direction3 = c - a;

	faceNormal = glm::cross(direction1, direction2);

	normals[0] = glm::cross(faceNormal, direction1);
	normals[1] = glm::cross(faceNormal, direction2);
	normals[2] = glm::cross(faceNormal, direction3);
	normals[3] - faceNormal;
}

void mAABBtomOBB(vec3* corners, vec3* normals, const mAABB &aabb)
{
	corners[0] = vec3(aabb.min.x, aabb.min.y, aabb.min.z);
	corners[1] = vec3(aabb.min.x, aabb.min.y, aabb.max.z);
	corners[2] = vec3(aabb.min.x, aabb.max.y, aabb.min.z);
	corners[3] = vec3(aabb.min.x, aabb.max.y, aabb.max.z);
	corners[4] = vec3(aabb.max.x, aabb.min.y, aabb.min.z);
	corners[5] = vec3(aabb.max.x, aabb.min.y, aabb.max.z);
	corners[6] = vec3(aabb.max.x, aabb.max.y, aabb.min.z);
	corners[7] = vec3(aabb.max.x, aabb.max.y, aabb.max.z);

	normals[0] = vec3(1, 0, 0);
	normals[1] = vec3(0, 1, 0);
	normals[2] = vec3(0, 0, 1);
}

//See Heron's formula
//a2,b2 and c2 are a,b and c squared
float mTriangleArea(float a2, float b2, float c2)
{
	return (0.25f)*sqrtf(2 * (a2*b2 + a2*c2 + b2*c2) - (a2*a2 + b2*b2 + c2*c2));
}

bool Intersects(LineSegment1D const & a, LineSegment1D const & b)
{
	if (a.end < b.start)
	{
		return false;
	}
	if (b.end < a.start)
	{
		return false;
	}

	return true;
}

bool Intersects(mAABB const & a, mAABB const & b)
{
	vec3 cornersA[8];
	vec3 cornersB[8];

	cornersA[0] = vec3(a.min.x, a.min.y, a.min.z);
	cornersA[1] = vec3(a.min.x, a.min.y, a.max.z);
	cornersA[2] = vec3(a.min.x, a.max.y, a.min.z);
	cornersA[3] = vec3(a.min.x, a.max.y, a.max.z);
	cornersA[4] = vec3(a.max.x, a.min.y, a.min.z);
	cornersA[5] = vec3(a.max.x, a.min.y, a.max.z);
	cornersA[6] = vec3(a.max.x, a.max.y, a.min.z);
	cornersA[7] = vec3(a.max.x, a.max.y, a.max.z);

	cornersB[0] = vec3(a.min.x, a.min.y, a.min.z);
	cornersB[1] = vec3(a.min.x, a.min.y, a.max.z);
	cornersB[2] = vec3(a.min.x, a.max.y, a.min.z);
	cornersB[3] = vec3(a.min.x, a.max.y, a.max.z);
	cornersB[4] = vec3(a.max.x, a.min.y, a.min.z);
	cornersB[5] = vec3(a.max.x, a.min.y, a.max.z);
	cornersB[6] = vec3(a.max.x, a.max.y, a.min.z);
	cornersB[7] = vec3(a.max.x, a.max.y, a.max.z);

	vec3 normals[3];

	normals[0] = vec3(1, 0, 0);
	normals[1] = vec3(0, 1, 0);
	normals[2] = vec3(0, 0, 1);

	return SeperatingAxisTest(cornersA, 8, cornersB, 8, normals, 3);
}

bool Intersects(mAABB const & aabb, mOBB const & obb)
{
	vec3 aabbCorners[8];
	vec3 normals[6];

	aabbCorners[0] = vec3(aabb.min.x, aabb.min.y, aabb.min.z);
	aabbCorners[1] = vec3(aabb.min.x, aabb.min.y, aabb.max.z);
	aabbCorners[2] = vec3(aabb.min.x, aabb.max.y, aabb.min.z);
	aabbCorners[3] = vec3(aabb.min.x, aabb.max.y, aabb.max.z);
	aabbCorners[4] = vec3(aabb.max.x, aabb.min.y, aabb.min.z);
	aabbCorners[5] = vec3(aabb.max.x, aabb.min.y, aabb.max.z);
	aabbCorners[6] = vec3(aabb.max.x, aabb.max.y, aabb.min.z);
	aabbCorners[7] = vec3(aabb.max.x, aabb.max.y, aabb.max.z);

	normals[0] = vec3(1, 0, 0);
	normals[1] = vec3(0, 1, 0);
	normals[2] = vec3(0, 0, 1);
	normals[4] = obb.axes[0];
	normals[5] = obb.axes[1];
	normals[6] = obb.axes[2];

	return SeperatingAxisTest(aabbCorners, 8, obb.corners, 8, normals, 6);
}

bool Intersects(mAABB const & aabb, mTriangle const & tri)
{
	vec3 aabbCorners[8];
	vec3 normals[7];

	mAABBtomOBB(aabbCorners, normals, aabb);
	getmTriangleNormals(normals + 3,tri);

	return SeperatingAxisTest(aabbCorners, 8, tri.corners, 3, normals, 7);
}

bool Intersects(mAABB const & aabb, mSphere const & sphere)
{
	vec3 aabbCorners[8];
	vec3 normals[11];

	mAABBtomOBB(aabbCorners, normals, aabb);

	for (int i = 0; i < 8; i++)
		normals[i+3] = aabbCorners[i] - sphere.centre;
	
	for (int j = 0; j < 11; j++)
	{
		LineSegment1D boxShadow;
		LineSegment1D sphereShadow;

		boxShadow = getProjection1D(aabbCorners, normals[j], 8);
		sphereShadow = getProjection1D(sphere, normals[j]);
		if (!Intersects(boxShadow, sphereShadow))
			return false;
	}
	return true;
}

bool Intersects(mAABB const & aabb, mRay const & ray, float * rayEnterDist, float * rayExitDist)
{
	//TODO
	return false;
}

bool Intersects(mOBB const & a, mOBB const & b)
{
	vec3 normals[6];

	normals[0] = a.axes[0];
	normals[1] = a.axes[1];
	normals[2] = a.axes[2];

	normals[3] = b.axes[0];
	normals[4] = b.axes[1];
	normals[5] = b.axes[2];

	return SeperatingAxisTest(a.corners,8,b.corners,8,normals,6);
}

bool Intersects(mOBB const & obb, mTriangle const & tri)
{
	vec3 normals[7];

	normals[0] = obb.axes[0];
	normals[1] = obb.axes[1];
	normals[2] = obb.axes[2];

	getmTriangleNormals(normals + 3, tri);

	return SeperatingAxisTest(obb.corners, 8, tri.corners, 3, normals, 7);
}

bool Intersects(mOBB const & obb, mSphere const & sphere)
{
	vec3 normals[11];
	
	normals[0] = obb.axes[0];
	normals[1] = obb.axes[0];
	normals[2] = obb.axes[0];

	for (int i = 0; i < 8; i++)
		normals[i + 3] = obb.corners[i] - sphere.centre;

	for (int j = 0; j < 11; j++)
	{
		LineSegment1D boxShadow;
		LineSegment1D sphereShadow;

		boxShadow = getProjection1D(obb.corners, normals[j], 8);
		sphereShadow = getProjection1D(sphere, normals[j]);
		if (!Intersects(boxShadow, sphereShadow))
			return false;
	}
	return true;
}

bool Intersects(mOBB const & obb, mRay const & ray)
{
	//TODO
	return false;
}

bool Intersects(mTriangle const & a, mTriangle const & b)
{
	vec3 normals[8];

	getmTriangleNormals(normals, a);
	getmTriangleNormals(normals + 4, b);

	SeperatingAxisTest(a.corners, 3, b.corners, 3, normals, 8);

	return false;
}

bool Intersects(mTriangle const & tri, mSphere const & sphere)
{
	vec3 normals[8];
	getmTriangleNormals(normals, tri);

	for (int i = 0; i < 4; i++)
		normals[i + 4] = tri.corners[i] - sphere.centre;

	for (int j = 0; j < 8; j++)
	{
		LineSegment1D triangleShadow;
		LineSegment1D sphereShadow;

		triangleShadow = getProjection1D(tri.corners, normals[j], 8);
		sphereShadow = getProjection1D(sphere, normals[j]);
		if (!Intersects(triangleShadow, sphereShadow))
			return false;
	}
	return true;
}

bool Intersects(Plane const & plane, mRay const & ray, float* distanceOut = nullptr)
{
	float proj = glm::dot(ray.direction, plane.normal);

	if (proj == 0)
	{
		return false;
	}
	if (distanceOut)
	{
		*distanceOut = glm::dot((plane.distance*plane.normal), plane.normal) / proj;
	}

	return true;
}

bool Intersects(mTriangle const & tri, mRay const & ray, float* distanceOut = nullptr)
{
	vec3 edgeAB,edgeBC,edgeCA;
	vec3 edgePA,edgePB,edgePC;
	float lengthAB, lengthBC, lengthCA;
	float lengthPA, lengthPB, lengthPC;

	Plane trianglePlane;
	float distance;
	vec3 P;
	float area, subA,subB,subC;

	vec3 a = tri.corners[0];
	vec3 b = tri.corners[1];
	vec3 c = tri.corners[2];

	edgeAB = b - a;
	edgeBC = c - b;
	edgeCA = a - c;

	trianglePlane.normal = normalize(glm::cross(edgeAB, edgeBC));	
	trianglePlane.distance = glm::dot(trianglePlane.normal, a);

	if (!Intersects(trianglePlane, ray, &distance))
	{
		return false;
	}

	//Intersection point P
	P = ray.direction*distance + ray.position;
	edgePA = P - a;
	edgePB = P - b;
	edgePC = P - c;

	lengthAB = glm::dot(edgeAB, edgeAB);
	lengthBC = glm::dot(edgeBC, edgeBC);
	lengthCA = glm::dot(edgeCA, edgeCA);

	lengthPA = glm::dot(edgePA, edgePA);
	lengthPB = glm::dot(edgePB, edgePB);
	lengthPC = glm::dot(edgePC, edgePC);

	area = mTriangleArea(lengthAB, lengthBC, lengthCA);
	subA = mTriangleArea(lengthPA, lengthAB, lengthPB);
	subB = mTriangleArea(lengthPB, lengthBC, lengthPC);
	subC = mTriangleArea(lengthPC, lengthCA, lengthPA);

	float margin = abs(((subA + subB + subC) / area) - 1);

	if (margin > 0.000001f)
	{
		return false;
	}
	if (distanceOut)
	{
		*distanceOut = distance;
	}

	return true;
}

bool Intersects(mSphere const & a, mSphere const & b)
{
	vec3 normal = a.centre - b.centre;

	LineSegment1D sphere1Shadow = getProjection1D(a,normal);
	LineSegment1D sphere2Shadow = getProjection1D(b,normal);

	if (!Intersects(sphere1Shadow, sphere2Shadow))
		return false;
	
	return true;
}

bool Intersects(mSphere const & sphere, mRay const & ray)
{
	//TODO
	return false;
}
