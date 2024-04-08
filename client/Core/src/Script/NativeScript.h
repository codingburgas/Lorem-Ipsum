#pragma once

namespace Core {
    class Entity;
    struct NativeScriptComponent;
    
    class NativeScript
    {
    public:
        NativeScript() = default;
        virtual ~NativeScript() = default;

        virtual void OnCreate() {}
        virtual void onLateAttach() {}
        virtual void OnDestroy() {}
        virtual void OnUpdate() {}

    protected:
        std::shared_ptr<Entity> m_Entity = nullptr;
        
        friend struct NativeScriptComponent;
    };
}