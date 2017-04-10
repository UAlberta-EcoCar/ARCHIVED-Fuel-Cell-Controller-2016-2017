#include <Arduino.h>
#include "ThermistorLookup.h"


int8_t Temp[] = {-40,-35,-30,-25,-20,-15,-10,-5,0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125};
float vn[] = {0.977763542f,0.968638264f,0.956469218f,0.940542761f,0.920066313f,0.894356414f,0.862823531f,0.825062278f,0.781187365f,0.731543624f,0.677117303f,0.619266631f,0.559626563f,0.5f,0.442032786f,0.387130976f,0.336328703f,0.29029694f,0.249221067f,0.213162222f,0.181830082f,0.154855776f,0.131823864f,0.112176499f,0.095562831f,0.081498627f,0.069603f,0.059593556f,0.051089349f,0.043922214f,0.037850944f,0.032694912f,0.028333787f,0.024599598f};


float therm_lookup(float norm_v)
{
    float temp;
    uint8_t indexl = 0;
    uint8_t indexh = 0;
    uint8_t max = sizeof(vn)/4-1; //size of gives number of bytes, divide by 4 gives number of floats. minus 1 gives max index

    if(norm_v > vn[0])
    {
      return(Temp[0]);
    }

    if(norm_v < vn[max])
    {
      return(Temp[max]);
    }

    for(uint8_t i = 0;i<=max;i++)
    {
      Serial.print(Temp[i]);
      Serial.print(" ");
      Serial.println(vn[i]);
    }

    for(uint8_t i = 0;i<max;i++)
    {
      if(vn[i]>norm_v)
      {
        indexl = i;
      }
    }

    for(int8_t i = max;i>=0;i--)
    {
      if(vn[i]<norm_v)
      {
        indexh = i;
      }
    }

    int8_t dT = Temp[indexh] - Temp[indexl];
    float dv = vn[indexh] - vn[indexl];

    temp = (float)dT / dv * (norm_v - vn[indexl]) + Temp[indexl];

    return(temp);
}
