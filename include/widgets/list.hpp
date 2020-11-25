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

    void SetInputAction(std::vector<std::function<void(Gui* gui)> > vec_function);

private:
    std::vector<std::string> stext;
    uint32_t number ;
    uint32_t curr_index;

    uint32_t x_wight = 200;
    uint32_t y_start_offset = 60;
    uint32_t y_offset = 100;

    std::vector<std::function<void(Gui* gui)> > vec_function;


};