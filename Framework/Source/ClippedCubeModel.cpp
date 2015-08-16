//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
// Updated by Gary Chang on 14/1/15
//
// Modified by: Liuai Hatter
//
// Copyright (c) 2014-2015 Concordia University. All rights reserved.
//



#include "ClippedCubeModel.h"
#include "Renderer.h"
#include "World.h"
#include "Model.h"

// Include GLEW - OpenGL Extension Wrangler
#include <GL/glew.h>
#include <iterator>

using namespace glm;
using namespace std;

ClippedCubeModel::ClippedCubeModel(vec4 planeL, vec3 size, bool s) : Model()
{
	// Create Vertex Buffer for all the vertices of the Cube
	vec3 halfSize = size * 1.0f;
	
    bool side = s;
    std::vector<Vertex> vertexBuffer;
    std::vector<Vertex> openFace;
    
	Vertex v1, v2, v3;
	v1.position = vec3(-halfSize.x,-halfSize.y,-halfSize.z);
	v1.normal = vec3(-1.0f, 0.0f, 0.0f);
	v1.color = vec3(0.0f, 1.0f, 1.0f);

	v2.position = vec3(-halfSize.x,-halfSize.y, halfSize.z);
	v2.normal = vec3(-1.0f, 0.0f, 0.0f);
	v2.color = vec3(0.0f, 1.0f, 1.0f);

	v3.position = vec3(-halfSize.x, halfSize.y, halfSize.z);
	v3.normal = vec3(-1.0f, 0.0f, 0.0f);
	v3.color = vec3(0.0f, 1.0f, 1.0f);

	Vertex v4, v5, v6;
	v4.position = vec3(-halfSize.x,-halfSize.y,-halfSize.z);
	v4.normal = vec3(-1.0f, 0.0f, 0.0f);
	v4.color = vec3(0.0f, 1.0f, 1.0f);

	v5.position = vec3(-halfSize.x, halfSize.y, halfSize.z);
	v5.normal = vec3(-1.0f, 0.0f, 0.0f);
	v5.color = vec3(0.0f, 1.0f, 1.0f);

	v6.position = vec3(-halfSize.x, halfSize.y,-halfSize.z);
	v6.normal = vec3(-1.0f, 0.0f, 0.0f);
	v6.color = vec3(0.0f, 1.0f, 1.0f);

		Vertex v7, v8, v9;
	v7.position = vec3( halfSize.x, halfSize.y,-halfSize.z);
	v7.normal = vec3( 0.0f, 0.0f,-1.0f);
	v7.color = vec3( 0.0f, 1.0f,1.0f);

	v8.position = vec3(-halfSize.x,-halfSize.y,-halfSize.z);
	v8.normal = vec3( 0.0f, 0.0f,-1.0f);
	v8.color = vec3( 0.0f, 1.0f,1.0f);

	v9.position = vec3(-halfSize.x, halfSize.y,-halfSize.z);
	v9.normal = vec3( 0.0f, 0.0f,-1.0f);
	v9.color = vec3(0.0f, 1.0f, 1.0f);

	Vertex v10, v11, v12;
	v10.position = vec3( halfSize.x, halfSize.y,-halfSize.z);
	v10.normal = vec3( 0.0f, 0.0f,-1.0f);
	v10.color = vec3( 0.0f, 1.0f,1.0f);

	v11.position = vec3( halfSize.x,-halfSize.y,-halfSize.z);
	v11.normal = vec3( 0.0f, 0.0f,-1.0f);
	v11.color = vec3( 0.0f, 1.0f,1.0f);

	v12.position = vec3(-halfSize.x,-halfSize.y,-halfSize.z);
	v12.normal = vec3( 0.0f, 0.0f,-1.0f);
	v12.color = vec3(0.0f, 1.0f, 1.0f);
    
    


	Vertex v13, v14, v15;

	v13.position = vec3( halfSize.x,-halfSize.y, halfSize.z);
	v13.normal = vec3( 0.0f,-1.0f, 0.0f);
	v13.color = vec3(0.0f, 1.0f, 1.0f);

	v14.position = vec3(-halfSize.x,-halfSize.y,-halfSize.z);
	v14.normal = vec3( 0.0f,-1.0f, 0.0f);
	v14.color = vec3(0.0f, 1.0f, 1.0f);

	v15.position = vec3( halfSize.x,-halfSize.y,-halfSize.z);
	v15.normal = vec3( 0.0f,-1.0f, 0.0f);
	v15.color = vec3(0.0f, 1.0f, 1.0f);

	Vertex v16, v17, v18;
	v16.position = vec3( halfSize.x,-halfSize.y, halfSize.z);
	v16.normal = vec3( 0.0f,-1.0f, 0.0f);
	v16.color = vec3(0.0f, 1.0f, 1.0f);

	v17.position = vec3(-halfSize.x,-halfSize.y, halfSize.z);
	v17.normal = vec3( 0.0f,-1.0f, 0.0f);
	v17.color = vec3(0.0f, 1.0f, 1.0f);

	v18.position = vec3(-halfSize.x,-halfSize.y,-halfSize.z);
	v18.normal = vec3( 0.0f,-1.0f, 0.0f);
	v18.color = vec3(0.0f, 1.0f, 1.0f);

	Vertex v19, v20, v21;
	v19.position = vec3(-halfSize.x, halfSize.y, halfSize.z);
	v19.normal = vec3( 0.0f, 0.0f, 1.0f);
	v19.color = vec3(0.0f, 1.0f, 1.0f);

	v20.position = vec3(-halfSize.x,-halfSize.y, halfSize.z);
	v20.normal = vec3( 0.0f, 0.0f, 1.0f);
	v20.color = vec3(0.0f, 1.0f, 1.0f);

	v21.position = vec3( halfSize.x,-halfSize.y, halfSize.z);
	v21.normal = vec3( 0.0f, 0.0f, 1.0f);
	v21.color = vec3(0.0f, 1.0f, 1.0f);

    Vertex v22, v23, v24;
	v22.position = vec3( halfSize.x, halfSize.y, halfSize.z);
	v22.normal = vec3( 0.0f, 0.0f, 1.0f);
	v22.color = vec3(0.0f, 1.0f, 1.0f);

	v23.position = vec3(-halfSize.x, halfSize.y, halfSize.z);
	v23.normal = vec3( 0.0f, 0.0f, 1.0f);
	v23.color = vec3(0.0f, 1.0f, 1.0f);

	v24.position = vec3( halfSize.x,-halfSize.y, halfSize.z);
	v24.normal = vec3( 0.0f, 0.0f, 1.0f);
	v24.color = vec3(0.0f, 1.0f, 1.0f);

    Vertex v25, v26, v27;
	v25.position = vec3( halfSize.x, halfSize.y, halfSize.z);
	v25.normal = vec3( 1.0f, 0.0f, 0.0f);
	v25.color = vec3(0.0f, 1.0f, 1.0f);
   
	v26.position = vec3( halfSize.x,-halfSize.y,-halfSize.z);
	v26.normal = vec3( 1.0f, 0.0f, 0.0f);
	v26.color = vec3(0.0f, 1.0f, 1.0f);

	v27.position = vec3( halfSize.x, halfSize.y,-halfSize.z);
	v27.normal = vec3( 1.0f, 0.0f, 0.0f);
	v27.color = vec3(0.0f, 1.0f, 1.0f);

	Vertex v28, v29, v30;
	v28.position = vec3( halfSize.x,-halfSize.y,-halfSize.z);
	v28.normal = vec3( 1.0f, 0.0f, 0.0f);
	v28.color = vec3(0.0f, 1.0f, 1.0f);

	v29.position = vec3( halfSize.x, halfSize.y, halfSize.z);
	v29.normal = vec3( 1.0f, 0.0f, 0.0f);
	v29.color = vec3(0.0f, 1.0f, 1.0f);

	v30.position = vec3( halfSize.x,-halfSize.y, halfSize.z);
	v30.normal = vec3( 1.0f, 0.0f, 0.0f);
	v30.color = vec3(0.0f, 1.0f, 1.0f);
  
	Vertex v31, v32, v33;
	v31.position = vec3( halfSize.x, halfSize.y, halfSize.z);
	v31.normal = vec3( 0.0f, 1.0f, 0.0f);
	v31.color = vec3(0.0f, 1.0f, 1.0f);

	v32.position = vec3( halfSize.x, halfSize.y,-halfSize.z);
	v32.normal = vec3( 0.0f, 1.0f, 0.0f);
	v32.color = vec3(0.0f, 1.0f, 1.0f);

	v33.position = vec3(-halfSize.x, halfSize.y,-halfSize.z);
	v33.normal = vec3( 0.0f, 1.0f, 0.0f);
	v33.color = vec3(0.0f, 1.0f, 1.0f);

	Vertex v34, v35, v36;
	v34.position = vec3( halfSize.x, halfSize.y, halfSize.z);
	v34.normal = vec3( 0.0f, 1.0f, 0.0f);
	v34.color = vec3(0.0f, 1.0f, 1.0f);

	v35.position = vec3(-halfSize.x, halfSize.y,-halfSize.z);
	v35.normal = vec3( 0.0f, 1.0f, 0.0f);
	v35.color = vec3(0.0f, 1.0f, 1.0f);

	v36.position = vec3(-halfSize.x, halfSize.y, halfSize.z);
	v36.normal = vec3( 0.0f, 1.0f, 0.0f);
	v36.color = vec3(0.0f, 1.0f, 1.0f);

    ClipTriangle( v1, v2, v3, planeL, vertexBuffer, openFace);
    ClipTriangle( v4, v5, v6, planeL, vertexBuffer, openFace);
	ClipTriangle( v7, v8, v9, planeL, vertexBuffer, openFace);
	ClipTriangle( v10, v11, v12, planeL, vertexBuffer, openFace);
	ClipTriangle( v13, v14, v15, planeL, vertexBuffer, openFace);
	ClipTriangle( v16, v17, v18, planeL, vertexBuffer, openFace);
	ClipTriangle( v19, v20, v21, planeL, vertexBuffer, openFace);
	ClipTriangle( v22, v23, v24, planeL, vertexBuffer, openFace);
	ClipTriangle( v25, v26, v27, planeL, vertexBuffer, openFace);
	ClipTriangle( v28, v29, v30, planeL, vertexBuffer, openFace);
	ClipTriangle( v31, v32, v33, planeL, vertexBuffer, openFace);
	ClipTriangle( v34, v35, v36, planeL, vertexBuffer, openFace);

	// Create a vertex array
	glGenVertexArrays(1, &mVertexArrayID);

	// Upload Vertex Buffer to the GPU, keep a reference to it (mVertexBufferID)
	glGenBuffers(1, &mVertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, vertexBuffer.size()*sizeof(Vertex), &vertexBuffer[0], GL_STATIC_DRAW);

	//Starting position
	mPosition = vec3(0, 4, 25);

    // IF you want it to go straight use: mVelocity = vec3(planeL);
	//Velocityof cubes going outwards and up
    if (side){
        mVelocity = vec3(10.0f, 10.0f, 0.0f);
    } else{
        mVelocity = vec3(-10.0f, 10.0f, 0.0f);
    }


}

