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

LineSegment1D getProjection1D(const mSphere &sphere, const vec3 &normal)
{
	LineSegment1D myLine;
	float centreProjection;

	centreProjection = glm::dot(sphere.centre, normal);
	myLine.start = centreProjection - sphere.radius;
	myLine.end = centreProjection + sphere.radius;

	return myLine;
}

LineSegment1D getProjection1D(const vec3* corners, const vec3 &normal, int numCorners)
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

//https://gamedev.stackexchange.com/questions/44500/how-many-and-which-axes-to-use-for-3d-obb-collision-with-sat/
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

bool SeperatingAxisTest(ConvexHull const& a, ConvexHull const& b)
{
  bool result = SeperatingAxisTest(a.vertices.data(), a.vertices.size(), b.vertices.data(), b.vertices.size(), a.axes.data(), a.axes.size());
  return result && SeperatingAxisTest(a.vertices.data(), a.vertices.size(), b.vertices.data(), b.vertices.size(), b.axes.data(), b.axes.size());
}

void getmTriangleNormals(vec3* normals, const mTriangle &tri)
{
	const vec3 &a = tri.corners[0];
	const vec3 &b = tri.corners[1];
	const vec3 &c = tri.corners[2];

	vec3 direction1 = a - b;
	vec3 direction2 = b - c;
	vec3 direction3 = c - a;
	vec3 faceNormal = glm::cross(direction1, direction2);

	normals[0] = glm::cross(faceNormal, direction1);
	normals[1] = glm::cross(faceNormal, direction2);
	normals[2] = glm::cross(faceNormal, direction3);
	normals[3] = faceNormal;
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
  if (b.start >= a.end)
    return false;
  if (a.start >= b.end)
    return false;

	return true;
}

bool Intersects(ConvexHull const & a, ConvexHull const & b)
{
  ConvexHull temp(a);
  int originalAxisCount = temp.axes.size();
  temp.axes.resize(temp.axes.size() + a.edgeDirs.size() * b.edgeDirs.size());

  for (int i = 0; i < a.edgeDirs.size(); i++)
    for (int j = 0; j < b.edgeDirs.size(); j++)
      temp.axes[originalAxisCount + i * b.edgeDirs.size() + j] = normalize(glm::cross(a.edgeDirs[i], b.edgeDirs[j]));

  return SeperatingAxisTest(temp, b);
}

bool Intersects(mAABB const & a, mAABB const & b)
{
	if (a.max.x > b.min.x &&
		a.min.x < b.max.x &&
		a.max.y > b.min.y &&
		a.min.y < b.max.y &&
		a.max.z > b.min.z &&
		a.min.z < b.max.z)
	{
		return true;
  }
	return false;
}

// bool Intersects(mAABB const & aabb, mOBB const & obb)
// {
// 	vec3 aabbCorners[8];
// 	vec3 normals[6];
// 
// 	aabbCorners[0] = vec3(aabb.min.x, aabb.min.y, aabb.min.z);
// 	aabbCorners[1] = vec3(aabb.min.x, aabb.min.y, aabb.max.z);
// 	aabbCorners[2] = vec3(aabb.min.x, aabb.max.y, aabb.min.z);
// 	aabbCorners[3] = vec3(aabb.min.x, aabb.max.y, aabb.max.z);
// 	aabbCorners[4] = vec3(aabb.max.x, aabb.min.y, aabb.min.z);
// 	aabbCorners[5] = vec3(aabb.max.x, aabb.min.y, aabb.max.z);
// 	aabbCorners[6] = vec3(aabb.max.x, aabb.max.y, aabb.min.z);
// 	aabbCorners[7] = vec3(aabb.max.x, aabb.max.y, aabb.max.z);
// 
// 	normals[0] = vec3(1, 0, 0);
// 	normals[1] = vec3(0, 1, 0);
// 	normals[2] = vec3(0, 0, 1);
// 	normals[3] = obb.axes[0];
// 	normals[4] = obb.axes[1];
// 	normals[5] = obb.axes[2];
// 
// 	return SeperatingAxisTest(aabbCorners, 8, obb.corners, 8, normals, 6);
// }

//bool Intersects(mAABB const & aabb, mTriangle const & tri)
//{
//	vec3 aabbCorners[8];
//	vec3 normals[7];
//
//	mAABBtomOBB(aabbCorners, normals, aabb);
//	getmTriangleNormals(normals + 3,tri);
//
//	return SeperatingAxisTest(aabbCorners, 8, tri.corners, 3, normals, 7);
//}

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

