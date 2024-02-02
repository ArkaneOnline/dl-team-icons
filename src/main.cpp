#include <Geode/utils/web.hpp>
#include <Geode/Geode.hpp>
#include <Geode/modify/ProfilePage.hpp>
#include <Geode/binding/ProfilePage.hpp>
#include <Geode/Bindings.hpp>
#include <Geode/loader/Loader.hpp>
#include <algorithm>
#include <cctype>
#include <set>
#include <iostream>

using namespace geode::prelude;

class buttonfunctionthing : public CCLayer {
public:
    void onButtonClick(CCObject* sender) {
        FLAlertLayer::create(
            "About",
            "This badge is given to <cp>members of the Demon List team</c>.",
            "OK"
        )->show();
    }
};

class $modify(ProfilePage) {
    bool m_hasBeenOpened = false;

    bool init(int p0, bool p1) {
        if (!ProfilePage::init(p0, p1)) return false;

        // URL of the raw text file on GitHub
        std::string githubFileUrl = "https://raw.githubusercontent.com/ArkaneOnline/ArkaneOnline/master/dl-team.txt";

        // Download the content of the text file using Geode's web request
        auto res = web::fetch(githubFileUrl);
        if (!res) {
            std::cerr << "Failed to fetch file from GitHub." << std::endl;
            return false;
        }

        // Get the content from the response
        std::string fileContent = res.value();

        // Parse the content and populate the set
        std::set<int> demonlistMembers;
        std::istringstream iss(fileContent);
        int contributorId;

        while (iss >> contributorId) {
            demonlistMembers.insert(contributorId);
        }

        m_mainLayer->removeChildByID("my-stuff-hint");
        auto mainMenu = static_cast<cocos2d::CCLayer*>(this->getChildByIDRecursive("main-menu"));
        auto spr = CCSprite::create("demonlist.png"_spr);
        auto btn = CCMenuItemSpriteExtra::create(
            spr, this, menu_selector(buttonfunctionthing::onButtonClick)
        );
        auto contentSize = mainMenu->getContentSize();

		auto posX = m_usernameLabel->getPositionX();
        auto posY = m_usernameLabel->getPositionY();

		std::string username = m_usernameLabel->getString();

        btn->setPosition(15, -50);
        btn->setZOrder(26);
        btn->setID("demonlist-badge");
        mainMenu->addChild(btn);
        btn->setVisible(false);

        if (demonlistMembers.count(p0) > 0) {
            btn->setVisible(true);
        }
        else {
            // how many times do we have to tell you this old man
        }

        

        return true;
    }
};
