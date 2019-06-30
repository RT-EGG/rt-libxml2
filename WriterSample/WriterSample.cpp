#include <iostream>
#include "../Include/XmlDocumentWriter.hpp"

int main()
{
	XmlDocument document;

	XmlElement* characters = document.addElement("characters");
	{
		XmlElement* character = characters->addChild("character");
		{
			character->addAttribute("name", "Jhon");
			character->addChild("Job")->setValue("warrior");
			character->addChild("Power")->setValue("1000");
			character->addChild("M-Power")->setValue("0");
		}
		character = characters->addChild("character");
		{
			character->addAttribute("name", "Hanako");
			character->addChild("Job")->setValue("wizard");
			character->addChild("Power")->setValue("10");
			character->addChild("M-Power")->setValue("2000");
		}
		character = characters->addChild("character");
		{
			character->addAttribute("name", "Piko");
			character->addChild("Job")->setValue("Housekeeper");
			character->addChild("Power")->setValue("10000");
			character->addChild("M-Power")->setValue("10000");
		}
	}
	XmlElement* items = document.addElement("items");
	{
		XmlElement* item = items->addChild("item");
		{
			item->addAttribute("category", "weapon");
			item->addAttribute("name", "sword");
			item->addChild("weight")->setValue("100");
			item->addChild("price")->setValue("5000");
		}
		item = items->addChild("item");
		{
			item->addAttribute("category", "food");
			item->addAttribute("name", "potato");
			item->addChild("weight")->setValue("10");
			item->addChild("price")->setValue("5");
		}
		item = items->addChild("item");
		{
			item->addAttribute("category", "important");
			item->addAttribute("name", "atmosphere");
			item->addChild("weight")->setValue("0");
			item->addChild("price")->setValue("0");
		}
	}

	std::string path = "";
	XmlDocumentWriter::writeToFile(path, document);

	return 0;
}
