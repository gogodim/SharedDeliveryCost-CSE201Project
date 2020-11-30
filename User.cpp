#include "User.h"

//Don't know what this line means
DBO_INSTANTIATE_TEMPLATES(User);

using namespace Wt::Dbo;

User::User() : isOrdered(0),
    amount(0)
{

}
