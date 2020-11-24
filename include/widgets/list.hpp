#include <switch.h>

#include <string>
#include <functional>
#include <vector>

#include "widgets/widget.hpp"

class List : public Widget
{
public:
    List(uint32_t x,uint32_t y,std::vector<std::string> &_stext);
    ~List();

    virtual void Draw(Gui* gui) override;
    virtual void OnKeyBoardInput(KeyBoard keystate)override;
    virtual void OnMouseInput(sMouseState* mouse)override;


    void SetInputAction(std::function<void(Gui* gui)> action);
    inline std::string GetText();

private:
    bool IsClip(uint32_t x, uint32_t y);

    uint32_t x,y,w,h;
    std::vector<std::string> stext;
    uint32_t number ;
    uint32_t curr_index;


};