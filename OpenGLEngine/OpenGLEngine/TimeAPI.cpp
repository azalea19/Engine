#include "TimeAPI.h"
#include <time.h>



float TimeAPI::ElapsedTimeMs()
{
	float time = clock() / float(CLOCKS_PER_SEC);

	return time;

}
void TimeAPI::Expose(LuaContextHandle contextHandle, string luaAPIName)
{
	LuaContext* pContext = LuaManager::GetInstance().GetContext(contextHandle);
	pContext->ExposeFunction(luaAPIName, "elapsedTimeMs", ElapsedTimeMs);
}