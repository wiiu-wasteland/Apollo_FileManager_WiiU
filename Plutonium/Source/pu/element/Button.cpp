#include <pu/element/Button.hpp>

namespace pu::element
{
    Button::Button(uint32_t X, uint32_t Y, uint32_t Width, uint32_t Height, std::string Content, draw::Color TextColor, draw::Color Color, uint32_t fontSize) : Element::Element()
    {
        this->x = X;
        this->y = Y;
        this->w = Width;
        this->h = Height;
        this->cnt = Content;
        this->clr = Color;
        this->hover = false;
        this->hoverfact = 255;
        this->fnt = render::LoadStandardFont(fontSize);
        this->ntex = render::RenderText(this->fnt, Content, TextColor);
        this->clickcb = [](){};
    }

    Button::~Button()
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

    uint32_t Button::GetX()
    {
        return this->x;
    }

    void Button::SetX(uint32_t X)
    {
        this->x = X;
    }

    uint32_t Button::GetY()
    {
        return this->y;
    }

    void Button::SetY(uint32_t Y)
    {
        this->y = Y;
    }

    uint32_t Button::GetWidth()
    {
        return this->w;
    }

    void Button::SetWidth(uint32_t Width)
    {
        this->w = Width;
    }

    uint32_t Button::GetHeight()
    {
        return this->h;
    }

    void Button::SetHeight(uint32_t Height)
    {
        this->h = Height;
    }

    std::string Button::GetContent()
    {
        return this->cnt;
    }

    void Button::SetContent(std::string Content)
    {
        this->cnt = Content;
        render::DeleteTexture(this->ntex);
        this->ntex = render::RenderText(this->fnt, Content, this->clr);
    }

    draw::Color Button::GetColor()
    {
        return this->clr;
    }

    void Button::SetColor(draw::Color Color)
    {
        this->clr = Color;
        render::DeleteTexture(this->ntex);
        this->ntex = render::RenderText(this->fnt, this->cnt, Color);
    }

    void Button::SetContentFont(render::NativeFont Font)
    {
        render::DeleteFont(this->fnt);
        this->fnt = Font;
        render::DeleteTexture(this->ntex);
        this->ntex = render::RenderText(this->fnt, this->cnt, this->clr);
    }

    void Button::SetOnClick(std::function<void()> ClickCallback)
    {
        this->clickcb = ClickCallback;
    }

    void Button::OnRender(render::Renderer *Drawer)
    {
        uint32_t rdx = this->GetProcessedX();
        uint32_t rdy = this->GetProcessedY();
        int32_t clrr = this->clr.R;
        int32_t clrg = this->clr.G;
        int32_t clrb = this->clr.B;
        int32_t nr = clrr - 70;
        if(nr < 0) nr = 0;
        int32_t ng = clrg - 70;
        if(ng < 0) ng = 0;
        int32_t nb = clrb - 70;
        if(nb < 0) nb = 0;
        draw::Color nclr(nr, ng, nb, this->clr.A);
        if(this->hover)
        {
            Drawer->RenderRectangleFill(this->clr, rdx, rdy, this->w, this->h);
            if(this->hoverfact < 255)
            {
                Drawer->RenderRectangleFill({ nr, ng, nb, this->hoverfact }, rdx, rdy, this->w, this->h);
                this->hoverfact += 48;
            }
            else Drawer->RenderRectangleFill(nclr, rdx, rdy, this->w, this->h);
        }
        else
        {
            Drawer->RenderRectangleFill(this->clr, rdx, rdy, this->w, this->h);
            if(this->hoverfact > 0)
            {
                Drawer->RenderRectangleFill({ nr, ng, nb, this->hoverfact }, rdx, rdy, this->w, this->h);
                this->hoverfact -= 48;
            }
            else Drawer->RenderRectangleFill(this->clr, rdx, rdy, this->w, this->h);
        }
        uint32_t xw = render::GetTextWidth(this->fnt, this->cnt);
        uint32_t xh = render::GetTextHeight(this->fnt, this->cnt);
        uint32_t tx = ((this->w - xw) / 2) + rdx;
        uint32_t ty = ((this->h - xh) / 2) + rdy;
        Drawer->RenderTexture(this->ntex, tx, ty);
    }

    void Button::OnInput(uint32_t Down, uint32_t Up, uint32_t Held, bool Touch, bool Focus)
    {
        if(this->hover)
        {
            if(!Touch)
            {
                (this->clickcb)();
                this->hover = false;
                this->hoverfact = 255;
            }
        }
        else
        {
            if(Touch)
            {
                this->hover = true;
                this->hoverfact = 0;
            }
        }
    }
}
