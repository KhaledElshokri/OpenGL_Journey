#shader vertex
#version 330 core
        
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord; // v_* means its a varing which is used to pass data from vertex to fragment shader
        
void main()
{
    gl_Position = position;
    v_TexCoord = texCoord;
};

#shader fragment
#version 330 core
        
layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform vec4 u_Color; // u_* means its a uniform
uniform sampler2D u_Texture;     

void main()
{
    vec4 texColor = texture(u_Texture, v_TexCoord);
    color = texColor; //RGBA
};