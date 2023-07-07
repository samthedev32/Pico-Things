#include "mic.h"

typedef struct speechsource
{
    int gpio, in;

    int bufsize;
    float *buffer;

    float interval;
    float prevtime;

} speechsource;

void speech_init(speechsource *ss, int in, int bufsize, float interval_ms)
{
    ss->in = in;
    ss->gpio = 26 + in;

    ss->bufsize = bufsize;
    ss->buffer = (float *)malloc(sizeof(float) * bufsize);

    ss->interval = interval_ms;
    ss->prevtime = -1;

    // mic_init(ss->in);
}

void speech_update(speechsource *ss)
{
    int size = ss->bufsize - 1;

    for (int i = 0; i < size; i++)
        ss->buffer[i] = ss->buffer[i + 1];

    to_ms_since_boot(get_absolute_time());

    // ss->buffer[size] = mic_read(ss->in);
}