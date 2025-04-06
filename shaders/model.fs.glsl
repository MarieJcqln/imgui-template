#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;

//
uniform vec3 viewPos;
//


uniform vec3 lightPos1;
uniform vec3 lightColor1;
uniform bool lightActive1;

uniform vec3 lightPos2;
uniform vec3 lightColor2;
uniform bool lightActive2;

// uniform vec3 lightPos;
// uniform vec3 viewPos;
// uniform vec3 lightColor;

uniform vec3 Kd;
uniform vec3 Ka;
uniform vec3 Ks;
uniform float Ns;

uniform bool useTexture;
uniform sampler2D map_Kd;

vec3 computeLight(vec3 lightPos, vec3 lightColor, vec3 N, vec3 V, vec3 diffuseColor) {
    vec3 L = normalize(lightPos - FragPos);
    vec3 H = normalize(L + V);

    float diff = max(dot(N, L), 0.0);
    float spec = pow(max(dot(N, H), 0.0), Ns);

    vec3 ambient = Ka * (lightColor * 0.25);
    vec3 diffuse = diff * diffuseColor * lightColor;
    vec3 specular = spec * Ks * lightColor;

    return ambient + diffuse + specular;
}

void main() {
    vec3 N = normalize(Normal);
    vec3 V = normalize(viewPos - FragPos);
    vec3 diffuseColor = useTexture ? texture(map_Kd, TexCoords).rgb : Kd;

    vec3 result = vec3(0.0);

    if (lightActive1)
        result += computeLight(lightPos1, lightColor1, N, V, diffuseColor);

    if (lightActive2)
        result += computeLight(lightPos2, lightColor2, N, V, diffuseColor);

    FragColor = vec4(result, 1.0);
}
