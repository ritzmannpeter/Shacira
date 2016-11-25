
#include "thunkmod.h"

class ThunkModule
{
public:
	ThunkModule();
	~ThunkModule();
};

ThunkModule::ThunkModule()
{
//Message("Construct module");
}

ThunkModule::~ThunkModule()
{
//Message("Destroy module");
	FreeRessources();
}

ThunkModule _ThunkModule;


