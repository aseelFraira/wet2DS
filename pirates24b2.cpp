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
    // TODO: Your code goes here
    if(fleetId <= 0){
        return StatusType::INVALID_INPUT;
    }
    if (m_fleets.m_table.find(fleetId)){
        return StatusType::FAILURE;
    }
    std::shared_ptr<Fleet> fleet = std::make_shared<Fleet>(fleetId);
    m_fleets.makeSet(fleet);
    return StatusType::SUCCESS;
}

StatusType oceans_t::add_pirate(int pirateId, int fleetId)
{
    if(pirateId <= 0 || fleetId <= 0){
        return StatusType::INVALID_INPUT;
    }

        std::shared_ptr<Fleet> fleet =  m_fleets.m_table.find(fleetId).m_data;

    if(!fleet || m_pirates.find(pirateId)){
        return StatusType::FAILURE;
    }
    std::shared_ptr<Pirate> pirate =  std::make_shared<Pirate>(pirateId);
    fleet->setPiratesNum(1);
    pirate->setArgument(fleet->getPiratesNum());
    m_pirates.insert(pirate);
    //TODO GET THE EXTRAS FOR THE ARGUMENT

    return StatusType::SUCCESS;
}

StatusType oceans_t::pay_pirate(int pirateId, int salary)
{
    if(pirateId <= 0 || salary <= 0){
        return StatusType::INVALID_INPUT;
    }
    std::shared_ptr<Pirate> pirate = m_pirates.find(pirateId);
    if(!pirate){
        return StatusType::FAILURE;
    }
    pirate->setSavings(salary);
	return StatusType::SUCCESS;
}

output_t<int> oceans_t::num_ships_for_fleet(int fleetId)
{
    if(fleetId <= 0){
        return StatusType::INVALID_INPUT;
    }
    std::shared_ptr<Fleet> fleet =  m_fleets.m_table.find(fleetId).m_data;
    if (!fleet){
        return StatusType::FAILURE;
    }

    return fleet->getShipsNum();
}

output_t<int> oceans_t::get_pirate_money(int pirateId)
{
    if(pirateId <= 0){
        return StatusType::INVALID_INPUT;
    }
    std::shared_ptr<Pirate> pirate = m_pirates.find(pirateId);
    if(!pirate){
        return StatusType::FAILURE;
    }
    return pirate->getSavings();
}

StatusType oceans_t::unite_fleets(int fleetId1, int fleetId2)
{
    if(fleetId1 <= 0|| fleetId2 <= 0 || fleetId2 == fleetId1){
        return StatusType::INVALID_INPUT;
    }
    std::shared_ptr<Fleet> fleet1 =  m_fleets.m_table.find(fleetId1).m_data;
    std::shared_ptr<Fleet> fleet2 =  m_fleets.m_table.find(fleetId2).m_data;
    if (!fleet1 || !fleet2){
        return StatusType::FAILURE;
    }
    m_fleets.unite(fleetId1,fleetId2);
    return StatusType::SUCCESS;
}

StatusType oceans_t::pirate_argument(int pirateId1, int pirateId2)
{
    if(pirateId1 <= 0|| pirateId2 <= 0|| pirateId2 == pirateId1){
        return StatusType::INVALID_INPUT;
    }
    std::shared_ptr<Pirate> pirate1 = m_pirates.find(pirateId1);
    std::shared_ptr<Pirate> pirate2 = m_pirates.find(pirateId2);

    if(!pirate1 || !pirate2){
        return StatusType::FAILURE;
    }
    if(pirate2->motherFleet.findDad().getID() != pirate1->motherFleet.findDad().getID()){
        return StatusType::FAILURE;
    }
    int argOne = pirate1->getArgument();//TODO THE GET ARGUMENT NEED TO INCLUDE THE EXTRAS
    int argTwo = pirate2->getArgument();
    if(argOne > argTwo){
        pirate1->setSavings(argTwo - argOne);
        pirate2->setSavings(argOne - argTwo);
    } else {
        pirate1->setSavings(argOne - argTwo);
        pirate2->setSavings(argTwo - argOne);
    }
    return StatusType::SUCCESS;
}
