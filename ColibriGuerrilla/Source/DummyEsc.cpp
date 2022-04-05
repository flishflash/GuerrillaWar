#include "DummyEsc.h"
#include <conio.h>

update_status DummyESC::PreUpdate() {
	if (_kbhit() && _getch() == 27) return update_status::UPDATE_STOP;
	LOG("ESCAPE NOT PRESSED\n");
	return update_status::UPDATE_CONTINUE;
}