#include "options_view.hpp"
#include <QDebug>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "game/game_data.hpp"
#include "events/event_data.hpp"
#include "events/event_manager.hpp"

namespace boost_pt = boost::property_tree;

OptionsView::OptionsView(QObject *qroot, QObject *qparent)
    : QtView(qparent), qroot_(qroot), qoptions_(), actor_id_(-1),
      player_types_(), player_nums_(), selected_players_()
{
}

OptionsView::~OptionsView()
{
    qDebug() << "destroying OptionsView";
}

bool OptionsView::init()
{
    if (!load_players_data()) {
        return false;
    }

    if (!connect_options()) {
        return false;
    }

    QVariantList types;
    for (const auto &type : player_types_) {
        types << type.c_str();
    }
    QMetaObject::invokeMethod(qoptions_, "setPlayerTypes",
            Q_ARG(QVariant, QVariant::fromValue(types)));

    QVariantList nums;
    for (int num : player_nums_) {
        nums << num;
    }
    QMetaObject::invokeMethod(qoptions_, "setPlayerNums",
            Q_ARG(QVariant, QVariant::fromValue(nums)));

    if (!connect_button("buttonStartGame", SLOT(button_start_game_clicked()))) {
        return false;
    }
    if (!connect_button("buttonBackToMainMenu", SLOT(button_back_clicked()))) {
        return false;
    }

    return true;
}

void OptionsView::on_msg()
{
}

void OptionsView::on_update()
{
}

void OptionsView::attach(ActorId actor_id)
{
    actor_id_ = actor_id;
}

void OptionsView::button_start_game_clicked()
{
    qDebug() << "button_start_game_clicked";

    send_new_actors_data();

    auto event = std::make_shared<EventData_Game>();
    if (!EventManager::get()->queue_event(event)) {
        qDebug() << "failed to queue Game event";
    }
}

void OptionsView::button_back_clicked()
{
    qDebug() << "button_back_clicked";
    auto event = std::make_shared<EventData_MainMenu>();
    if (!EventManager::get()->queue_event(event)) {
        qDebug() << "failed to queue MainMenu event";
    }
}

void OptionsView::on_players_changed(QVariant player_list)
{
    QVariantList lst = player_list.toList();
    selected_players_.clear();
    for (QVariant ptype_str : lst) {
        PlayerType ptype = str_to_player_type.at(ptype_str.toString().toStdString());
        selected_players_.push_back(ptype);
    }
    qDebug() << "selected players:";
    for (auto ptype : selected_players_) {
        qDebug() << "\t" << player_type_to_str.at(ptype).c_str();
    }
}

QObject *OptionsView::find_object_by_name(const char *name) const
{
    return qroot_->findChild<QObject*>(name);
}

bool OptionsView::load_players_data()
{
    static const char *players_file = "../board/data/players.json";

    boost_pt::ptree pt;
    try {
        boost_pt::read_json(players_file, pt);
    }
    catch (boost_pt::ptree_error &e) {
        qDebug() << "failed to open file:" << e.what();
        return false;
    }

    boost::optional<boost_pt::ptree &> types = pt.get_child_optional("types");
    if (!types) {
        return false;
    }
    player_types_.clear();
    for (auto type : *types) {
        player_types_.push_back(type.second.get_value<std::string>());
    }

    boost::optional<boost_pt::ptree &> nums = pt.get_child_optional("nums");
    if (!nums) {
        return false;
    }
    player_nums_.clear();
    for (auto num : *nums) {
        player_nums_.push_back(num.second.get_value<int>());
    }

    return true;
}

bool OptionsView::connect_options()
{
    qoptions_ = find_object_by_name("options");
    if (qoptions_ == NULL) {
        return false;
    }
    QObject::connect(
            qoptions_, SIGNAL(playersChanged(QVariant)),
            this, SLOT(on_players_changed(QVariant))
    );
    return true;
}

void OptionsView::send_new_actors_data() const
{
    for (PlayerType ptype : selected_players_) {
        auto ev = std::make_shared<EventData_RequestNewActor>(ptype);
        EventManager::get()->queue_event(ev);
    }
}
