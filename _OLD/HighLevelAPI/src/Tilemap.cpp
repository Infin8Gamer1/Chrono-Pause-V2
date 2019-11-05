/**
	* Author: David Wong
	* Project: CS230 Lab 7
	* File Name: Tilemap.cpp
**/

// Includes //
#include "stdafx.h"
#include "Tilemap.h"

#include <fstream>			// File IO

// Public Member Functions //
// Constructor ///
Tilemap::Tilemap(unsigned numColumns, unsigned numRows, int** data)
	: numColumns(numColumns), numRows(numRows), data(data)
{
}

// Destructor //
Tilemap::~Tilemap()
{
	// Delete the contents inside the array first
	for (unsigned i = 0; i < numColumns; ++i)
	{
		delete[] data[i];
	}
	// Then delete the 2D array itself
	delete[] data;
}

// Accessors //
unsigned Tilemap::GetWidth() const
{
	return numColumns;
}

unsigned Tilemap::GetHeight() const
{
	return numRows;
}

int Tilemap::GetCellValue(unsigned column, unsigned row) const
{
	if (column >= 0 && column < numColumns && row < numRows && row >= 0)
	{
		return data[column][row];
	}

	return -1;
}

// Mutators
Tilemap* Tilemap::CreateTilemapFromFile(const std::string& file)
{
	// Create the file stream
	std::ifstream mapStream(file);
	Tilemap* tilemap = nullptr;
	// Check if the file is valid
	if(mapStream.is_open())
	{
		// Read through the file stram and initialize the corresponding parts of the map with the part in the file
		std::string currLine;
		// Read the width of the map
		int width;
		if (!ReadIntegerVariable(mapStream, "width", width))
		{
			// ERROR: Could not load the file's width
			std::cerr << "[ERROR]: Could not find the map's width" << std::endl;
			return nullptr;
		}
		// Read the height of the map
		int height;
		if (!ReadIntegerVariable(mapStream, "height", height))
		{
			std::cerr << "[ERROR]: Could not find the map's height" << std::endl;
			return nullptr;
		}

		// Finally, read the map's data
		int** data = ReadArrayVariable(mapStream, "data", width, height);
		if (!data)
		{
			std::cerr << "[ERROR]: Could not find the map's data" << std::endl;
			return nullptr;
		}
		
		// Create the map and return it
		tilemap = new Tilemap(width, height, data);
	}
	else
	{
		std::cerr << "[ERROR]: Could not find the file for the map" << std::endl;
	}

	return tilemap;
}

bool Tilemap::ReadIntegerVariable(std::ifstream& stream, const std::string& varName, int& var)
{
	// Get the whole line
	std::string line;
	stream >> line;
	std::cout << "Loading Variable " << line;
	// If we found the name of the variable to be the same as the one we are looking for, the read the rest of the line
	if (varName == line)
	{
		stream >> line;
		std::cout << ", Value: " << line << std::endl;
		var = std::stoi(line);
		return true;
	}

	// Otherwise, the value didn't exist
	std::cout << std::endl;
	std::cerr << "[ERROR]: Could not find the variable " << varName << " in the file" << std::endl;
	return false;
}

int** Tilemap::ReadArrayVariable(std::ifstream& stream, const std::string& name, unsigned numColumns, unsigned numRows)
{
	// Get the next line of data
	std::string currLine;
	stream >> currLine;
	std::cout << "Loading Variable " << currLine << std::endl;
	// If the line contains the name of the variable we are looking for, then continue processing the data
	if (currLine == name)
	{
		// Create an empty int[][] list while we fill it up
		int** data = new int*[numColumns];
		for (unsigned i = 0; i < numColumns; ++i)
		{
			data[i] = new int[numRows];
		}

		for (unsigned i = 0; i < numRows; ++i)
		{
			std::cout << "[ ";
			for (unsigned j = 0; j < numColumns; ++j)
			{
				// Look for text until we found a space
				// If we hit the end of the file by accident, quit out, delete the list, and return nullptr
				stream >> currLine;
				if (stream.eof() && i != numRows-1 && j != numColumns-1)
				{
					std::cerr << "[ERROR]: Hit the end of line before finishing reading the data";
					std::cerr << " in index: [" << j << ", " << i << "]" << std::endl;
					for (unsigned k = 0; k < numColumns; ++k)
					{
						delete[] data[k];
					}
					delete[] data;
					return nullptr;
				}
				// Process the number and add it to the corresponding part of the list
				data[j][i] = std::stoi(currLine);
				std::cout << currLine;
				if (j < numColumns - 1)
					std::cout << ", ";
			}

			std::cout << "]" << std::endl;
		}

		// Return the data
		return data;
	}
	// Otherwise, quit early and return nullptr
	std::cerr << "[ERROR]: Could not find the " << name << " in the file" << std::endl;
	return nullptr;
}