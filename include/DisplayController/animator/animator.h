#include <Arduino.h>

// fps : frames per second.
// bpf : bytes per frame (in frames array).
// frames : frames array.
// repeat : repeat animation "repeat" times. so would run animation for repeat+1 times.
class Animator
{
public:
    Animator() {}

    void animateArray(int fps, int count_frames, int repeat, int reverse, const uint8_t frames[][1024], uint8_t chXpos, uint8_t chYpos, uint8_t chWidth, uint8_t chHeight)
    {
        uint8_t temp[1024];

        for (int r = 0; r < repeat + 1; r++)
        {
            for (int i = 0; i < count_frames; i++)
            {
                // // ssd1306_FillBlueArea(backgroundColor);
                for (int j = 0; j < 1024; j++)
                {
                    temp[j] = frames[i][j];
                }
                display.clearDisplayArea(chXpos, chYpos, chWidth, chHeight);
                display.drawBitmap(chXpos, chYpos, temp, chWidth, chHeight, 1);
                display.display();
                delay(1000 / fps);
            }
            if (reverse == 1)
            {
                for (int i = count_frames - 1; i >= 0; i--)
                {
                    // ssd1306_Fill(backgroundColor);
                    for (int j = 0; j < 1024; j++)
                    {
                        temp[j] = frames[i][j];
                    }
                    display.clearDisplayArea(chXpos, chYpos, chWidth, chHeight);
                    display.drawBitmap(chXpos, chYpos, temp, chWidth, chHeight, 1);
                    display.display();
                    delay(1000 / fps);
                }
            }
        }
    }
};