ClippedCubeModel::~ClippedCubeModel()
{

	// Free the GPU from the Vertex Buffer
	glDeleteBuffers(1, &mVertexBufferID);
	glDeleteVertexArrays(1, &mVertexArrayID);
    
}


void ClippedCubeModel::ClipTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3, const vec4& L, std::vector<Vertex> &vertexBuffer, std::vector<Vertex> &oF)
{
    // TODO - Add clipping code, calculate new triangles
    // Add triangles to vertex buffer - vertice should be a multiple of 3
 
    
    //Counter to keep track of how many are kept
    int inCounter = 0;
    vector<Vertex> outside;

	//Keep vector of intersection vertices
    //vector<Vertex>openFace = of;

    //Intersecting plane and plane normal
    vec4 plane = L;
    vec3 pNormal = vec3(L.x, L.y, L.z);
    
    //Triangles that are inside will be stored in this:
    vector<Vertex> in;
    bool v1In = 0;
    bool v2In = 0;
    bool v3In = 0;
    
    //CHECKING TO SEE IF ALL VERTICES ARE IN, OR ATLEAST ONE VERTEX IN & ONE OUT:

    //Assuming that point on plane is <0,0,0>
    //TODO GET A POINT ON THE PLANE
    vec3 origin = vec3(0.0f,0.0f,0.0f);
    
    //FOR V1
    vec3 v1_toPlane = vec3(v1.position - origin);
    float cosA = dot(v1_toPlane, pNormal);
    if (cosA < 0){
        //Vertex is inside
        in.push_back(v1);
        v1In = true;
        inCounter++;
    } else {
        outside.push_back(v1);
    }
    
    
    //FOR V2
    vec3 v2_toPlane = vec3(v2.position - origin);
    float cosB = dot(v2_toPlane, pNormal);
    if (cosB < 0){
        //Vertex is inside
        in.push_back(v2);
        v2In = true;
        inCounter++;
    } else {
        outside.push_back(v2);
    }
    
    //FOR V3
    vec3 v3_toPlane = vec3(v3.position - origin);
    float cosC = dot(v3_toPlane, pNormal);
    if (cosC < 0){
        //Vertex is inside
        in.push_back(v3);
        v3In = true;
        inCounter++;
    } else {
        outside.push_back(v3);
    }
    
    
    if (inCounter == 3){
        // keep points since all are inside. just let them be
        vertexBuffer.push_back(v1);
        vertexBuffer.push_back(v2);
        vertexBuffer.push_back(v3);
        return;
    } else if (inCounter == 0){
        // All outside
        // Do not add to vertexBuffer.
        return;
    } else if (inCounter == 1 || inCounter == 2){
        //Clip triangle
        
        //vector<vec3> in;
        vector<vec3> intersection;
        
        //FIND INTERSECTIONS
        if((v1In && !v2In) || (!v1In && v2In)) {
            //vec3 vint = intersection of plane and line v2-v1
            vec3 vint  = vec3(GetIntersection(v1.position, v2.position, plane));
            intersection.push_back(vint);
            Vertex vintVertex;
            vintVertex.position = vint;
            vintVertex.normal =v1.normal;
            vintVertex.color =v1.color;
            oF.push_back(vintVertex);
        }
        if ((v2In && !v3In )|| (!v2In && v3In)) {
            // vec3 vint = intersection of plane and line v3-v2
             vec3 vint  = vec3(GetIntersection(v2.position, v3.position, plane));
            intersection.push_back(vint);
            Vertex vintVertex;
            vintVertex.position = vint;
            vintVertex.normal =v1.normal;
            vintVertex.color =v1.color;
            oF.push_back(vintVertex);
        }
        if((v3In && !v1In) || (!v3In & v1In)){
            // vec3 vint = intersection of plane and line v3-v1
             vec3 vint  = vec3(GetIntersection(v1.position, v3.position, plane));
            intersection.push_back(vint);
            Vertex vintVertex;
            vintVertex.position = vint;
            vintVertex.normal =v1.normal;
            vintVertex.color =v1.color;
            oF.push_back(vintVertex);
        }

       
		// If it's a quad, send 2 triangles that split up the quad
        if (in.size() == 2){
			//If V2 is inside, then do this to get CCW
			if (v2In){
				//TRIANGLE 1
				//Vertex 1
				vertexBuffer.push_back(in[0]);

				//Vertex 2 & Vertex 3
				//Get vertex opposite vertex 1 (vertex 2 does not fall on line between vertex 1 & outside vertex)
				float ab = glm::distance(in[0].position, intersection[0]);
				float cd = glm::distance(outside[0].position, intersection[0]);
				float ad = glm::distance(in[0].position, outside[0].position);
				//If the segments don't equal the total, then Vertex 2 is opposite/not on the line.
				if (ab + cd != ad){
					Vertex vertex2;
					vertex2.position = intersection[0];
					vertex2.normal = v1.normal;
					vertex2.color = v1.color;
					vertexBuffer.push_back(vertex2);

					//Take the remaining vertex as Vertex3
					Vertex vertex3;
					vertex3.position = intersection[1];
					vertex3.normal = v1.normal;
					vertex3.color = v1.color;
					vertexBuffer.push_back(vertex3);
				}
				else {
					Vertex vertex2;
					vertex2.position = intersection[1];
					vertex2.normal = v1.normal;
					vertex2.color = v1.color;
					vertexBuffer.push_back(vertex2);

					//Take the remaining vertex as Vertex3
					Vertex vertex3;
					vertex3.position = intersection[0];
					vertex3.normal = v1.normal;
					vertex3.color = v1.color;
					vertexBuffer.push_back(vertex3);
				}

				//TRIANGLE 2
				//Vertex1
				vertexBuffer.push_back(in[0]);
				//Vertex2
				vertexBuffer.push_back(in[1]);
				//Vertex3
				//Get vertex opposite vertex 1 (vertex 3 does not fall on line between vertex 1 & outside vertex)
				float xy = glm::distance(in[0].position, intersection[0]);
				float yz = glm::distance(outside[0].position, intersection[0]);
				float xz = glm::distance(in[0].position, outside[0].position);
				//If the segments don't equal the total, then Vertex 3 is opposite/not on the line.
				if (xy + yz != xz){
					Vertex vertex3;
					vertex3.position = intersection[0];
					vertex3.normal = v1.normal;
					vertex3.color = v1.color;
					vertexBuffer.push_back(vertex3);
				}
				else {
					Vertex vertex3;
					vertex3.position = intersection[1];
					vertex3.normal = v1.normal;
					vertex3.color = v1.color;
					vertexBuffer.push_back(vertex3);
				}
			} else {
				//If V2 is out, then do this to get CCW
                //Vertex1 == last vertex
				vertexBuffer.push_back(in[1]);

				//Vertex 2 & Vertex 3
				//Get vertex opposite vertex 1 (vertex 2 does not fall on line between vertex 1 & outside vertex)
				float ab = glm::distance(in[1].position, intersection[0]);
				float cd = glm::distance(outside[0].position, intersection[0]);
				float ad = glm::distance(in[1].position, outside[0].position);
				//If the segments don't equal the total, then Vertex 2 is opposite/not on the line.
				if (ab + cd != ad){
					Vertex vertex2;
					vertex2.position = intersection[0];
					vertex2.normal = v1.normal;
					vertex2.color = v1.color;
					vertexBuffer.push_back(vertex2);

					//Take the remaining vertex as Vertex3
					Vertex vertex3;
					vertex3.position = intersection[1];
					vertex3.normal = v1.normal;
					vertex3.color = v1.color;
					vertexBuffer.push_back(vertex3);
				}
				else {
					Vertex vertex2;
					vertex2.position = intersection[1];
					vertex2.normal = v1.normal;
					vertex2.color = v1.color;
					vertexBuffer.push_back(vertex2);

					//Take the remaining vertex as Vertex3
					Vertex vertex3;
					vertex3.position = intersection[0];
					vertex3.normal = v1.normal;
					vertex3.color = v1.color;
					vertexBuffer.push_back(vertex3);
				}

				//TRIANGLE 2
				//Vertex1
				vertexBuffer.push_back(in[1]);
				//Vertex2
				vertexBuffer.push_back(in[0]);
				//Vertex3
				//Get vertex opposite vertex 1 (vertex 3 does not fall on line between vertex 1 & outside vertex)
				float xy = glm::distance(in[1].position, intersection[0]);
				float yz = glm::distance(outside[0].position, intersection[0]);
				float xz = glm::distance(in[1].position, outside[0].position);
				//If the segments don't equal the total, then Vertex 3 is opposite/not on the line.
				if (xy + yz != xz){
					Vertex vertex3;
					vertex3.position = intersection[0];
					vertex3.normal = v1.normal;
					vertex3.color = v1.color;
					vertexBuffer.push_back(vertex3);
				}
				else {
					Vertex vertex3;
					vertex3.position = intersection[1];
					vertex3.normal = v1.normal;
					vertex3.color = v1.color;
					vertexBuffer.push_back(vertex3);
				}
			}
        }
        else if (in.size() == 1){
			//Send 1 triangle
			//If v1 is in, then do this to get CCW
			if (v1In){
				//Vertex1
				vertexBuffer.push_back(in[0]);
				//Vertex2
				Vertex vertex2;
				vertex2.position = intersection[0];
				vertex2.normal = v1.normal;
				vertex2.color = v1.color;
				vertexBuffer.push_back(vertex2);
				//Vertex3
				Vertex vertex3;
				vertex3.position = intersection[1];
				vertex3.normal = v1.normal;
				vertex3.color = v1.color;
				vertexBuffer.push_back(vertex3);
			}
			else {
				//If V2 is out, then do this to get CCW
				//Vertex1
				vertexBuffer.push_back(in[0]);
				//Vertex2
				Vertex vertex2;
				vertex2.position = intersection[1];
				vertex2.normal = v1.normal;
				vertex2.color = v1.color;
				vertexBuffer.push_back(vertex2);
				//Vertex3
				Vertex vertex3;
				vertex3.position = intersection[0];
				vertex3.normal = v1.normal;
				vertex3.color = v1.color;
				vertexBuffer.push_back(vertex3);

			}
        }
        
		//For the open face
        if (oF.size() >= 12){
            //Make 2 triangles
            //Tri 1
            vertexBuffer.push_back(oF[0]);
            vertexBuffer.push_back(oF[3]);
            vertexBuffer.push_back(oF[7]);
            //Tri2
            vertexBuffer.push_back(oF[0]);
            vertexBuffer.push_back(oF[7]);
            vertexBuffer.push_back(oF[11]);         
        }

		/*
		For some reason the triangles only get rendered from >= 12. 
		However the number of intersections is 16 / oF[0]-oF[15]
		Hardcoding a tiangle fan for the top of the openface does not work.
		Two triangles render a bit better than more.
		Any triangles rendered for the open face, creates bugs in the rest of the cube.
		//if (oF.size() >= 15){
        if (numberOfIntersections >= 12){
        //Make 2 triangles
            //For the open face
            //Tri1
            
            //Find the normal! It is the same as the plane!
            Vertex vertex1;
            vertex1.position = oF[1].position;
            vertex1.normal = pNormal;
            vertex1.color = vec3(1,1,1);
            vertexBuffer.push_back(vertex1);
            Vertex vertex2;
            vertex2.position = oF[6].position;
            vertex2.normal = pNormal;
            vertex2.color = vec3(1,1,1);
            vertexBuffer.push_back(vertex2);
            Vertex vertex3;
            vertex3.position = oF[2].position;
            vertex3.normal = pNormal;
            vertex3.color = vec3(1,1,1);
            vertexBuffer.push_back(vertex3);
            
            
		//Top half
		Vertex vertex1;
		vertex1.position = oF[14].position;
		vertex1.normal = pNormal;
		vertex1.color = vec3(1, 1, 1);
		vertexBuffer.push_back(vertex1);
		Vertex vertex2;
		vertex2.position = oF[15].position;
		vertex2.normal = pNormal;
		vertex2.color = vec3(1, 1, 1);
		vertexBuffer.push_back(vertex2);
		Vertex vertex3;
		vertex3.position = oF[11].position;
		vertex3.normal = pNormal;
		vertex3.color = vec3(1, 1, 1);
		vertexBuffer.push_back(vertex3);

		//v14
		vertexBuffer.push_back(vertex1);
		//v11
		vertexBuffer.push_back(vertex3);
		Vertex vertex6;
		vertex6.position = vec3(0, 0, 0);
		vertex6.normal = pNormal;
		vertex6.color = vec3(1, 1, 1);
		vertexBuffer.push_back(vertex6);

		//v14
		vertexBuffer.push_back(vertex1);
		//Origin
		vertexBuffer.push_back(vertex6);
		Vertex vertex9;
		vertex9.position = oF[0].position;
		vertex9.normal = pNormal;
		vertex9.color = vec3(1, 1, 1);
		vertexBuffer.push_back(vertex9);

		//v14
		vertexBuffer.push_back(vertex1);
		//v0
		vertexBuffer.push_back(vertex9);
		Vertex vertex12;
		vertex12.position = oF[12].position;
		vertex12.normal = pNormal;
		vertex12.color = vec3(1, 1, 1);
		vertexBuffer.push_back(vertex12);



		//Tri2
		
		Vertex vertex4;
		vertex4.position = oF[12].position;
		vertex4.normal = pNormal;
		vertex4.color = vec3(1,1,1);
		vertexBuffer.push_back(vertex4);
		Vertex vertex5;
		vertex5.position = oF[15].position;
		vertex5.normal = pNormal;
		vertex5.color = vec3(1,1,1);
		vertexBuffer.push_back(vertex5);
		Vertex vertex6;
		vertex6.position = oF[8].position;
		vertex6.normal = pNormal;
		vertex6.color = vec3(1,1,1);
		vertexBuffer.push_back(vertex6);
		

		*/

    }
    
}

