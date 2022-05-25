
# CpuRayTracingRenderer
## How To Build This Project
You should download the Cmake from this link:
https://cmake.org/

And you should download the Vcpkg from this link:
https://github.com/microsoft/vcpkg

( I also push the Vcpkg tools into the project . You can use it easily. )

And then , I will show how to build this project by Cmake GUI . You can see the operation instruction in the follow picture . Good luck to you building it .

![image](https://github.com/1393650770/CpuRayTracingRenderer/blob/main/image/operation_instruction_picture.png)
## Show The Render Result
![image](https://github.com/1393650770/CpuRayTracingRenderer/blob/main/image/result-Level-1.png)

## Feature(Already done)
### ① My Math Library --- TinyGlm
### ---Library Supported Data Types : Vec2 Vec3 Vec4 Mat4
#### -------Vector Supported :
##### -----------Template
##### -----------Add / Sub / Div / Mul
##### -----------Dot / Cross
##### -----------Normalize / Length

#### -------Matrix Supported :
##### -----------Template
##### -----------Add/ Sub / Div / Mul
##### -----------Cofactor / Adjoint
##### -----------Transpose / Inverse
##### -----------Multiply with vector
### ② Multithreading Acceleration Rendering
### ---Thread Pool
### ---Message Queue

### ③ Space Accelerating Structurer
### ---BVH
### ④ Object
### ---Sphere
### ---Rectangle
### ---Triangle
### ---MeshTriangle
### ④ Material
### ---Diffuse
### ---Microfacet BRDF
### ⑤ Sampling
### ---Cos-Weighted Importance Sampling
### ⑤ Light
### ---SphereLight (PointLight)
### ---AreaLight
### ⑤ Camera
### ---Perspective Camera

### ⑤ Tool
### ---Toon-mapping
### ---NormalSpace To WorldSpace
### ---Random number generator

## Feature(To done list)
### ③ Space Accelerating Structurer
### ---SAH
### ---Octree
### ④ Object(Maybe will do)
### ---OBJLoader
### ---Texture
### ④ Material
### ---Dielectrics
### ---BSSRDF 
### ⑤ Sampling
### ---Importance Sampling
### ---Multiple Importance Sampling
### ⑤ Post process
### ---TAA
### ⑤ Tool
### ---Toon-mapping
### ---NormalSpace To WorldSpace
### ---Random number generator



