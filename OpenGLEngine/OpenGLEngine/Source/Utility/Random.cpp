#include "Random.h"



float RandomFloat(float min, float max)
{
  assert(max > min);
  float random = ((float)rand()) / (float)RAND_MAX;
  float range = max - min;
  return (random*range) + min;
}

int RandomInt(int min, int max, bool includeMaxVal /*= false*/) //range : [min, max) or [min,max]
{
  float range = max - min;
  if (includeMaxVal)
    range++;

  return min + rand() * range / (float(RAND_MAX) + 1);
}