bool RayAABBPlane(const float boxMin, const float boxMax, const float vertOrigin, const float vertEnd, float& globalMin, float& globalMax, float norm)
{

	// planeMin is the fraction at which the line collides with the AABB first, planeMax is the second collision, temp is used to move values around
	float planeMin, planeMax, temp;
	bool isColliding = true;	//If true, then the line is colliding on this plane
								// Gets the location of the first collision with the cube along the line as a fraction, the fraction is the percent that the line moved before colliding.

	if ((vertEnd <= boxMax && vertEnd >= boxMin) ||
		(vertOrigin <= boxMax && vertOrigin >= boxMin) ||
		(boxMin <= vertOrigin && boxMin >= vertEnd) ||
		(boxMin >= vertOrigin && boxMin <= vertEnd) ||
		(boxMax <= vertOrigin && boxMax >= vertEnd) ||
		(boxMax >= vertOrigin && boxMax <= vertEnd))
	{

		planeMin = (boxMin - vertOrigin) / (norm);
		//Same as above, but for the second collision (line leaves Object)
		planeMax = (boxMax - vertOrigin) / (norm);

		// check if the max value is larger than the min value
		if (planeMax < planeMin) {
			//If it is, then swap the values
			temp = planeMin;
			planeMin = planeMax;
			planeMax = temp;
		}

		// set the new values for the global min and max values, get the largest min value, and the smallest max value, this shrinks the scope of the line
		if (planeMin > globalMin)
			globalMin = planeMin;

		if (planeMax < globalMax)
			globalMax = planeMax;

		//If the minimum value is greater than the max value, there is no collision
		if (globalMin > globalMax) {
			isColliding = false;
		}
		if (globalMax < 0)
		{
			isColliding = false;
		}
	}
	else {
		isColliding = false;
	}

	return isColliding;
}


