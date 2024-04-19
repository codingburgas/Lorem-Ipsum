#include "organisationHeader.hpp"

OrganisationRepository::OrganisationRepository() {};

Organisation OrganisationRepository::CreateOrganisation(OrganisationInput input)
{
    *DatabaseConnection::sql << "SELECT * FROM organisations WHERE name = :name", soci::use(input.name);

    if(DatabaseConnection::sql->got_data())
    {
        throw std::invalid_argument("Name already exist");
    }
    
    Organisation org;
    org.name = input.name;
    org.code = input.code;
    org.ownerId = input.ownerId;

    *DatabaseConnection::sql << "INSERT INTO organisations(name, code, owner_id) VALUES(:name, :code, :ownerId)",
        soci::use(org.name),
        soci::use(org.code),
        soci::use(org.ownerId);

    *DatabaseConnection::sql << "SELECT id FROM organisations WHERE code = " << "\'" << org.code << "\'", soci::into(org.id);

    *DatabaseConnection::sql << "INSERT INTO organisations_users(organisation_id, user_id, role) VALUES(:organisationId, :userId, 'owner')",
        soci::use(org.id),
        soci::use(org.ownerId);

    return org;
}

Organisation OrganisationRepository::ReadOrganisation(int id)
{
    Organisation org;
    *DatabaseConnection::sql << "SELECT id, name, owner_id, code FROM organisations WHERE id = " << id, soci::into(org.id), soci::into(org.name), soci::into(org.ownerId), soci::into(org.code);

    return org;
}

Organisation OrganisationRepository::ReadOrganisation(std::string name)
{
    Organisation org;
    *DatabaseConnection::sql << "SELECT id, name, ownerId, code FROM organisations WHERE name = " << name, soci::into(org.id), soci::into(org.name), soci::into(org.ownerId), soci::into(org.code);

    return org;
}

Organisation OrganisationRepository::ReadOrganisationByCode(std::string code)
{
    Organisation org;
    *DatabaseConnection::sql << "SELECT id, name, owner_id, code FROM organisations WHERE code = " << "\'" << code << "\'", soci::into(org.id), soci::into(org.name), soci::into(org.ownerId), soci::into(org.code);

    return org;
}

void OrganisationRepository::DeleteOrganisation(int id){
    Organisation org;
    *DatabaseConnection::sql << "DELETE FROM organisations WHERE id=:id", soci::use(org.id);

}

std::vector<Organisation> OrganisationRepository::ReadOrganisations(uint32_t userId)
{

    std::vector<Organisation> organisations;
    Organisation org;
    soci::rowset<soci::row> rs = (DatabaseConnection::sql->prepare << "SELECT o.id, o.name, o.owner_id, o.code FROM organisations o JOIN organisations_users ou ON o.id = ou.organisation_id WHERE ou.user_id = :userId", soci::use(userId));

    for (soci::rowset<soci::row>::const_iterator it = rs.begin(); it != rs.end(); ++it)
    {
        soci::row const &row = *it;
        org.id = row.get<int>(0);
        org.name = row.get<std::string>(1);
        org.ownerId = row.get<int>(2);
        org.code = row.get<std::string>(3);
        organisations.push_back(org);
    }

    return organisations;
}

void OrganisationRepository::AddUserToOrganisation(uint32_t userId, uint32_t orgId)
{
    *DatabaseConnection::sql << "INSERT INTO organisations_users(organisation_id, user_id, role) VALUES(:organisationId, :userId, 'member')",
        soci::use(orgId),
        soci::use(userId);
}
