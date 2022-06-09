#version 120

uniform vec4 u_Color;
uniform sampler2D u_Sampler;

void main(void)
{
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture2D(u_Sampler, gl_TexCoord[0].st).r);
    gl_FragColor = u_Color * sampled;
}