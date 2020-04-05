#include "ModelExtractor.h"

ModelExtractor::ModelExtractor(FileFinder& lib):
	lib(lib)
{

}


ModelExtractor::~ModelExtractor()
{

}

int ModelExtractor::dataToOBJ(AppFile::data & data, std::string name) {
	//zie tuxture gedeelte py bestand.
	std::string objName = name + ".obj";
	std::string mtlName = name + ".mtl";
	std::fstream file;
	file.open(objName, std::fstream::out);
	int totalvertices = 0;
	file << "O " << name << std::endl;
	file << "mtllib " << mtlName << std::endl;
	for (auto & mesh : data.meshes)
	{
		file << "g " << mesh.name << std::endl;
		for (auto vert : mesh.vertices) {
			file << vert;
		}
		for (auto face : mesh.faces) {
			AppFile::print(file, face, totalvertices);
		}
		totalvertices += mesh.vertices.size();
	}
	file.close();

	file.open(mtlName, std::fstream::out);
	for (auto & texture : data.textureContents.textureChunks)
	{
		//texture search and build
		if (lib.extractFile(texture.id) == ERROR_SUCCESS) {
			std::cout << std::endl << texture.name << " succes" << std::endl;
		}
		else {
			std::cout << std::endl << texture.name << " no succes" << std::endl;
		}
		file << texture;
	}
	

	return 1;
}
AppFile::data ModelExtractor::convertFromFile(std::string &filename) {
	std::ifstream infile;
	infile.open(filename, std::ios::binary);
	unsigned char bufferChar;
	while (infile >> std::noskipws >> bufferChar) {
		filebuffer.push_back(bufferChar);
	}
	infile.close();

	AppFile::data_obj model;
	
	//header
	std::stringstream header = Utility::toStream(Utility::vectorResize<unsigned char>(filebuffer, 0, 360));
	header >> model.headerContents;
	std::cout << static_cast<AppFile::header&>(model.headerContents);

	// theoretically a -16 is enough as an offset.
	
	// textures
	std::stringstream texture = Utility::toStream(Utility::vectorResize<unsigned char>(filebuffer, 436, 448));
	texture >> model.textureContents;
	std::cout << static_cast<AppFile::textures&>(model.textureContents);

	int textureChuckOffset = model.textureContents.offset + 16;
	int textureChunkSize = model.textureContents.size / model.textureContents.count;

	for (size_t i = 0; i < model.textureContents.count; i++)
	{
		int textureOffset = i * textureChunkSize;
		AppFile::texture_obj tmpTxt;
		std::stringstream texture = Utility::toStream(
			Utility::vectorResize<unsigned char>(
				filebuffer, textureChuckOffset + textureOffset,
				textureChuckOffset + model.textureContents.offset + textureOffset
				)
		);
		texture >> tmpTxt;

		//ID extraction
		int idChunkOffset = tmpTxt.fileOffset + 16;
		std::cout << "idChunkOffset: " << idChunkOffset << std::endl;
		AppFile::texture_id_chunk tmpTxtChunk;
		std::stringstream idChunk = Utility::toStream(
			Utility::vectorResize<unsigned char>(
				filebuffer, idChunkOffset,
				idChunkOffset + tmpTxt.fileSize
			)
		);
		idChunk >> tmpTxtChunk;

		int idOffset = tmpTxtChunk.offset + 16;
		std::cout << "id offset: " << idOffset << std::endl;
		AppFile::texture_id tmpTxtId;
		std::stringstream id = Utility::toStream(
			Utility::vectorResize<unsigned char>(
				filebuffer, idOffset,
				idOffset + tmpTxtChunk.size
				)
		);
		id >> tmpTxtId;
		tmpTxt.id = tmpTxtId.id;

		model.textureContents.textureChunks.push_back(tmpTxt);
		std::cout << static_cast<AppFile::texture&>(tmpTxt);
		
	}
	//meshes

	int meshChunkOffset = model.headerContents.meshChunkOffset + 16;
	int meshchunksize = model.headerContents.meshChunkSize / model.headerContents.meshChunkCount;
	for (size_t i = 0; i < model.headerContents.meshChunkCount; i++)
	{
		int meshOffset = i * meshchunksize;
		AppFile::mesh_obj tmpMesh;
		std::stringstream meshes = Utility::toStream(
			Utility::vectorResize<unsigned char>(
				filebuffer, meshChunkOffset + meshOffset, 
				meshChunkOffset + model.headerContents.meshChunkSize + meshOffset
			)
		);
		meshes >> tmpMesh;
		model.meshes.push_back(tmpMesh);
		std::cout << static_cast<AppFile::mesh&>(tmpMesh);
	}

	for (AppFile::mesh_obj & mesh : model.meshes)
	{
		int verticeChunkOffset = mesh.verticeOffset + 16;
		int verticeChunkSize = mesh.verticeSize / mesh.verticeCount;

		for (size_t i = 0; i < mesh.verticeCount; i++)
		{
			int verticeOffset = i * verticeChunkSize;
			AppFile::vertice_obj tmpVert;
			std::stringstream vertice = Utility::toStream(Utility::vectorResize<unsigned char>(filebuffer, verticeChunkOffset + verticeOffset
				, verticeChunkOffset + verticeChunkSize + verticeOffset));
			vertice >> tmpVert;
			mesh.vertices.push_back(tmpVert);
			if (i == 0) {
				std::cout << static_cast<AppFile::vertice&>(tmpVert);
			}
		}
		int faceChunkOffset = mesh.FaceOffset + 16;
		int faceChunkSize = 6;
		for (size_t i = 0; i < (mesh.FaceCount/3); i++)
		{
			int faceOffset = i * faceChunkSize;
			AppFile::face_obj tmpFace;
			std::stringstream face= Utility::toStream(Utility::vectorResize<unsigned char>(filebuffer, faceChunkOffset + faceOffset
				, faceChunkOffset + faceChunkSize + faceOffset));
			face >> tmpFace;
			mesh.faces.push_back(tmpFace);
			if (i == 0) {
				std::cout << static_cast<AppFile::face&>(tmpFace);
			}
		}
	}


	//std::cout << std::ifstream(filename, std::ios::binary).rdbuf();
	return model;
};