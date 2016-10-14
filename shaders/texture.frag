#version 130

uniform vec4 tint;
uniform sampler2D tex;

uniform float applyFog;
uniform vec2 windowSize;

in vec2 texCoordFrag;
out vec4 outColor;


void main()
{
	// Discard fragment if texture sample has alpha < 0.5
	// otherwise compose the texture sample with the fragment's interpolated color
	vec4 texColor = texture(tex, texCoordFrag);
        if(texColor.a < 0.5f) discard;
        outColor = texColor * mix(vec4(1), tint, tint.a);

        /*int fogRegionHeight = 100;
        if (gl_FragCoord.y < fogRegionHeight)
        {
            float fogFactorY = (gl_FragCoord.y / fogRegionHeight);
            outColor *= min( 1.0f, pow(fogFactorY, 0.5) );
        }
        */
}
