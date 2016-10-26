#version 130

uniform vec4 tint;
uniform sampler2D tex;

uniform float bloodAmount; // 0.0 to 1.0
uniform float grayAmount; // 0.0 to 1.0
uniform float isSelectedByPlayer = 0; // For blocks
uniform vec2 windowSize;
uniform vec2 texCoordDispl;

in vec2 texCoordFrag;
out vec4 outColor;

// uservj06
// Syiryeg4

void main()
{
    // Discard fragment if texture sample has alpha < 0.5
    // otherwise compose the texture sample with the fragment's interpolated color
    vec4 texColor = texture(tex, texCoordFrag);
    if(texColor.a < 0.5f) discard;
    outColor = texColor * tint;

    float gray = dot(outColor.rgb, vec3(0.299, 0.587, 0.114));
    outColor = vec4(  mix( outColor.rgb, vec3(gray), min(grayAmount * 2.0, 1) ), 1);

    if (grayAmount > 0.5)
    {
        outColor *= 1.0 - grayAmount * 2.0 + 1.0;
    }

    // ONLY FOR BLOCK
    if (isSelectedByPlayer > 0)
    {
        outColor += vec4(1, 1, 1, 1) * 0.3;
    }
    //
}
