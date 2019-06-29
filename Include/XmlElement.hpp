/*
The MIT License (MIT)

Copyright (c) 2019 RT-EGG.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#pragma once

#include <string>
#include <vector>
#include "XmlAttribute.hpp"

class XmlElement
{
public:
	XmlElement(XmlElement* in_parent, const std::string& in_name)
		: parent(in_parent)
		, name(in_name)
		, value("")
		, attributes()
		, children()
	{
		return;
	}

	virtual ~XmlElement(void)
	{
		clearAttributes();
		clearElements();	
		return;
	}

	XmlElement* getParent(void) const
	{
		return parent;
	}

	int getDepth(void) const
	{
		if (parent)
			return parent->getDepth() + 1;
		else
			return 0;
	}

	const std::string& getName(void) const
	{
		return name;
	}

	void setValue(const std::string& in_value)
	{
		value = in_value;
		return;
	}

	const std::string& getValue(void) const
	{
		return value;
	}

	XmlAttribute* addAttribute(const std::string& in_name = "", const std::string& in_value = "")
	{
		XmlAttribute* att = new XmlAttribute(in_name, in_value);
		attributes.push_back(att);
		return att;
	}

	void clearAttributes(void)
	{
		for (auto attribute : attributes)
			delete attribute;
		attributes.clear();
		return;
	}

	void clearElements(void)
	{
		for (auto child : children)
			delete child;
		children.clear();
		return;
	}

	XmlElement* addChild(const std::string& in_name)
	{
		XmlElement* child = new XmlElement(this, in_name);
		children.push_back(child);
		return child;
	}

	const std::vector<XmlAttribute*>& getAttributes(void) const
	{
		return attributes;
	}

	const std::vector<XmlElement*>& getChildren(void) const
	{
		return children;
	}

private:
	XmlElement* parent;
	std::string name;
	std::string value;
	std::vector<XmlAttribute*> attributes;
	std::vector<XmlElement*> children;
};