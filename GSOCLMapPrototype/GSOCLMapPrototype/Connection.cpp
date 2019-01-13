#include "Connection.h"

void to_json(nlohmann::json& j, const Connection& c)
{
	j = nlohmann::json{ {"dest_node", c.dest_node} };
}
void from_json(const nlohmann::json& j, Connection& c)
{

}
