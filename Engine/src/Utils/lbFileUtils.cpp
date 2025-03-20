#include "Utils/lbFileUtils.h"

namespace Lambix
{
    std::filesystem::path lbJoinPath(const std::filesystem::path &path1, const std::filesystem::path &path2)
    {
        return path1 / path2;
    }
}