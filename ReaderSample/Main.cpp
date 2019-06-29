#include <iostream>
#include "../Include/XmlDocumentReader.hpp"

void writeElement(XmlElement* in)
{
	for (int i = 0; i < in->getDepth(); ++i)
		std::cout << "\t";

	std::cout << "<" << in->getName();
	for (int i = 0; i < in->getAttributes().size(); ++i) {
		auto atts = in->getAttributes()[i];
		std::cout << " " << atts->getName() << "=\"" << atts->getValue() << "\"";
	}

	if ((in->getValue() == "") && (in->getChildren().empty()))
		std::cout << "/>" << std::endl;
	else {
		std::cout << ">";

		if (in->getChildren().empty())
			std::cout << in->getValue() << "</" << in->getName() << ">" << std::endl;
		else {
			std::cout << std::endl;
			for (auto child : in->getChildren())
				writeElement(child);
			for (int i = 0; i < in->getDepth(); ++i)
				std::cout << "\t";
			std::cout << "</" << in->getName() << ">" << std::endl;
		}
	}
}

int main(int argc, char** argv)
{
	std::string path = "";
	XmlDocument document;
	XmlDocumentReader::readFromFile(path, document);

	for (auto& element : document.getElements()) {
		writeElement(element);
	}

	return 0;
}