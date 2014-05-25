attribute vec4 a_position;
attribute vec3 a_normal;
attribute vec2 a_texCoords;

uniform int  u_lights_count;
uniform vec3 u_lights_pos[8];
uniform float u_lights_intensity[8];

uniform mat4 u_mvMatrix;
uniform mat4 u_pMatrix;

uniform mat3 u_normalMatrix;

varying highp vec2 v_texCoords;
varying lowp float v_light_intensity;

const lowp float maxLightLength = 7.0;

void main()
{
    //passing texture coords
    v_texCoords = a_texCoords;
    
    //Vertex position in model coords
    vec3 modelViewVertex = vec3(u_mvMatrix * a_position);
    
    //Normal in model coords
    vec3 modelViewNormal = normalize(vec3(u_mvMatrix * vec4(a_normal,0)));
    
    v_light_intensity = 0.0;
    lowp vec3 lightPos;
    lowp float lightIntensity;
    lowp vec3 lightVector;
    lowp float lightResult;
    lowp float lightDistKoof;
    
    for (int i=0; i < u_lights_count; i++)
    {
        lightPos = u_lights_pos[i];
        lightIntensity = u_lights_intensity[i];
        
        lightVector = lightPos - modelViewVertex;
        lightDistKoof = max(0.1, min(1.0, maxLightLength/length(lightVector)));
        
        lightVector = normalize(lightVector);
        lightResult = lightDistKoof * lightIntensity * max(0.1, dot(modelViewNormal, lightVector));
        
        v_light_intensity = v_light_intensity + lightResult;
    }
    
    gl_Position = u_pMatrix * u_mvMatrix * a_position;
}
