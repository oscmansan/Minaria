#ifndef TEXT_H
#define TEXT_H

#include <vector>
#include <string>

#include "Sprite.h"
#include "Texture.h"
#include "Rect.h"

class Text
{
public:
    Text();
    std::vector<Sprite*> letterSprites;

    void render();

    void setPosition(const glm::ivec2 &pos);

    void setColor(const glm::vec4 &color);
    void setText(const std::string &str, int size = 5);
    void centerHorizontally();
    void setVisible(bool visible);
    Rect getBoundingRect() const;

private:
    bool visible = true;
    glm::vec4 color = glm::vec4(1,1,1,1);
    glm::ivec2 position = glm::ivec2(0);
    std::string currentText = "";

    static Texture *textSheet;
    static glm::vec2 letterSizeInTextsheet;
};

#endif // TEXT_H