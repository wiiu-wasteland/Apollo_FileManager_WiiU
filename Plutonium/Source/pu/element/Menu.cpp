#include <pu/element/Menu.hpp>

namespace pu::element
{
    MenuItem::MenuItem(std::string Name, std::string SecondName)
    {
        this->font = render::LoadStandardFont(25);
		this->secondfont = render::LoadStandardFont(20);
        this->clr = { 10, 10, 10, 255 };
		this->snclr = { 10, 10, 10, 255 };
        this->name = Name;
		this->secondname = SecondName;
        this->ntex = render::RenderText(this->font, Name, this->clr);
		this->sntex = render::RenderText(this->secondfont, SecondName, this->snclr);
        this->hasicon = false;
    }

    MenuItem::~MenuItem()
    {
        if(this->font != NULL)
        {
            render::DeleteFont(this->font);
            this->font = NULL;
        }
		if(this->secondfont != NULL)
        {
            render::DeleteFont(this->secondfont);
            this->secondfont = NULL;
        }
        if(this->ntex != NULL)
        {
            render::DeleteTexture(this->ntex);
            this->ntex = NULL;
        }
		if(this->sntex != NULL)
        {
            render::DeleteTexture(this->sntex);
            this->sntex = NULL;
        }
        if(this->hasicon && (this->itex != NULL))
        {
            render::DeleteTexture(this->itex);
            this->itex = NULL;
        }
    }

    std::string MenuItem::GetName()
    {
        return this->name;
    }
	
	std::string MenuItem::GetSecondName()
    {
        return this->secondname;
    }

    void MenuItem::SetName(std::string Name)
    {
        this->name = Name;
        render::DeleteTexture(this->ntex);
        this->ntex = render::RenderText(this->font, Name, this->clr);
    }

	void MenuItem::SetSecondName(std::string SecondName)
	{
		this->secondname = SecondName;
		render::DeleteTexture(this->sntex);
		this->sntex = render::RenderText(this->secondfont, SecondName, this->clr);
	}
	
	void MenuItem::SetSecondNameColor(draw::Color Color)
	{
		this->snclr = Color;
        render::DeleteTexture(this->sntex);
        this->sntex = render::RenderText(this->secondfont, this->secondname, Color);
	}
	
	void MenuItem::SetNameFont(std::string Font, uint32_t Size)
	{
		render::DeleteFont(this->font);
		this->font = render::LoadFont(Font, Size);;
		render::DeleteTexture(this->ntex);
		this->ntex = render::RenderText(this->font, this->name, this->clr);
		
	}
	
	void MenuItem::SetSecondNameFont(std::string Font, uint32_t Size)
	{
		render::DeleteFont(this->secondfont);
		this->secondfont = render::LoadFont(Font, Size);;
		render::DeleteTexture(this->sntex);
		this->sntex = render::RenderText(this->secondfont, this->secondname, this->snclr);
	}
	
    draw::Color MenuItem::GetColor()
    {
        return this->clr;
    }
	
	draw::Color MenuItem::GetSecondNameColor()
	{
		return this->snclr;
	}

    void MenuItem::SetColor(draw::Color Color)
    {
        this->clr = Color;
        render::DeleteTexture(this->ntex);
        this->ntex = render::RenderText(this->font, this->name, Color);
    }

    void MenuItem::AddOnClick(std::function<void()> Callback, uint32_t Key)
    {
        this->cbs.push_back(Callback);
        this->cbipts.push_back(Key);
    }

    uint32_t MenuItem::GetCallbackCount()
    {
        return this->cbs.size();
    }

    std::function<void()> MenuItem::GetCallback(uint32_t Index)
    {
        return this->cbs[Index];
    }

    uint32_t MenuItem::GetCallbackKey(uint32_t Index)
    {
        return this->cbipts[Index];
    }

    std::string MenuItem::GetIcon()
    {
        return this->icon;
    }

    void MenuItem::SetIcon(std::string Icon)
    {
        std::ifstream ifs(Icon);
        if(ifs.good())
        {
            this->icon = Icon;
            if(this->hasicon) render::DeleteTexture(this->itex);
            this->itex = render::LoadImage(Icon);
            this->hasicon = true;
        }
        ifs.close();
    }
	
