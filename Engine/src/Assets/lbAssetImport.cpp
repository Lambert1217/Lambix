#include "lbAssetImport.h"
#include "lbTextureSourceAsset.h"
#include "lbTextureAsset.h"

namespace Lambix
{
    lbAssetImport::lbAssetImport()
    {
        // 注册导入器
        // lbTextureSourceAsset
        RegisterImporter<lbTextureSourceAsset>("jpg");
        RegisterImporter<lbTextureSourceAsset>("png");
        // lbTexture2DAsset
        RegisterImporter<lbTexture2DAsset>("ltex");
    }
}