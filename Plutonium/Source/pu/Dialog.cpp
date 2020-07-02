#include <pu/Dialog.hpp>
#include <pu/Application.hpp>
#include <cmath>

namespace pu
{
    Dialog::Dialog(std::string Title, std::string Content)
    {
        this->tfont = render::LoadStandardFont(30);
        this->cfont = render::LoadStandardFont(20);
        this->ofont = render::LoadStandardFont(18);
        this->title = render::RenderText(this->tfont, Title, { 10, 10, 10, 255 });
        this->cnt = render::RenderText(this->cfont, Content, { 20, 20, 20, 255 });
        this->osel = 0;
        this->prevosel = 0;
        this->selfact = 255;
        this->pselfact = 0;
        this->hicon = false;
        this->cancel = false;
        this->hcancel = false;
    }

    Dialog::~Dialog()
    {
        if(this->tfont != NULL)
        {
            render::DeleteFont(this->tfont);
            this->tfont = NULL;
        }
        if(this->cfont != NULL)
        {
            render::DeleteFont(this->cfont);
            this->cfont = NULL;
        }
        if(this->ofont != NULL)
        {
            render::DeleteFont(this->ofont);
            this->ofont = NULL;
        }
        if(this->title != NULL)
        {
            render::DeleteTexture(this->title);
            this->title = NULL;
        }
        if(this->cnt != NULL)
        {
            render::DeleteTexture(this->cnt);
            this->cnt = NULL;
        }
        if(this->hicon && (this->icon != NULL))
        {
            render::DeleteTexture(this->icon);
            this->icon = NULL;
            this->hicon = false;
        }
        if(!this->opts.empty()) for(uint32_t i = 0; i < this->opts.size(); i++) render::DeleteTexture(this->opts[i]);
        this->opts.clear();
        this->sopts.clear();
    }

    void Dialog::AddOption(std::string Name)
    {
        this->opts.push_back(render::RenderText(this->ofont, Name, { 10, 10, 10, 255 }));
        this->sopts.push_back(Name);
    }

    void Dialog::SetCancelOption(std::string Name)
    {
        this->hcancel = true;
        this->scancel = Name;
    }

    void Dialog::RemoveCancelOption()
    {
        this->hcancel = false;
        this->scancel = "";
    }

    bool Dialog::HasCancelOption()
    {
        return this->hcancel;
    }

    void Dialog::SetIcon(std::string Icon)
    {
        if(this->hicon) render::DeleteTexture(this->icon);
        this->icon = render::LoadImage(Icon);
        this->hicon = true;
    }

    bool Dialog::Hasicon()
    {
        return this->hicon;
    }

