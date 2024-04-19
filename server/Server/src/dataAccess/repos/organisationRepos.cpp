#include "organisationHeader.hpp"

OrganisationRepository::OrganisationRepository() {};

Organisation OrganisationRepository::CreateOrganisation(OrganisationInput input)
{
    *DatabaseConnection::sql << "SELECT * FROM organisations WHERE name = :name", soci::use(input.name);

    if(DatabaseConnection::sql->got_data())
    {
        throw std::invalid_argument("Name already exist");
    }
    User user;
    

    Organisation org;
    org.name = input.name;
    org.ownerId = user.id;
    org.code = input.code;

    *DatabaseConnection::sql << "INSERT INTO organisations(name) VALUES(:name, :code)",
        soci::use(input.name),
        soci::use(input.code);
        soci::use(input.ownerId);

    return org;
}

Organisation OrganisationRepository::ReadOrganisation(int id)
{
    Organisation org;
    *DatabaseConnection::sql << "SELECT id, name, ownerId, code FROM organisations WHERE id = " << id, soci::into(org.id), soci::into(org.name), soci::into(org.ownerId), soci::into(org.code);

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
