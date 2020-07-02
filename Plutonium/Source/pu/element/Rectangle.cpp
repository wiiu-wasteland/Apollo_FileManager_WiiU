#include <pu/element/Rectangle.hpp>

namespace pu::element
{
    Rectangle::Rectangle(uint32_t X, uint32_t Y, uint32_t Width, uint32_t Height, draw::Color RecColor, uint32_t BorderRadius) : Element::Element()
    {
        this->x = X;
        this->y = Y;
        this->w = Width;
        this->h = Height;
        this->clr = RecColor;
        this->borderr = BorderRadius;
		this->drawSideShadow = false;
		this->sideShadowWidth = 5;
		this->sideShadowMainAlpha = 160;
    }

    uint32_t Rectangle::GetX()
    {
        return this->x;
    }

    void Rectangle::SetX(uint32_t X)
    {
        this->x = X;
    }

    uint32_t Rectangle::GetY()
    {
        return this->y;
    }

    void Rectangle::SetY(uint32_t Y)
    {
        this->y = Y;
    }

    uint32_t Rectangle::GetWidth()
    {
        return this->w;
    }

    void Rectangle::SetWidth(uint32_t Width)
    {
        this->w = Width;
    }

    uint32_t Rectangle::GetHeight()
    {
        return this->h;
    }

    void Rectangle::SetHeight(uint32_t Height)
    {
        this->h = Height;
    }

    uint32_t Rectangle::GetBorderRadius()
    {
        return this->h;
    }

    void Rectangle::SetBorderRadius(uint32_t Radius)
    {
        this->borderr = Radius;
    }

    draw::Color Rectangle::GetColor()
    {
        return this->clr;
    }

    void Rectangle::SetColor(draw::Color RecColor)
    {
        this->clr = RecColor;
    }

	void Rectangle::SetDrawSideShadow(bool drawSideShadow, uint32_t sideShadowWidth, uint32_t sideShadowMainAlpha)
	{
		this->drawSideShadow = drawSideShadow;
		this->sideShadowWidth = sideShadowWidth;
		this->sideShadowMainAlpha = sideShadowMainAlpha;
	}
	
    void Rectangle::OnRender(render::Renderer *Drawer)
    {
        uint32_t rdx = this->GetProcessedX();
        uint32_t rdy = this->GetProcessedY();
        Drawer->RenderRectangleFill(this->clr, rdx, rdy, this->w, this->h);
		
		if (this->drawSideShadow)
			Drawer->RenderSideShadowSimple(this->x+this->w, this->y, this->sideShadowWidth, this->h, this->sideShadowMainAlpha);	
    }

    void Rectangle::OnInput(uint32_t Down, uint32_t Up, uint32_t Held, bool Touch, bool Focus)
    {
    }
}
