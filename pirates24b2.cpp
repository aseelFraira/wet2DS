#include "pirates24b2.h"

oceans_t::oceans_t()
{
	// TODO: Your code goes here
}

oceans_t::~oceans_t()
{
	// TODO: Your code goes here
}


StatusType oceans_t::add_fleet(int fleetId)
{
    if(fleetId <= 0){
        return StatusType::INVALID_INPUT;
    }
    if (m_AllFleets.find(fleetId)){
        return StatusType::FAILURE;
    }
    std::shared_ptr<Fleet> fleet = std::make_shared<Fleet>(fleetId);
    m_fleets.makeSet(fleet);
    m_AllFleets.insert(fleet,fleetId);
    return StatusType::SUCCESS;
}

StatusType oceans_t::add_pirate(int pirateId, int fleetId)
{
    if(pirateId <= 0 || fleetId <= 0){
        return StatusType::INVALID_INPUT;
    }

    UFnode* fleetNode = m_fleets.find(fleetId);

    if(!fleetNode || m_pirates.find(pirateId)){
        return StatusType::FAILURE;
    }
    std::shared_ptr<Fleet> fleet =  fleetNode->m_fleet;
    std::shared_ptr<Pirate> pirate = std::make_shared<Pirate>(pirateId);

    fleet->setPiratesNum(1);
    pirate->setArgument(fleet->getPiratesNum() - fleetNode->getExtraPath());
    pirate->motherFleet = fleetNode;
    m_pirates.insert(pirate,pirateId);

    return StatusType::SUCCESS;
}

StatusType oceans_t::pay_pirate(int pirateId, int salary)
{
    if(pirateId <= 0 || salary <= 0){
        return StatusType::INVALID_INPUT;
    }
    NodeList<std::shared_ptr<Pirate>>* pirateNode = m_pirates.find(pirateId);
    if(!pirateNode){
        return StatusType::FAILURE;
    }
    std::shared_ptr<Pirate> pirate = pirateNode->m_data;
    pirate->setSavings(salary);
	return StatusType::SUCCESS;
}

output_t<int> oceans_t::num_ships_for_fleet(int fleetId)
{
    if(fleetId <= 0){
        return StatusType::INVALID_INPUT;
    }

    UFnode* fleetNode = m_fleets.find(fleetId);
    if(!fleetNode){
        return StatusType::FAILURE;
    }

    std::shared_ptr<Fleet> fleet = fleetNode->m_fleet;
    return fleet->getShipsNum();
}

output_t<int> oceans_t::get_pirate_money(int pirateId)
{
    if(pirateId <= 0){
        return StatusType::INVALID_INPUT;
    }
    NodeList<std::shared_ptr<Pirate>>* pirateNode = m_pirates.find(pirateId);
    if(!pirateNode){
        return StatusType::FAILURE;
    }
    std::shared_ptr<Pirate> pirate = pirateNode->m_data;

    return pirate->getSavings();
}

StatusType oceans_t::unite_fleets(int fleetId1, int fleetId2)
{
    if(fleetId1 <= 0|| fleetId2 <= 0 || fleetId2 == fleetId1){
        return StatusType::INVALID_INPUT;
    }
    NodeList<std::shared_ptr<Fleet>>* fleet1 =  m_fleets.m_table->find(fleetId1);
    NodeList<std::shared_ptr<Fleet>>* fleet2 =  m_fleets.m_table->find(fleetId2);

    if (!fleet1 || !fleet2 || fleet1->m_data->getPiratesNum() == 0 || fleet2->m_data->getPiratesNum() == 0){
        return StatusType::FAILURE;
    }

    m_fleets.unite(fleetId1, fleetId2);
    return StatusType::SUCCESS;
}

StatusType oceans_t::pirate_argument(int pirateId1, int pirateId2)
{
    if(pirateId1 <= 0|| pirateId2 <= 0|| pirateId2 == pirateId1){
        return StatusType::INVALID_INPUT;
    }
    NodeList<std::shared_ptr<Pirate>>* pirateNode1 = m_pirates.find(pirateId1);
    NodeList<std::shared_ptr<Pirate>>* pirateNode2 = m_pirates.find(pirateId2);

    if(!pirateNode1 || !pirateNode2){
        return StatusType::FAILURE;
    }
    std::shared_ptr<Pirate> pirate1 = pirateNode1->m_data;
    std::shared_ptr<Pirate> pirate2 = pirateNode2->m_data;

    if(pirate2->motherFleet->findDad()->m_key != pirate1->motherFleet->findDad()->m_key){
        return StatusType::FAILURE;
    }

    int argOne = pirate1->getArgument();
    int argTwo = pirate2->getArgument();
    if(argOne > argTwo){
        pirate1->setSavings(argTwo - argOne);
        pirate2->setSavings(argOne - argTwo);
    } else {
        pirate1->setSavings(argTwo - argOne);
        pirate2->setSavings(argOne - argTwo);
    }
    return StatusType::SUCCESS;
}
