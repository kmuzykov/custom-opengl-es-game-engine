attribute vec4 a_position;
attribute vec4 a_normal;
attribute vec2 a_texCoords;

uniform mat4 u_mvMatrix;
uniform mat4 u_pMatrix;

varying highp vec2 v_texCoords;

void main()
{
    vec4 n = a_normal;
    v_texCoords = a_texCoords;
    gl_Position = u_pMatrix * u_mvMatrix * a_position;
}
