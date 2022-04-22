#pragma once
#include "Module.h"
enum class Idioma {
	CAT = 'C',
	ESP = 'S',
	ENG = 'E'
};
class ModuleState : public Module {
	public:
		bool god = false;
		Idioma lang = Idioma::ESP;
};