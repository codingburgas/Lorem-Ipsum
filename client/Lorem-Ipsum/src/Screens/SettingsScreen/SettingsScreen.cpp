#include "SettingsScreen.h"
#include "../Screens.h"

void settingCallback(std::shared_ptr<Core::Entity> e) {}

void SettingsScreen::OnScreenChange()
{
    if(m_User->Name.find(" ") != std::string::npos)
    {
        m_FirstName = m_User->Name.substr(0, m_User->Name.find(" "));
        m_LastName = m_User->Name.substr(m_User->Name.find(" "));
    }
    
    m_FirstName = m_User->Name;
    
    m_Email = m_User->Email;
    
    InitRenderElementsOnResize();
}

void SettingsScreen::HandleOverview(std::shared_ptr<Core::Entity> e)
{
    m_SwitchScreens(m_Screens->OverviewScreen);
}

void SettingsScreen::InitRenderElements()
{
    SideBar();
    SettingsPanel();
    PersonalInformationPanel();
}

void SettingsScreen::SideBar()
{
     std::shared_ptr<Core::UI::ButtonMaterial> p_SettingsButtonMaterial = std::make_shared<Core::UI::ButtonMaterial>();
     p_SettingsButtonMaterial->Color = {0.0f, 0.46f, 0.98f, 1.0f};
     p_SettingsButtonMaterial->Roundness = 0.25f;
     p_SettingsButtonMaterial->TextSize = 22;
     p_SettingsButtonMaterial->Scene = m_Scene;
 
     std::shared_ptr<Core::UI::ButtonMaterial> p_UnselectedButtonMaterial = std::make_shared<Core::UI::ButtonMaterial>();
     p_UnselectedButtonMaterial->Color = {1.0f, 1.0f, 1.0f, 1.0f};
     p_UnselectedButtonMaterial->Roundness = 0.25f;
     p_UnselectedButtonMaterial->TextColor = {0.7f, 0.7f, 0.7f, 1.0f};
     p_UnselectedButtonMaterial->TextSize = 22;
     p_UnselectedButtonMaterial->Scene = m_Scene;
     
     Core::UI::Text("Menu", {40, 120}, {0.42, 0.42, 0.44, 1.0}, 20, "regualar", m_Scene);
 
     Core::UI::Button("Overview", {35, 157}, {180, 45}, p_UnselectedButtonMaterial, HandleOverview, "assets/icons/home-icon.png");
     
     Core::UI::Text("Account", {40, 271}, {0.42, 0.42, 0.44, 1.0}, 20, "regualar", m_Scene);
     
     Core::UI::Button("Settings", {35, 316}, {180, 45}, p_UnselectedButtonMaterial, settingCallback, "assets/icons/settings-icon.png");
}

void SettingsScreen::SettingsPanel()
{
     std::shared_ptr<Core::UI::ButtonMaterial> p_PersonalInformationMaterial = std::make_shared<Core::UI::ButtonMaterial>();
     p_PersonalInformationMaterial->Color = {0.0f, 0.46f, 0.98f, 1.0f};
     p_PersonalInformationMaterial->Roundness = 0.2f;
     p_PersonalInformationMaterial->TextSize = 18;
     p_PersonalInformationMaterial->Scene = m_Scene;
    
     Core::UI::Text("Settings", {260, 120}, {0.0, 0.0, 0.0, 1.0}, 36, "regualar", m_Scene);
     Core::UI::Button("Personal Information", {260, 180}, {190, 40}, p_PersonalInformationMaterial, settingCallback);
}

void SettingsScreen::PersonalInformationPanel()
{
    Core::UI::Text("Personal Information", {350 + MeasureText("Settings", 36), 120}, {0.0, 0.0, 0.0, 1.0}, 36, "regualar", m_Scene);
    Core::UI::Text("Profile", {350 + MeasureText("Settings", 36), 180}, {0.0, 0.0, 0.0, 1.0}, 22, "regualar", m_Scene);
    Core::UI::Text("This information will be displayed publicly so be careful what you share.", {350 + MeasureText("Settings", 36), 210}, {0.67, 0.69, 0.74, 1.0}, 16, "regualar", m_Scene);

    Core::UI::Text("First Name", {350 + MeasureText("Settings", 36), 250}, {0.4, 0.4, 0.4, 1.0}, 18, "regualar", m_Scene);
    
    Core::UI::Text(m_FirstName, {350 + MeasureText("Settings", 36), 285}, {0.1, 0.1, 0.1, 1.0}, 24, "regualar", m_Scene);

    Core::UI::Text("Last Name", {650 + MeasureText("Settings", 36), 250}, {0.4, 0.4, 0.4, 1.0}, 18, "regualar", m_Scene);
    Core::UI::Text(m_LastName, {650 + MeasureText("Settings", 36), 285}, {0.1, 0.1, 0.1, 1.0}, 24, "regualar", m_Scene);
    
    Core::UI::Text("Email", {350 + MeasureText("Settings", 36), 350}, {0.4, 0.4, 0.4, 1.0}, 18, "regualar", m_Scene);
    Core::UI::Text(m_Email, {350 + MeasureText("Settings", 36), 385}, {0.1, 0.1, 0.1, 1.0}, 24, "regualar", m_Scene);

    Core::UI::Text("Personal Information", {350 + MeasureText("Settings", 36), 450}, {0.0, 0.0, 0.0, 1.0}, 22, "regualar", m_Scene);
    Core::UI::Text("This information will be displayed publicly so be careful what you share.", {350 + MeasureText("Settings", 36), 480}, {0.67, 0.69, 0.74, 1.0}, 16, "regualar", m_Scene);

    Core::UI::Text("Country", {350 + MeasureText("Settings", 36), 530}, {0.4, 0.4, 0.4, 1.0}, 18, "regualar", m_Scene);
    Core::UI::Text("Bulgaria", {350 + MeasureText("Settings", 36), 560}, {0.1, 0.1, 0.1, 1.0}, 24, "regualar", m_Scene);
    
    Core::UI::Text("Language", {650 + MeasureText("Settings", 36), 530}, {0.4, 0.4, 0.4, 1.0}, 18, "regualar", m_Scene);
    Core::UI::Text("Bulgarian", {650 + MeasureText("Settings", 36), 560}, {0.1, 0.1, 0.1, 1.0}, 24, "regualar", m_Scene);
}

