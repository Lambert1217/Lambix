#include "Core/Utils/lbFileUtils.h"

namespace Lambix
{
    std::string lbJoinPath(const std::string &path1, const std::string &path2)
    {
        return path1 + "/" + path2;
    }
}