#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(Shader shader) : shader(shader)
{
	InitRenderData();
}

SpriteRenderer::~SpriteRenderer()
{
	glDeleteVertexArrays(1, &vao);
}

void SpriteRenderer::DrawSprite(const Texture2D& texture, const glm::vec2 position, const glm::vec2 size, const GLfloat rotate, const glm::vec3 color)
{
    shader.Use();
    glm::mat4 model{ glm::mat4(1.0f) };
    model = glm::translate(model, glm::vec3(position, 0.0f));

    //Move to rotate around center
    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

    model = glm::scale(model, glm::vec3(size, 1.0f));

    shader.SetMatrix4("model", model);
    shader.SetVector3f("spriteColor", color);

    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    glBindVertexArray(vao);
    {
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
    glBindVertexArray(0);

}

void SpriteRenderer::InitRenderData()
{
	GLuint vbo;
	const GLfloat vertices[]{
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    {
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        {
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)nullptr);
            glEnableVertexAttribArray(0);
        }
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    glBindVertexArray(0);
}