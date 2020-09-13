#include "AppFile.h"

namespace AppFile {
	
	/*
	 * HEADER
	 */

	std::istream& operator>>(std::istream& is, header& rhs) {

		is.read(reinterpret_cast<char *>(&rhs.deadbeef), sizeof(rhs.deadbeef));
		is.read(reinterpret_cast<char *>(&rhs.version), sizeof(rhs.version));
		is.read(reinterpret_cast<char *>(&rhs.unkown1), sizeof(rhs.unkown1));
		is.read(reinterpret_cast<char *>(&rhs.fileId), sizeof(rhs.fileId));
		is.read(reinterpret_cast<char *>(&rhs.unkown2), sizeof(rhs.unkown2));
		is.read(reinterpret_cast<char *>(&rhs.meshChunkCount), sizeof(rhs.meshChunkCount));
		is.read(reinterpret_cast<char *>(&rhs.meshChunkOffset), sizeof(rhs.meshChunkOffset));
		is.read(reinterpret_cast<char *>(&rhs.meshChunkSize), sizeof(rhs.meshChunkSize));
		is.read(reinterpret_cast<char *>(&rhs.unkown3), sizeof(rhs.unkown3));
		is.read(reinterpret_cast<char *>(&rhs.hardPointCount), sizeof(rhs.hardPointCount));
		is.read(reinterpret_cast<char *>(&rhs.hardPointOffset), sizeof(rhs.hardPointOffset));
		is.read(reinterpret_cast<char *>(&rhs.hardPointSize), sizeof(rhs.hardPointSize));
		is.read(reinterpret_cast<char *>(&rhs.unkown4), sizeof(rhs.unkown4));
		is.read(reinterpret_cast<char *>(&rhs.unkownOffset1), sizeof(rhs.unkownOffset1));
		is.read(reinterpret_cast<char *>(&rhs.unkownSize1), sizeof(rhs.unkownSize1));
		is.read(reinterpret_cast<char *>(&rhs.unkown5), sizeof(rhs.unkown5));
		is.read(reinterpret_cast<char *>(&rhs.unkownOffset2), sizeof(rhs.unkownOffset2));
		is.read(reinterpret_cast<char *>(&rhs.unkownSize2), sizeof(rhs.unkownSize2));
		is.read(reinterpret_cast<char *>(&rhs.unkown6), sizeof(rhs.unkown6));
		is.read(reinterpret_cast<char *>(&rhs.unkownOffset3), sizeof(rhs.unkownOffset3));
		is.read(reinterpret_cast<char *>(&rhs.unkownSize3), sizeof(rhs.unkownSize3));

		// Just so we know our stream is intended endian
		bool goodEndian = false;
		if (rhs.deadbeef == 3735928559)
		{
			goodEndian = true;
		}

		if (!goodEndian)
		{
			rhs.deadbeef = Utility::convertEndian(rhs.deadbeef);
			rhs.version = Utility::convertEndian(rhs.version);
			rhs.fileId = Utility::convertEndian(rhs.fileId);
			rhs.meshChunkCount = Utility::convertEndian(rhs.meshChunkCount);
			rhs.meshChunkOffset = Utility::convertEndian(rhs.meshChunkOffset);
			rhs.meshChunkSize = Utility::convertEndian(rhs.meshChunkSize);
			rhs.hardPointCount = Utility::convertEndian(rhs.hardPointCount);
			rhs.hardPointOffset = Utility::convertEndian(rhs.hardPointOffset);
			rhs.hardPointSize = Utility::convertEndian(rhs.hardPointSize);
			rhs.unkownOffset1 = Utility::convertEndian(rhs.unkownOffset1);
			rhs.unkownSize1 = Utility::convertEndian(rhs.unkownSize1);
			rhs.unkownOffset2 = Utility::convertEndian(rhs.unkownOffset2);
			rhs.unkownSize2 = Utility::convertEndian(rhs.unkownSize2);
			rhs.unkownOffset3 = Utility::convertEndian(rhs.unkownOffset3);
			rhs.unkownSize3 = Utility::convertEndian(rhs.unkownSize3);
		}



		return is;
	}

