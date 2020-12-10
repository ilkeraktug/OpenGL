#include "Mesh.h"

#include "VertexBufferLayout.h"
#include "Renderer.h"
#include "assimp\BaseImporter.h"

namespace obj {
	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<size_t> indices, std::vector<s_Texture> textures)
		: m_Vertices(vertices), m_Indices(indices), m_Textures(textures)
	{
		m_VAO = new VertexArray();
		m_VAO->Bind();

		m_VBO = new VertexBuffer(&m_Vertices[0], sizeof(Vertex) * m_Vertices.size());
		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(3);
		layout.Push<float>(2);
		//layout.Push<float>(3);
		//layout.Push<float>(3);
		m_VAO->AddBuffer(*m_VBO, layout);

		//m_IBO = new IndexBuffer(m_Indices.data(), m_Indices.size());
		//m_IBO->Bind();

		m_VAO->Unbind();
		m_VBO->Unbind();
		//m_IBO->Unbind();
	}

	Mesh::~Mesh()
	{
	}

	void Mesh::Draw(Shader& shader)
	{
		m_VAO->Bind();
		for (size_t i = 0; i < m_Textures.size(); i++)
		{
			m_Textures[i].Texture->Bind(i);
			if (m_Textures[i].Type == aiTextureType_DIFFUSE)
				shader.SetUniform1i("u_Material.Diffuse", i);
			else if (m_Textures[i].Type == aiTextureType_SPECULAR)
				shader.SetUniform1i("u_Material.Specular", i);
			else if(m_Textures[i].Type == aiTextureType_HEIGHT)
				shader.SetUniform1i("u_Material.Normal", i);

		}
		glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);
		m_VAO->Unbind();
	}
}