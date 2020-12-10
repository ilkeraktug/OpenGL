#pragma once

#include <string>
#include <vector>

#include "Mesh.h"

namespace obj {

	class Model {
	public:
		Model(const std::string& filePath);
		~Model();

		void processNode(aiNode* node, const aiScene* scene);
		Mesh processMesh(aiMesh* mesh, const aiScene* scene);
		void LoadTexture(std::vector<s_Texture>& textures, aiMaterial* material, aiTextureType type);
		void Draw(Shader& shader);
	private:
		std::string m_FilePath;

		std::unordered_map<std::string, Texture*> m_Textures;
		std::vector<Mesh> m_Meshes;
	};


}