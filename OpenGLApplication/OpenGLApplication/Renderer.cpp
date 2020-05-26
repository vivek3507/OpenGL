#include "Renderer.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Draw(const VertexArray& va, const ElementArray& ea, const Shaders& sh) const
{
	va.bind();
	ea.bind();
	sh.bind();

	GL_CALL(glDrawElements(GL_TRIANGLES, ea.getCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::clear() const
{
	GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
}
