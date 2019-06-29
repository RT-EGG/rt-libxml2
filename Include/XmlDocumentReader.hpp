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
#include <libxml/xmlreader.h>
#include "XmlDocument.hpp"
#include "XmlDocumentReadError.hpp"

class XmlDocumentReader
{
public:
	static void readFromFile(const std::string& in_path, XmlDocument& out_result)
	{
		xmlTextReaderPtr reader = xmlReaderForFile(in_path.c_str(), nullptr, 0);
		if (!reader)
			throw new FileReadError(in_path);

		out_result.clearElements();
		NodeAnalyzer analizer(out_result);

		while (true) {
			int read_result = xmlTextReaderRead(reader);
			if (read_result == 1)
				analizer.Analyze(reader);
			else if (read_result == 0)
				break;
			else
				throw new ParseError();
		}

		xmlCleanupParser();
		return;
	}

private:
	class NodeAnalyzer
	{
	public:
		NodeAnalyzer(XmlDocument& in_document)
			: document(in_document)
			, current_element(nullptr)
		{
			return;
		}

		bool Analyze(xmlTextReaderPtr in_reader)
		{
			const xmlChar* c_name = xmlTextReaderConstName(in_reader);
			const xmlChar* c_value = xmlTextReaderConstValue(in_reader);;
			std::string name = (c_name == nullptr) ? "<null>" : (const char*)xmlTextReaderConstName(in_reader);
			std::string value = (c_value == nullptr) ? "<null>" : (const char*)xmlTextReaderConstValue(in_reader);
			bool is_empty = xmlTextReaderIsEmptyElement(in_reader) != 0;

			int type = xmlTextReaderNodeType(in_reader);
			switch (type) {
			case XML_READER_TYPE_ELEMENT:
				if (current_element)
					current_element = current_element->addChild(name);
				else
					current_element = document.addElement(name);

				if (xmlTextReaderHasAttributes(in_reader) && xmlTextReaderMoveToFirstAttribute(in_reader)) {
					do {
						current_element->addAttribute((const char*)xmlTextReaderConstName(in_reader),
													  (const char*)xmlTextReaderConstValue(in_reader));
					} while (xmlTextReaderMoveToNextAttribute(in_reader));
				}

				if (is_empty)
					current_element = current_element->getParent();
				break;

			case XML_READER_TYPE_END_ELEMENT:
				if (!current_element)
					throw new EndOfNullElementError(name);
				if (current_element->getName() != name)
					throw new EndOfInvalidElementError(current_element->getName(), name);

				current_element = current_element->getParent();
				break;

			case XML_READER_TYPE_TEXT:
				if (!current_element)
					throw new ValueOfNullElementError(value);

				current_element->setValue(value);
				break;
			}

			return true;
		}

	private:
		XmlDocument& document;
		XmlElement* current_element;
	};
};