vec3 ClippedCubeModel::GetIntersection(vec3 point0, vec3 point1, vec4 p){
    vec3 p0 = point0;
    vec3 p1 = point1;
    vec4 plane = p;
    vec3 pNormal = vec3(plane.x, plane.y, plane.z);
    //float degree = 1e-6;
    
    vec3 u = vec3(p1 - p0);
    float dotProd = dot(pNormal, u);
    //if( dotProd > degree){
        float dist = -plane[3] / (dot(pNormal, pNormal));
        vec3 pCoord = vec3(dist*plane.x, dist*plane.y, dist*plane.z);
        vec3 w = vec3(p0 - pCoord);
        float factor = - dot(pNormal, w)/dotProd;
        u = u * factor;
        vec3 intersectionPoint = p0 + u;
        return intersectionPoint;
    /*
    } else {
        return vec3(0,0,0);
    }*/
    
}


void ClippedCubeModel::Update(float dt)
{
	// If you are curious, un-comment this line to have spinning cubes!
	// That will only work if your world transform is correct...
	//mRotationAngleInDegrees += 90 * dt; // spins by 90 degrees per second

    // Add damping to velocity
    //mVelocity -= 0.3f * dt * mVelocity;
    //vec3 velocity = vec3(10.0f, 10.0f, 0.0f);
    
    vec3 acceleration = vec3(0.0f, -5.0f, 0.0f);
    
    mVelocity += acceleration * dt;
    mPosition += mVelocity*dt;
    
	Model::Update(dt);
}

