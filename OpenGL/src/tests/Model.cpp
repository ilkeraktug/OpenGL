#include "Model.h"

#include <iostream>
#include <chrono>
namespace obj {

	Model::Model(const std::string& filePath)
		: m_FilePath(filePath)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(m_FilePath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

		std::cout << "Loading Meshes" << std::endl;
		auto begin = std::chrono::high_resolution_clock::now();
		processNode(scene->mRootNode, scene);
		auto end = std::chrono::high_resolution_clock::now();
		std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000.0f << "[ms]" << std::endl;
	}
	Model::~Model()
	{
	}
	void Model::processNode(aiNode* node, const aiScene* scene)
	{
		for (size_t i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			m_Meshes.emplace_back(processMesh(mesh, scene));
		}
		for (size_t i = 0; i < node->mNumChildren; i++)
		{
			processNode(node->mChildren[i], scene);
		}
	}
	Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
	{
		std::vector<Vertex> vertices;
		std::vector<size_t> indices;
		std::vector<s_Texture> textures;
		for (size_t i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;
			if (mesh->HasPositions())
			{
				vertex.Position.x = mesh->mVertices[i].x;
				vertex.Position.y = mesh->mVertices[i].y;
				vertex.Position.z = mesh->mVertices[i].z;
			}
			if (mesh->HasNormals())
			{
				vertex.Normal.x = mesh->mNormals[i].x;
				vertex.Normal.y = mesh->mNormals[i].y;
				vertex.Normal.x = mesh->mNormals[i].z;
			}
			if (mesh->mTextureCoords[0])
			{
				vertex.TextCoords.x = mesh->mTextureCoords[0][i].x;
				vertex.TextCoords.y = mesh->mTextureCoords[0][i].y;
			}
			/*if (mesh->HasTangentsAndBitangents())
			{
				vertex.Tangent.x = mesh->mTangents[i].x;
				vertex.Tangent.y = mesh->mTangents[i].y;
				vertex.Tangent.z = mesh->mTangents[i].z;

				vertex.Bitangent.x = mesh->mBitangents[i].x;
				vertex.Bitangent.y = mesh->mBitangents[i].y;
				vertex.Bitangent.z = mesh->mBitangents[i].z;
			}*/
			vertices.emplace_back(vertex);
		}

		for (size_t i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (size_t j = 0; j < face.mNumIndices; j++)
				indices.emplace_back(face.mIndices[j]);
		}

		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
			LoadTexture(textures, material, aiTextureType_DIFFUSE);
			LoadTexture(textures, material, aiTextureType_SPECULAR);
			LoadTexture(textures, material, aiTextureType_HEIGHT);
		}

		return Mesh(vertices, indices, textures);
	}
	void Model::LoadTexture(std::vector<s_Texture>& textures, aiMaterial* material, aiTextureType type)
	{
		for (size_t i = 0; i < material->GetTextureCount(type); i++)
		{
			auto begin = std::chrono::high_resolution_clock::now();
			aiString name;
			material->GetTexture(type, i, &name);
			if (m_Textures.find(name.C_Str()) == m_Textures.end())
			{
				s_Texture texture;
				std::string path(m_FilePath.begin(), m_FilePath.begin() + m_FilePath.find_last_of('/'));
				texture.Type = type;
				std::string clear(name.C_Str());
				size_t location = clear.find_last_of("\\") + 1;
				std::string c = clear.substr(location, clear.size());
				texture.Texture = new Texture(path + '/' + c.c_str());
				textures.emplace_back(texture);
				m_Textures[c.c_str()] = texture.Texture;
				std::cout << "Loading Texture :" << c.c_str() << " Path : " << path + '/' + c.c_str() << std::endl;
				auto end = std::chrono::high_resolution_clock::now();
				std::cout << "Passed time : " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() / 1000.0f << "[ms]" << std::endl;
			}
			else
			{
				s_Texture texture;
				texture.Type = type;
				texture.Texture = m_Textures[name.C_Str()];
				textures.emplace_back(texture);
			}
		}
	}
	void Model::Draw(Shader& shader)
	{
		shader.Bind();
		for (size_t i = 0; i < m_Meshes.size(); i++)
		{
			m_Meshes[i].Draw(shader);
		}
	}
}