	std::ostream& operator<<(std::ostream& os, header& rhs) {
		os << "---------HEADER Chunk---------" << std::endl;
		os << "Deadbeef: " << ((rhs.deadbeef == 3735928559) ? "true" : "false") << std::endl;
		os << "Version: " << ((rhs.version == 247) ? "Diablo 3" : (rhs.version == 260) ? "Diablo 3 - Reaper of Souls" : "unkown version: " + rhs.version) << std::endl;
		os << "File Id: " << rhs.fileId << std::endl;
		os << "Mesh Chunk Count: " << rhs.meshChunkCount << std::endl;
		os << "Mesh Chunk Offset: " << rhs.meshChunkOffset << std::endl;
		os << "Mesh Chunk Size: " << rhs.meshChunkSize << std::endl;
		os << "Hardpoint Count: " << rhs.hardPointCount << std::endl;
		os << "Hardpoint Offset: " << rhs.hardPointOffset << std::endl;
		os << "Hardpoint Size: " << rhs.hardPointSize << std::endl;
		os << "Unkown Offset 1: " << rhs.unkownOffset1 << std::endl;
		os << "Unkown Size 1: " << rhs.unkownSize1 << std::endl;
		os << "Unkown Offset 2: " << rhs.unkownOffset2 << std::endl;
		os << "Unkown Size 2: " << rhs.unkownSize2 << std::endl;
		os << "Unkown Offset 3: " << rhs.unkownOffset3 << std::endl;
		os << "Unkown Size 3: " << rhs.unkownSize3 << std::endl;
		os << "------------------------------" << std::endl;
		return os;
	}
	/*
	 * HEADER obj
	 */

	/*
	 * FACE
	 */


	std::ostream& operator<<(std::ostream& os, face& rhs) {
		os << "----------FACE Chunk----------" << std::endl;
		os << "Face point 1: " << rhs.facePoint1 << std::endl;
		os << "Face point 2: " << rhs.facePoint2 << std::endl;
		os << "Face point 3: " << rhs.facePoint3 << std::endl;
		os << "------------------------------" << std::endl;
		return os;
	}

	std::ostream& print(std::ostream& os, face_obj& rhs, int& count) {
		int facePoint1 = rhs.facePoint1 + 1 + count;
		int facePoint2 = rhs.facePoint2 + 1 + count;
		int facePoint3 = rhs.facePoint3 + 1 + count;
		os << "f ";
		os << facePoint1 << "/" << facePoint1 << "/" << facePoint1 << " ";
		os << facePoint2 << "/" << facePoint2 << "/" << facePoint2 << " ";
		os << facePoint3 << "/" << facePoint3 << "/" << facePoint3 << std::endl;

		return os;
	}
	std::istream& operator>>(std::istream& is, face& rhs) {
		is.read(reinterpret_cast<char*>(&rhs.facePoint1), sizeof(rhs.facePoint1));
		is.read(reinterpret_cast<char*>(&rhs.facePoint2), sizeof(rhs.facePoint2));
		is.read(reinterpret_cast<char*>(&rhs.facePoint3), sizeof(rhs.facePoint3));
		return is;
	}

	/*
	 * VERTICE
	 */

	std::istream& operator>>(std::istream& is, vertice& rhs) {

		is.read(reinterpret_cast<char *>(&rhs.x), sizeof(rhs.x));
		is.read(reinterpret_cast<char *>(&rhs.y), sizeof(rhs.y));
		is.read(reinterpret_cast<char *>(&rhs.z), sizeof(rhs.z));


		uint8_t tmpNx;
		uint8_t tmpNy;
		uint8_t tmpNz;
		is.read(reinterpret_cast<char *>(&tmpNx), sizeof(tmpNx));
		is.read(reinterpret_cast<char *>(&tmpNy), sizeof(tmpNy));
		is.read(reinterpret_cast<char *>(&tmpNz), sizeof(tmpNz));

		rhs.nx = (static_cast<float>(tmpNx) - 127) / 127;
		rhs.ny = (static_cast<float>(tmpNy) - 127) / 127;
		rhs.nz = (static_cast<float>(tmpNz) - 127) / 127;

		is.read(reinterpret_cast<char *>(&rhs.unkown), sizeof(rhs.unkown));

		uint16_t tmpU;
		uint16_t tmpV;
		
		is.read(reinterpret_cast<char *>(&tmpU), sizeof(tmpU));
		is.read(reinterpret_cast<char *>(&tmpV), sizeof(tmpV));

		rhs.u = (static_cast<float>(tmpU) - 32767) / 512.0f;
		rhs.v = 1 - ((static_cast<float>(tmpV) - 32767) / 512.0f);

		return is;
	}

	/*
	 * VERTICE DEBUG
	 */
	std::ostream& operator<<(std::ostream& os, const vertice& rhs) {
		os << "----------VERT Chunk----------" << std::endl;
		os << "x: " << rhs.x << std::endl;
		os << "y: " << rhs.y << std::endl;
		os << "z: " << rhs.z << std::endl;
		os << "nx: " << rhs.nx << std::endl;
		os << "ny: " << rhs.ny << std::endl;
		os << "nz: " << rhs.nz << std::endl;
		os << "u: " << rhs.u << std::endl;
		os << "v: " << rhs.v << std::endl;
		os << "------------------------------" << std::endl;
		return os;
	}
	/*
	 * VERTICE OBJ
	 */
	std::ostream& operator<<(std::ostream& os, const vertice_obj& rhs) {
		os << "v " << rhs.x << " " << rhs.y << " " << rhs.z << std::endl;
		os << "vt " << rhs.u << " " << rhs.v << std::endl;
		os << "vn " << rhs.nx << " " << rhs.ny << " " << rhs.nz << std::endl;
		return os;
	}

