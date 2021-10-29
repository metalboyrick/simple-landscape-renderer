#version 330 core

layout(location = 0) in vec3 v_in_position;

out vec3 v_out_textureCoordinates;

uniform mat4 v_uni_projection;
uniform mat4 v_uni_view;

void main()
{
    vec4 pos = v_uni_projection * v_uni_view * vec4(v_in_position, 1.0f);
    // Having z equal w will always result in a depth of 1.0f
    gl_Position = pos.xyww;
    v_out_textureCoordinates = vec3(v_in_position.x, v_in_position.y, -1 * v_in_position.z);
}