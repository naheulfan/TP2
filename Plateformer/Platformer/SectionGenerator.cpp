#include "SectionGenerator.h"



SectionGenerator::SectionGenerator()
{

}

Sections* SectionGenerator::GenerateSection(int sectionNumber)
{
	if (sectionNumber == 1)
	{
		return new Sections(1);
	}
	else if (sectionNumber == 2)
	{
		return new Sections(2);
	}
	else if (sectionNumber == 3)
	{
		return new Sections(3);
	}
	return nullptr;
}
