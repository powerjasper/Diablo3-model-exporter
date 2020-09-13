#pragma once

#include <iostream>
#include <cstdint>
#include <vector>

#include "Utility.h"

/*
i do not like the way this works, it looks very messy, complicated and the obj to file is annoying to implement due to inheretence
*/

namespace AppFile {

	struct header {							// 0x168 in size (so far)
		uint32_t deadbeef;					//+0x00		(deadbeef check for corruption I think)
		uint32_t version;
		uint32_t unkown1[2];				//+0x04		(some stuff oci and version) 
		uint32_t fileId;					//+0x10		(file id used as refrence)
		uint32_t unkown2[37];				//+0x14		(unkowns for now)
		uint32_t meshChunkCount;			//+0xA8		(mesh count)
		uint32_t meshChunkOffset;			//+0xAC		(mesh offset)
		uint32_t meshChunkSize;				//+0xB0		(mesh size)
		uint32_t unkown3[19];				//+0xB4		(unkowns for now)
		uint32_t hardPointCount;			//+0x100	(hardpoint count)
		uint32_t hardPointOffset;			//+0x104	(hardpoint offset)
		uint32_t hardPointSize;				//+0x108	(hardpoint Size)
		uint32_t unkown4[13];				//+0x10C	(unkown for now)
		uint32_t unkownOffset1;				//+0x140	(I have seen weird offsets in the files these can be calculated using the actual size and the last offset and size)
		uint32_t unkownSize1;				//+0x144	(^)
		uint32_t unkown5[2];				//+0x148	(unkown for now)
		uint32_t unkownOffset2;				//+0x150	(I have seen weird offsets in the files these can be calculated using the actual size and the last offset and size)
		uint32_t unkownSize2;				//+0x154	(^)
		uint32_t unkown6[2];				//+0x158	(unkown for now)
		uint32_t unkownOffset3;				//+0x160	(I have seen weird offsets in the files these can be calculated using the actual size and the last offset and size)
		uint32_t unkownSize3;				//+0x164	(^)


		/*
		 * Does not work yet, stream does not get read properly i think, the order of bytes also need to be flipped.
		 */

		friend std::istream& operator>>(std::istream& is, header& rhs);

		friend std::ostream& operator<<(std::ostream& os, header& rhs);
	};

	struct header_obj : header {
		friend std::ostream& operator<<(std::ostream& os, header_obj& rhs);
	};



	struct face {							// 0x06 in size
		uint16_t facePoint1;				//+0x00
		uint16_t facePoint2;				//+0x02
		uint16_t facePoint3;				//+0x04

		friend std::istream& operator>>(std::istream& is, face& rhs);
		friend std::ostream& operator<<(std::ostream& os, face& rhs);
	};

	struct face_obj : face {
	
	};

	std::ostream& print(std::ostream& os, face_obj& rhs, int& count);

	/*
	 *	be carefull that you should round these numbers some fuckery can occur if not rounded.
	 * TODO: make this like the header so that the operator will work better
	 */
	struct vertice { // 0x2C in size
		float x;							//+0x00		( x point )
		float y;							//+0x04		( y point )
		float z;							//+0x08		( z point )
		float nx;							//+0x0C		(normals, single byte calculated as such | (nx - 127) / 127 | )
		float ny;							//+0x0D		(normals, single byte calculated as such | (ny - 127) / 127 | )
		float  nz;							//+0x0E		(normals, single byte calculated as such | (nz - 127) / 127 | )
		uint8_t unkown[9];					//x
		float u;							//+0x18		( calculated as such 2 bytes | (u - 32767 ) / 512.0 | )
		float v;							//+0x1A		( calculated as such 2 bytes | 1 - ( (v - 32767) / 512.0 )| )

		friend std::istream & operator>>(std::istream& is, vertice& rhs);
		friend std::ostream& operator<<(std::ostream& os, const vertice& rhs);
	};

	struct vertice_obj : vertice {
		friend std::ostream& operator<<(std::ostream& os, const vertice_obj& rhs);
	};

	struct mesh {
		uint32_t unkown0[1];				//+0x0C
		uint32_t verticeCount;				//+0x00
		uint32_t verticeOffset;				//+0x04
		uint32_t verticeSize;				//+0x08
		uint32_t unkown1[6];				//+0x0C
		uint32_t FaceCount;					//+0x28
		uint32_t FaceOffset;				//+0x2C
		uint32_t FaceSize;					//+0x30
		uint32_t unkown2[10];				//+0x34
		char name[128];						//+0x5C (this is the texture name wich is also used in the .tex file)
		std::vector<vertice_obj> vertices;		// vector containing the vertices
		std::vector<face_obj> faces;			// vector containing the faces

		friend std::istream & operator>>(std::istream& is, mesh&rhs);
		friend std::ostream& operator<<(std::ostream& os, mesh& rhs);
	};
	
	struct mesh_obj : mesh {
		friend std::ostream& operator<<(std::ostream& os, mesh_obj& rhs);
	};


	struct texture_id_chunk {
		uint32_t id;
		uint32_t unkown1[24];
		uint32_t offset;
		uint32_t size;

		friend std::istream& operator>>(std::istream& is, texture_id_chunk& rhs);
		friend std::ostream& operator<<(std::ostream& os, texture_id_chunk& rhs);
	};

	struct texture_id {
		uint32_t unkown1[2];
		uint32_t id;

		friend std::istream& operator>>(std::istream& is, texture_id& rhs);
		friend std::ostream& operator<<(std::ostream& os, texture_id& rhs);

	};

	struct texture {
		char name[128];
		uint32_t fileOffset;
		uint32_t fileSize;
		uint32_t id;
		std::string snoName = "unset" ;

		friend std::istream& operator>>(std::istream& is, texture& rhs);
		friend std::ostream& operator<<(std::ostream& os, texture& rhs);
	};

	struct texture_obj : texture {
		friend std::ostream& operator<<(std::ostream& os, texture_obj& rhs);
	};
	struct textures {
		uint32_t count;
		uint32_t offset;
		uint32_t size;
		std::vector<texture_obj> textureChunks;

		friend std::istream& operator>>(std::istream& is, textures& rhs);
		friend std::ostream& operator<<(std::ostream& os, textures& rhs);
	};


	struct data {
		header_obj headerContents;
		textures textureContents;
		std::vector<mesh_obj> meshes;
		

	};
	struct data_obj : data {};

}