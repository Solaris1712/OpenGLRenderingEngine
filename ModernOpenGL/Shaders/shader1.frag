#version 330                                                    
                                                                 
in vec4 vCol;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
                                                    
out vec4 color;

struct DirectionalLight{
	vec3 color;
	float ambientIntensity;
	vec3 direction;
	float diffuseIntensity;
};

struct Material{
	float specularIntensity;
	float shininess;
};


uniform sampler2D theTexture;
uniform DirectionalLight dLight;
uniform Material material;

uniform vec3 eyePosition;  
                                                
void main()                                                      
{
	vec4 ambientColor = vec4(dLight.color,1.f)*dLight.ambientIntensity;
	
	float diffuseFactor = max(dot(normalize(Normal),normalize(dLight.direction)),0.f);
	vec4 diffuseColor = vec4(dLight.color,1.f)*dLight.diffuseIntensity*diffuseFactor;
	
	vec4 specularColor = vec4(0,0,0,0);
	
	if(diffuseFactor > 0.0f)
	{
		vec3 eyeToFrag = normalize(eyePosition - FragPos);
		vec3 reflectedVertex = normalize(reflect(dLight.direction,normalize(Normal)));
		
		float specularFactor = dot(eyeToFrag,reflectedVertex);
		if(specularFactor > 0.f)
		{
			specularFactor = pow(specularFactor,material.shininess);
			specularColor = vec4(dLight.color * material.specularIntensity*specularFactor,1.f);
		}
		
	}
	
	color = texture(theTexture,TexCoord) * (ambientColor + diffuseColor + specularColor);		                                             
}