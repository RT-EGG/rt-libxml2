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
#include "XmlElement.hpp"

class XmlDocument
{
public:
	XmlDocument(void)
		: elements()
	{
		return;
	}

	virtual ~XmlDocument(void)
	{
		clearElements();
		return;
	}

	XmlElement* addElement(const std::string& in_name)
	{
		XmlElement* element = new XmlElement(nullptr, in_name);
		elements.push_back(element);
		return element;
	}

	void clearElements(void)
	{
		for (auto element : elements)
			delete element;
		elements.clear();
		return;
	}

	const std::vector<XmlElement*>& getElements(void) const
	{
		return elements;
	}

private:
	std::vector<XmlElement*> elements;
};