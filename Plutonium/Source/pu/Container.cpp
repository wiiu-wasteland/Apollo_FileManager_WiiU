#include <pu/Container.hpp>

namespace pu
{
    Container::Container(uint32_t X, uint32_t Y, uint32_t Width, uint32_t Height)
    {
        this->x = X;
        this->y = Y;
        this->w = Width;
        this->h = Height;
    }

    void Container::Add(element::Element *Elm)
    {
        this->elms.push_back(Elm);
    }

    element::Element *Container::At(uint32_t Index)
    {
        if(Index < this->elms.size()) return this->elms[Index];
        return NULL;
    }

    bool Container::Has(element::Element *Elm)
    {
        if(!this->elms.empty()) for(uint32_t i = 0; i < this->elms.size(); i++)
        {
            if(this->elms[i] == Elm) return true;
        }
        return false;
    }

    void Container::Clear()
    {
        if(!this->elms.empty()) for(uint32_t i = 0; i < this->elms.size(); i++) delete this->elms[i];
        this->elms.clear();
    }

    uint32_t Container::GetCount()
    {
        return this->elms.size();
    }

    void Container::SetX(uint32_t X)
    {
        this->x = X;
    }

    uint32_t Container::GetX()
    {
        return this->x;
    }

    void Container::SetY(uint32_t Y)
    {
        this->y = Y;
    }

    uint32_t Container::GetY()
    {
        return this->y;
    }

    void Container::SetWidth(uint32_t Width)
    {
        this->w = Width;
    }

    uint32_t Container::GetWidth()
    {
        return this->w;
    }

    void Container::SetHeight(uint32_t Height)
    {
        this->h = Height;
    }

    uint32_t Container::GetHeight()
    {
        return this->h;
    }

    void Container::PreRender()
    {
        if(!this->elms.empty()) for(uint32_t i = 0; i < this->elms.size(); i++)
        {
            this->elms[i]->SetParent(this);
        }
    }
}