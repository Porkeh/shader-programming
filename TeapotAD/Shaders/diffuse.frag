#version 430

in vec3 vertPos;
in vec3 N;
in vec3 lightPos;

uniform vec3 La; //ambient light intensity
uniform vec3 Ka;
uniform vec3 Kd;            // Diffuse reflectivity
uniform vec3 Ld;            // Diffuse light intensity
uniform vec3 Ks;

layout( location = 0 ) out vec4 FragColour;

void main() {

   //Calculate the light vector
   vec3 L = normalize(lightPos - vertPos);  
   
   //Ambient
   vec4 Ia = vec4((La*Ka),1);
   //Ia = clamp(Ia, 0.0, 1.0);
   vec4 ambient = Ia;
   
   
    
   //calculate Diffuse Light Intensity making sure it is not negative 
   //and is clamped 0 to 1  
   vec4 Id = vec4(Ld,1.0) * max(dot(N,L), 0.0);
   Id = clamp(Id, 0.0, 1.0);     
   vec4 diff = vec4(Kd,1.0) * Id;
   //Multiply the Reflectivity by the Diffuse intensity
   
   
   //specular
  vec4 surfaceReflection = vec4((reflect(L,N)),1.0);
  float dp = max(0.0,dot(surfaceReflection, normalize(vec4(vertPos,1.0))));
  dp = pow(dp,5);
  vec4 Is = vec4(Ld,1.0) * dp;
  //Is = clamp(Is, 0.0,1.0);
  vec4 spec = Is * vec4(Ks,1.0);

   //att
   vec3 dist = vec3(lightPos - vertPos);
   float distSquare = pow(dist.x,2) + pow(dist.y,2) + pow(dist.z,2);
   float D = sqrt(distSquare);
   float att = 1.0 / (1.0 + (0.01 * D) + (0.001 * pow(D,2.0)));
 
//   clamp(att,0.0, 1.0);


   FragColour = ambient + att * (diff + spec);

}
