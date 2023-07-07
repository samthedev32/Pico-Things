#include <stdlib.h>
#include <math.h>

float *freq_create(int buf_size, float density, float freq, float offset)
{
    float *ret = (float *)malloc(buf_size * sizeof(float));

    for (int i = 0; i < buf_size; i++)
        ret[i] = sin(i * density * M_PI * freq + offset);

    return ret;
}

float freq_get(float i, float freq, float offset)
{
    return sin(i * M_PI * freq + offset);
}

float freq_appearance(float *buffer, int size, float freq)
{
    return 0.0f;
}