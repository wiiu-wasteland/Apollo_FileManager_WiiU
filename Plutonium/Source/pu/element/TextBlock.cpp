#include <pu/element/TextBlock.hpp>

namespace pu::element
{
    TextBlock::TextBlock(uint32_t X, uint32_t Y, std::string Text, uint32_t FontSize) : Element::Element()
    {
        this->x = X;
        this->y = Y;
        this->text = Text;
        this->clr = { 0, 0, 0, 255 };
        this->fnt = render::LoadStandardFont(FontSize);
        this->fsize = FontSize;
        this->ntex = render::RenderText(this->fnt, Text, this->clr);
    }

    TextBlock::~TextBlock()
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

    uint32_t TextBlock::GetX()
    {
        return this->x;
    }

    void TextBlock::SetX(uint32_t X)
    {
        this->x = X;
    }

    uint32_t TextBlock::GetY()
    {
        return this->y;
    }

    void TextBlock::SetY(uint32_t Y)
    {
        this->y = Y;
    }

    uint32_t TextBlock::GetWidth()
    {
        return this->GetTextWidth();
    }

    uint32_t TextBlock::GetHeight()
    {
        return this->GetTextHeight();
    }

    uint32_t TextBlock::GetTextWidth()
    {
        return render::GetTextWidth(this->fnt, this->text);
    }

    uint32_t TextBlock::GetTextHeight()
    {
        return render::GetTextHeight(this->fnt, this->text);
    }

    std::string TextBlock::GetText()
    {
        return this->text;
    }

    void TextBlock::SetText(std::string Text)
    {
        this->text = Text;
        render::DeleteTexture(this->ntex);
        this->ntex = render::RenderText(this->fnt, Text, this->clr);
    }

    void TextBlock::SetFont(render::NativeFont Font)
    {
        render::DeleteFont(this->fnt);
        this->fnt = Font;
        render::DeleteTexture(this->ntex);
        this->ntex = render::RenderText(Font, this->text, this->clr);
    }
	
	void TextBlock::SetFont(std::string Font, uint32_t Size)
	{
		render::DeleteFont(this->fnt);
		this->fnt = render::LoadFont(Font, Size);;
		render::DeleteTexture(this->ntex);
		this->ntex = render::RenderText(this->fnt, this->text, this->clr);
	}

    draw::Color TextBlock::GetColor()
    {
        return this->clr;
    }

    void TextBlock::SetColor(draw::Color Color)
    {
        this->clr = Color;
        render::DeleteTexture(this->ntex);
        this->ntex = render::RenderText(this->fnt, this->text, Color);
    }

    void TextBlock::OnRender(render::Renderer *Drawer)
    {
        uint32_t rdx = this->GetProcessedX();
        uint32_t rdy = this->GetProcessedY();
        Drawer->RenderTexture(this->ntex, rdx, rdy);
    }

    void TextBlock::OnInput(uint32_t Down, uint32_t Up, uint32_t Held, bool Touch, bool Focus)
    {
    }
}
