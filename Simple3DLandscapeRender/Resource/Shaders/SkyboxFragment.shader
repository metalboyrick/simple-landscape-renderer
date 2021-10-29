#version 430 core

in vec3 v_out_textureCoordinates;

out vec4 f_out_color;

uniform samplerCube f_uni_texture;

void main()
{
    f_out_color = texture(f_uni_texture, v_out_textureCoordinates);
}