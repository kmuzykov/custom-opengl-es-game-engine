uniform sampler2D u_texture0;
varying highp vec2 v_texCoords;

void main()
{
    lowp vec2 texCoords = v_texCoords;
    texCoords.y = 1.0 - texCoords.y;
    
    gl_FragColor = texture2D(u_texture0, texCoords);
}