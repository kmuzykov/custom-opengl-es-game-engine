uniform sampler2D u_texture0;

varying highp vec2 v_texCoords;
varying lowp float v_light_intensity;

void main()
{
    highp vec2 texCoords = v_texCoords;
    texCoords.y = 1.0 - texCoords.y;
    
    highp vec4 color = texture2D(u_texture0, texCoords);
    color = vec4(color.rgb * v_light_intensity, color.a);
    gl_FragColor =  color;
}