void ClippedCubeModel::Draw()
{
	// Draw the Vertex Buffer
	// Note this draws a unit Cube
	// The Model View Projection transforms are computed in the Vertex Shader
	glBindVertexArray(mVertexArrayID);

	GLuint WorldMatrixLocation = glGetUniformLocation(Renderer::GetShaderProgramID(), "WorldTransform"); 
	glUniformMatrix4fv(WorldMatrixLocation, 1, GL_FALSE, &GetWorldMatrix()[0][0]);
	
	// 1st attribute buffer : vertex Positions
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	glVertexAttribPointer(	0,				// attribute. No particular reason for 0, but must match the layout in the shader.
							3,				// size
							GL_FLOAT,		// type
							GL_FALSE,		// normalized?
							sizeof(Vertex), // stride
							(void*)0        // array buffer offset
						);

	// 2nd attribute buffer : vertex normal
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	glVertexAttribPointer(	1,
							3,
							GL_FLOAT,
							GL_FALSE,
							sizeof(Vertex),
							(void*)sizeof(vec3)    // Normal is Offseted by vec3 (see class Vertex)
						);


	// 3rd attribute buffer : vertex color
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	glVertexAttribPointer(	2,
							3,
							GL_FLOAT,
							GL_FALSE,
							sizeof(Vertex),
							(void*) (2* sizeof(vec3)) // Color is Offseted by 2 vec3 (see class Vertex)
						);

	// Draw the triangles !
	glDrawArrays(GL_TRIANGLES, 0, 36); // 36 vertices: 3 * 2 * 6 (3 per triangle, 2 triangles per face, 6 faces)

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
}

bool ClippedCubeModel::ParseLine(const std::vector<ci_string> &token)
{
	if (token.empty())
	{
		return true;
	}
	else
	{
		return Model::ParseLine(token);
	}
}


