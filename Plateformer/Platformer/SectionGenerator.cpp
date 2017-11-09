#include "SectionGenerator.h"



SectionGenerator::SectionGenerator()
{
	currentSection = -1;//donc présentement inactif
	*sectionsToGenerate[0] = Sections(0);
	*sectionsToGenerate[1] = Sections(1);
	*sectionsToGenerate[2] = Sections(2);
}


SectionGenerator::~SectionGenerator()
{
}

Sections* SectionGenerator::getNextInstance()
{
	int sectionToReturn;
	if (currentSection == 3)
	{
		sectionToReturn = 0;
		currentSection = 0;
	}
	else
	{
		currentSection++;
		sectionToReturn = currentSection;
	}
	return sectionsToGenerate[sectionToReturn];

}
