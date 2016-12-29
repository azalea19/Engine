#include "PrintAPI.h"
#include "LuaManager.h"

static void PrintInt(int val)
{
  printf("%d", val);
}

static void PrintString(string val)
{
  printf("%s", val.c_str());
}

static void PrintFloat(float val)
{
  printf("%f", val);
}

static void PrintRef(LuaRef val)
{
  if (val.isNil())
    PrintString("Nil");
  else if (val.isNumber())
    PrintFloat(val);
  else if (val.isString())
    PrintString(val);
  else
    PrintString("No print function defined for this type.\n");
}

void PrintAPI::Expose(LuaContextHandle contextHandle, string luaAPIName)
{
  LuaContext* pContext = LuaManager::GetInstance().GetContext(contextHandle);
  pContext->ExposeFunction(luaAPIName, "printInt", PrintInt);
  pContext->ExposeFunction(luaAPIName, "printString", PrintString);
  pContext->ExposeFunction(luaAPIName, "printFloat", PrintFloat);
  pContext->ExposeFunction(luaAPIName, "print", PrintRef);
}
