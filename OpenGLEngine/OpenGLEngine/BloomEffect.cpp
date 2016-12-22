#include "BloomEffect.h"
#include "Texture.h"

BloomEffect::BloomEffect()
{
  for(int i = 0; i < 3; i++)
    tempTex[i] = CreateColourFTexture();
}

void BloomEffect::Apply(GLuint inputTex, GLuint outputTex, int bloomRadius)
{
  m_splitEffect.Apply(inputTex, tempTex[0], tempTex[1]);
  m_blurEffect.Apply(tempTex[1], tempTex[2], bloomRadius);
  m_blurEffect.Apply(tempTex[2], tempTex[1], bloomRadius);
  m_blurEffect.Apply(tempTex[1], tempTex[2], bloomRadius);
  m_blendEffect.Apply(tempTex[0], tempTex[2], outputTex);
}
