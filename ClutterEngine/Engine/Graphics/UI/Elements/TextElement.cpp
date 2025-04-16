#include "pch.h"
#include "TextElement.h"

using namespace clt;



TextElement::TextElement(std::string text, std::string font, Color color, float textSize, Vector2 position, int ZOrder)
	: WidgetElement(textSize, position, ZOrder), mText(text), mFont(nullptr), mColor(color)
{
	mFont = Assets::Get().GetFont(font);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

TextElement::TextElement(std::string text, Font* font, Color color, float textSize, Vector2 position, int ZOrder) : WidgetElement(textSize, position, ZOrder), mText(text), mFont(font), mColor(color)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void TextElement::Draw(RendererGL* renderer)
{
   // renderer->mTextShader.Use();
    renderer->mTextShader.SetVec4f("textColor", mColor);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    float x = mTransform.location.x;

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    std::string::const_iterator c;
    for (c = mText.begin(); c != mText.end(); c++)
    {
        Character ch = mFont->mCharacters[*c];

        float xpos = x + ch.Bearing.x * mTransform.scale.x;
        float ypos = mTransform.location.y - (ch.Size.y - ch.Bearing.y) * mTransform.scale.y;

        float w = ch.Size.x * mTransform.scale.x;
        float h = ch.Size.y * mTransform.scale.y;

        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }
        };

        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        x += (ch.Advance >> 6) * mTransform.scale.x;
    }

    glBindTexture(GL_TEXTURE_2D, 0);

}
