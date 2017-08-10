/*
 * Utility.cpp
 *
 *  Created on: N/A
 *      Author: Scott Freitas
 */

#include "Utility.h"

int Utility::vectorIntersection(std::vector<int> v1, std::vector<int> v2) {
	std::vector<int> v3;

	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());

	set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(v3));

	return v3.size();
}

bool Utility::vectorIntIntersection(const std::vector<int> &v1, int v2) {
	
	return find(v1.begin(), v1.end(), v2) != v1.end();
}

std::string Utility::vectorToString(std::vector<int> &v1) {
	std::stringstream convertedData;

	copy(v1.begin(), v1.end(), std::ostream_iterator<int>(convertedData, " "));
	return convertedData.str();
}