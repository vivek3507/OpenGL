#pragma once
#include <string>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <assert.h>

#include "GLBase.h"
#include "Shaders.h"

struct BufferLayoutUnit
{
	bool isName;
	unsigned int program;
	std::string attribName;
	unsigned int location;
	unsigned int type;
	unsigned int count;
	bool isNormalised;

	static unsigned int getSizeOfType(unsigned int type) {
		switch (type) {
		case GL_FLOAT:
			return sizeof(float);
		case GL_INT:
			return sizeof(int);
		case GL_BYTE:
			return sizeof(char);
		assert(0);

		}
		return 0;
	}
};

class BufferLayout
{
	std::vector<BufferLayoutUnit> m_elements;
	unsigned int m_stride;
public:
	BufferLayout();
	~BufferLayout();

	std::vector<BufferLayoutUnit>& getBufferLayoutUnits()
	{
		return m_elements;
	}

	unsigned int getStride()
	{
		return m_stride;
	}
	/*

Two floats --> coord
one floats --> info
-------------------
Two floats --> coord
One floats --> info
-------------------
Two floats --> coord
One floats --> info

To fetch coordinate
offset = 0;
stride = 8;
To fetch info
offset = 8;
stride = 4;

*/

	//Generic template member declaration/definition
	template <typename T>
	void addAttribute(unsigned int program, std::string name, unsigned int count, bool isNormalised)
	{
		static_assert(false);
	}

	//Template specialtization
	template <>
	void addAttribute<float>(unsigned int program, std::string name, unsigned int count, bool isNormalised)
	{
		m_elements.push_back({true, program, name, 0, GL_FLOAT, count, isNormalised});
		m_stride += BufferLayoutUnit::getSizeOfType(GL_FLOAT) * count;
	}

	template <>
	void addAttribute<char>(unsigned int program, std::string name, unsigned int count, bool isNormalised)
	{
		m_elements.push_back({ true, program, name, 0, GL_BYTE, count, isNormalised });
		m_stride += BufferLayoutUnit::getSizeOfType(GL_BYTE) * count;
	}

	template <>
	void addAttribute<int>(unsigned int program, std::string name, unsigned int count, bool isNormalised)
	{
		m_elements.push_back({ true, program, name, 0, GL_INT, count, isNormalised });
		m_stride += BufferLayoutUnit::getSizeOfType(GL_INT) * count;
	}

	//Generic template member declaration/definition
	template <typename T>
	void addAttribute(unsigned int loc, unsigned int count, bool isNormalised)
	{
		static_assert(false);
	}

	//Template specialtization
	template <>
	void addAttribute<float>(unsigned int loc, unsigned int count, bool isNormalised)
	{
		m_elements.push_back({false, 0, "", loc, GL_FLOAT, count, isNormalised });
		m_stride += sizeof(float) * count;
	}

	template <>
	void addAttribute<char>(unsigned int loc, unsigned int count, bool isNormalised)
	{
		m_elements.push_back({false, 0, "", loc, GL_BYTE, count, isNormalised });
		m_stride += sizeof(char) * count;
	}

	template <>
	void addAttribute<int>(unsigned int loc, unsigned int count, bool isNormalised)
	{
		m_elements.push_back({false, 0, "", loc, GL_INT, count, isNormalised });
		m_stride += sizeof(int) * count;
	}

	template <>
	void addAttribute<unsigned int>(unsigned int loc, unsigned int count, bool isNormalised)
	{
		m_elements.push_back({ false, 0, "", loc, GL_UNSIGNED_INT, count, isNormalised });
		m_stride += sizeof(unsigned int) * count;
	}

};

