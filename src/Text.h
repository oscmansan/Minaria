#ifndef TEXT_H
#define TEXT_H

#include <vector>
#include <string>

#include "Rect.h"
#include "Sprite.h"
#include "Texture.h"
#include "ISceneNode.h"

class Text : public ISceneNode
{
public:
    static ShaderProgram program;

    Text();
    virtual ~Text();

    std::vector<Sprite*> letterSprites;
    std::vector<Sprite*> strokeSprites;

    void render(ShaderProgram &program) override;

    void setPosition(const glm::ivec2 &pos);

    void setColor(const glm::vec4 &color);
    void setText(const std::string &str, int size = 5);
    void centerHorizontally();
    void setVisible(bool visible);
    void setStroke(int stroke, const glm::vec4 &strokeColor);
    Rect getBoundingRect() const;

private:
    int stroke = 0;
    int size = 0;
    bool visible = true;
    glm::vec4 strokeColor = glm::vec4(0,0,0,1);
    glm::vec4 color = glm::vec4(1,1,1,1);
    glm::ivec2 position = glm::ivec2(0);
    std::string currentText = "";

    static Texture *textSheet1, *textSheet2, *textSheet3;
    static glm::vec2 letterSizeInTextsheet;

    void renderLetter(const glm::ivec2 &pos, Sprite *letterSprite);
};

#endif // TEXT_H
