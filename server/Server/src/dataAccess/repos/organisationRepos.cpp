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
    *DatabaseConnection::sql << "SELECT id, name, ownerId, code FROM organisations WHERE code = " << code, soci::into(org.id), soci::into(org.name), soci::into(org.ownerId), soci::into(org.code);

    return org;
}

void OrganisationRepository::DeleteOrganisation(int id){
    Organisation org;
    *DatabaseConnection::sql << "DELETE FROM organisations WHERE id=:id", soci::use(org.id);

}

std::vector<Organisation> OrganisationRepository::ReadOrganisations()
{
    std::vector<Organisation> orgs;
    Organisation org;
    soci::rowset<soci::row> rs = (DatabaseConnection::sql->prepare << "SELECT id, name, owner_id, code FROM organisations");
    for(soci::row& r : rs)
    {
        r >> org.id;
        r >> org.name;
        r >> org.ownerId;
        r >> org.code;
        orgs.push_back(org);
    }

    return orgs;
}
