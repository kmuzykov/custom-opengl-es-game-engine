uniform sampler2D u_texture0;
varying highp vec2 v_texCoords;

void main()
{
    gl_FragColor = texture2D(u_texture0, v_texCoords);
}