    bool MenuItem::HasIcon()
    {
        return this->hasicon;
    }

    render::NativeFont MenuItem::GetFont()
    {
        return this->font;
    }

	render::NativeFont MenuItem::GetSecondFont()
	{
		return this->secondfont;
	}
	
    render::NativeTexture MenuItem::GetNameTexture()
    {
        return this->ntex;
    }
	
	render::NativeTexture MenuItem::GetSecondNameTexture()
    {
        return this->sntex;
    }

    render::NativeTexture MenuItem::GetIconTexture()
    {
        return this->itex;
    }

    Menu::Menu(uint32_t X, uint32_t Y, uint32_t Width, draw::Color OptionColor, uint32_t ItemSize, uint32_t ItemsToShow) : Element::Element()
    {
        this->x = X;
        this->y = Y;
        this->w = Width;
        this->clr = OptionColor;
        this->scb = { 110, 110, 110, 255 };
        this->isize = ItemSize;
        this->ishow = ItemsToShow;
        this->previsel = 0;
        this->isel = 0;
        this->fisel = 0;
        this->selfact = 255;
        this->pselfact = 0;
        this->onselch = [&](){};
        this->icdown = false;
        this->dtouch = false;
        this->fcs = { 40, 40, 40, 255 };
        this->uptime = false;
        this->uphold = false;
        this->downtime = false;
        this->downhold = false;
		this->drawShadow = true;
		this->onFocus = true;
		this->iconScale = 1;
		this->iconOnly = false;
		this->scbpos = 0;
		this->scbwidth = 20;
		this->snposper = 0.5;
    }

    Menu::~Menu()
    {
        this->ClearItems();
    }

    uint32_t Menu::GetX()
    {
        return this->x;
    }

    void Menu::SetX(uint32_t X)
    {
        this->x = X;
    }

    uint32_t Menu::GetY()
    {
        return this->y;
    }

    void Menu::SetY(uint32_t Y)
    {
        this->y = Y;
    }

    uint32_t Menu::GetWidth()
    {
        return this->w;
    }

    void Menu::SetWidth(uint32_t Width)
    {
        this->w = Width;
    }

    uint32_t Menu::GetHeight()
    {
        return (this->isize * this->ishow);
    }

    uint32_t Menu::GetItemSize()
    {
        return this->isize;
    }

    void Menu::SetItemSize(uint32_t ItemSize)
    {
        this->isize = ItemSize;
    }

    uint32_t Menu::GetNumberOfItemsToShow()
    {
        return this->ishow;
    }

    void Menu::SetNumberOfItemsToShow(uint32_t ItemsToShow)
    {
        this->ishow = ItemsToShow;
    }

    draw::Color Menu::GetColor()
    {
        return this->clr;
    }

    void Menu::SetColor(draw::Color Color)
    {
        this->clr = Color;
    }
    
    draw::Color Menu::GetOnFocusColor()
    {
        return this->fcs;
    }

    void Menu::SetOnFocusColor(draw::Color Color)
    {
        this->fcs = Color;
    }

    draw::Color Menu::GetScrollbarColor()
    {
        return this->scb;
    }

    void Menu::SetScrollbarColor(draw::Color Color)
    {
        this->scb = Color;
    }

    void Menu::SetOnSelectionChanged(std::function<void()> Callback)
    {
        this->onselch = Callback;
    }

    void Menu::AddItem(MenuItem *Item)
    {
        this->itms.push_back(Item);
    }

    void Menu::ClearItems()
    {
        if(!this->itms.empty()) for(uint32_t i = 0; i < this->itms.size(); i++) delete this->itms[i];
        this->itms.clear();
    }

    void Menu::SetCooldownEnabled(bool Cooldown)
    {
        this->icdown = Cooldown;
    }

    MenuItem *Menu::GetSelectedItem()
    {
        return this->itms[this->isel];
    }

    uint32_t Menu::GetSelectedIndex()
    {
        return this->isel;
    }

	uint32_t Menu::GetScrollIndex()
	{
		return this->fisel;
	}
	
