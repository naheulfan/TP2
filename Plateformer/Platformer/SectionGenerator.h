#pragma once
#include "Sections.h"
#include <queue>
class SectionGenerator
{
public:
	SectionGenerator();
	~SectionGenerator();
	Sections* getNextInstance();
private:
	Sections* sectionsToGenerate[3];
	int currentSection;

};

