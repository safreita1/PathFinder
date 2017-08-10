/*
 * PathInformation.h
 *
 *  Created on: Jan 18, 2016
 *      Author: scott
 */
#ifndef PATHINFORMATION_H_
#define PATHINFORMATION_H_

#include <iostream>
#include <sstream>
#include <vector>
#include <iterator> 

/**
 * This class stores and manipulates data for a string and integer
 */
class PathInformation {

public:
	/**
	 * Constructor.
	 * Creates an empty string for path and sets pathLength to 0.
	 */
	PathInformation();

	/**
	 * Constructor.
	 * @parameter tempPath  Initializes path with tempPath.
	 * @parameter tempPathLength  Initializes the pathLength with tempPathLength.
	 */
	PathInformation(std::vector<int> tempPath, int tempPathLength);

	/**
	 * Gets the path.
	 * @return vector  Containing the path information.
	 */
	std::vector<int> getPath() const;

	/**
	 * Gets the path information at a given index.
	 * @return int  The value at the index in the path.
	 */
	int getPathAt(int index) const;


	/**
	 * Returns the path length
	 * @return integer  The length of the path.
	 */
	int getPathLength() const;


	/**
	 * Sets the path
	 * @parameter updatedPath  Sets the path to updatedPath.
	 */
	void setPath(std::vector<int> updatedPath);


	/**
	 * Sets the path length
	 * @parameter tempPathLength  Sets the pathLength to updatedPathLength.
	 */
	void setPathLength(int updatedPathLength);


	/**Returns the path and pathLength
	 * @return a string that contains the path and pathLength
	 */
	std::string toString() const;


	/**
	 * Compares two PathInformation objects.
	 * @return true if the paths are equal, false otherwise
	 */
	bool equals(PathInformation other) const;


private:
	std::vector<int> path;
	int pathLength;
};

#endif
