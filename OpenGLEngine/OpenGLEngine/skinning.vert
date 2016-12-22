#version 330                                                                        
                                                                                    
layout (location = 0) in vec3 Position;                                             
layout (location = 1) in vec2 TexCoord;                                             
layout (location = 2) in vec3 Normal;                                               
layout (location = 3) in ivec4 BoneIDs;
layout (location = 4) in vec4 Weights;

out vec2 TexCoord0;
out vec3 Normal0;                                                                   
out vec3 WorldPos0;  
out float val; 

out vec4 color;                                                              

const int MAX_BONES = 100;

uniform mat4 mvp;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 BONES[MAX_BONES];


void main()
{       
    mat4 BoneTransform = BONES[BoneIDs[0]] * Weights[0];
    BoneTransform     += BONES[BoneIDs[1]] * Weights[1];
    BoneTransform     += BONES[BoneIDs[2]] * Weights[2];
    BoneTransform     += BONES[BoneIDs[3]] * Weights[3];

    vec3 PosL    = (BoneTransform * vec4(Position, 1.0)).xyz;
    gl_Position  = mvp * vec4(PosL, 1.0);

    TexCoord0    = TexCoord;
    vec4 NormalL = BoneTransform * vec4(Normal, 0.0);
    Normal0      = (modelMatrix * NormalL).xyz;
    WorldPos0    = (modelMatrix * vec4(PosL, 1)).xyz;                  
}
