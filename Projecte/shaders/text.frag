#version 130

uniform vec4 tint;
uniform sampler2D tex;
uniform float stroke = 0.0;
uniform vec2 texCoordDispl;
uniform vec4 strokeColor;
uniform vec2 textureSize;
uniform float grayAmount; // 0.0 to 1.0

in vec2 texCoordFrag;
out vec4 outColor;

// uservj06
// Syiryeg4

void main()
{
    vec4 texColor = texture(tex, texCoordFrag);
    float stepx = 1.0 / textureSize.x;
    float stepy = 1.0 / textureSize.y;
    float letterWidth  = 0.03125f;
    if (texColor.a < 0.95)
    {
        if (stroke <= 0) discard;

        for (float dx = -stroke; dx <= stroke; dx += stroke)
        {
            for (float dy = -stroke; dy <= stroke; dy += stroke)
            {
                if ((texCoordFrag.x - texCoordDispl.x) + dx * stepx <= letterWidth &&
                    (texCoordFrag.x - texCoordDispl.x) + dx * stepx >= 0.0 &&
                    texture(tex, texCoordFrag + vec2(dx * stepx, dy * stepy)).a > 0.95)
                {
                    outColor = strokeColor;
                    if (grayAmount > 0.5)
                    {
                        outColor *= 1.0 - grayAmount * 2.0 + 1.0;
                    }
                    return;
                }
            }
        }
        discard;
    }
    else
    {
        outColor = texColor * tint;
        if (grayAmount > 0.5)
        {
            outColor *= 1.0 - grayAmount * 2.0 + 1.0;
        }
    }

}
