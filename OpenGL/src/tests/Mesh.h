#pragma once
#include <vector>
#include <utility>

#include "glm\glm.hpp"
#include "assimp\Importer.hpp"
#include "assimp\scene.h"
#include "assimp\postprocess.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture.h"

namespace obj {

	struct Vertex {
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TextCoords;
		//glm::vec3 Tangent;
		//glm::vec3 Bitangent;
	};

	struct s_Texture {
		aiTextureType Type = aiTextureType::aiTextureType_NONE;
		Texture* Texture;
	};

	class Mesh {
	public:
		Mesh(std::vector<Vertex> vertices,
			std::vector<size_t> indices,
			std::vector<s_Texture> textures
			);
		~Mesh();

		void Draw(Shader& shader);
	private:
		VertexArray* m_VAO;
		VertexBuffer* m_VBO;
		IndexBuffer* m_IBO;

		std::vector<Vertex> m_Vertices;
		std::vector<size_t> m_Indices;
		std::vector<s_Texture> m_Textures;
	};
}