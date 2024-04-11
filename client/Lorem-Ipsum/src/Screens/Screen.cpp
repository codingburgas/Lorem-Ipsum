# include "Screen.h"

void Screen::RenderElementsOnResize()
{
    for (auto entity: m_Scene->GetEntities<Core::UIComponent>())
    {
        entity->Destroy();
    }

    RenderElements();  
}
