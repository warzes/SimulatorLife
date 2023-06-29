#include "stdafx.h"
#include "Context.h"
#include "GameApp.h"
//-----------------------------------------------------------------------------
#pragma comment( lib, "OpenGL32.lib" )
#pragma comment( lib, "glu32.lib" )
//-----------------------------------------------------------------------------
int main(
	[[maybe_unused]] int   argc,
	[[maybe_unused]] char* argv[])
{
	try
	{
		Context context;
		context.Run(std::make_unique<GameApp>());
	}
	catch (const Exception& exc)
	{
		std::cout << "ERROR: " + exc.What();
	}
	catch (...)
	{
		std::cout << "Unknown error";
	}
}
//-----------------------------------------------------------------------------