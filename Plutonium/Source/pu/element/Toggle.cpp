#include <pu/element/Toggle.hpp>

namespace pu::element
{
    Toggle::Toggle(uint32_t X, uint32_t Y, std::string Content, uint32_t Key, draw::Color Color) : Element::Element()
    {
        this->x = X;
        this->y = Y;
        this->key = Key;
        this->cnt = Content;
        this->clr = Color;
        this->fnt = render::LoadStandardFont(25);
        this->fsize = 25;
        this->togfact = 255;
        this->checked = false;
        this->ntex = render::RenderText(this->fnt, Content, Color);
    }

    Toggle::~Toggle()
    {
        if(this->fnt != NULL)
        {
            render::DeleteFont(this->fnt);
            this->fnt = NULL;
        }
        if(this->ntex != NULL)
        {
            render::DeleteTexture(this->ntex);
            this->ntex = NULL;
        }
    }

    uint32_t Toggle::GetX()
    {
        return this->x;
    }

    void Toggle::SetX(uint32_t X)
    {
        this->x = X;
    }

    uint32_t Toggle::GetY()
    {
        return this->y;
    }

    void Toggle::SetY(uint32_t Y)
    {
        this->y = Y;
    }

    uint32_t Toggle::GetWidth()
    {
        return 0;
    }

    uint32_t Toggle::GetHeight()
    {
        return 0;
    }

    std::string Toggle::GetContent()
    {
        return this->cnt;
    }

    void Toggle::SetContent(std::string Content)
    {
        this->cnt = Content;
        render::DeleteTexture(this->ntex);
        this->ntex = render::RenderText(this->fnt, Content, this->clr);
    }

    void Toggle::SetFont(render::NativeFont Font)
    {
        render::DeleteFont(this->fnt);
        this->fnt = Font;
        this->ntex = render::RenderText(Font, this->cnt, this->clr);
    }

    draw::Color Toggle::GetColor()
    {
        return this->clr;
    }

    void Toggle::SetColor(draw::Color Color)
    {
        this->clr = Color;
        render::DeleteTexture(this->ntex);
        this->ntex = render::RenderText(this->fnt, this->cnt, Color);
    }

    uint32_t Toggle::GetKey()
    {
        return this->key;
    }

    void Toggle::SetKey(uint32_t Key)
    {
        this->key = Key;
    }

    bool Toggle::IsChecked()
    {
        return this->checked;
    }

    void Toggle::OnRender(render::Renderer *Drawer)
    {
        uint32_t tw = render::GetTextWidth(this->fnt, this->cnt);
        uint32_t th = render::GetTextHeight(this->fnt, this->cnt);
        uint32_t rw = th;
        uint32_t rh = (2 * th);
        uint32_t rx = this->GetProcessedX();
        uint32_t ry = this->GetProcessedY();
        uint32_t tx = rx + rw + (th / 2);
        uint32_t ty = ry + (th / 2);
        if(this->checked)
        {
            Drawer->RenderRectangleFill({ 130, 130, 130, 255 }, rx, ry, rw, rh);
            if(this->togfact < 255)
            {
                Drawer->RenderRectangleFill({ this->clr.R, this->clr.G, this->clr.B, (255 - this->togfact) }, rx, ry, rw, rh);
                this->togfact += 48;
            }
            else Drawer->RenderRectangleFill({ 130, 130, 130, 255 }, rx, ry, rw, rh);
        }
        else
        {
            Drawer->RenderRectangleFill(this->clr, rx, ry, rw, rh);
            if(this->togfact > 0)
            {
                Drawer->RenderRectangleFill({ 130, 130, 130, this->togfact }, rx, ry, rw, rh);
                this->togfact -= 48;
            }
            else Drawer->RenderRectangleFill(this->clr, rx, ry, rw, rh);
        }
        Drawer->RenderTexture(this->ntex, tx, ty);
    }

    void Toggle::OnInput(uint32_t Down, uint32_t Up, uint32_t Held, bool Touch, bool Focus)
    {
        if((Down & this->key) || ((this->key == BUTTON_TOUCH) && Touch)) this->checked = !this->checked;
    }
}
