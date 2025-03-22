#include "lbPanel.h"

namespace Lambix
{
    ImVec4 ToImVec4(uint32_t value)
    {
        // 提取各个通道的值
        uint8_t r = (value >> 24) & 0xff;
        uint8_t g = (value >> 16) & 0xff;
        uint8_t b = (value >> 8) & 0xff;
        uint8_t a = value & 0xff;

        // 将通道值从0 - 255范围转换为0.0 - 1.0范围
        float fr = static_cast<float>(r) / 255.0f;
        float fg = static_cast<float>(g) / 255.0f;
        float fb = static_cast<float>(b) / 255.0f;
        float fa = static_cast<float>(a) / 255.0f;

        return ImVec4(fr, fg, fb, fa);
    }

} // namespace Lambix