    void Menu::SetSelectedIndex(uint32_t Index)
    {
		if (this->itms.size() > 0)
		{
			if (this->itms.size() > Index)
				this->isel = Index;
			else
				this->isel = itms.size()-1;
	
			this->fisel = 0;
			this->selfact = 255;
			this->pselfact = 0;
		}
    }

	void Menu::SetScrollIndex(uint32_t Scroll)
	{
		if (this->itms.size() > this->ishow)
		{
			if (this->itms.size() >= Scroll + this->ishow)
				this->fisel = Scroll;
			else
				this->fisel = itms.size() - this->ishow;
		}
	}
	
	void Menu::SetDrawShadow(bool drawShadow)
	{
		this->drawShadow = drawShadow;
	}

	void Menu::SetOnFocus(bool onFocus)
	{
		this->onFocus = onFocus;
	}
	
	void Menu::SetIconScale(double Scale)
	{
		this->iconScale = Scale;
	}
	
	double Menu::GetIconScale()
	{
		return this->iconScale;
	}
	
	void Menu::SetIconOnly(bool iconOnly)
	{
		this->iconOnly = iconOnly;
	}
	
	bool Menu::IsIconOnly()
	{
		return this->iconOnly;
	}
	
	void Menu::SetScrollbarPosition(uint32_t scbpos)
	{
		this->scbpos = scbpos;
	}
	
	void Menu::SetScrollbarWidth(uint32_t scbwidth)
	{
		this->scbwidth = scbwidth;
	}
	
	void Menu::SetSecondNamePositionPercent(double Percent)
	{
		this->snposper = Percent;
	}
	
    void Menu::OnRender(render::Renderer *Drawer)
    {
        uint32_t rdx = this->GetProcessedX();
        uint32_t rdy = this->GetProcessedY();
        if(!this->itms.empty())
        {
            uint32_t cx = rdx;
            uint32_t cy = rdy;
            uint32_t cw = this->w;
            uint32_t ch = this->isize;
            uint32_t its = this->ishow;
            if(its > this->itms.size()) its = this->itms.size();
            for(uint32_t i = this->fisel; i < (its + this->fisel); i++)
            {
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
                if(this->isel == i)
                {
                    Drawer->RenderRectangleFill(this->clr, cx, cy, cw, ch);
                    if(this->selfact < 255)
                    {
                        Drawer->RenderRectangleFill(draw::Color(this->fcs.R, this->fcs.G, this->fcs.B, this->selfact), cx, cy, cw, ch);
                        this->selfact += 48;
                    }
                    else Drawer->RenderRectangleFill(this->fcs, cx, cy, cw, ch);
                }
                else if(this->previsel == i)
                {
                    Drawer->RenderRectangleFill(this->clr, cx, cy, cw, ch);
                    if(this->pselfact > 0)
                    {
                        Drawer->RenderRectangleFill(draw::Color(this->fcs.R, this->fcs.G, this->fcs.B, this->pselfact), cx, cy, cw, ch);
                        this->pselfact -= 48;
                    }
                    else Drawer->RenderRectangleFill(this->clr, cx, cy, cw, ch);
                }
                else Drawer->RenderRectangleFill(this->clr, cx, cy, cw, ch);
                MenuItem *itm = this->itms[i];
                uint32_t xh = render::GetTextHeight(itm->GetFont(), itm->GetName());
                uint32_t tx = (cx + 25);
                uint32_t ty = ((ch - xh) / 2) + cy;
				uint32_t sxh = render::GetTextHeight(itm->GetFont(), "0");
				uint32_t sxh2 = render::GetTextHeight(itm->GetSecondFont(), "0");
				uint32_t sxh3 = (sxh-sxh2 > 0) ? sxh-sxh2 : sxh2-sxh;
				uint32_t stx = (double)((cw * this->snposper) + cx + 25);
				uint32_t sty = ((ch - sxh) / 2) + cy + sxh3;
                if(itm->HasIcon())
                {
					if (this->IsIconOnly())
					{
						uint32_t icd = (double)(this->isize - 10)*this->GetIconScale();
						uint32_t icx = (cx + (cw / 2) - (icd / 2));
						uint32_t icy = (cy + (ch / 2) - (icd / 2));
						tx = (icx + icd + 25);
						Drawer->RenderTextureScaled(itm->GetIconTexture(), icx, icy, icd, icd);
					}
					else
					{
						uint32_t icd = (this->isize - 10);
						uint32_t icx = (cx + 25);
						uint32_t icy = (cy + 5);
						tx = (icx + icd + 25);
						Drawer->RenderTextureScaled(itm->GetIconTexture(), icx, icy, icd, icd);
					}
                }
                Drawer->RenderTexture(itm->GetNameTexture(), tx, ty);
				Drawer->RenderTexture(itm->GetSecondNameTexture(), stx, sty);
                cy += ch;
            }
            if(this->ishow < this->itms.size())
            {
                int32_t sccr = this->scb.R;
                int32_t sccg = this->scb.G;
                int32_t sccb = this->scb.B;
                int32_t snr = sccr - 30;
                if(snr < 0) snr = 0;
                int32_t sng = sccg - 30;
                if(sng < 0) sng = 0;
                int32_t snb = sccb - 30;
                if(snb < 0) snb = 0;
                draw::Color sclr(snr, sng, snb, this->scb.A);
				uint32_t scx = 0;
				uint32_t scy = rdy;	
				uint32_t scw = this->scbwidth;
				uint32_t sch = (this->ishow * this->isize);;
				switch (this->scbpos)
				{
					case 0:
						scx = rdx + (this->w - 20);
					break;
					case 1:
						scx = rdx;			
					break;
				}
                Drawer->RenderRectangleFill(this->scb, scx, scy, scw, sch);
                uint32_t fch = ((this->ishow * sch) / this->itms.size());
                uint32_t fcy = scy + (this->fisel * (sch / this->itms.size()));
                Drawer->RenderRectangleFill(sclr, scx, fcy, scw, fch);
            }

			if(this->drawShadow)
				Drawer->RenderShadowSimple(cx, cy, cw, 5, 160);
        }
    }

