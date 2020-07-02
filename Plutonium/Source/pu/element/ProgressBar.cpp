#include <pu/element/ProgressBar.hpp>

namespace pu::element
{
    ProgressBar::ProgressBar(uint32_t X, uint32_t Y, uint32_t Width, uint32_t Height, double MaxValue) : Element::Element()
    {
        this->x = X;
        this->y = Y;
        this->w = Width;
        this->h = Height;
        this->clr = { 140, 140, 140, 255 };
        this->oclr = { 139, 195, 74, 255 };
        this->val = 0.0f;
        this->maxval = MaxValue;
    }

    uint32_t ProgressBar::GetX()
    {
        return this->x;
    }

    void ProgressBar::SetX(uint32_t X)
    {
        this->x = X;
    }

    uint32_t ProgressBar::GetY()
    {
        return this->y;
    }

    void ProgressBar::SetY(uint32_t Y)
    {
        this->y = Y;
    }

    uint32_t ProgressBar::GetWidth()
    {
        return this->w;
    }

    void ProgressBar::SetWidth(uint32_t Width)
    {
        this->w = Width;
    }

    uint32_t ProgressBar::GetHeight()
    {
        return this->h;
    }

    void ProgressBar::SetHeight(uint32_t Height)
    {
        this->h = Height;
    }

    draw::Color ProgressBar::GetColor()
    {
        return this->clr;
    }

    void ProgressBar::SetColor(draw::Color Color)
    {
        this->clr = Color;
    }

    draw::Color ProgressBar::GetProgressColor()
    {
        return this->oclr;
    }

    void ProgressBar::SetProgressColor(draw::Color Color)
    {
        this->oclr = Color;
    }

    double ProgressBar::GetProgress()
    {
        return this->val;
    }

    void ProgressBar::SetProgress(double Progress)
    {
        if(Progress >= this->maxval) this->FillProgress();
        else this->val = Progress;
    }

    void ProgressBar::IncrementProgress(double Progress)
    {
        double res = (this->val + Progress);
        if(res >= this->maxval) this->FillProgress();
        else this->val = res;
    }

    void ProgressBar::DecrementProgress(double Progress)
    {
        if(this->val > Progress) this->ClearProgress();
        else this->val -= Progress;
    }

    void ProgressBar::SetMaxValue(double Max)
    {
        this->maxval = Max;
    }

    double ProgressBar::GetMaxValue()
    {
        return this->maxval;
    }

    void ProgressBar::FillProgress()
    {
        this->val = this->maxval;
    }

    void ProgressBar::ClearProgress()
    {
        this->val = 0;
    }

    bool ProgressBar::IsCompleted()
    {
        return (this->val >= this->maxval);
    }

    void ProgressBar::OnRender(render::Renderer *Drawer)
    {
        uint32_t rdx = this->GetProcessedX();
        uint32_t rdy = this->GetProcessedY();
        uint32_t pcw = (uint32_t)((this->val / this->maxval) * (double)this->w);
        uint32_t rad = (this->h / 3);
        Drawer->RenderRoundedRectangleFill(this->clr, rdx, rdy, this->w, this->h, rad);
        Drawer->RenderRoundedRectangleFill(this->oclr, rdx, rdy, std::max(this->h, pcw), this->h, rad);
    }

    void ProgressBar::OnInput(uint32_t Down, uint32_t Up, uint32_t Held, bool Touch, bool Focus)
    {
    }
}
