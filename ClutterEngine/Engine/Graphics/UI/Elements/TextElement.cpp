#include "pch.h"
#include "TextElement.h"

using namespace clt;



TextElement::TextElement(std::string text, std::string font, Color color, float textSize, Vector2 position, int ZOrder)
	: WidgetElement(textSize, position, ZOrder), mText(text), mFont(nullptr), mColor(color)
{
	mFont = Assets::Get().GetFont(font);
}

TextElement::TextElement(std::string text, Font* font, Color color, float textSize, Vector2 position, int ZOrder) : WidgetElement(textSize, position, ZOrder), mText(text), mFont(font), mColor(color)
{
}

void TextElement::Draw(RendererGL* renderer)
{
    renderer->BindText(mColor);

    float x = mTransform.location.x;

    for (char c : mText)
    {
        auto it = mFont->mCharacters.find(c);
        if (it == mFont->mCharacters.end())
            continue;
        Character ch = it->second;

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
        renderer->mTextVAO->Set()
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        x += (ch.Advance >> 6) * mTransform.scale.x;
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
