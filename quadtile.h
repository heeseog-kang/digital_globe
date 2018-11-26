#ifndef __QUADTILE_H__
#define __QUADTILE_H__


#include <array>

class spheroid;

float ytolat(float y);
int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
glm::vec3 calc_normal(glm::vec3 pt1, glm::vec3 pt2, glm::vec3 pt3);
double N(double phi);
std::array<double,3> ecef2lla(double x, double y, double z);
glm::vec3 lla2ecef(double lat_indegrees, double lon_indegrees);

struct normalspack
{
	glm::vec3 upperleft, upperright, bottomleft, bottomright;
};

class quadtile
{
public:
	quadtile* children;
	string quadkey;
	vector<glm::vec3> vertices;
	vector<glm::vec3> normals;
	vector<glm::vec2> uvs;
	vector<glm::vec2> borderuvs;
	normalspack corners;
	//only accessed from MT
	bool requested = false;

	shared_ptr<texturemesh> tm;
	wstring fname;
	int platenum;

	quadtile();
	~quadtile();
	void init(string _quadkey = "");

	quadtile* getchild(char c);
	quadtile* gettile(string tile, bool forcenew = false);
	vector<quadtile*> getdisplayedtiles(glm::vec3 camerapos, int zoomlevel);
	void invalidate(string tile);
	void getmap();
	
};


#endif//__QUADTILE_H__