    uint32_t Dialog::Show(render::Renderer *Drawer, void *App)
    {
        if(this->hcancel) this->AddOption(this->scancel);
        if(this->opts.empty()) return 0;
        uint32_t dw = (20 * (this->opts.size() - 1)) + 250;
        for(uint32_t i = 0; i < this->opts.size(); i++)
        {
            uint32_t tw = render::GetTextWidth(this->ofont, this->sopts[i]);
            dw += tw + 20;
        }
        if(dw > 1280) dw = 1280;
        uint32_t icm = 30;
        uint32_t elemh = 60;
        uint32_t tdw = render::GetTextureWidth(this->cnt) + 90;
        if(tdw > dw) dw = tdw;
        tdw = render::GetTextureWidth(this->title) + 90;
        if(tdw > dw) dw = tdw;
        uint32_t ely = render::GetTextureHeight(this->title) + render::GetTextureHeight(this->cnt) + 140;
        if(this->hicon)
        {
            uint32_t tely = render::GetTextureHeight(this->icon) + icm + 25;
            if(tely > ely) ely = tely;
            tdw = render::GetTextureWidth(this->cnt) + 90 + render::GetTextureWidth(this->icon) + 20;
            if(tdw > dw) dw = tdw;
            tdw = render::GetTextureWidth(this->title) + 90 + render::GetTextureWidth(this->icon) + 20;
            if(tdw > dw) dw = tdw;
        }
        if(dw > 1280) dw = 1280;
        uint32_t dh = ely + elemh + 30;
        if(dh > 720) dh = 720;
        uint32_t dx = (1280 - dw) / 2;
        uint32_t dy = (720 - dh) / 2;
        ely += dy;
        uint32_t elemw = ((dw - (20 * (this->opts.size() + 1))) / this->opts.size());
        uint32_t elx = dx + ((dw - ((elemw * this->opts.size()) + (20 * (this->opts.size() - 1)))) / 2);
        uint32_t r = 35;
        uint32_t nr = 180;
        uint32_t ng = 180;
        uint32_t nb = 200;
        bool end = false;
        int32_t initfact = 0;
        while(true)
        {
            bool ok = ((Application*)App)->CallForRenderWithRenderOver([&](render::Renderer *Drawer) -> bool
            {
				uint32_t k = input::ButtonsDown();
				uint32_t h = input::ButtonsHeld();
                if((k & BUTTON_DLEFT) || (k & BUTTON_LSTICK_LEFT) || (h & BUTTON_RSTICK_LEFT))
                {
                    if(this->osel > 0)
                    {
                        this->prevosel = this->osel;
                        this->osel--;
                        for(uint32_t i = 0; i < this->opts.size(); i++)
                        {
                            if(i == this->osel) this->selfact = 0;
                            else if(i == this->prevosel) this->pselfact = 255;
                        }
                    }
                }
                else if((k & BUTTON_DRIGHT) || (k & BUTTON_LSTICK_RIGHT) || (h & BUTTON_RSTICK_RIGHT))
                {
                    if(this->osel < (this->opts.size() - 1))
                    {
                        this->prevosel = this->osel;
                        this->osel++;
                        for(uint32_t i = 0; i < this->opts.size(); i++)
                        {
                            if(i == this->osel) this->selfact = 0;
                            else if(i == this->prevosel) this->pselfact = 255;
                        }
                    }
                }
                else if(k & BUTTON_A)
                {
                    this->cancel = false;
                    end = true;
                }
                else if(k & BUTTON_B)
                {
                    this->cancel = true;
                    end = true;
                }
                else if(k & BUTTON_TOUCH)
                {
					uint32_t xtch, ytch;
					input::TouchPosition(xtch, ytch);
                    for(uint32_t i = 0; i < this->opts.size(); i++)
                    {
                        std::string txt = this->sopts[i];
                        uint32_t rx = elx + ((elemw + 20) * i);
                        uint32_t ry = ely;
						if(((rx + elemw) > xtch) && (xtch > rx) && ((ry + elemh) > ytch) && (ytch > ry))
                        {
                            this->osel = i;
                            this->cancel = false;
                            end = true;
                        }
                    }
                }
                uint32_t bw = dw;
                uint32_t bh = dh;
                uint32_t fw = bw - (r * 2);
                uint32_t fh = bh - (r * 2);
                draw::Color clr = { 225, 225, 225, initfact };
                int32_t aclr = initfact;
                if(aclr < 0) aclr = 0;
                if(aclr > 125) aclr = 125;
                Drawer->RenderRectangleFill({ 0, 0, 0, (uint8_t)aclr }, 0, 0, 1280, 720);
                Drawer->RenderRoundedRectangleFill(clr, dx, dy, bw, bh, r);
                render::SetAlphaValue(this->title, initfact);
                render::SetAlphaValue(this->cnt, initfact);
                Drawer->RenderTexture(this->title, (dx + 45), (dy + 55));
                Drawer->RenderTexture(this->cnt, (dx + 45), (dy + 140));
                if(this->hicon)
                {
                    uint32_t icw = render::GetTextureWidth(this->icon);
                    uint32_t icx = dx + (dw - (icw + icm));
                    uint32_t icy = dy + icm;
                    Drawer->RenderTexture(this->icon, icx, icy, initfact);
                }
                for(uint32_t i = 0; i < this->opts.size(); i++)
                {
                    std::string txt = this->sopts[i];
                    uint32_t tw = render::GetTextWidth(this->ofont, txt);
                    uint32_t th = render::GetTextHeight(this->ofont, txt);
                    uint32_t tx = elx + ((elemw - tw) / 2) + ((elemw + 20) * i);
                    uint32_t ty = ely + ((elemh - th) / 2);
                    uint32_t rx = elx + ((elemw + 20) * i);
                    uint32_t ry = ely;
                    uint32_t rr = (elemh / 2);
                    draw::Color dclr = { nr, ng, nb, initfact };
                    if(this->osel == i)
                    {
                        if(this->selfact < 255)
                        {
                            dclr = { nr, ng, nb, this->selfact };
                            Drawer->RenderRoundedRectangleFill(dclr, rx, ry, elemw, elemh, rr);
                            this->selfact += 48;
                        }
                        else
                        {
                            dclr = { nr, ng, nb, initfact };
                            Drawer->RenderRoundedRectangleFill(dclr, rx, ry, elemw, elemh, rr);
                        }
                    }
                    else if(this->prevosel == i)
                    {
                        if(this->pselfact > 0)
                        {
                            dclr = { nr, ng, nb, this->pselfact };
                            Drawer->RenderRoundedRectangleFill(dclr, rx, ry, elemw, elemh, rr);
                            this->pselfact -= 48;
                        }
                    }
                    render::SetAlphaValue(this->opts[i], initfact);
                    Drawer->RenderTexture(this->opts[i], tx, ty);
                }
                if(end)
                {
                    if(initfact == 0) return false;
                    if(initfact > 0) initfact -= 25;
                    if(initfact < 0) initfact = 0;
                }
                else
                {
                    if(initfact < 255) initfact += 25;
                    if(initfact > 255) initfact = 255;
                }
                return true;
            });
            if(!ok)
            {
                ((Application*)App)->CallForRenderWithRenderOver([&](render::Renderer *Drawer) -> bool {});
                break;
            }
        }
        return this->osel;
    }

    bool Dialog::UserCancelled()
    {
        return this->cancel;
    }

    bool Dialog::IsOk()
    {
        bool ok = true;
        if(this->cancel) ok = false;
        if(this->hcancel && (this->osel == (this->opts.size() - 1))) ok = false;
        return ok;
    }
}
