#include "pch.h"
#include "TextElement.h"

using namespace clt;



void TextElement::CalculateWidth()
{
    float width = 0.0f;
    for (const char& c : mText)
    {
        Character ch = mFont->mCharacters.at(c);
        width += (ch.Advance >> 6);
    }
    
    mWidth = width;
}

TextElement::TextElement(std::string text, std::string font, Color color, float textSize, Vector2 position, int ZOrder)
    : WidgetElement(textSize, position, ZOrder), mText(text), mFont(nullptr), mColor(color), mAlignment(alignment::Center)
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

    CalculateWidth();
}

TextElement::TextElement(std::string text, Color color, float textSize, Vector2 position, int ZOrder)
    : WidgetElement(textSize, position, ZOrder), mText(text), mFont(nullptr), mColor(color), mAlignment(alignment::Center)
{
    mFont = Assets::Get().GetFont("BebasNeue");

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    CalculateWidth();
}

TextElement::TextElement(std::string text, Font* font, Color color, float textSize, Vector2 position, int ZOrder) : WidgetElement(textSize, position, ZOrder), mText(text), mFont(font), mColor(color), mAlignment(alignment::Center)
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

    CalculateWidth();
}

TextElement::~TextElement()
{
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

void TextElement::SetText(std::string text)
{
    mText = text;
    CalculateWidth();
}

void TextElement::SetSize(float size)
{
    mTransform.scale = size;
    CalculateWidth();
}

void TextElement::SetColor(Color color)
{
    mColor = color;
}

void TextElement::SetAlignment(alignment alignment)
{
    mAlignment = alignment;
}

void TextElement::Draw(RendererGL* renderer)
{
    renderer->mTextShader.Use();
    renderer->mTextShader.SetMat4Row("uWorldTransform", GetTransform().To3D().GetMat4Transform());
    renderer->mTextShader.SetVec4f("textColor", mColor);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    float x = mTransform.location.x;

    if (mAlignment == alignment::Center)
    {
        x -= (GetTextWidth() * 0.5f) * mTransform.scale.x;
    }
    else if (mAlignment == alignment::Right)
    {
        x -= GetTextWidth() * mTransform.scale.x;
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    std::string::const_iterator c;
    for (c = mText.begin(); c != mText.end(); c++)
    {
        Character ch = mFont->mCharacters[*c];

        float xpos = x + ch.Bearing.x * mTransform.scale.x;
        float ypos = -mTransform.location.y - (ch.Size.y - ch.Bearing.y) * mTransform.scale.y;

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

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}