	/*
	 * MESH
 	 */

	std::istream& operator>>(std::istream& is, mesh& rhs) {
		is.read(reinterpret_cast<char *>(&rhs.unkown0), sizeof(rhs.unkown0));
		is.read(reinterpret_cast<char *>(&rhs.verticeCount), sizeof(rhs.verticeCount));
		is.read(reinterpret_cast<char *>(&rhs.verticeOffset), sizeof(rhs.verticeOffset));
		is.read(reinterpret_cast<char *>(&rhs.verticeSize), sizeof(rhs.verticeSize));
		is.read(reinterpret_cast<char *>(&rhs.unkown1), sizeof(rhs.unkown1));
		is.read(reinterpret_cast<char *>(&rhs.FaceCount), sizeof(rhs.FaceCount));
		is.read(reinterpret_cast<char *>(&rhs.FaceOffset), sizeof(rhs.FaceOffset));
		is.read(reinterpret_cast<char *>(&rhs.FaceSize), sizeof(rhs.FaceSize));
		is.read(reinterpret_cast<char *>(&rhs.unkown2), sizeof(rhs.unkown2));
		is.read(reinterpret_cast<char *>(&rhs.name), sizeof(rhs.name));
		
		return is;
	}
	/*
	 * MESH DEBUG
	 */
	std::ostream& operator<<(std::ostream& os, mesh& rhs) {
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

	/*
	* TEXTURE
	*/

	std::istream& operator>>(std::istream& is, texture& rhs) {
		is.read(reinterpret_cast<char*>(&rhs.name), sizeof(rhs.name));
		is.read(reinterpret_cast<char*>(&rhs.fileOffset), sizeof(rhs.fileOffset));
		is.read(reinterpret_cast<char*>(&rhs.fileSize), sizeof(rhs.fileSize));
		return is;
	}
	std::ostream& operator<<(std::ostream& os, texture& rhs) {
		os << "----------Texture Chunk----------" << std::endl;
		os << "Name: " << rhs.name << std::endl;
		os << "File offset: " << rhs.fileOffset << std::endl;
		os << "File size: " << rhs.fileSize << std::endl;
		os << "Id: " << rhs.id << std::endl;
		os << "---------------------------------" << std::endl;
		return os;
	}
	/*
	* TEXTURES
	*/
	std::istream& operator>>(std::istream& is, textures& rhs) {
		is.read(reinterpret_cast<char*>(&rhs.count), sizeof(rhs.count));
		is.read(reinterpret_cast<char*>(&rhs.offset), sizeof(rhs.offset));
		is.read(reinterpret_cast<char*>(&rhs.size), sizeof(rhs.size));
		return is;
	}

	std::ostream& operator<<(std::ostream& os, textures& rhs) {
		os << "----------Texture Chunk----------" << std::endl;
		os << "Textures count: " << rhs.count << std::endl;
		os << "Textures offset: " << rhs.offset << std::endl;
		os << "Textures size: " << rhs.size << std::endl;
		os << "---------------------------------" << std::endl;
		return os;
	}

	std::ostream& operator<<(std::ostream& os, texture_obj& rhs) {
		os << "newmtl " << rhs.name << std::endl;
		os << "map_Kd " << rhs.snoName << ".png" << std::endl;

		return os;
	}

	/*
	* Texture id chunk
	*/
	std::istream& operator>>(std::istream& is, texture_id_chunk& rhs) {
		is.read(reinterpret_cast<char*>(&rhs.id), sizeof(rhs.id));
		is.read(reinterpret_cast<char*>(&rhs.unkown1), sizeof(rhs.unkown1));
		is.read(reinterpret_cast<char*>(&rhs.offset), sizeof(rhs.offset));
		is.read(reinterpret_cast<char*>(&rhs.size), sizeof(rhs.size));
		return is;
		
	}
	std::ostream& operator<<(std::ostream& os, texture_id_chunk& rhs) {
		os << "----------Texture id Chunk----------" << std::endl;
		os << "Texture type id: " << rhs.id << std::endl;
		os << "Texture id offset: " << rhs.offset << std::endl;
		os << "Texture id size: " << rhs.size << std::endl;
		os << "---------------------------------" << std::endl;
		return os;
	}

	std::istream& operator>>(std::istream& is, texture_id& rhs) {
		is.read(reinterpret_cast<char*>(&rhs.unkown1), sizeof(rhs.unkown1));
		is.read(reinterpret_cast<char*>(&rhs.id), sizeof(rhs.id));
		return is;
	}
	std::ostream& operator<<(std::ostream& os, texture_id& rhs) {
		os << "----------Texture id----------" << std::endl;
		os << "Texture id: " << rhs.id << std::endl;
		os << "---------------------------------" << std::endl;
		return os;
	}
}