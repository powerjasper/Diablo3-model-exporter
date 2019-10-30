#pragma once
#include <cstdint>
#include <vector>
#include <iostream>
#include <fstream>

namespace appFile {
	
	
	struct header {							// 0x168 in size (so far)
		uint32_t deadbeef;					//+0x00		(deadbeef check for corruption I think)
		uint32_t unkown1[3];				//+0x04		(some stuff oci or somestuffs) 
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
		friend std::istream& operator>>(std::istream& is, header& rhs) {
			return is >> rhs.deadbeef;
		}

		friend std::ostream& operator<<(std::ostream& os, header& rhs) {
			os << "Deadbeef: " << ((rhs.deadbeef == 3735928559) ? "true": "false") << std::endl;
			return os;
		}
	};



	struct face {							// 0x06 in size
		uint16_t facePoint1;				//+0x00
		uint16_t facePoint2;				//+0x02
		uint16_t facePoint3;				//+0x04
	};

	struct face_debug : face {
		friend std::ostream & operator<<(std::ostream& os, const face_debug& rhs) {
			os << "----------FACE Chunk----------" << std::endl;
			os << "Face point 1: " << rhs.facePoint1 << std::endl;
			os << "Face point 2: " << rhs.facePoint2 << std::endl;
			os << "Face point 3: " << rhs.facePoint3 << std::endl;
			os << "------------------------------" << std::endl;
			return os;
		}
	};

	struct face_obj : face {};

	/*
	 *	be carefull that you should round these numbers some fuckery can occur if not rounded.
	 * TODO: make this like the header so that the operator will work better
	 */
	struct vertice { // 0x2C in size
		float x;							//+0x00		( x point )
		float y;							//+0x04		( y point )
		float z;							//+0x08		( z point )
		float nx;							//+0xC		(normals, single byte calculated as such | (nx - 127 | )
		float nz;							//+0xD		(normals, single byte calculated as such |  | )
		float ny;							//+0xE		(normals, single byte calculated as such |  | )
		float u;							//+0x18		( calculated as such 2 bytes | (u - 32767 ) / 512.0 | )
		float v;							//+0x1A		( calculated as such 2 bytes | 1 - ( (v - 32767) / 512.0 | )

		friend std::istream & operator>>(std::istream& is, const vertice& v) {

			//magic

		}
	};
	struct vertice_debug : vertice {
		friend std::ostream& operator<<(std::ostream& os, const vertice_debug& rhs) {
			os << "----------VERT Chunk----------" << std::endl;
			os << "x: " << rhs.x << std::endl;
			os << "y: " << rhs.y << std::endl;
			os << "z: " << rhs.z << std::endl;
			os << "nx: " << rhs.nx << std::endl;
			os << "ny: " << rhs.ny << std::endl;
			os << "nz: " << rhs.nz << std::endl;
			os << "u: "	<< rhs.u << std::endl;
			os << "v: "	<< rhs.v << std::endl;
			os << "------------------------------" << std::endl;
			return os;
		}
	};

	struct vertice_obj : vertice {
		friend std::ostream& operator<<(std::ostream& os, const vertice_obj& rhs) {
			os << "v " << rhs.x << " " << rhs.y << " " << rhs.z  << std::endl;
			os << "vt " << rhs.u << " " << rhs.v << std::endl;
			os << "vn " << rhs.nx << " " << rhs.ny << " " << rhs.nz << std::endl;
			return os;
		}
	};

	struct mesh {
		uint32_t verticeCount;				//+0x00
		uint32_t verticeOffset;				//+0x04
		uint32_t verticeSize;				//+0x08
		uint32_t FaceCount;					//+0x28
		uint32_t FaceOffset;				//+0x2C
		uint32_t FaceSize;					//+0x30
		char name[128];						//+0x5C (this is the texture name wich is also used in the .tex file)
		std::vector<vertice> vertices;		// vector containing the vertices
		std::vector<face> faces;			// vector containing the faces
	};
	struct mesh_debug : mesh {
		friend std::ostream& operator<<(std::ostream& os, const mesh_debug& rhs) {
			os << "----------MESH Chunk----------" << std::endl;
			os << "Name: " << rhs.name << std::endl;
			os << "Vertice Count: " << rhs.verticeCount << std::endl;
			os << "Vertice Offset: " << rhs.verticeOffset << std::endl;
			os << "Vertice Size: " << rhs.verticeSize << std::endl;
			os << "Face Count: " << rhs.FaceCount << std::endl;
			os << "Face Offset: " << rhs.FaceOffset << std::endl;
			os << "Face Size: " << rhs.FaceSize << std::endl;
			os << "------------------------------" << std::endl;
			return os;
		}
	};

	struct mesh_obj : mesh {
	};

	struct data {
		header headerContents;
		std::vector<mesh> meshes;

	};
	struct data_debug : data {};
	struct data_obj : data {};

}



class ModelExtractor
{
public:
	ModelExtractor();
	~ModelExtractor();

	void convertFile(std::string & fileName);
};


