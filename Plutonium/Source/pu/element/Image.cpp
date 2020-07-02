#include <pu/element/Image.hpp>

namespace pu::element
{
    Image::Image(uint32_t X, uint32_t Y, std::string Image) : Element::Element()
    {
        this->x = X;
        this->y = Y;
        this->w = 0;
        this->h = 0;
        std::ifstream ifs(Image);
        if(ifs.good())
        {
            this->img = Image;
            this->ntex = render::LoadImage(Image);
        }
        ifs.close();
    }

    Image::~Image()
    {
        if(this->ntex != NULL)
        {
            render::DeleteTexture(this->ntex);
            this->ntex = NULL;
        }
    }

    uint32_t Image::GetX()
    {
        return this->x;
    }

    void Image::SetX(uint32_t X)
    {
        this->x = X;
    }

    uint32_t Image::GetY()
    {
        return this->y;
    }

    void Image::SetY(uint32_t Y)
    {
        this->y = Y;
    }

    uint32_t Image::GetWidth()
    {
        return this->w;
    }

    void Image::SetWidth(uint32_t Width)
    {
        this->w = Width;
    }

    uint32_t Image::GetHeight()
    {
        return this->h;
    }

    void Image::SetHeight(uint32_t Height)
    {
        this->h = Height;
    }

    std::string Image::GetImage()
    {
        return this->img;
    }

    void Image::SetImage(std::string Image)
    {
        std::ifstream ifs(Image);
        if(ifs.good())
        {
            this->img = Image;
            render::DeleteTexture(this->ntex);
            this->ntex = render::LoadImage(Image);
        }
        ifs.close();
    }

    bool Image::IsImageValid()
    {
        std::ifstream ifs(this->img);
        bool ok = ifs.good();
        ifs.close();
        return ok;
    }

    void Image::OnRender(render::Renderer *Drawer)
    {
        uint32_t rdx = this->GetProcessedX();
        uint32_t rdy = this->GetProcessedY();
        uint32_t iw = this->w;
        uint32_t ih = this->h;
        if((iw == 0) || (ih == 0)) Drawer->RenderTexture(this->ntex, rdx, rdy);
        else Drawer->RenderTextureScaled(this->ntex, rdx, rdy, iw, ih);
    }

    void Image::OnInput(uint32_t Down, uint32_t Up, uint32_t Held, bool Touch, bool Focus)
    {
    }
}
