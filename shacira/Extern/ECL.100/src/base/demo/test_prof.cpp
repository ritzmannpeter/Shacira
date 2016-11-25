
#include <iostream.h>
#include "base/eb_prof.hpp"
#include "base/eb_str.hpp"


void TestPrivate()
{
   cProfile profile(".\\TEST_PROF.INI");
   cString value = profile.read("Application", "Key", "DefaultValue");
   profile.write("Application", "Key", value);
}

void TestPublic()
{
   cProfile profile;
   cString app_path = "HKEY_CURRENT_USER/Software/Sirius Cybernetic Corp/Nutrimat/Drink/Tea";
   long hot_water = profile.read(app_path, "HotWater", 1);
   profile.write(app_path, "HotWater", hot_water + 1);
   cString leafes = profile.read(app_path, "Leafes", "TeaPlant");
   profile.write(app_path, "Leafes", leafes + "!");
}

void TestCurUsr()
{
   cProfile profile(":USR:Sirius Cybernetic Corp/Nutrimat");
   cString app_path = "Drink/Tea";
   long hot_water = profile.read(app_path, "HotWater", 1);
   profile.write(app_path, "HotWater", hot_water + 1);
   cString leafes = profile.read(app_path, "Leafes", "TeaPlant");
   profile.write(app_path, "Leafes", leafes + "!");
}

int main()
{
   TestPrivate();
   TestPublic();
   TestCurUsr();
   return 0;
}

