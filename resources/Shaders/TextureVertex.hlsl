// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See License.md in the repository root for more information.
// Originally taken from the TerraFX repository. Licenced under the MIT Licence (MIT). See Licence.md in https://github.com/terrafx/terrafx for more information.

#include "TextureTypes.hlsl"

PSInput main(VSInput input)
{
    PSInput output;
    output.position = float4(input.position, 1.0f);
    output.uv = input.uv;
    return output;
}
