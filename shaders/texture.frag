#version 130

uniform vec4 tint;
uniform sampler2D tex;

uniform float bloodAmount; // 0.0 to 1.0
uniform float grayAmount; // 0.0 to 1.0
uniform vec2 windowSize;

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
        //outColor = texColor * mix(vec4(1), tint, tint.a);
        outColor = texColor * tint;

       // vec2 distToCenter = vec2( abs(gl_FragCoord.x-windowSize.x/2), abs(gl_FragCoord.y-windowSize.y/2));
       // vec2 bloodFade = (pow(distToCenter, vec2(2.0)) / length(windowSize)) / 120.0f;
       // outColor.r += bloodFade.x * bloodFade.y;

        float gray = dot(outColor.rgb, vec3(0.299, 0.587, 0.114));
        outColor = vec4(  mix( outColor.rgb, vec3(gray), min(grayAmount * 2.0, 1) ), 1);

        if (grayAmount > 0.5)
        {
            outColor *= 1.0 - grayAmount * 2.0 + 1.0;
        }

        /*int fogRegionHeight = 100;
        if (gl_FragCoord.y < fogRegionHeight)
        {
            float fogFactorY = (gl_FragCoord.y / fogRegionHeight);
            outColor *= min( 1.0f, pow(fogFactorY, 0.5) );
        }
        */
}
