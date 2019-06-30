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

#include <fstream>
#include "XmlDocument.hpp"

class XmlDocumentWriter
{
public:
	static bool writeToFile(const std::string& in_path, XmlDocument& in_document, const std::string& in_indent = "  ")
	{
		std::ofstream output(in_path, std::ios::out);
		if (output.fail())
			return false;

		output << "<?xml version=\"" << in_document.getVersion() << "\" encoding=\"UTF-8\"?>" << std::endl;
		for (int i = 0; i < in_document.getElements().size(); ++i)
			writeElement(in_document.getElements().at(i), output, in_indent);

		return true;
	}

private:
	static void writeElement(const XmlElement* in_element, std::ofstream& output, const std::string& in_indent)
	{
		for (int i = 0; i < in_element->getDepth(); ++i)
			output << in_indent;

		output << "<" << in_element->getName();
		for (int i = 0; i < in_element->getAttributes().size(); ++i) {
			auto atts = in_element->getAttributes()[i];
			output << " " << atts->getName() << "=\"" << atts->getValue() << "\"";
		}

		if ((in_element->getValue() == "") && (in_element->getChildren().empty()))
			output << "/>" << std::endl;
		else {
			output << ">";

			if (in_element->getChildren().empty())
				output << in_element->getValue() << "</" << in_element->getName() << ">" << std::endl;
			else {
				output << std::endl;
				for (auto child : in_element->getChildren())
					writeElement(child, output, in_indent);
				for (int i = 0; i < in_element->getDepth(); ++i)
					output << "\t";
				output << "</" << in_element->getName() << ">" << std::endl;
			}
		}
		return;
	}
};