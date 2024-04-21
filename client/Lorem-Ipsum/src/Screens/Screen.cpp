# include "Screen.h"

void Screen::InitRenderElementsOnResize()
{
    for (auto entity: m_Scene->GetEntities<Core::UIComponent>())
    {
        if(entity->HasComponent<Core::NativeScript>())
            entity->GetComponent<Core::NativeScript>().OnDestroy();
        
        entity->Destroy();
    }

    InitRenderElements();  
}

void Screen::ClearScene()
{
    for (auto entity: m_Scene->GetEntities<Core::UIComponent>())
    {
        entity->Destroy();
    }
}