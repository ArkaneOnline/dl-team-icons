#include <Geode/Geode.hpp>
#include <Geode/modify/ProfilePage.hpp>
#include <Geode/utils/web.hpp>
#include <cctype> // Include for std::tolower

using namespace geode::prelude;
bool downloaded = false;
std::set<std::string> demonlistMembers;

class $modify(ProfilePage) {

CCSprite * icon;

    void setupPageInfo(gd::string name, char const* chars) {
        ProfilePage::setupPageInfo(name,chars);

        auto director = CCDirector::sharedDirector();
        auto size = director->getWinSize();

        if (!downloaded) {
            auto res = web::fetch("https://raw.githubusercontent.com/ArkaneOnline/dl-team-icons/main/dl-team.txt");
            if (!res) {
                log::info("Failed to fetch file from GitHub.");
            }
            auto data = res.value();
        
            std::istringstream iss(data);
            std::string temp_string;
            log::info("Downloaded Demon List team member list");

            while (std::getline(iss, temp_string)) {
                demonlistMembers.insert(temp_string);
            }
            downloaded = true;
        }

        std::string player_name = m_usernameLabel->getString();

        for (const auto& names : demonlistMembers) {
            std::string lowercase_player_name = player_name;
            std::transform(lowercase_player_name.begin(), lowercase_player_name.end(), lowercase_player_name.begin(), ::tolower);

            std::string lowercase_names = names;
            std::transform(lowercase_names.begin(), lowercase_names.end(), lowercase_names.begin(), ::tolower);

            if (lowercase_names == lowercase_player_name) {
                log::info("DL Member Found! {}", names);
                CCNode* first_letter = reinterpret_cast<CCNode*>(m_usernameLabel->getChildren()->objectAtIndex(0));
                m_fields->icon = CCSprite::create("demonlist.png"_spr);
                m_fields->icon->setScale(m_usernameLabel->getScale() - 0.1);
                m_fields->icon->setPosition(first_letter->convertToWorldSpace(getPosition()));
                m_fields->icon->setPosition({m_fields->icon->getPositionX() - 13.f, m_fields->icon->getPositionY() + 11.f});
                addChild(m_fields->icon);
            }
        }
    } 
};
