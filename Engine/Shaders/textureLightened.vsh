attribute vec4 a_position;
attribute vec3 a_normal;
attribute vec2 a_texCoords;

uniform mat4 u_mvMatrix;
uniform mat4 u_pMatrix;

uniform mat3 u_normalMatrix;

uniform float u_light0_intensity;
uniform vec3  u_light0_pos;

uniform float u_light1_intensity;
uniform vec3  u_light1_pos;

uniform float u_light2_intensity;
uniform vec3  u_light2_pos;

varying highp vec2 v_texCoords;
varying lowp float v_light_intensity;

void main()
{
    //passing texture coords
    v_texCoords = a_texCoords;
    
    //Vertex position in model coords
    vec3 modelViewVertex = vec3(u_mvMatrix * a_position);
    
    //Normal in model coords
    vec3 modelViewNormal = normalize(vec3(u_mvMatrix * vec4(a_normal,0)));

    //Light vector in model coords
    vec3 light0Vector = normalize(u_light0_pos - modelViewVertex);
    vec3 light1Vector = normalize(u_light1_pos - modelViewVertex);
    vec3 light2Vector = normalize(u_light2_pos - modelViewVertex);
    
    float light0Intensity = u_light0_intensity * max(0.1, dot(modelViewNormal, light0Vector));
    float light1Intensity = u_light1_intensity * max(0.1, dot(modelViewNormal, light1Vector));
    float light2Intensity = u_light2_intensity * max(0.1, dot(modelViewNormal, light2Vector));
    
    
    //v_light_intensity = max(max(light0Intensity,light1Intensity),light2Intensity);
    v_light_intensity = light0Intensity + light1Intensity + light2Intensity;
    
    gl_Position = u_pMatrix * u_mvMatrix * a_position;
}