    void Menu::OnInput(uint32_t Down, uint32_t Up, uint32_t Held, bool Touch, bool Focus)
    {
        uint32_t rdx = this->GetProcessedX();
        uint32_t rdy = this->GetProcessedY();
		if (this->onFocus)
		{
			if(Touch)
			{
				uint32_t xtch, ytch;
				input::TouchPosition(xtch, ytch);
				uint32_t cx = rdx;
				uint32_t cy = rdx;
				uint32_t cw = this->w;
				uint32_t ch = this->isize;
				uint32_t its = this->ishow;
				if(its > this->itms.size()) its = this->itms.size();
				for(uint32_t i = this->fisel; i < (this->fisel + its); i++)
				{
					if(((cx + cw) > xtch) && (xtch > cx) && ((cy + ch) > ytch) && (ytch > cy))
					{
						this->dtouch = true;
						this->previsel = this->isel;
						this->isel = i;
						(this->onselch)();
						if(i == this->isel) this->selfact = 255;
						else if(i == this->previsel) this->pselfact = 0;
						break;
					}
					cy += this->isize;
				}
			}
			else if(this->dtouch)
			{
				if((this->selfact >= 255) && (this->pselfact <= 0))
				{
					if(this->icdown) this->icdown = false;
					else (this->itms[this->isel]->GetCallback(0))();
					this->dtouch = false;
				}
			}
			else
			{
				if(Down & BUTTON_DOWN)
				{
					if(!downtime) this->downtp = std::chrono::steady_clock::now();
					if(this->isel < (this->itms.size() - 1))
					{
						if((this->isel - this->fisel) == (this->ishow - 1))
						{
							this->fisel++;
							this->isel++;
							(this->onselch)();
						}
						else
						{
							this->previsel = this->isel;
							this->isel++;
							(this->onselch)();
							if(!this->itms.empty()) for(uint32_t i = 0; i < this->itms.size(); i++)
							{
								if(i == this->isel) this->selfact = 0;
								else if(i == this->previsel) this->pselfact = 255;
							}
						}
					}
					else
					{
						this->isel = 0;
						this->fisel = 0;
						(this->onselch)();
						if(!this->itms.empty()) for(uint32_t i = 0; i < this->itms.size(); i++)
						{
							if(i == this->isel) this->selfact = 0;
							else if(i == this->previsel) this->pselfact = 255;
						}
					}
					downtime = !downtime;
				}
				else if(Down & BUTTON_UP)
				{
					if(!uptime) this->uptp = std::chrono::steady_clock::now();
					if(this->isel > 0)
					{
						if(this->isel == this->fisel)
						{
							this->fisel--;
							this->isel--;
							(this->onselch)();
						}
						else
						{
							this->previsel = this->isel;
							this->isel--;
							(this->onselch)();
							if(!this->itms.empty()) for(uint32_t i = 0; i < this->itms.size(); i++)
							{
								if(i == this->isel) this->selfact = 0;
								else if(i == this->previsel) this->pselfact = 255;
							}
						}
					}
					else
					{
						this->isel = this->itms.size() - 1;
						if(this->itms.size() > this->ishow) this->fisel = this->itms.size() - this->ishow;
						else this->fisel = 0;
						(this->onselch)();
						if(!this->itms.empty()) for(uint32_t i = 0; i < this->itms.size(); i++)
						{
							if(i == this->isel) this->selfact = 0;
							else if(i == this->previsel) this->pselfact = 255;
						}
					}
					uptime = !uptime;
				}
				else
				{
					uint32_t ipc = this->itms[this->isel]->GetCallbackCount();
					if(ipc > 0) for(uint32_t i = 0; i < ipc; i++)
					{
						if(Down & this->itms[this->isel]->GetCallbackKey(i))
						{
							if(this->icdown) this->icdown = false;
							else (this->itms[this->isel]->GetCallback(i))();
						}
					}
				}
				auto curtp = std::chrono::steady_clock::now();
				if(downtime && !downhold)
				{
					uint64_t downdiff = std::chrono::duration_cast<std::chrono::milliseconds>(curtp - this->downtp).count();
					if(downdiff >= 500)
					{
						downhold = true;
					}
				}
				else if(downhold)
				{
					if(Held & BUTTON_DOWN)
					{
						if(this->isel < (this->itms.size() - 1))
						{
							if((this->isel - this->fisel) == (this->ishow - 1))
							{
								this->fisel++;
								this->isel++;
								(this->onselch)();
							}
							else
							{
								this->previsel = this->isel;
								this->isel++;
								(this->onselch)();
								if(!this->itms.empty()) for(uint32_t i = 0; i < this->itms.size(); i++)
								{
									if(i == this->isel) this->selfact = 0;
									else if(i == this->previsel) this->pselfact = 255;
								}
							}
						}
						else
						{
							this->isel = 0;
							this->fisel = 0;
							(this->onselch)();
							if(!this->itms.empty()) for(uint32_t i = 0; i < this->itms.size(); i++)
							{
								if(i == this->isel) this->selfact = 0;
								else if(i == this->previsel) this->pselfact = 255;
							}
						}
					}
					else
					{
						downhold = false;
						downtime = false;
					}
				}
				if(uptime && !uphold)
				{
					uint64_t updiff = std::chrono::duration_cast<std::chrono::milliseconds>(curtp - this->uptp).count();
					if(updiff >= 500)
					{
						uphold = true;
					}
				}
				else if(uphold)
				{
					if(Held & BUTTON_UP)
					{
						if(this->isel > 0)
						{
							if(this->isel == this->fisel)
							{
								this->fisel--;
								this->isel--;
								(this->onselch)();
							}
							else
							{
								this->previsel = this->isel;
								this->isel--;
								(this->onselch)();
								if(!this->itms.empty()) for(uint32_t i = 0; i < this->itms.size(); i++)
								{
									if(i == this->isel) this->selfact = 0;
									else if(i == this->previsel) this->pselfact = 255;
								}
							}
						}
						else
						{
							this->isel = this->itms.size() - 1;
							if(this->itms.size() > this->ishow) this->fisel = this->itms.size() - this->ishow;
							else this->fisel = 0;
							(this->onselch)();
							if(!this->itms.empty()) for(uint32_t i = 0; i < this->itms.size(); i++)
							{
								if(i == this->isel) this->selfact = 0;
								else if(i == this->previsel) this->pselfact = 255;
							}
						}
					}
					else
					{
						uphold = false;
						uptime = false;
					}
				}
			}
		}
    }
}
