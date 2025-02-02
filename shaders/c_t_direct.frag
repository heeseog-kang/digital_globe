
#version 330 core
struct ulight {
    vec3 position;  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct umaterial  {
    sampler2D diffuse;
    vec3 specular;
    float shininess;
}; 

uniform ulight light;
uniform umaterial material;
uniform vec3 view_pos;

in vec2 tex_coord;
in vec3 normal;
in vec3 frag_position;

out vec4 frag_color;


void main()
{
        // ambient
    vec3 ambient = light.ambient * texture(material.diffuse, tex_coord).rgb;
  	
    // diffuse 
    vec3 norm = normalize(normal);
    vec3 light_dir = normalize(-light.position);
    float diff = max(dot(light_dir, norm), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, tex_coord).rgb;  

    vec3 specular = vec3(0, 0, 0);
    // specular
    //if( diff > 0 ){
//        vec3 view_dir = normalize(view_pos - frag_position);
//        vec3 reflect_dir = reflect(-light_dir, norm);  
//        float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
//        specular = light.specular * (spec * material.specular);   
    //}
    frag_color = vec4(ambient + diffuse + specular, 1.0);
}