/// <summary>
/// Intersectses the specified aabb. 
/// Author Nathan
/// </summary>
/// <param name="aabb">The aabb.</param>
/// <param name="ray">The ray.</param>
/// <param name="rayEnterDist">The ray enter dist.</param>
/// <param name="rayExitDist">The ray exit dist.</param>
/// <returns></returns>
bool Intersects(mAABB const & aabb, mRay const & ray, float * rayEnterDist, float * rayExitDist)
{
  vec3 dirfrac;

  // r.dir is unit direction vector of ray
  dirfrac.x = 1.0f / ray.direction.x;
  dirfrac.y = 1.0f / ray.direction.y;
  dirfrac.z = 1.0f / ray.direction.z;

  // lb is the corner of AABB with minimal coordinates - left bottom, rt is maximal corner
  // r.org is origin of ray
  float t1 = (aabb.min.x - ray.position.x)*dirfrac.x;
  float t2 = (aabb.max.x - ray.position.x)*dirfrac.x;
  float t3 = (aabb.min.y - ray.position.y)*dirfrac.y;
  float t4 = (aabb.max.y - ray.position.y)*dirfrac.y;
  float t5 = (aabb.min.z - ray.position.z)*dirfrac.z;
  float t6 = (aabb.max.z - ray.position.z)*dirfrac.z;

  float tmin = mMax(mMax(mMin(t1, t2), mMin(t3, t4)), mMin(t5, t6));
  float tmax = mMin(mMin(mMax(t1, t2), mMax(t3, t4)), mMax(t5, t6));
  float t = FLT_MAX;

  // if tmax < 0, ray (line) is intersecting AABB, but the whole AABB is behind us
  if (tmax < 0)
  {
    t = tmax;
    return false;
  }

  // if tmin > tmax, ray doesn't intersect AABB
  if (tmin > tmax)
  {
    t = tmax;
    return false;
  }

  t = tmin;

  if (rayEnterDist)
    *rayEnterDist = t;
  return true;



/*float tmin = (aabb.min.x - ray.position.x) / ray.direction.x;
float tmax = (aabb.max.x - ray.position.x) / ray.direction.x;
float tmp;

if (tmin > tmax) {
	tmp = tmin;
	tmin = tmax;
	tmax = tmp;
}

float tymin = (aabb.min.y - ray.position.y) / ray.direction.y;
float tymax = (aabb.max.y - ray.position.y) / ray.direction.y;

if (tymin > tymax)
{
	tmp = tymin;
	tymin = tymax;
	tymax = tmp;
}

if ((tmin > tymax) || (tymin > tmax))
return false;

if (tymin > tmin)
tmin = tymin;

if (tymax < tmax)
	tmax = tymax;

float tzmin = (aabb.min.z - ray.position.z) / ray.direction.z;
float tzmax = (aabb.max.z - ray.position.z) / ray.direction.z;

if (tzmin > tzmax) {
	tmp = tzmin;
	tzmin = tzmax;
	tzmax = tmp;
}

if ((tmin > tzmax) || (tzmin > tmax))
return false;

if (tzmin > tmin)
tmin = tzmin;

if (tzmax < tmax)
	tmax = tzmax;

return true;*/




  //--------- this one
		//float globalMin = -1000000000;	//minimum value is 0%
		//float globalMax = 1000000000;	//max value is 100%
		//bool isColliding = false;	//whether the line is colliding with the AABB2

		//							//Check every plane, if all checks return true then the line is colliding with the Box
		//if (RayAABBPlane(aabb.min.x, aabb.max.x, ray.position.x, ray.position.x + ray.direction.x * 50, globalMin, globalMax, ray.direction.x)) {
		//	if (RayAABBPlane(aabb.min.y, aabb.max.y, ray.position.y, ray.position.y + ray.direction.y * 50, globalMin, globalMax, ray.direction.y)) {
		//		if (RayAABBPlane(aabb.min.z, aabb.max.z, ray.position.z, ray.position.z + ray.direction.z * 50, globalMin, globalMax, ray.direction.z)) {
		//			isColliding = true;
		//		}
		//	}
		//}

		////collisionFraction = globalMin;	//set the value for the collision fraction, so we can use it later for collision resolution

		//return isColliding;
	
  //-----------




	/*float Tnear = -std::numeric_limits<float>::infinity();
	float Tfar = std::numeric_limits<float>::infinity();

	if (ray.direction.x == 0) {
		if (ray.position.x < aabb.min.x || ray.position.x > aabb.max.x) {
			return false;
		}
	}
	float Tone = (aabb.min.x - ray.position.x) / ray.direction.x;
	float Ttwo = (aabb.max.x - ray.position.x) / ray.direction.x;
	float tmp = 0;

	if (Tone > Ttwo) {
		tmp = Tone;
		Tone = Ttwo;
		Ttwo = tmp;
	}

	if (Tone > Tnear)
	{
		Tnear = Tone;
	}
	if (Ttwo < Tfar) 
	{
		Tfar = Ttwo;
	}
	if (Tnear > Tfar)
	{
		return false;
	}
	if(Tfar < 0)
	{
		return false;
	}

	if (ray.direction.y == 0) {
		if (ray.position.y < aabb.min.y || ray.position.y > aabb.max.y) {
			return false;
		}
	}
	Tone = (aabb.min.y - ray.position.y) / ray.direction.y;
	Ttwo = (aabb.max.y - ray.position.y) / ray.direction.y;
	tmp = 0;

	if (Tone > Ttwo) {
		tmp = Tone;
		Tone = Ttwo;
		Ttwo = tmp;
	}

	if (Tone > Tnear)
	{
		Tnear = Tone;
	}
	if (Ttwo < Tfar)
	{
		Tfar = Ttwo;
	}
	if (Tnear > Tfar)
	{
		return false;
	}
	if (Tfar < 0)
	{
		return false;
	}

	if (ray.direction.z == 0) {
		if (ray.position.z < aabb.min.z || ray.position.z > aabb.max.z) {
			return false;
		}
	}
	Tone = (aabb.min.z - ray.position.z) / ray.direction.z;
	Ttwo = (aabb.max.z - ray.position.z) / ray.direction.z;
	tmp = 0;

	if (Tone > Ttwo) {
		tmp = Tone;
		Tone = Ttwo;
		Ttwo = tmp;
	}

	if (Tone > Tnear)
	{
		Tnear = Tone;
	}
	if (Ttwo < Tfar)
	{
		Tfar = Ttwo;
	}
	if (Tnear > Tfar)
	{
		return false;
	}
	if (Tfar < 0)
	{
		return false;
	}
	
	if (rayEnterDist != nullptr && rayExitDist != nullptr)
	{

	}


	//TODO
	return true;*/
}

//bool Intersects(mOBB const & a, mOBB const & b)
//{
//	vec3 normals[6];
//
//	normals[0] = a.axes[0];
//	normals[1] = a.axes[1];
//	normals[2] = a.axes[2];
//
//	normals[3] = b.axes[0];
//	normals[4] = b.axes[1];
//	normals[5] = b.axes[2];
//
//	return SeperatingAxisTest(a.corners,8,b.corners,8,normals,6);
//}

//bool Intersects(mOBB const & obb, mTriangle const & tri)
//{
//	vec3 normals[7];
//
//	normals[0] = obb.axes[0];
//	normals[1] = obb.axes[1];
//	normals[2] = obb.axes[2];
//
//	getmTriangleNormals(normals + 3, tri);
//
//	return SeperatingAxisTest(obb.corners, 8, tri.corners, 3, normals, 7);
//}

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

//bool Intersects(mTriangle const & a, mTriangle const & b)
//{
//	vec3 normals[8];
//
//	getmTriangleNormals(normals, a);
//	getmTriangleNormals(normals + 4, b);
//
//	SeperatingAxisTest(a.corners, 3, b.corners, 3, normals, 8);
//
//	return false;
//}

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
