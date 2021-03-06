// Credit to: James Randall; github.com/JamesRandall/SimpleVoxelEngine/blob/master/voxelEngine/include/AABB.h
#include "AABB.h"

AABB::AABB() : minx(0), miny(0), minz(0), maxx(0), maxy(0), maxz(0), surface_area(0) {
	// Intentionally Blank
	// Passes blank information to next constructor
}

AABB::AABB(float minx, float miny, float minz, float maxx, float maxy, float maxz) : minx(minx), miny(miny), minz(minz), maxx(maxx), maxy(maxy), maxz(maxz) {
	surface_area = get_surface_area();
	//std::cout << "Mins: (" << minx << ", " << miny << ", " << minz << ") " << " Maxs: (" << maxx << ", " << maxy << ", " << maxz << ")" << std::endl;
}

AABB::AABB(glm::vec3 min, glm::vec3 max, glm::vec3 centre) : minx(min.x), miny(min.y), minz(min.z), maxx(max.x), maxy(max.y), maxz(max.z), centre(centre) {
	surface_area = get_surface_area();
}

bool AABB::overlaps(const AABB& obj) const {
	bool checkx = (maxx > obj.minx) && (minx < obj.maxx);
	bool checky = (maxy > obj.miny) && (miny < obj.maxy);
	bool checkz = (maxz > obj.minz) && (minz < obj.maxz);
	return checkx && checky && checkz;
}

bool AABB::contains(const AABB& obj) const {
	bool checkx = (obj.minx >= minx) && (obj.maxx <= maxx);
	bool checky = (obj.miny >= miny) && (obj.maxy <= maxy);
	bool checkz = (obj.minz >= minz) && (obj.maxz <= maxz);
	return checkx && checky && checkz;
}

AABB AABB::merge(const AABB& obj) const {
	return AABB(std::min(minx, obj.minx), std::min(miny, obj.miny), std::min(minz, obj.minz), std::max(maxx, obj.maxx), std::max(maxy, obj.maxy), std::max(maxz, obj.maxx));
}

AABB AABB::intersection(const AABB& obj) const {
	return AABB(std::max(minx, obj.minx), std::max(miny, obj.miny), std::max(minz, obj.minz), std::min(maxx, obj.maxx), std::min(maxy, obj.maxy), std::min(maxz, obj.maxx));
}

void AABB::scale(const float& val) {
	scale(glm::vec3(val, val, val));
}
void AABB::scale(const glm::vec3& val) {
	std::cout << "before_scale_bounds min/max: (" << minx << "/" << maxx << "," << miny << "/" << maxy << "," << minz << "/" << maxz << ")" << std::endl;
	glm::vec3 centre((glm::vec3(minx, miny, minz) + glm::vec3(maxx, maxy, maxz)) / 2.0f);

	minx = (centre.x - minx) * val.x;
	miny = (centre.y - miny) * val.y;
	minz = (centre.z - minz) * val.z;

	maxx = (centre.x - maxx) * val.x;
	maxy = (centre.y - maxy) * val.y;
	maxz = (centre.z - maxz) * val.z;

	std::cout << "after_scale_bounds min/max: (" << minx << "/" << maxx << "," << miny << "/" << maxy << "," << minz << "/" << maxz << ")" << std::endl;

}

float AABB::get_surface_area() { return 2 * (get_width() * get_height() + get_width() * get_depth() + get_height() * get_depth()); }
float AABB::get_width() { return maxx - minx; }
float AABB::get_height() { return maxy - miny; }
float AABB::get_depth() { return maxz - minz; }

void AABB::print() { std::cout << "bounds min/max: (" << minx << "/" << maxx << "," << miny << "/" << maxy << "," << minz << "/" << maxz << ")" << std::endl; }