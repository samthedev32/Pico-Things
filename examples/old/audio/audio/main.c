#include "audio.h"

#include "sample.h"

int main()
{
    audio_init(15);

    audio_set(WAV_DATA, WAV_DATA_LENGTH);

    audio_play(true);
    while (!audio_is_finished())
    {
    }

    return 0;
}