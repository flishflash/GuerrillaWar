#ifndef __DUMMY_ESC_H__
#define __DUMMY_ESC_H__

#include "Module.h"

class DummyESC : public Module {
	public:
		update_status PreUpdate() override;
};

#endif // !__DUMMYESC_H__

