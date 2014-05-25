uniform sampler2D u_texture0;

varying highp vec2 v_texCoords;
varying lowp float v_light_intensity;

void main()
{
    highp vec4 color = texture2D(u_texture0, v_texCoords);
    color = vec4(color.rgb * v_light_intensity, color.a);
    gl_FragColor =  color;
}