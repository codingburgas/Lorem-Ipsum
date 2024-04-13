# include "Screen.h"

void Screen::InitRenderElementsOnResize()
{
    for (auto entity: m_Scene->GetEntities<Core::UIComponent>())
    {
        entity->Destroy();
    }

    InitRenderElements();  
}
