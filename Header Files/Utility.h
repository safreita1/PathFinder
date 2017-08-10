/*
 * Utility.h
 *
 *  Created on: N/A
 *      Author: Scott Freitas
 */

#ifndef UTILITY_H_
#define UTILITY_H_

#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>

/**
 * This class contains helper functions that are used to manipulate
 * vectors.
 */
class Utility {

public:

	/**
	 * Determines the number of elements that two vectors have in common.
	 * @parameter v1 The first vector.
	 * @parameter v2 The second vector.
	 * @return integer containing the number of intersected elements.
	 */
	static int vectorIntersection(std::vector<int> v1, std::vector<int> v2);

	/**
	 * Determines if an integer exists in a vector.
	 * @parameter v1 The vector.
	 * @parameter v2 The integer.
	 * @return bool True if it's found, false otherwise
	 */
	static bool vectorIntIntersection(const std::vector<int> &v1, int v2);

	/**
	 * Converts a vector to a string.
	 * @parameter v1 The vector.
	 * @return string containing the vector information.
	 */
	static std::string vectorToString(std::vector<int> &v1);
};

#endif 